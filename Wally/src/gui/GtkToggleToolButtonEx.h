#ifndef GTKTOGGLETOOLBUTTONEX_H
#define GTKTOGGLETOOLBUTTONEX_H

#include "GtkToolButtonEx.h"


class GtkToggleToolButtonEx : public GtkToolButtonEx
{
    public:
        GtkToggleToolButtonEx(const char* caption = NULL, bool isStock = false): GtkToolButtonEx(caption, false)
        {
			setWidget(GTK_WIDGET(gtk_toggle_tool_button_new()));
			if (isStock)
				setStockID(caption);
			else if (caption)
				setText(caption);
        }
        virtual operator GtkToggleToolButton *()
        {
            return GTK_TOGGLE_TOOL_BUTTON(getWidget());
        }

        virtual bool isChecked()
        {
            return  gtk_toggle_tool_button_get_active(*this);
        }

        virtual void setChecked(bool value)
        {
            gtk_toggle_tool_button_set_active(*this,value);
        }

        virtual ~GtkToggleToolButtonEx() {}
        virtual void actToToggledEvent(GtkEventWatcher*listener)
        {
            g_signal_connect(getWidget(), "toggled", G_CALLBACK(toggledEvent), listener);
        }
    private:
        static void toggledEvent(GtkToggleButton*button, GtkEventWatcher *listener)
        {
            listener->onToggled(GTK_WIDGET(button));
        }
};

#endif // GTKTOGGLETOOLBUTTONEX_H
