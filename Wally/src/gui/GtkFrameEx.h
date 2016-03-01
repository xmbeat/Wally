#ifndef GTKFRAMEEX_H
#define GTKFRAMEEX_H
#include "GtkContainerEx.h"

class GtkFrameEx: public GtkContainerEx
{
    public:
        GtkFrameEx(const char *caption = NULL) {
            setWidget(gtk_frame_new(caption));
        }
        virtual ~GtkFrameEx() {}
        virtual operator GtkFrame*()
        {
            return GTK_FRAME(getWidget());
        }
        virtual void setText(const char* caption)
        {
            gtk_frame_set_label(*this, caption);
        }

        virtual String getText()
        {
            return gtk_frame_get_label(*this);
        }

    protected:
    private:
};

#endif // GTKFRAMEEX_H
