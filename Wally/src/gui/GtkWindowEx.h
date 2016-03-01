#ifndef GTKWINDOWEX_H
#define GTKWINDOWEX_H
#include "GtkContainerEx.h"

class GtkWindowEx: public GtkContainerEx{
    private:
        GdkGeometry gdkGeo;
    public:
        GtkWindowEx(const char* caption = NULL)
        {
            gdkGeo.min_width = 0;
            gdkGeo.min_height = 0;
            gdkGeo.max_width = 0;
            gdkGeo.max_height = 0;
            setWidget(gtk_window_new(GTK_WINDOW_TOPLEVEL));
            setText(caption);
        }
        GtkWindowEx(GtkWidget* init)
        {
            setWidget(init);
        }
        virtual ~GtkWindowEx() {}
        virtual operator GtkContainer*()
        {
            return (GTK_CONTAINER(getWidget()));
        }

        virtual operator GtkWindow*()
        {
            return (GtkWindow*)getWidget();
        }

        virtual void setDefaultSize(int width, int height)
        {
            gtk_window_set_default_size(*this, width, height);
        }
        virtual void setPosition(int x, int y)
        {
            gtk_window_move(*this,x,y);
        }

        virtual void getPosition(int *x, int *y)
        {
           // gdk_window_get_position(widget->window, &x, &y);
            gdk_window_get_root_origin(getWidget()->window, x,  y);
        }
        virtual void setDefaultCloseOperation()
        {
             g_signal_connect_swapped(getWidget(), "destroy",
                G_CALLBACK(gtk_main_quit), getWidget());
        }
        virtual bool isModal()
        {
            return gtk_window_get_modal(*this);
        }
        virtual void setModal(bool value)
        {
            gtk_window_set_modal(*this, value);
        }
        virtual void setSize(int width, int height)
        {
            gtk_window_resize(*this, width, height);
        }
        virtual void getSize(int *width, int* height)
        {
            gtk_window_get_size(*this, width, height);
        }
        virtual void setVisibleInTaskBar(bool value)
        {
            gtk_window_set_skip_taskbar_hint(*this, !value);
        }
        virtual void present(){
        	gtk_window_present(*this);
        }
        virtual void setIcon(GdkPixbuf *icon)
        {
            gtk_window_set_icon(*this, icon);
        }
        virtual GdkPixbuf* getIcon()
        {
            return gtk_window_get_icon(*this);
        }
        virtual void setText(const char* text)
        {
            gtk_window_set_title(*this, text);
        }
        virtual void setMinimumSize(int width, int height)
        {
            int flag = GDK_HINT_MIN_SIZE;
            gdkGeo.min_height = height;
            gdkGeo.min_width = width;
            if (gdkGeo.max_width > 0|| gdkGeo.max_height > 0)
                flag |= GDK_HINT_MAX_SIZE;
            gtk_window_set_geometry_hints(*this, getWidget(), &gdkGeo,
                                          (GdkWindowHints)flag);
        }
        virtual void setMaximumSize(int width, int height)
        {
            int flag = GDK_HINT_MAX_SIZE;
            gdkGeo.max_height = height;
            gdkGeo.max_width = width;
            if (gdkGeo.min_width > 0|| gdkGeo.min_height > 0)
                flag |= GDK_HINT_MIN_SIZE;
            gtk_window_set_geometry_hints(*this, getWidget(), &gdkGeo,
                                          (GdkWindowHints)
                                            flag);
        }
        virtual void setTypeHint(GdkWindowTypeHint type)
        {
            gtk_window_set_type_hint(*this, type);
        }
        virtual GdkWindowTypeHint getTypeHint()
        {
            return gtk_window_get_type_hint(*this);
        }
        virtual void setDeleteable(bool value)
        {
            gtk_window_set_deletable(*this, value);
        }
        virtual void setDecorated(bool value)
        {
            gtk_window_set_decorated(*this, value);
        }
        virtual bool isDecorated()
        {
            return gtk_window_get_decorated (*this);
        }
        virtual bool isDeleteable()
        {
            return gtk_window_get_deletable(*this);
        }
        virtual void setFullScreen(bool value)
        {
            if (value)
                gtk_window_fullscreen(*this);
            else
                gtk_window_unfullscreen(*this);
        }
        virtual void setIconFromFile(const char* path)
        {
            GError **error = NULL;
            gtk_window_set_icon_from_file(*this, path, error);
            //Implementar una llamada a throw
        }
        virtual String getText()
        {
            return gtk_window_get_title(*this);
        }
        virtual void setResizable(bool value)
        {
            gtk_window_set_resizable(*this, value);
        }
        virtual bool isResizable()
        {
            return gtk_window_get_resizable(*this);
        }
        virtual void actToWindowDestroyEvent(GtkEventWatcher*listener)
        {
            g_signal_connect(getWidget(), "destroy", G_CALLBACK(windowDestroyEvent), listener);
        }
        virtual void actToWindowCloseEvent(GtkEventWatcher *listener)
        {
            g_signal_connect(getWidget(), "delete-event", G_CALLBACK(windowCloseEvent), listener);
        }
    protected:
        static bool windowCloseEvent(GtkWidget *widget, GdkEvent  *event, GtkEventWatcher*user_data)
        {
            return user_data->onWindowClose(widget, event);
        }
        static void windowDestroyEvent(GtkWindow* widget, GtkEventWatcher *listener)
        {
            listener->onWindowDestroy(widget);
        }
};

#endif // GTKWINDOWEX_H
