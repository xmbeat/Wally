/*
 * GtkFileFilterEx.h
 *
 *  Created on: 20/07/2015
 *      Author: xmbeat
 */

#ifndef GTKFILEFILTEREX_H_
#define GTKFILEFILTEREX_H_

#include "GtkWidgetEx.h"
#include <Utils/String.h>

class GtkFileFilterEx{
public:
	GtkFileFilterEx(){
		mFilter = gtk_file_filter_new();
	}
	virtual operator GtkFileFilter*(){
		return mFilter;
	}
	void setName(const char* name){
		gtk_file_filter_set_name(*this, name);
	}
	String getName(){
		return gtk_file_filter_get_name(*this);
	}
	void addMimeType(const char* mimeType){
		gtk_file_filter_add_mime_type(*this, mimeType);
	}
	void addPattern(const char* pattern){
		gtk_file_filter_add_pattern(*this, pattern);
	}
	void addPixbufFormats(){
		gtk_file_filter_add_pixbuf_formats(*this);
	}

private:
	GtkFileFilter* mFilter;
};


#endif /* GTKFILEFILTEREX_H_ */
