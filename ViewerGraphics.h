#pragma once
#include <QWidget>
#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QMutex>
#include <QEvent>
#include <QQueue>
#include <QSet>
#include <QInputEvent>

#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>

// forward declarations
class ViewerGraphics;
class GLCanvas;

class GLCanvas : public QGLWidget
{
	typedef QGLWidget inherited;

	Q_OBJECT
public:

	GLCanvas(QWidget* parent = NULL, const QGLWidget* shareWidget = NULL, Qt::WindowFlags f = 0, bool forwardKeyEvents = false);
	GLCanvas(QGLContext* context, QWidget* parent = NULL, const QGLWidget* shareWidget = NULL, Qt::WindowFlags f = 0, bool forwardKeyEvents = false);
	GLCanvas(const QGLFormat& format, QWidget* parent = NULL, const QGLWidget* shareWidget = NULL, Qt::WindowFlags f = 0, bool forwardKeyEvents = false);
	virtual ~GLCanvas();

	inline void setGraphicsWindow(ViewerGraphics* gw) { _gw = gw; }
	inline ViewerGraphics* getGraphicsWindow() { return _gw; }
	inline const ViewerGraphics* getGraphicsWindow() const { return _gw; }
	void setKeyboardModifiers(QInputEvent* event);

	inline bool getTouchEventsEnabled() const { return _touchEventsEnabled; }
	void setTouchEventsEnabled(bool e) { _touchEventsEnabled = e; }

	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);

	bool isEntered() const;
protected:

	int getNumDeferredEvents()
	{
		QMutexLocker lock(&_deferredEventQueueMutex);
		return _deferredEventQueue.count();
	}
	void enqueueDeferredEvent(QEvent::Type eventType, QEvent::Type removeEventType = QEvent::None)
	{
		QMutexLocker lock(&_deferredEventQueueMutex);

		if (removeEventType != QEvent::None)
		{
			if (_deferredEventQueue.removeOne(removeEventType))
				_eventCompressor.remove(eventType);
		}

		if (_eventCompressor.find(eventType) == _eventCompressor.end())
		{
			_deferredEventQueue.enqueue(eventType);
			_eventCompressor.insert(eventType);
		}
	}
	void processDeferredEvents();
	virtual void resizeEvent(QResizeEvent* event);
	virtual void moveEvent(QMoveEvent* event);
	virtual void glDraw();
	virtual bool event(QEvent* event);
signals:
	void sizeChanged(int width,int height);
protected:
	friend class ViewerGraphics;
	ViewerGraphics* _gw;

	QMutex _deferredEventQueueMutex;
	QQueue<QEvent::Type> _deferredEventQueue;
	QSet<QEvent::Type> _eventCompressor;
	bool _touchEventsEnabled;
	qreal _devicePixelRatio;
	bool	_enterFlag;
};


class ViewerGraphics : public osgViewer::GraphicsWindow
{
	friend class GLCanvas;
public:
	ViewerGraphics(osg::GraphicsContext::Traits *traits, QWidget* parent = NULL, const QGLWidget* shareWidget = NULL, Qt::WindowFlags f = 0);

	static ViewerGraphics* CreateViewerGraphics(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false);

	virtual ~ViewerGraphics();

	inline GLCanvas* getGLWidget() { return _widget; }
	inline const GLCanvas* getGLWidget() const { return _widget; }

	/// deprecated
	inline GLCanvas* getGraphWidget() { return _widget; }
	/// deprecated
	inline const GLCanvas* getGraphWidget() const { return _widget; }

	struct WindowData : public osg::Referenced
	{
		WindowData(GLCanvas* widget = NULL, QWidget* parent = NULL) : _widget(widget), _parent(parent) {}
		GLCanvas* _widget;
		QWidget* _parent;
	};

	bool init(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f);

	static QGLFormat traits2qglFormat(const osg::GraphicsContext::Traits* traits);
	static void qglFormat2traits(const QGLFormat& format, osg::GraphicsContext::Traits* traits);
	static osg::GraphicsContext::Traits* createTraits(const QGLWidget* widget);

	virtual bool setWindowRectangleImplementation(int x, int y, int width, int height);
	virtual void getWindowRectangle(int& x, int& y, int& width, int& height);
	virtual bool setWindowDecorationImplementation(bool windowDecoration);
	virtual bool getWindowDecoration() const;
	virtual void grabFocus();
	virtual void grabFocusIfPointerInWindow();
	virtual void raiseWindow();
	virtual void setWindowName(const std::string& name);
	virtual std::string getWindowName();
	virtual void useCursor(bool cursorOn);
	virtual void setCursor(MouseCursor cursor);
	inline bool getTouchEventsEnabled() const { return _widget->getTouchEventsEnabled(); }
	virtual void setTouchEventsEnabled(bool e) { _widget->setTouchEventsEnabled(e); }


	virtual bool valid() const;
	virtual bool realizeImplementation();
	virtual bool isRealizedImplementation() const;
	virtual void closeImplementation();
	virtual bool makeCurrentImplementation();
	virtual bool releaseContextImplementation();
	virtual void swapBuffersImplementation();
	virtual void runOperations();

	virtual void requestWarpPointer(float x, float y);
protected:

	friend class GLCanvas;
	GLCanvas* _widget;
	bool _ownsWidget;
	QCursor _currentCursor;
	bool _realized;
};