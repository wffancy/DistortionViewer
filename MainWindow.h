#pragma once
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>

#include "DistortionViewer.h"


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	void initViewerGraphics();
	inline DistortionViewer* getViewer() { return _dviewer; }

	virtual void timerEvent(QTimerEvent *e) override;
	virtual void paintEvent(QPaintEvent *e) override;

public slots:
	void updateSliderValue(int num);
	void resizeWidget(int width, int height);

private:
	void setupConnection();
	void initComboBox();

private:
	Ui::MainWindow* _ui;
	osg::ref_ptr<ViewerGraphics> _viewerGraphics;
	DistortionViewer* _dviewer;
};