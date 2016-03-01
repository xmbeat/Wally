#ifndef GTKLISTSTOREEX_H_H
#define GTKLISTSTOREEX_H_H
#include <stdarg.h>
#include "ClassControls.h"
class GtkListStoreEx
{
    public:
        virtual operator GtkListStore*()
        {
            return store;
        }
        virtual operator GtkTreeModel*()
        {
			
            return GTK_TREE_MODEL(store);
        }
        GtkListStore* getStore()
        {
            return store;
        }
		GtkListStoreEx(GtkTreeModel* store)
		{
			this->store = GTK_LIST_STORE(store);
		}
        GtkListStoreEx(GtkListStore* store)
        {
            this->store = store;
        }
        GtkListStoreEx(int nCols, ...)
        {
            GType *cols = new GType[nCols];
            va_list params;
            va_start(params, nCols);
            for (int i = 0; i < nCols; i++)
            {
                cols[i] = va_arg(params, GType);
            }
            va_end(params);
            store = gtk_list_store_newv(nCols, cols);
            delete[] cols;
        }
        virtual void add(int pos, ...)
        {
            GtkTreeIter iter;
            if (pos<0)
                gtk_list_store_append(store, &iter);
            else
                gtk_list_store_insert(store, &iter, pos);
            va_list params;
            va_start(params, pos);
            gtk_list_store_set_valist(store, &iter, params);
            va_end(params);//Estabilizamos la pila
        }
        virtual void clear()
        {
            gtk_list_store_clear(store);
        }
        virtual bool remove(int pos)
        {
            GtkTreeIter  iter;
            if (getIterFromIndex(&iter, pos))
            {
                return gtk_list_store_remove(store, &iter);
            }
            return false;
        }
		virtual bool remove(GtkTreeIter *iter)
		{
			return gtk_list_store_remove(store, iter);
		}
        virtual void get(int pos, ...)
        {
            GtkTreeIter iter;
            if (getIterFromIndex(&iter, pos))
            {
                va_list params;
                va_start(params, pos);
                gtk_tree_model_get_valist(*this, &iter, params);
                va_end(params);
            }
        }
	
		virtual bool modify(GtkTreeIter *iter, ...)
		{
			va_list params;
			va_start(params, iter);
			gtk_list_store_set_valist(store, iter, params);
			va_end(params);
			return true;
		}
        virtual bool modify(int pos, ...)
        {
            GtkTreeIter  iter;
            if (getIterFromIndex(&iter, pos))
            {
                va_list params;
                va_start(params, pos);
                gtk_list_store_set_valist(store, &iter, params);
                va_end(params);
                return true;
            }
            return false;
        }
        virtual int getRowsCount()
        {
            return gtk_tree_model_iter_n_children(*this, NULL);
        }
        virtual ~GtkListStoreEx() {
        }
		virtual void destroy()
		{
			g_object_unref(store);//Eliminamos	
		}
        virtual bool getIterFromIndex(GtkTreeIter *iter, const int &index)
        {
            if (gtk_tree_model_get_iter_first(*this, iter))
            {
                int i = 0;
                for(;i<index;i++)
                {
                    if (!gtk_tree_model_iter_next(*this, iter))
                        return false;
                }
                return true;
            }
            return false;
        }
    private:
        GtkListStore *store;
};

#endif // GTKLISTSTOREEX_H_H
