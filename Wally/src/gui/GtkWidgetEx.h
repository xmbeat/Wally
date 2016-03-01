#ifndef GTKWIDGETEX_H
#define GTKWIDGETEX_H
#include <gtk/gtk.h>
#include "GtkEventWatcher.h"
#ifndef NULL
#define NULL 0
#endif
class GtkWidgetEx
{
    public:
        GtkWidgetEx(): mWidget(NULL){}
        static void Initialize(char**);
        virtual ~GtkWidgetEx() {}

		virtual bool operator==(GtkWidget*widget)
		{
			return mWidget == widget;
		} 
        virtual void showAll()
        {
            gtk_widget_show_all(*this);
        }
        virtual void setVisible(bool value)
        {
            if (value)
                gtk_widget_show(mWidget);
            else
                gtk_widget_hide(mWidget);
        }
        virtual bool isVisible()
        {
            return gtk_widget_get_visible(getWidget());
        }
        virtual void setSize(int width, int height)
        {
            gtk_widget_set_size_request(mWidget, width, height);
        }
        virtual void getSize(int* width, int* height)
        {
            gtk_widget_get_size_request(getWidget(), width, height);
        }
        virtual bool isEnabled()
        {
            return gtk_widget_is_sensitive(*this);
        }
        virtual void setEnabled(bool value)
        {
            gtk_widget_set_sensitive(*this, value);
        }
        virtual operator GtkWidget*()
        {
            return getWidget();
        }
        virtual String getTooltipText()
        {
            return  gtk_widget_get_tooltip_text(*this);
        }
        virtual void setTooltipText(const char* text)
        {
            gtk_widget_set_tooltip_text(*this,text);
        }
        virtual void destroy(){
        	gtk_widget_destroy(*this);
        }
        virtual GtkWidget* getWidget()
        {
            return mWidget;
        }
        //==========SIGNALS=========//
        //The enter-notify-event will be emitted when the pointer enters the widget's window.
        virtual void actToMouseMoveEvent(GtkEventWatcher *listener)
        {
            gtk_widget_add_events(getWidget(), GDK_POINTER_MOTION_MASK);
            g_signal_connect(getWidget(), "motion-notify-event",G_CALLBACK(mouseMoveEvent), listener);
        }

        virtual void actToMouseEnterEvent(GtkEventWatcher *listener)
        {
            gtk_widget_add_events(getWidget(), GDK_ENTER_NOTIFY_MASK);
            g_signal_connect(getWidget(), "enter-notify-event", G_CALLBACK(mouseEnterEvent), listener);
        }
        virtual void actToMouseOutEvent(GtkEventWatcher *listener)
        {
            gtk_widget_add_events(getWidget(), GDK_LEAVE_NOTIFY_MASK);
            g_signal_connect(getWidget(), "leave-notify-event", G_CALLBACK(mouseOutEvent), listener);
        }
        virtual void actToResizeEvent(GtkEventWatcher *listener)
        {
            gtk_widget_add_events(getWidget(), GDK_STRUCTURE_MASK);
            g_signal_connect(getWidget(), "configure-event", G_CALLBACK(resizeEvent), listener);
        }
        virtual void actToPressEvent(GtkEventWatcher *listener)
        {

            gtk_widget_add_events(getWidget(), GDK_BUTTON_PRESS_MASK);
            g_signal_connect(getWidget(), "button-press-event", G_CALLBACK(pressEvent), listener);
        }
        virtual void actToReleaseEvent(GtkEventWatcher *listener)
        {
            gtk_widget_add_events(getWidget(), GDK_BUTTON_RELEASE_MASK);
            g_signal_connect(getWidget(), "button-release-event", G_CALLBACK(releaseEvent), listener);
        }
        virtual void actToKeypressEvent(GtkEventWatcher*listener)
        {
            gtk_widget_add_events(getWidget(), GDK_KEY_PRESS_MASK);
            g_signal_connect(getWidget(), "key-press-event", G_CALLBACK(keypressEvent), listener);
        }
        virtual void actToKeyreleaseEvent(GtkEventWatcher*listener)
        {
            gtk_widget_add_events(getWidget(), GDK_KEY_RELEASE_MASK);
            g_signal_connect(getWidget(), "key-release-event", G_CALLBACK(keyreleaseEvent), listener);
        }
    protected:

        void setWidget(GtkWidget* widget)
        {
            mWidget = widget;
        }
        static bool mouseMoveEvent(GtkWidget *widget, GdkEventMotion* event, GtkEventWatcher*listener)
        {
            return listener->onMouseMove(widget, event);
        }
        static bool mouseOutEvent(GtkWidget *widget, GdkEventCrossing *event, GtkEventWatcher* listener)
        {
            return listener->onMouseOut(widget, event);
        }
        static bool resizeEvent(GtkWidget *widget, GdkEventConfigure *event, GtkEventWatcher *listener)
        {
            return listener->onResize(widget, event);
        }
        static bool mouseEnterEvent(GtkWidget* widget, GdkEventCrossing *event, GtkEventWatcher* listener)
        {
            return (listener->onMouseEnter(widget, event));
        }
        static bool releaseEvent(GtkWidget* widget, GdkEventButton *event, GtkEventWatcher *listener)
        {
            return listener->onRelease(widget, event);
        }
        static bool pressEvent(GtkWidget* widget, GdkEventButton *event, GtkEventWatcher *listener)
        {
            return listener->onPress(widget, event);
        }
        static bool keypressEvent(GtkWidget* widget, GdkEventKey *event, GtkEventWatcher *listener)
        {
            return listener->onKeyPress(widget, event);
        }
        static bool keyreleaseEvent(GtkWidget* widget, GdkEventKey *event, GtkEventWatcher *listener)
        {
            return listener->onKeyRelease(widget, event);
        }
    private:
        GtkWidget *mWidget;//Se elimina solo
};
void GtkWidgetEx::Initialize(char**args)
{
    int argc = 1;
    gtk_init(&argc, &args);
}
#endif // GTKWIDGETEX_H
