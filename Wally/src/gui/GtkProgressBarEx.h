#ifndef GTKPROGRESSBAREX_H
#define GTKPROGRESSBAREX_H
#include "GtkWidgetEx.h"

class GtkProgressBarEx: public GtkWidgetEx
{
    public:

        GtkProgressBarEx(const char* caption = NULL)
        {
            setWidget(gtk_progress_bar_new());
            setText(caption);
        }
        virtual operator GtkProgressBar*()
        {
            return (GtkProgressBar*)getWidget();
        }

        virtual void setPulse()
        {
            gtk_progress_bar_pulse(*this);
        }
        virtual void setPulseStep(double step)
        {
            gtk_progress_bar_set_pulse_step(*this, step);
        }
        virtual double getPulseStep()
        {
            return gtk_progress_bar_get_pulse_step(*this);
        }
        virtual void setText(const char* text)
        {
            gtk_progress_bar_set_text(*this, text);
        }
        virtual String getText()
        {
            return gtk_progress_bar_get_text(*this);
        }
        virtual void setOrientation(GtkProgressBarOrientation orientation)
        {
            gtk_progress_bar_set_orientation(*this,orientation);
        }
        virtual void setEllipsize(PangoEllipsizeMode mode)
        {
            gtk_progress_bar_set_ellipsize(*this, mode);
        }
        virtual PangoEllipsizeMode getEllipsize()
        {
            return gtk_progress_bar_get_ellipsize(*this);
        }
        virtual void setValue(double value)
        {
            gtk_progress_bar_set_fraction(*this,value);
        }
        virtual double getValue()
        {
            return gtk_progress_bar_get_fraction(*this);
        }
        virtual ~GtkProgressBarEx() {}
    private:

};

#endif // GTKPROGRESSBAREX_H
