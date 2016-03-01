#ifndef GTKRADIOBUTTONEX_H
#define GTKRADIOBUTTONEX_H
#include "GtkCheckButtonEx.h"
class GtkRadioButtonEx: public GtkCheckButtonEx
{
    public:
        GtkRadioButtonEx(const char *caption = NULL, GtkRadioButton *radioGroupMember = NULL):
        	GtkCheckButtonEx((GtkWidget*)NULL)
        {
			if (radioGroupMember)
				setWidget(gtk_radio_button_new_from_widget(radioGroupMember));
			else
				setWidget(gtk_radio_button_new(NULL));
            setText(caption);
        }
        virtual ~GtkRadioButtonEx() {}
        virtual operator GtkRadioButton*()
        {
            return (GtkRadioButton*)getWidget();
        }

};


class GtkRadioGroup
{
    private:
        GSList *list;
    public:
        GtkRadioGroup(){
            list = NULL;
        }
        virtual ~GtkRadioGroup()
		{
        }
        virtual void add(GtkRadioButtonEx *radioButton)
        {
            add(*radioButton);
        }
        virtual void add(GtkRadioButton* radioButton)
        {
            gtk_radio_button_set_group(radioButton, list);
            list = gtk_radio_button_get_group(radioButton);
        }
};

#endif // GTKRADIOBUTTONEX_H
