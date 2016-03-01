#ifndef GTKLABELEX_H
#define GTKLABELEX_H
#include "GtkMiscEx.h"
class GtkLabelEx: public GtkMiscEx
{
    public:
        virtual operator GtkLabel*()
        {
            return GTK_LABEL(getWidget());
        }
        GtkLabelEx(const char *text = NULL)
        {
            setWidget(gtk_label_new(text));
        }
        virtual ~GtkLabelEx(){}

        virtual void setText(const char *text)
        {
            gtk_label_set_text(*this, text);
        }
        virtual String getText()
        {
            return gtk_label_get_text(*this);
        }

        virtual void setSelectable(bool value)
        {
             gtk_label_set_selectable(*this, value);
        }
        virtual bool getSelectable()
        {
             return gtk_label_get_selectable(*this);
        }
        virtual void setLineWrap(bool value)
        {
            gtk_label_set_line_wrap(*this, value);
        }
        virtual bool isLineWrap()
        {
            return gtk_label_get_line_wrap(*this);
        }
};
#endif
