#ifndef GTKSCROLLEDWINDOWEX_H
#define GTKSCROLLEDWINDOWEX_H
#include "GtkContainerEx.h"

class GtkScrolledWindowEx:public GtkContainerEx
{
    public:
        virtual operator GtkScrolledWindow*()
        {
            return GTK_SCROLLED_WINDOW(getWidget());
        }
        GtkScrolledWindowEx(GtkAdjustment *hAdj = NULL, GtkAdjustment *vAdj = NULL) {
            setWidget(gtk_scrolled_window_new(hAdj, vAdj));
        }
        virtual void setPolicy(GtkPolicyType hScrollPolicy, GtkPolicyType vScrollPolicy)
        {
            gtk_scrolled_window_set_policy(*this, hScrollPolicy, vScrollPolicy);
        }
        virtual void getPolicy(GtkPolicyType *h, GtkPolicyType *v)
        {
            gtk_scrolled_window_get_policy(*this, h, v);
        }
        virtual void addWithViewport(GtkWidget *widget)
        {
            gtk_scrolled_window_add_with_viewport(*this, widget);
        }
        virtual GtkWidget* getHScrollbar()
        {
            return gtk_scrolled_window_get_hscrollbar(*this);
        }
        virtual GtkWidget* getVScrollbar()
        {
            return gtk_scrolled_window_get_vscrollbar(*this);
        }
        virtual void setPlacement(GtkCornerType pos)
        {
            gtk_scrolled_window_set_placement(*this, pos);
        }
        virtual void setShadowType(GtkShadowType tipo)
        {
             gtk_scrolled_window_set_shadow_type(*this, tipo);
        }
        virtual GtkShadowType getShadowType()
        {
            return  gtk_scrolled_window_get_shadow_type(*this);
        }
        virtual void setHAdjustment(GtkAdjustment *adj)
        {
            gtk_scrolled_window_set_hadjustment(*this, adj);
        }
        virtual void setVAdjustment(GtkAdjustment *adj)
        {
            gtk_scrolled_window_set_vadjustment(*this, adj);
        }
        virtual GtkAdjustment * getHAdjustment()
        {
            return gtk_scrolled_window_get_hadjustment(*this);
        }
        virtual GtkAdjustment * getVAdjustment()
        {
            return gtk_scrolled_window_get_hadjustment(*this);
        }
        virtual ~GtkScrolledWindowEx() {}
    protected:
    private:
};

#endif // GTKSCROLLEDWINDOWEX_H
