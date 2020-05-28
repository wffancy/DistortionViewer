#pragma once
#include <stdio.h>
#include <vector>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Camera>
#include <osg/Texture2D>
#include <osg/TexEnv>
#include <QObject>

#include "ViewerGraphics.h"
#include "CameraModel.h"

class DistortionViewer : public QObject
{
	Q_OBJECT

public:
	DistortionViewer(ViewerGraphics* vg);
	~DistortionViewer() {}

	inline void frame() { _viewer->frame(); }
	void initViewer();
	void initRTTCamera();
	void initHudCamera();
	void scissor(osg::Group* node, int x, int y, int width, int height);
	osg::Geode* createHudQuad(int width, int height);
	inline void setBarrelDisParams(std::vector<float> model) { _barrelModel = model; }

public slots:
	void resizeCamera(int width, int height);
	void changeAspectRatio(int num);
	void changeCameraType(int type);
	void changeCameraFOV(int fov);

private:
	void addHudShader(osg::Geode* gnode);
	void EnlargeView();

private:
	int _widgetWidth, _widgetHeight;
	osg::ref_ptr<ViewerGraphics>	_viewerGraphics;
	osg::ref_ptr<osgViewer::Viewer> _viewer;
	osg::ref_ptr<osg::Camera>	_rttCamera;
	osg::ref_ptr<osg::Camera>	_hudCamera;
	osg::ref_ptr<osg::Texture2D>	_rttTexture;
	osg::ref_ptr<osg::Group>	_sceneRoot;
	osg::ref_ptr<osg::Group>	_modelRoot;

	CameraModel::CameraType		_type;
	osg::ref_ptr<CameraModel>	_cameraModel;
	std::vector<float>	_barrelModel;
};
