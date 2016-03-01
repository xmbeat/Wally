#ifndef GTKCHECKBUTTONEX_H
#define GTKCHECKBUTTONEX_H
#include "GtkToggleButtonEx.h"

class GtkCheckButtonEx: public GtkToggleButtonEx
{
    public:
        GtkCheckButtonEx(const char *caption = NULL): GtkToggleButtonEx((GtkWidget*)NULL)
        {
            setWidget(gtk_check_button_new_with_label(caption));
        }
        virtual ~GtkCheckButtonEx() {}
		GtkCheckButtonEx(GtkWidget* widget): GtkToggleButtonEx(widget)
		{}
};

#endif // GTKCHECKBUTTONEX_H
