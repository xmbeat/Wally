#ifndef GTKNOTEBOOKEX_H
#define GTKNOTEBOOKEX_H
#include "GtkContainerEx.h"

class GtkNotebookEx: public GtkContainerEx
{
    public:
        virtual operator GtkNotebook*()
        {
            return GTK_NOTEBOOK(getWidget());
        }
        GtkNotebookEx()
        {
            setWidget(gtk_notebook_new());
        }
        virtual void add(GtkWidget *child, const char* label, int pos = -1)
        {
            GtkLabelEx etiqueta(label);
            add(child, etiqueta, pos);
        }
        virtual void add(GtkWidget*child, GtkWidget *tabLabel, int pos = -1)
        {
            gtk_notebook_insert_page(*this, child, tabLabel, pos);
        }
        virtual void remove(int pos)
        {
            gtk_notebook_remove_page(*this, pos);
        }
        virtual int getCurrentPage()
        {
            return gtk_notebook_get_current_page(*this);
        }
        virtual void setCurrentPage(int pos)
        {
            gtk_notebook_set_current_page(*this, pos);
        }
		virtual bool setCurrentPage(GtkWidget* widget)
		{
			int index = getPageNum(widget);
			if (index >= 0)
			{
				setCurrentPage(index);
				return true;
			}
			return false;
		}
        virtual void prevPage()
        {
            gtk_notebook_prev_page(*this);
        }
        virtual void nextPage()
        {
            gtk_notebook_next_page(*this);
        }
        virtual void setHomogeneusTab(bool value)
        {
            gtk_notebook_set_homogeneous_tabs(*this, value);
        }
        virtual int getPageNum(GtkWidget*child)
        {
            return gtk_notebook_page_num(*this, child);
        }
        virtual void setTabPos(GtkPositionType pos)
        {
            gtk_notebook_set_tab_pos(*this, pos);
        }
        virtual void showTabs(bool value)
        {
            gtk_notebook_set_show_tabs(*this, value);
        }
		virtual void setScrollable(bool value)
		{
			gtk_notebook_set_scrollable(*this, value);
		}
		virtual bool getScrollable()
		{
			return gtk_notebook_get_scrollable(*this);
		}
        virtual void actToChangePageEvent(GtkEventWatcher*listener)
        {
            g_signal_connect(getWidget(), "change-current-page", G_CALLBACK(changePageEvent), listener);
        }
        virtual ~GtkNotebookEx(){}
    private:
        static bool changePageEvent(GtkWidget *widget, int arg1, GtkEventWatcher *listener)
        {
            return listener->onChangePage(widget);
        }
};

#endif // GTKNOTEBOOKEX_H
