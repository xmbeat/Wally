#ifndef GTKTREEVIEW_H
#define GTKTREEVIEW_H
#include "GtkContainerEx.h"

class GtkTreeViewEx: public GtkContainerEx
{
    public:
        virtual operator GtkTreeView*()
        {
            return GTK_TREE_VIEW(getWidget());
        }
        GtkTreeViewEx() {
            setWidget(gtk_tree_view_new());
        }
        GtkTreeViewEx(GtkTreeModel *model)
        {
            setWidget(gtk_tree_view_new_with_model(model));
        }
        virtual bool getShowExpanders()
        {
            return gtk_tree_view_get_show_expanders(*this);
        }
        virtual void setModel(GtkTreeModel*model)
        {
            gtk_tree_view_set_model(*this, model);
        }
        virtual GtkTreeModel* getModel()
        {
            return gtk_tree_view_get_model(*this);
        }
        virtual GtkTreeSelection* getSelection()
        {
            return gtk_tree_view_get_selection(*this);
        }
        virtual void setHeadersVisible(bool value)
        {
            gtk_tree_view_set_headers_visible(*this, value);
        }
        virtual bool getHeadersVisible()
        {
            return gtk_tree_view_get_headers_visible(*this);
        }
        virtual void setRulesHint(bool value)
        {
            gtk_tree_view_set_rules_hint(*this, value);
        }
        virtual bool getRulesHint()
        {
            return gtk_tree_view_get_rules_hint(*this);
        }
        virtual void setHeadersClickable(bool value)
        {
            gtk_tree_view_set_headers_clickable(*this, value);
        }
        virtual bool getHeadersClickable()
        {
            return gtk_tree_view_get_headers_clickable(*this);
        }
        virtual void setGridLines(GtkTreeViewGridLines lines)
        {
            gtk_tree_view_set_grid_lines(*this, lines);
        }
        virtual int addColumn(GtkTreeViewColumn *column, int pos = -1)
        {
            return gtk_tree_view_insert_column(*this, column, pos);
        }
        virtual int removeColumn(int pos)
        {
            GtkTreeViewColumn *column = gtk_tree_view_get_column(*this, pos);
            if (column)
            {
                 return gtk_tree_view_remove_column(*this, column);
            }
            return -1;
        }
		virtual void actToCursorChangedEvent(GtkEventWatcher *listener)
		{
			g_signal_connect(getWidget(), "cursor-changed", G_CALLBACK(cursorChangedEvent), listener);
		}
        virtual ~GtkTreeViewEx() {}
    private:
		static void cursorChangedEvent(GtkWidget*widget, GtkEventWatcher *listener)
		{
			listener->onCursorChanged(widget);
		}
};

#endif // GTKTREEVIEW_H
