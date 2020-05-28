#include "CameraModel.h"

CameraModel::CameraModel(CameraType type, std::vector<float> model, float fovy, float aspect_ratio) :
	_type(type), _fovy(fovy), _aspect_ratio(aspect_ratio)
{
	_lenOfModel = model.size();
	_barrelModel = model;
}

void CameraModel::setGeode(osg::Geode* gnode)
{
	computeScale();
	switch (_type) {
	case Normal:
		addNormalUniform(gnode);   break;
	case Barrel:
		addBarrelUniform(gnode);   break;
	case Fisheye:
		addFisheyeUniform(gnode);  break;
	case Panorama:
		addPanoramaUniform(gnode); break;
	}
}

void CameraModel::setBarrelDisParams(std::vector<float> model)
{
	_barrelModel = model;
	_lenOfModel = _barrelModel.size();
}

void CameraModel::computeScale()
{
	float f = 1.0;
	float corner = EDGE * sqrt(1 + _aspect_ratio*_aspect_ratio);
	switch (_type) {
	case Barrel:
		if (BuildLrInverse(_scale, corner, _lenOfModel - 1, _barrelModel) == -1) {
			std::cout << "compute G(r) error!" << std::endl;
		}
		break;
	case Fisheye:
		f = 0.5 / tan(osg::DegreesToRadians(_fovy) / 2);
		_scale = f / corner * atan(corner / f);
		break;
	default:_scale = 1.0f;
	}
}

float CameraModel::enlargeRatio()
{
	float f,scale = 1.0;
	switch (_type) {
	case Barrel:
		scale = PolynomialEvaluation(_barrelModel, _lenOfModel - 1, 0.5);
		return scale;
	case Fisheye:
		f = 0.5 / tan(osg::DegreesToRadians(_fovy) / 2);
		scale = f / 0.5 * tan(0.5 / f);
		return scale;
	default:
		return 1.0;
	}
}

void CameraModel::addNormalUniform(osg::Geode* gnode)
{
	osg::Program* program = new osg::Program;
	osg::ref_ptr<osg::Shader> verFragObj = new osg::Shader(osg::Shader::VERTEX);
	osg::ref_ptr<osg::Shader> texFragObj = new osg::Shader(osg::Shader::FRAGMENT);
	verFragObj->loadShaderSourceFromFile("./shaders/shader.vert");
	texFragObj->loadShaderSourceFromFile("./shaders/normal.frag");
	program->addShader(verFragObj);
	program->addShader(texFragObj);
	gnode->getOrCreateStateSet()->setAttributeAndModes(program, osg::StateAttribute::ON);
}

void CameraModel::addBarrelUniform(osg::Geode* gnode)
{
	osg::Program* program = new osg::Program;

	osg::ref_ptr<osg::Uniform> factor = new osg::Uniform(osg::Uniform::FLOAT, "factor", _lenOfModel);
	for (int i = 0; i < _lenOfModel; i++)
	{
		factor->setElement(i, _barrelModel[i]);
	}
	gnode->getOrCreateStateSet()->addUniform(factor);
	gnode->getOrCreateStateSet()->addUniform(new osg::Uniform("scale", _scale));
	gnode->getOrCreateStateSet()->addUniform(new osg::Uniform("aspectRatio", _aspect_ratio));

	osg::ref_ptr<osg::Shader> verFragObj = new osg::Shader(osg::Shader::VERTEX);
	osg::ref_ptr<osg::Shader> texFragObj = new osg::Shader(osg::Shader::FRAGMENT);
	verFragObj->loadShaderSourceFromFile("./shaders/shader.vert");
	texFragObj->loadShaderSourceFromFile("./shaders/barrel.frag");
	program->addShader(verFragObj);
	program->addShader(texFragObj);
	gnode->getOrCreateStateSet()->setAttributeAndModes(program, osg::StateAttribute::ON);
}

void CameraModel::addFisheyeUniform(osg::Geode* gnode)
{
	osg::Program* program = new osg::Program;

	gnode->getOrCreateStateSet()->addUniform(new osg::Uniform("scale", _scale));
	gnode->getOrCreateStateSet()->addUniform(new osg::Uniform("fovy", _fovy));
	gnode->getOrCreateStateSet()->addUniform(new osg::Uniform("aspectRatio", _aspect_ratio));

	osg::ref_ptr<osg::Shader> verFragObj = new osg::Shader(osg::Shader::VERTEX);
	osg::ref_ptr<osg::Shader> texFragObj = new osg::Shader(osg::Shader::FRAGMENT);
	verFragObj->loadShaderSourceFromFile("./shaders/shader.vert");
	texFragObj->loadShaderSourceFromFile("./shaders/fisheye.frag");
	program->addShader(verFragObj);
	program->addShader(texFragObj);
	gnode->getOrCreateStateSet()->setAttributeAndModes(program, osg::StateAttribute::ON);
}

void CameraModel::addPanoramaUniform(osg::Geode* gnode)
{
	osg::Program* program = new osg::Program;

	gnode->getOrCreateStateSet()->addUniform(new osg::Uniform("scale", _scale));
	gnode->getOrCreateStateSet()->addUniform(new osg::Uniform("fovy", _fovy));
	gnode->getOrCreateStateSet()->addUniform(new osg::Uniform("aspectRatio", _aspect_ratio));

	osg::ref_ptr<osg::Shader> verFragObj = new osg::Shader(osg::Shader::VERTEX);
	osg::ref_ptr<osg::Shader> texFragObj = new osg::Shader(osg::Shader::FRAGMENT);
	verFragObj->loadShaderSourceFromFile("./shaders/shader.vert");
	texFragObj->loadShaderSourceFromFile("./shaders/panorama.frag");
	program->addShader(verFragObj);
	program->addShader(texFragObj);
	gnode->getOrCreateStateSet()->setAttributeAndModes(program, osg::StateAttribute::ON);
}

int CameraModel::BuildLrInverse(float& l1r, float width, int Na, std::vector<float> a) {
	if (a[Na] == 0.) return(-1);

	std::vector<float> b, b2;
	float root2, root = 1.;

	b.push_back(-width);

	// WE DEFINE THE POLYNOM WE NEED TO COMPUTE ROOTS AND THE DERIVATIVE */
	for (int i = 1; i < (Na + 2); i++) {
		b.push_back(a[i - 1]);
	}
	for (int i = 0; i < (Na + 1); i++) {
		b2.push_back(a[i] * (i + 1));       //derivative
	};

	//NEWTON-RAPHSON TO COMPUTE THE POLYNOMIAL ROOT
	for (int k = 0; k < 10000; k++) {
		double pol_eval = PolynomialEvaluation(b, Na + 1, root);
		double pol_der = PolynomialEvaluation(b2, Na, root);
		if (pol_der == 0.) break;
		root2 = root - pol_eval / pol_der;
		if (fabs(root - root2) < (fabs(root)*1e-8)) {
			root = root2;
			//printf("k=%d   ",k);
			break;
		}
		root = root2;
	}

	l1r = root / width;
	return 0;
}

double CameraModel::PolynomialEvaluation(std::vector<float> a,int Na,float x) {
	float sol = a[Na];
	int i;
	for (i = Na - 1; i > -1; i--) sol = sol*x + a[i];
	return(sol);
}