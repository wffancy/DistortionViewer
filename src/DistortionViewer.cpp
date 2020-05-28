#include "DistortionViewer.h"
#include <osg/Scissor>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osgGA/TrackballManipulator>

DistortionViewer::DistortionViewer(ViewerGraphics* vg) : _viewerGraphics(vg), _type(CameraModel::Normal), _widgetWidth(800), _widgetHeight(600)
{
	initViewer();
	initRTTCamera();
	initHudCamera();
}

void DistortionViewer::initViewer()
{
	_viewer = new osgViewer::Viewer();
	_viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);

	auto camera = _viewer->getCamera();
	camera->setGraphicsContext(_viewerGraphics);

	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	camera->setClearColor(osg::Vec4(0.9f, 0.9f, 1.0f, 1.0f));
	camera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
	camera->setNearFarRatio(0.000001);
	camera->setDrawBuffer(GL_BACK);
	camera->setReadBuffer(GL_BACK);
	camera->setProjectionMatrixAsPerspective(60.0f, static_cast<double>(_widgetWidth)/_widgetHeight, 0.1f, 1000.0f);
	camera->setViewport(0, 0, _widgetWidth, _widgetHeight);

	_viewer->addEventHandler(new osgViewer::StatsHandler);
	_viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	_viewer->addEventHandler(new osgGA::StateSetManipulator(_viewer->getCamera()->getOrCreateStateSet()));
	_viewer->setCameraManipulator(new osgGA::TrackballManipulator());

	_sceneRoot = new osg::Group();
	_modelRoot = new osg::Group();
	_modelRoot->addChild(osgDB::readNodeFile("Resources/cow.osg"));

	_sceneRoot->addChild(_modelRoot);

	_viewer->setSceneData(_sceneRoot);
}

void DistortionViewer::initRTTCamera()
{
	_rttTexture = new osg::Texture2D;
	_rttTexture->setInternalFormat(GL_RGBA);
	_rttTexture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
	_rttTexture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
	_rttTexture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::CLAMP_TO_BORDER);
	_rttTexture->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::CLAMP_TO_BORDER);

	_rttCamera = new osg::Camera;
	_rttCamera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
	_rttCamera->setRenderOrder(osg::Camera::PRE_RENDER);
	_rttCamera->setViewport(0, 0, _widgetWidth, _widgetHeight);
	//_rttCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//添加会导致重复绘制
	_rttCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
	_rttCamera->attach(osg::Camera::COLOR_BUFFER, _rttTexture, 0, 0, true, 8, 8);

	_rttCamera->addChild(_modelRoot);

	_sceneRoot->addChild(_rttCamera);
}

void DistortionViewer::initHudCamera()
{
	_hudCamera = new osg::Camera;
	_hudCamera->setViewMatrix(osg::Matrix::identity());
	_hudCamera->setRenderOrder(osg::Camera::POST_RENDER);
	_hudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
	_hudCamera->setAllowEventFocus(false);
	_hudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	_hudCamera->setProjectionMatrixAsOrtho2D(0, _widgetWidth, 0, _widgetHeight);
	_hudCamera->setViewport(0, 0, _widgetWidth, _widgetHeight);

	osg::ref_ptr<osg::Geode> gnode = createHudQuad(_widgetWidth, _widgetHeight);

	_hudCamera->addChild(gnode);
	_sceneRoot->addChild(_hudCamera);
	EnlargeView();	//因镜头畸变原因引入视野扩大
}


void DistortionViewer::scissor(osg::Group* node, int x, int y, int width, int height)
{
	osg::ref_ptr<osg::Scissor> cc = new osg::Scissor();
	cc->setScissor(x, y, width, height);
	node->getOrCreateStateSet()->setAttributeAndModes(cc, osg::StateAttribute::ON);
}


osg::Geode* DistortionViewer::createHudQuad(int width, int height)
{
	osg::ref_ptr<osg::Geode> gnode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> quad = osg::createTexturedQuadGeometry(osg::Vec3(0, 0, 0), osg::Vec3(width, 0, 0), osg::Vec3(0, height, 0), 1, 1);
	gnode->addDrawable(quad);
	gnode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	gnode->getOrCreateStateSet()->setTextureAttributeAndModes(0, _rttTexture, osg::StateAttribute::ON);
	osg::ref_ptr<osg::TexEnv> texEnv = new osg::TexEnv;
	texEnv->setMode(osg::TexEnv::Mode::DECAL);
	texEnv->setColor(osg::Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
	gnode->getOrCreateStateSet()->setTextureAttributeAndModes(0, texEnv, osg::StateAttribute::ON);
	addHudShader(gnode);
	return gnode.release();
}


void DistortionViewer::resizeCamera(int width, int height)
{
	_widgetWidth = width;
	_widgetHeight = height;

	_rttCamera->resize(width, height);
	_hudCamera->resize(width, height);

	addHudShader(dynamic_cast<osg::Geode*>(_hudCamera->getChild(0)));
}


void DistortionViewer::changeAspectRatio(int num)
{
	double temp = 1.0;
	temp += num / 100.0;
	int cameraViewWidth = _widgetWidth, cameraViewHeight = _widgetHeight;
	if (static_cast<double>(cameraViewWidth) / cameraViewHeight > temp) {
		cameraViewWidth = cameraViewHeight * temp;
	}
	else {
		cameraViewHeight = cameraViewWidth / temp;
	}
	int cameraViewLeftSpaing = (_widgetWidth - cameraViewWidth) / 2;
	int cameraViewHeightSpacing = (_widgetHeight - cameraViewHeight) / 2;

	double temp_fov, temp_ar, temp_near, temp_far;
	_viewer->getCamera()->getProjectionMatrixAsPerspective(temp_fov, temp_ar, temp_near, temp_far);

	_viewer->getCamera()->setProjectionMatrixAsPerspective(temp_fov, temp, temp_near, temp_far);
	_viewer->getCamera()->setViewport(cameraViewLeftSpaing, cameraViewHeightSpacing, cameraViewWidth, cameraViewHeight);

	//_hudCamera->removeChild(static_cast<unsigned int>(0));
	//_hudCamera->addChild(createHudQuad(cameraViewWidth, cameraViewHeight));
	//_hudCamera->setProjectionMatrixAsOrtho2D(0, cameraViewWidth, 0, cameraViewHeight);
	_hudCamera->setViewport(cameraViewLeftSpaing, cameraViewHeightSpacing, cameraViewWidth, cameraViewHeight);

	addHudShader(dynamic_cast<osg::Geode*>(_hudCamera->getChild(0)));
}


void DistortionViewer::changeCameraType(int type)
{
	_type = static_cast<CameraModel::CameraType>(type);
	addHudShader(dynamic_cast<osg::Geode*>(_hudCamera->getChild(0)));
}


void DistortionViewer::changeCameraFOV(int fov)
{
	double temp_fov, temp_ar, temp_near, temp_far;
	_viewer->getCamera()->getProjectionMatrixAsPerspective(temp_fov, temp_ar, temp_near, temp_far);
	_viewer->getCamera()->setProjectionMatrixAsPerspective(static_cast<double>(fov), temp_ar, temp_near, temp_far);
	addHudShader(dynamic_cast<osg::Geode*>(_hudCamera->getChild(0)));
}

void DistortionViewer::addHudShader(osg::Geode* gnode)
{
	_cameraModel = new CameraModel(_type);
	double fovy, aspectRatio, zNear, zFar;
	_viewer->getCamera()->getProjectionMatrixAsPerspective(fovy, aspectRatio, zNear, zFar);
	switch (_type) {
	case CameraModel::Normal:
		_cameraModel->setGeode(gnode);
		break;
	case CameraModel::Fisheye:
		_cameraModel->setFOV(fovy);
		_cameraModel->setAspectRatio(aspectRatio);
		_cameraModel->setGeode(gnode);
		break;
	case CameraModel::Panorama:
		_cameraModel->setFOV(fovy);
		_cameraModel->setAspectRatio(aspectRatio);
		_cameraModel->setGeode(gnode);
		break;
	default:
		if (_barrelModel.size() == 0)
			_cameraModel = new CameraModel(_type);
		else
			_cameraModel = new CameraModel(_type, _barrelModel);
		_cameraModel->setAspectRatio(aspectRatio);
		_cameraModel->setGeode(gnode);
	}
}

void DistortionViewer::EnlargeView()
{
	double fovy, aspectRatio, zNear, zFar, fov_after;
	float scale = 1.0;
	_viewer->getCamera()->getProjectionMatrixAsPerspective(fovy, aspectRatio, zNear, zFar);
	switch (_type) {
	case CameraModel::Barrel:
	case CameraModel::Fisheye:
		scale = _cameraModel->enlargeRatio();
		fov_after = atan(scale*tan(fovy));
		_viewer->getCamera()->setProjectionMatrixAsPerspective(fov_after, aspectRatio, zNear, zFar);
		break;
	default:break;
	}
}

