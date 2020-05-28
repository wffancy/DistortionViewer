#pragma once
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

#include <osg/Geode>

#define EDGE (0.5)
class CameraModel : public osg::Referenced
{
public:
	enum CameraType {
		Normal,
		Barrel,
		Fisheye,
		Panorama
	};
	CameraModel(CameraType type = Normal, std::vector<float> model = { 1.0f, 0.0f, 0.5f, 0.0f, 10.0f }
		, float fovy = 60.0, float aspect_ratio = 1.0);
	~CameraModel() {}

	inline void setFOV(float fovy) { _fovy = fovy; }
	inline void setAspectRatio(float aspect_ratio) { _aspect_ratio = aspect_ratio; }
	void setGeode(osg::Geode* gnode);
	void setBarrelDisParams(std::vector<float> model);
	void computeScale();
	float enlargeRatio();

protected:
	int BuildLrInverse(float& l1r, float width, int Na, std::vector<float> a);
	double PolynomialEvaluation(std::vector<float> a, int Na, float x);
	void addNormalUniform(osg::Geode* gnode);
	void addBarrelUniform(osg::Geode* gnode);
	void addFisheyeUniform(osg::Geode* gnode);
	void addPanoramaUniform(osg::Geode* gnode);

private:
	CameraType _type;
	int _lenOfModel;
	std::vector<float> _barrelModel;
	float _fovy, _aspect_ratio;
	float _scale = 1.0;
};