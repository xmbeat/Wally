#ifndef GTKBUTTONEX_H
#define GTKBUTTONEX_H
#include "GtkContainerEx.h"

class GtkButtonEx: public GtkContainerEx
{
    public:
		GtkButtonEx(GtkWidget* button){
			setWidget(button);
		}
		GtkButtonEx(const char *caption = NULL)
		{
			setWidget(gtk_button_new_with_label(caption));
		}

        virtual operator GtkButton*()
        {
            return GTK_BUTTON(getWidget());
        }
        virtual ~GtkButtonEx() {}

        virtual void setText(String text)
        {
            gtk_button_set_label(*this, text);
        }
        virtual String getText()
        {
            return gtk_button_get_label(*this);
        }
        virtual void setUseMnemonic(bool value)
        {
        	int rv = value?TRUE:FALSE;
            gtk_button_set_use_underline(*this, rv);
        }
        virtual bool isMnemonic()
        {
            return gtk_button_get_use_underline(*this);
        }
        //=========SIGNALS========//
        //Emitted when the button has been activated (pressed and released).
        virtual void actToClickEvent(GtkEventWatcher *listener)
        {
            g_signal_connect(getWidget(), "clicked", G_CALLBACK(clickEvent), listener);
        }

    private:
        static void clickEvent(GtkWidget* widget, GtkEventWatcher* listener)
        {
            listener->onClick(widget);
        }
};

#endif // GTKBUTTONEX_H
