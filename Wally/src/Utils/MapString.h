/*
 * MapString.h
 *
 *  Created on: 27/07/2015
 *      Author: xmbeat
 */

#ifndef MAPSTRING_H_
#define MAPSTRING_H_

#include "TreeSet.h"
#include "String.h"
class Hoja{
public:
	String *key;
	void* data;
	Hoja(){
		key = 0;
		data = 0;
	}
	virtual ~Hoja(){
		if (key){
			delete key;
		}
	}
	virtual bool operator==(const Hoja &hoja){
		if (key == hoja.key){
			return true;
		}
		if (key != 0 && hoja.key != 0){
			return *key == *(hoja.key);
		}
		return false;
	}
};
static
int comparador(const void * hoja1, const void* hoja2){
	String *key1 = ((Hoja*)hoja1)->key;
	String *key2 = ((Hoja*)hoja2)->key;
	return strcmp(*key1, *key2);
}

template <class T>
class MapString{
private:
	TreeSet<Hoja*> *mContainer;
	Hoja* mAuxHoja;
public:
	MapString(){
		mContainer = new TreeSet<Hoja*>(comparador);
		mAuxHoja = new Hoja();
	}

	T get(String &key){
		mAuxHoja->key = &key;
		Hoja *hoja = mContainer->get(mAuxHoja);
		if (hoja){
			return (T)hoja->data;
		}
		return (T)0;
	}

	bool containsKey(String &key){
		mAuxHoja->key = &key;
		return mContainer->contains(mAuxHoja);
	}
	void clear(){
		mContainer->clearAndDelete();
	}
	void clearAndDelete(){
		for (int i = 0; i < mContainer->size(); i++){
			T data = (T) mContainer->getFromIndex(i)->data;
			if (data){
				delete data;
			}
		}
		mContainer->clearAndDelete();
	}
	T put(String &key, T data){
		mAuxHoja->key = &key;
		Hoja *hoja = mContainer->get(mAuxHoja);
		if (hoja){
			T aux = (T)hoja->data;
			hoja->data = data;
			return aux;
		}
		else{
			hoja = new Hoja();
			hoja->key = new String(key);
			hoja->data = data;
			mContainer->insert(hoja);
			return (T)0;
		}
	}
	virtual int size(){
		return mContainer->size();
	}
	virtual ArrayList<String> getKeys(){
		ArrayList<String> ret;
		ArrayList<Hoja*> aux = mContainer->toArrayList();
		for (int i = 0; i < aux.size(); i++){
			ret.add(*(aux.get(i)->key));
		}
		return ret;
	}
	virtual ~MapString(){
		mAuxHoja->key = 0;
		clear();
		delete mContainer;
		delete mAuxHoja;
	}
};



#endif /* MAPSTRING_H_ */
