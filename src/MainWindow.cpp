#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <iostream>

#include <osg/BlendFunc>
#include <osgDB/ReadFile>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, _ui(new Ui::MainWindow)
{
	_ui->setupUi(this);

	initViewerGraphics();
	initComboBox();
	setupConnection();

	startTimer(1000 / 60.0);
}

MainWindow::~MainWindow()
{
	delete _ui;
	delete _dviewer;
}

void MainWindow::timerEvent(QTimerEvent *e)
{
	update();
	QMainWindow::timerEvent(e);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
	_dviewer->frame();
	QMainWindow::paintEvent(e);
}

void MainWindow::updateSliderValue(int num)
{
	double temp = 1.0;
	temp += num / 100.0;
	_ui->label_arNum->setText(QString::number(temp, 'f', 2));
}

void MainWindow::resizeWidget(int width, int height)
{
	double ar = static_cast<double>(width) / height;
	ar -= 1.0;
	ar *= 100;
	_ui->ARhorizontalSlider->setValue(static_cast<int>(ar));
}

void MainWindow::setupConnection()
{
	connect(_ui->ARhorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(updateSliderValue(int)));
	connect(_ui->ARhorizontalSlider, SIGNAL(valueChanged(int)), _dviewer, SLOT(changeAspectRatio(int)));
	connect(_ui->TypecomboBox, SIGNAL(currentIndexChanged(int)), _dviewer, SLOT(changeCameraType(int)));
	connect(_ui->FOVspinBox, SIGNAL(valueChanged(int)), _dviewer, SLOT(changeCameraFOV(int)));
}

void MainWindow::initComboBox()
{
	_ui->TypecomboBox->clear();
	_ui->TypecomboBox->addItem(QStringLiteral("normal"));
	_ui->TypecomboBox->addItem(QStringLiteral("barrel"));
	_ui->TypecomboBox->addItem(QStringLiteral("fisheye"));
	_ui->TypecomboBox->addItem(QStringLiteral("panorama"));
}

void MainWindow::initViewerGraphics()
{
	_viewerGraphics = ViewerGraphics::CreateViewerGraphics(0, 0, 800, 600);
	_viewerGraphics->setClearColor(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
	_viewerGraphics->setClearMask(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	_ui->verticalLayout_3->addWidget(_viewerGraphics->getGLWidget());
	_dviewer = new DistortionViewer(_viewerGraphics);
	connect(_viewerGraphics->getGLWidget(), SIGNAL(sizeChanged(int,int)), this, SLOT(resizeWidget(int,int)));
	connect(_viewerGraphics->getGLWidget(), SIGNAL(sizeChanged(int, int)), _dviewer, SLOT(resizeCamera(int, int)));
}