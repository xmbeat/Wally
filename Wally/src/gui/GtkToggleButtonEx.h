#ifndef GTKTOGGLEBUTTONEX_H
#define GTKTOGGLEBUTTONEX_H
#include "GtkButtonEx.h"

class GtkToggleButtonEx: public GtkButtonEx
{
    public:
		GtkToggleButtonEx(GtkWidget* widget): GtkButtonEx(widget)
		{}
        GtkToggleButtonEx(const char* caption = NULL): 
		GtkButtonEx((GtkWidget*)NULL)
        {
			setWidget(gtk_toggle_button_new_with_label (caption));
        }
        virtual operator GtkToggleButton *()
        {
            return GTK_TOGGLE_BUTTON(getWidget());
        }
        virtual ~GtkToggleButtonEx() {}

        virtual bool isChecked()
        {
            return gtk_toggle_button_get_active(*this);
        }

        virtual void setChecked(bool value)
        {
        	int rv = value?TRUE:FALSE;
            gtk_toggle_button_set_active(*this,rv);
        }
        virtual bool isInconsitent()
        {
            return gtk_toggle_button_get_inconsistent(*this);
        }
        virtual void setInconsistent(bool value)
        {
        	int rv = value?TRUE:FALSE;
            gtk_toggle_button_set_inconsistent(*this, rv);
        }
        virtual void actToToggledEvent(GtkEventWatcher*listener)
        {
            g_signal_connect(getWidget(), "toggled", G_CALLBACK(toggledEvent), listener);
        }
    private:
        static void toggledEvent(GtkToggleButton*button, GtkEventWatcher *listener)
        {
            listener->onToggled(GTK_WIDGET(button));
        }
	protected:
};

#endif // GTKTOGGLEBUTTONEX_H
