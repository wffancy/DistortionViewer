#include "ViewerGraphics.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGLFormat>

class QtKeyboardMap
{

public:
	QtKeyboardMap()
	{
		mKeyMap[Qt::Key_Escape] = osgGA::GUIEventAdapter::KEY_Escape;
		mKeyMap[Qt::Key_Delete] = osgGA::GUIEventAdapter::KEY_Delete;
		mKeyMap[Qt::Key_Home] = osgGA::GUIEventAdapter::KEY_Home;
		mKeyMap[Qt::Key_Enter] = osgGA::GUIEventAdapter::KEY_KP_Enter;
		mKeyMap[Qt::Key_End] = osgGA::GUIEventAdapter::KEY_End;
		mKeyMap[Qt::Key_Return] = osgGA::GUIEventAdapter::KEY_Return;
		mKeyMap[Qt::Key_PageUp] = osgGA::GUIEventAdapter::KEY_Page_Up;
		mKeyMap[Qt::Key_PageDown] = osgGA::GUIEventAdapter::KEY_Page_Down;
		mKeyMap[Qt::Key_Left] = osgGA::GUIEventAdapter::KEY_Left;
		mKeyMap[Qt::Key_Right] = osgGA::GUIEventAdapter::KEY_Right;
		mKeyMap[Qt::Key_Up] = osgGA::GUIEventAdapter::KEY_Up;
		mKeyMap[Qt::Key_Down] = osgGA::GUIEventAdapter::KEY_Down;
		mKeyMap[Qt::Key_Backspace] = osgGA::GUIEventAdapter::KEY_BackSpace;
		mKeyMap[Qt::Key_Tab] = osgGA::GUIEventAdapter::KEY_Tab;
		mKeyMap[Qt::Key_Space] = osgGA::GUIEventAdapter::KEY_Space;
		mKeyMap[Qt::Key_Delete] = osgGA::GUIEventAdapter::KEY_Delete;
		mKeyMap[Qt::Key_Alt] = osgGA::GUIEventAdapter::KEY_Alt_L;
		mKeyMap[Qt::Key_Shift] = osgGA::GUIEventAdapter::KEY_Shift_L;
		mKeyMap[Qt::Key_Control] = osgGA::GUIEventAdapter::KEY_Control_L;
		mKeyMap[Qt::Key_Meta] = osgGA::GUIEventAdapter::KEY_Meta_L;

		mKeyMap[Qt::Key_F1] = osgGA::GUIEventAdapter::KEY_F1;
		mKeyMap[Qt::Key_F2] = osgGA::GUIEventAdapter::KEY_F2;
		mKeyMap[Qt::Key_F3] = osgGA::GUIEventAdapter::KEY_F3;
		mKeyMap[Qt::Key_F4] = osgGA::GUIEventAdapter::KEY_F4;
		mKeyMap[Qt::Key_F5] = osgGA::GUIEventAdapter::KEY_F5;
		mKeyMap[Qt::Key_F6] = osgGA::GUIEventAdapter::KEY_F6;
		mKeyMap[Qt::Key_F7] = osgGA::GUIEventAdapter::KEY_F7;
		mKeyMap[Qt::Key_F8] = osgGA::GUIEventAdapter::KEY_F8;
		mKeyMap[Qt::Key_F9] = osgGA::GUIEventAdapter::KEY_F9;
		mKeyMap[Qt::Key_F10] = osgGA::GUIEventAdapter::KEY_F10;
		mKeyMap[Qt::Key_F11] = osgGA::GUIEventAdapter::KEY_F11;
		mKeyMap[Qt::Key_F12] = osgGA::GUIEventAdapter::KEY_F12;
		mKeyMap[Qt::Key_F13] = osgGA::GUIEventAdapter::KEY_F13;
		mKeyMap[Qt::Key_F14] = osgGA::GUIEventAdapter::KEY_F14;
		mKeyMap[Qt::Key_F15] = osgGA::GUIEventAdapter::KEY_F15;
		mKeyMap[Qt::Key_F16] = osgGA::GUIEventAdapter::KEY_F16;
		mKeyMap[Qt::Key_F17] = osgGA::GUIEventAdapter::KEY_F17;
		mKeyMap[Qt::Key_F18] = osgGA::GUIEventAdapter::KEY_F18;
		mKeyMap[Qt::Key_F19] = osgGA::GUIEventAdapter::KEY_F19;
		mKeyMap[Qt::Key_F20] = osgGA::GUIEventAdapter::KEY_F20;

		mKeyMap[Qt::Key_hyphen] = '-';
		mKeyMap[Qt::Key_Equal] = '=';

		mKeyMap[Qt::Key_division] = osgGA::GUIEventAdapter::KEY_KP_Divide;
		mKeyMap[Qt::Key_multiply] = osgGA::GUIEventAdapter::KEY_KP_Multiply;
		mKeyMap[Qt::Key_Minus] = '-';
		mKeyMap[Qt::Key_Plus] = '+';
		//mKeyMap[Qt::Key_H              ] = osgGA::GUIEventAdapter::KEY_KP_Home;
		//mKeyMap[Qt::Key_                    ] = osgGA::GUIEventAdapter::KEY_KP_Up;
		//mKeyMap[92                    ] = osgGA::GUIEventAdapter::KEY_KP_Page_Up;
		//mKeyMap[86                    ] = osgGA::GUIEventAdapter::KEY_KP_Left;
		//mKeyMap[87                    ] = osgGA::GUIEventAdapter::KEY_KP_Begin;
		//mKeyMap[88                    ] = osgGA::GUIEventAdapter::KEY_KP_Right;
		//mKeyMap[83                    ] = osgGA::GUIEventAdapter::KEY_KP_End;
		//mKeyMap[84                    ] = osgGA::GUIEventAdapter::KEY_KP_Down;
		//mKeyMap[85                    ] = osgGA::GUIEventAdapter::KEY_KP_Page_Down;
		mKeyMap[Qt::Key_Insert] = osgGA::GUIEventAdapter::KEY_KP_Insert;
		//mKeyMap[Qt::Key_Delete        ] = osgGA::GUIEventAdapter::KEY_KP_Delete;
	}

	~QtKeyboardMap()
	{
	}

	int remapKey(QKeyEvent* event)
	{
		KeyMap::iterator itr = mKeyMap.find(event->key());
		if (itr == mKeyMap.end())
		{
			return int(*(event->text().toLatin1().data()));
		}
		else
			return itr->second;
	}

private:
	typedef std::map<unsigned int, int> KeyMap;
	KeyMap mKeyMap;
};

static QtKeyboardMap s_QtKeyboardMap;


#if (QT_VERSION < QT_VERSION_CHECK(5, 2, 0))
#define GETDEVICEPIXELRATIO() 1.0
#else
#define GETDEVICEPIXELRATIO() devicePixelRatio()
#endif

GLCanvas::GLCanvas(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f, bool forwardKeyEvents)
	: QGLWidget(parent, shareWidget, f),
	_gw(NULL),
	_enterFlag(true)
{
	setFocusPolicy(Qt::ClickFocus);
	setAttribute(Qt::WA_AcceptTouchEvents, true);
	setMouseTracking(true);
}

GLCanvas::GLCanvas(QGLContext* context, QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f,
	bool forwardKeyEvents)
	: QGLWidget(context, parent, shareWidget, f),
	_gw(NULL),
	_enterFlag(true)
{
	setFocusPolicy(Qt::ClickFocus);
	setAttribute(Qt::WA_AcceptTouchEvents, true);
	setMouseTracking(true);
}

GLCanvas::GLCanvas(const QGLFormat& format, QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f,
	bool forwardKeyEvents)
	: QGLWidget(format, parent, shareWidget, f),
	_gw(NULL),
	_enterFlag(true)
{
	setFocusPolicy(Qt::ClickFocus);
	setAttribute(Qt::WA_AcceptTouchEvents, true);
	setMouseTracking(true);
}

bool GLCanvas::isEntered() const
{
	return _enterFlag;
}

GLCanvas::~GLCanvas()
{
	// close VViewerGraphics and remove the reference to us
	if (_gw)
	{
		_gw->close();
		_gw->_widget = NULL;
		_gw = NULL;
	}
}

void GLCanvas::processDeferredEvents()
{
	QQueue<QEvent::Type> deferredEventQueueCopy;
	{
		QMutexLocker lock(&_deferredEventQueueMutex);
		deferredEventQueueCopy = _deferredEventQueue;
		_eventCompressor.clear();
		_deferredEventQueue.clear();
	}

	while (!deferredEventQueueCopy.isEmpty())
	{
		QEvent event(deferredEventQueueCopy.dequeue());
		QGLWidget::event(&event);
	}
}

bool GLCanvas::event(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::Hide:
	{
		enqueueDeferredEvent(QEvent::Hide, QEvent::Show);
		return true;
	}
	case QEvent::Show:
	{
		enqueueDeferredEvent(QEvent::Show, QEvent::Hide);
		return true;
	}
	case QEvent::ParentChange:
	{
		enqueueDeferredEvent(QEvent::ParentChange);
		return true;
	}
	case QEvent::Enter:
	{
		_enterFlag = true;
		break;
	}
	case QEvent::Leave:
	{
		_enterFlag = false;
		break;
	}
	default:
		break;
	}
	// perform regular event handling
	return QGLWidget::event(event);
}

void GLCanvas::setKeyboardModifiers(QInputEvent* event)
{
	if (_gw == NULL)
	{
		return;
	}
	int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
	unsigned int mask = 0;
	if (modkey & Qt::ShiftModifier) mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
	if (modkey & Qt::ControlModifier) mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
	if (modkey & Qt::AltModifier) mask |= osgGA::GUIEventAdapter::MODKEY_ALT;
	_gw->getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
}

void GLCanvas::resizeEvent(QResizeEvent* event)
{
	const QSize& size = event->size();
	_gw->resized(x(), y(), size.width(), size.height());
	_gw->getEventQueue()->windowResize(x(), y(), size.width(), size.height());
	_gw->requestRedraw();
	inherited::resizeEvent(event);
	emit sizeChanged(size.width(), size.height());
}

void GLCanvas::moveEvent(QMoveEvent* event)
{
	const QPoint& pos = event->pos();
	_gw->resized(pos.x(), pos.y(), width(), height());
	_gw->getEventQueue()->windowResize(pos.x(), pos.y(), width(), height());
	inherited::moveEvent(event);
}

void GLCanvas::glDraw()
{
	_gw->requestRedraw();
}

void GLCanvas::keyPressEvent(QKeyEvent* event)
{
	setKeyboardModifiers(event);
	int value = s_QtKeyboardMap.remapKey(event);
	_gw->getEventQueue()->keyPress(value);

	// this passes the event to the regular Qt key event processing,
	// among others, it closes popup windows on ESC and forwards the event to the parent widgets
	inherited::keyPressEvent(event);
}

void GLCanvas::keyReleaseEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		event->ignore();
	}
	else
	{
		setKeyboardModifiers(event);
		int value = s_QtKeyboardMap.remapKey(event);
		_gw->getEventQueue()->keyRelease(value);
	}

	// this passes the event to the regular Qt key event processing,
	// among others, it closes popup windows on ESC and forwards the event to the parent widgets
	inherited::keyReleaseEvent(event);
}

void GLCanvas::mousePressEvent(QMouseEvent* event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	_gw->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
	inherited::mousePressEvent(event);
}

void GLCanvas::mouseReleaseEvent(QMouseEvent* event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	_gw->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);
	inherited::mouseReleaseEvent(event);
}

void GLCanvas::mouseDoubleClickEvent(QMouseEvent* event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	_gw->getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);
	inherited::mouseDoubleClickEvent(event);
}

void GLCanvas::mouseMoveEvent(QMouseEvent* event)
{
	setKeyboardModifiers(event);
	_gw->getEventQueue()->mouseMotion(event->x(), event->y());
	inherited::mouseMoveEvent(event);
}

void GLCanvas::wheelEvent(QWheelEvent* event)
{
	setKeyboardModifiers(event);
	_gw->getEventQueue()->mouseScroll(
		event->orientation() == Qt::Vertical ?
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));

	inherited::wheelEvent(event);
}

ViewerGraphics::ViewerGraphics(osg::GraphicsContext::Traits *traits, QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f)
	: _realized(false)
{
	_widget = NULL;

	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	_traits = traits;
	if (!_traits.valid())
	{
		_traits = new osg::GraphicsContext::Traits;
		_traits->windowName = "";
		_traits->windowDecoration = false;
		_traits->x = 0;
		_traits->y = 0;
		_traits->width = 960;
		_traits->height = 540;
		_traits->doubleBuffer = true;
		_traits->alpha = ds->getMinimumNumAlphaBits();
		_traits->stencil = ds->getMinimumNumStencilBits();
		_traits->sampleBuffers = ds->getMultiSamples();
		_traits->samples = ds->getNumMultiSamples();
	}
	init(parent, shareWidget, f);
	//setGraphicsThread(new VGraphicThread());
}

ViewerGraphics* ViewerGraphics::CreateViewerGraphics(int x, int y, int w, int h, const std::string& name, bool windowDecoration)
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	traits->samples = 8;
	traits->sampleBuffers = 1;

	//traits->alpha = ds->getMinimumNumAlphaBits();
	//traits->stencil = ds->getMinimumNumStencilBits();
	//traits->sampleBuffers = ds->getMultiSamples();
	//traits->samples = ds->getNumMultiSamples();

	return new ViewerGraphics(traits.get());
}

ViewerGraphics::~ViewerGraphics()
{
	close();

	// remove reference from VGLCanvas
	if (_widget)
		_widget->_gw = NULL;
}

bool ViewerGraphics::init(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f)
{
	// update _widget and parent by WindowData
	WindowData* windowData = _traits.get() ? dynamic_cast<WindowData*>(_traits->inheritedWindowData.get()) : 0;
	if (!_widget)
		_widget = windowData ? windowData->_widget : NULL;
	if (!parent)
		parent = windowData ? windowData->_parent : NULL;

	// create widget if it does not exist
	_ownsWidget = _widget == NULL;
	if (!_widget)
	{
		// shareWidget
		if (!shareWidget) {
			ViewerGraphics* sharedContextQt = dynamic_cast<ViewerGraphics*>(_traits->sharedContext.get());
			if (sharedContextQt)
				shareWidget = sharedContextQt->getGLWidget();
		}

		// WindowFlags
		Qt::WindowFlags flags = f | Qt::Window | Qt::CustomizeWindowHint;
		if (_traits->windowDecoration)
			flags |= Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint
#if (QT_VERSION_CHECK(4, 5, 0) <= QT_VERSION)
			| Qt::WindowCloseButtonHint
#endif
			;

		// create widget
		_widget = new GLCanvas(traits2qglFormat(_traits.get()), parent, shareWidget, flags);
	}

	// set widget name and position
	// (do not set it when we inherited the widget)
	if (_ownsWidget)
	{
		_widget->setWindowTitle(_traits->windowName.c_str());
		_widget->move(_traits->x, _traits->y);
		if (!_traits->supportsResize) _widget->setFixedSize(_traits->width, _traits->height);
		else _widget->resize(_traits->width, _traits->height);
	}

	// initialize widget properties
	_widget->setAutoBufferSwap(false);
	_widget->setMouseTracking(true);
	_widget->setFocusPolicy(Qt::WheelFocus);
	_widget->setGraphicsWindow(this);
	useCursor(_traits->useCursor);

	// initialize State
	setState(new osg::State);
	getState()->setGraphicsContext(this);

	// initialize contextID
	if (_traits.valid() && _traits->sharedContext.valid())
	{
		getState()->setContextID(_traits->sharedContext->getState()->getContextID());
		incrementContextIDUsageCount(getState()->getContextID());
	}
	else
	{
		getState()->setContextID(osg::GraphicsContext::createNewContextID());
	}

	// make sure the event queue has the correct window rectangle size and input range
	getEventQueue()->syncWindowRectangleWithGraphicsContext();
	return true;
}

QGLFormat ViewerGraphics::traits2qglFormat(const osg::GraphicsContext::Traits* traits)
{
	QGLFormat format(QGLFormat::defaultFormat());

	format.setAlphaBufferSize(traits->alpha);
	format.setRedBufferSize(traits->red);
	format.setGreenBufferSize(traits->green);
	format.setBlueBufferSize(traits->blue);
	format.setDepthBufferSize(traits->depth);
	format.setStencilBufferSize(traits->stencil);
	format.setSampleBuffers(traits->sampleBuffers);
	format.setSamples(traits->samples);

	format.setAlpha(traits->alpha > 0);
	format.setDepth(traits->depth > 0);
	format.setStencil(traits->stencil > 0);
	format.setDoubleBuffer(traits->doubleBuffer);
	format.setSwapInterval(traits->vsync ? 1 : 0);
	format.setStereo(traits->quadBufferStereo ? 1 : 0);

	return format;
}

void ViewerGraphics::qglFormat2traits(const QGLFormat& format, osg::GraphicsContext::Traits* traits)
{
	traits->red = format.redBufferSize();
	traits->green = format.greenBufferSize();
	traits->blue = format.blueBufferSize();
	traits->alpha = format.alpha() ? format.alphaBufferSize() : 0;
	traits->depth = format.depth() ? format.depthBufferSize() : 0;
	traits->stencil = format.stencil() ? format.stencilBufferSize() : 0;

	traits->sampleBuffers = format.sampleBuffers() ? 1 : 0;
	traits->samples = format.samples();

	traits->quadBufferStereo = format.stereo();
	traits->doubleBuffer = format.doubleBuffer();

	traits->vsync = format.swapInterval() >= 1;
}

osg::GraphicsContext::Traits* ViewerGraphics::createTraits(const QGLWidget* widget)
{
	osg::GraphicsContext::Traits *traits = new osg::GraphicsContext::Traits;

	qglFormat2traits(widget->format(), traits);

	QRect r = widget->geometry();
	traits->x = r.x();
	traits->y = r.y();
	traits->width = r.width();
	traits->height = r.height();

	traits->windowName = widget->windowTitle().toLocal8Bit().data();
	Qt::WindowFlags f = widget->windowFlags();
	traits->windowDecoration = (f & Qt::WindowTitleHint) &&
		(f & Qt::WindowMinMaxButtonsHint) &&
		(f & Qt::WindowSystemMenuHint);
	QSizePolicy sp = widget->sizePolicy();
	traits->supportsResize = sp.horizontalPolicy() != QSizePolicy::Fixed ||
		sp.verticalPolicy() != QSizePolicy::Fixed;

	return traits;
}

bool ViewerGraphics::setWindowRectangleImplementation(int x, int y, int width, int height)
{
	if (_widget == NULL)
		return false;

	_widget->setGeometry(x, y, width, height);
	return true;
}

void ViewerGraphics::getWindowRectangle(int& x, int& y, int& width, int& height)
{
	if (_widget)
	{
		const QRect& geom = _widget->geometry();
		x = geom.x();
		y = geom.y();
		width = geom.width();
		height = geom.height();
	}
}

bool ViewerGraphics::setWindowDecorationImplementation(bool windowDecoration)
{
	Qt::WindowFlags flags = Qt::Window | Qt::CustomizeWindowHint;//|Qt::WindowStaysOnTopHint;
	if (windowDecoration)
		flags |= Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint;
	_traits->windowDecoration = windowDecoration;

	if (_widget)
	{
		_widget->setWindowFlags(flags);

		return true;
	}

	return false;
}

bool ViewerGraphics::getWindowDecoration() const
{
	return _traits->windowDecoration;
}

void ViewerGraphics::grabFocus()
{
	if (_widget)
		_widget->setFocus(Qt::ActiveWindowFocusReason);
}

void ViewerGraphics::grabFocusIfPointerInWindow()
{
	if (_widget->underMouse())
		_widget->setFocus(Qt::ActiveWindowFocusReason);
}

void ViewerGraphics::raiseWindow()
{
	if (_widget)
		_widget->raise();
}

void ViewerGraphics::setWindowName(const std::string& name)
{
	if (_widget)
		_widget->setWindowTitle(name.c_str());
}

std::string ViewerGraphics::getWindowName()
{
	return _widget ? _widget->windowTitle().toStdString() : "";
}

void ViewerGraphics::useCursor(bool cursorOn)
{
	if (_widget)
	{
		_traits->useCursor = cursorOn;
		if (!cursorOn) _widget->setCursor(Qt::BlankCursor);
		else _widget->setCursor(_currentCursor);
	}
}

void ViewerGraphics::setCursor(MouseCursor cursor)
{
	if (cursor == InheritCursor && _widget)
	{
		_widget->unsetCursor();
	}

	switch (cursor)
	{
	case NoCursor: _currentCursor = Qt::BlankCursor; break;
	case RightArrowCursor: case LeftArrowCursor: _currentCursor = Qt::ArrowCursor; break;
	case InfoCursor: _currentCursor = Qt::SizeAllCursor; break;
	case DestroyCursor: _currentCursor = Qt::ForbiddenCursor; break;
	case HelpCursor: _currentCursor = Qt::WhatsThisCursor; break;
	case CycleCursor: _currentCursor = Qt::ForbiddenCursor; break;
	case SprayCursor: _currentCursor = Qt::SizeAllCursor; break;
	case WaitCursor: _currentCursor = Qt::WaitCursor; break;
	case TextCursor: _currentCursor = Qt::IBeamCursor; break;
	case CrosshairCursor: _currentCursor = Qt::CrossCursor; break;
	case HandCursor: _currentCursor = Qt::OpenHandCursor; break;
	case UpDownCursor: _currentCursor = Qt::SizeVerCursor; break;
	case LeftRightCursor: _currentCursor = Qt::SizeHorCursor; break;
	case TopSideCursor: case BottomSideCursor: _currentCursor = Qt::UpArrowCursor; break;
	case LeftSideCursor: case RightSideCursor: _currentCursor = Qt::SizeHorCursor; break;
	case TopLeftCorner: _currentCursor = Qt::SizeBDiagCursor; break;
	case TopRightCorner: _currentCursor = Qt::SizeFDiagCursor; break;
	case BottomRightCorner: _currentCursor = Qt::SizeBDiagCursor; break;
	case BottomLeftCorner: _currentCursor = Qt::SizeFDiagCursor; break;
	default: break;
	};
	if (_widget) _widget->setCursor(_currentCursor);
}

bool ViewerGraphics::valid() const
{
	return _widget && _widget->isValid();
}

bool ViewerGraphics::realizeImplementation()
{
	// save the current context
	// note: this will save only Qt-based contexts
	const QGLContext *savedContext = QGLContext::currentContext();

	// initialize GL context for the widget
	if (!valid())
		_widget->glInit();

	// make current
	_realized = true;
	bool result = makeCurrent();
	_realized = false;

	// fail if we do not have current context
	if (!result)
	{
		if (savedContext)
			const_cast<QGLContext*>(savedContext)->makeCurrent();

		OSG_WARN << "Window realize: Can make context current." << std::endl;
		return false;
	}

	_realized = true;

	// make sure the event queue has the correct window rectangle size and input range
	getEventQueue()->syncWindowRectangleWithGraphicsContext();

	// make this window's context not current
	// note: this must be done as we will probably make the context current from another thread
	//       and it is not allowed to have one context current in two threads
	if (!releaseContext())
		OSG_WARN << "Window realize: Can not release context." << std::endl;

	// restore previous context
	if (savedContext)
		const_cast<QGLContext*>(savedContext)->makeCurrent();

	return true;
}

bool ViewerGraphics::isRealizedImplementation() const
{
	return _realized;
}

void ViewerGraphics::closeImplementation()
{
	if (_widget)
		_widget->close();
	_realized = false;
}

void ViewerGraphics::runOperations()
{
	// While in graphics thread this is last chance to do something useful before
	// graphics thread will execute its operations.
	if (_widget->getNumDeferredEvents() > 0)
		_widget->processDeferredEvents();

	if (QGLContext::currentContext() != _widget->context())
		_widget->makeCurrent();

	GraphicsWindow::runOperations();
}

bool ViewerGraphics::makeCurrentImplementation()
{
	if (_widget->getNumDeferredEvents() > 0)
		_widget->processDeferredEvents();

	_widget->makeCurrent();

	return true;
}

bool ViewerGraphics::releaseContextImplementation()
{
	_widget->doneCurrent();
	return true;
}

void ViewerGraphics::swapBuffersImplementation()
{
	_widget->swapBuffers();

	// FIXME: the processDeferredEvents should really be executed in a GUI (main) thread context but
	// I couln't find any reliable way to do this. For now, lets hope non of *GUI thread only operations* will
	// be executed in a QGLWidget::event handler. On the other hand, calling GUI only operations in the
	// QGLWidget event handler is an indication of a Qt bug.
	if (_widget->getNumDeferredEvents() > 0)
		_widget->processDeferredEvents();

	// We need to call makeCurrent here to restore our previously current context
	// which may be changed by the processDeferredEvents function.
	if (QGLContext::currentContext() != _widget->context())
		_widget->makeCurrent();
}

void ViewerGraphics::requestWarpPointer(float x, float y)
{
	if (_widget)
		QCursor::setPos(_widget->mapToGlobal(QPoint((int)x, (int)y)));
}