/*
 * TreeSet.h
 *
 *  Created on: 19/07/2015
 *      Author: xmbeat
 */

#ifndef TREESET_H_
#define TREESET_H_
#include <Utils/ArrayList.h>
typedef struct _Node{
	struct _Node* parent; //parent node;
	struct _Node* left; //left node
	struct _Node* right; //right node
	const void* data; //data
	char color;//color
}Node;
typedef int (*Comparator)(const void *, const void*);


template <class T>
class TreeSet {
public:
	TreeSet(Comparator comparator);
	virtual bool insert(const T data);
	virtual T remove(const T data);
	virtual bool contains(const T data);
	virtual T get(T data);
	virtual T getFromIndex(int index);
	virtual int size();
	virtual void clear();
	virtual void clearAndDelete();
	virtual ArrayList<T> toArrayList();
	virtual ~TreeSet();
protected:
	void leftRotation(void *nodeX);
	void rightRotation(void *nodeY);
	void insertFixUp(void *node);
	void* search(const T data);
	void transplant(void *nodeU, void *nodeV);
	void* minimum (void* nodo);
	void removeFixUp(void* nodo);
	bool get2(void* nodo, T* data, int index, int *currentIndex);
	void toArrayList2(void* nodo, ArrayList<T> &array);
	void inordenDelete(void*parent, bool delData);
private:
	Comparator mComparator;
	int mSize;
	void *mRoot;
	void *mNil;
};


#include "TreeSet.cpp"
#endif /* TREESET_H_ */
