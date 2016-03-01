#ifndef GTKEVENTWATCHER_H
#define GTKEVENTWATCHER_H
/*
    ESTA CLASE ES TEMPORAL, QUIERO SEPARARLA DEPENDIENDO SU FUNCIONAMIENTO Y CONTROLES QUE LOS USAN
*/
class GtkEventWatcher
{
    public:
		virtual void onResponse(GtkDialog* dialog, int id){}
		virtual void onClose(GtkDialog* dialog){}
		virtual void onFileSet(GtkWidget*widget)
		{}
		virtual void onCursorChanged(GtkWidget *widget)
		{}
        virtual void onActivate(GtkWidget* menu)
        {

        }
		virtual void onChangeValue(GtkWidget *spinbutton, GtkScrollType arg1)
		{

		}
        virtual void onChange(GtkWidget *button)
        {

        }
        virtual void onToggled(GtkWidget *button)
        {

        }
        virtual void onClick(GtkWidget* widget)
        {

        }
        virtual bool onMouseMove(GtkWidget* widget, GdkEventMotion *event)
        {
            return false;
        }
        virtual bool onMouseEnter(GtkWidget* widget,  GdkEventCrossing *event)
        {
            return false;
        }
        virtual bool onMouseOut(GtkWidget* widget, GdkEventCrossing *event)
        {
            return false;
        }
        virtual bool onRelease(GtkWidget* widget, GdkEventButton *event)
        {
            return false;
        }
        virtual bool onPress(GtkWidget* widget, GdkEventButton *event)
        {
            return false;
        }
        virtual bool onKeyPress(GtkWidget* widget, GdkEventKey *event)
        {
            return false;
        }
        virtual bool onKeyRelease(GtkWidget* widget, GdkEventKey *event)
        {
            return false;
        }
        virtual void onWindowDestroy(GtkWindow* widget)
        {
            //
        }
        virtual bool onWindowClose(GtkWidget *widget, GdkEvent *event)
        {
            return false;
        }
        virtual bool onResize(GtkWidget* widget, GdkEventConfigure *event)
        {
            return false;
        }
        virtual bool onChangePage(GtkWidget*widget)
        {
            return false;
        }

};
#endif
