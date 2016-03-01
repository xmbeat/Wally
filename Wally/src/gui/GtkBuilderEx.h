/*
 * GtkBuilder.h
 *
 *  Created on: 20/07/2015
 *      Author: xmbeat
 */

#ifndef GTKBUILDEREX_H_
#define GTKBUILDEREX_H_
#include "GtkWidgetEx.h"

class GtkBuilderEx{
public:

	GtkBuilderEx(){
		mBuilder = gtk_builder_new();
	}
	virtual ~GtkBuilderEx(){
		g_object_unref(G_OBJECT(mBuilder));
	}
	virtual GtkWidget* operator[](String name){
		return (GtkWidget*)gtk_builder_get_object(*this, name);
	}
	virtual operator GtkBuilder*(){
		return mBuilder;
	}
	bool addFromFile(String filename){
		return gtk_builder_add_from_file(*this, filename, NULL);
	}

	bool addFromString(String buffer){
		return gtk_builder_add_from_string(*this, buffer, -1, NULL);
	}

	GObject* getObject(String name){
		return gtk_builder_get_object(*this, name);
	}

private:
	GtkBuilder* mBuilder;
};


#endif /* GTKBUILDER_H_ */
