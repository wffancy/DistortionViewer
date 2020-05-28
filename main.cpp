#include <QApplication>
#include "MainWindow.h"
#ifdef _DEBUG
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgUtild.lib")
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"OpenThreadsd.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgTextd.lib")
#pragma comment(lib,"osgFXd.lib")
#pragma comment(lib,"osgShadowd.lib")
#pragma comment(lib,"osgManipulatord.lib")
#pragma comment(lib,"osgAnimationd.lib")
#pragma comment(lib,"osgPresentationd.lib")
#pragma comment(lib,"osgParticled.lib")
//#pragma comment(lib,"osgOceand.lib")
// #pragma comment(lib,"osgQtd.lib")
//#pragma comment(lib,"osgwToolsd.lib")
#else
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgUtil.lib")
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"OpenThreads.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgText.lib")
#pragma comment(lib,"osgFX.lib")
#pragma comment(lib,"osgShadow.lib")
#pragma comment(lib,"osgManipulator.lib")
#pragma comment(lib,"osgAnimation.lib")
#pragma comment(lib,"osgParticle.lib")
//#pragma comment(lib,"osgOcean.lib")
// #pragma comment(lib,"osgQt.lib")
//#pragma comment(lib,"osgwTools.lib")
#endif // _DEBUG
int main(int argc, char **argv) {
	osg::setNotifyLevel(osg::ALWAYS);

	QApplication a(argc, argv);
	MainWindow w;
	//w.getViewer()->setBarrelDisParams({1.0f,0.0f,0.2f,0.0f,1.0f});
	w.show();
	return a.exec();
}
