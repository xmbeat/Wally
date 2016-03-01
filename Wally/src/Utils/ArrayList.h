/*
 * ArrayList.h
 *
 *  Created on: 19/07/2015
 *      Author: xmbeat
 */

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_
#include "List.h"
template <class T>
class ArrayList: public List<T>
{
public:
	ArrayList();
	ArrayList(int initialCapacity);
	ArrayList(List<T>*c);
	ArrayList(const ArrayList<T> &c);
	virtual ~ArrayList();
	virtual ArrayList& operator=(const ArrayList<T> &a);
	virtual T operator[](int index)const;
	virtual T &operator[](int index);
	virtual bool operator==(const ArrayList<T> &a);
	virtual T get(int index);
	virtual bool add(T element);
	virtual bool add(int index, T element);//Inserta un elemento
	virtual bool addAll(List<T>*c);
	virtual bool addAll(int index, List<T>*c);
	virtual void clear();//Elimina la lista, pero no los elementos
	virtual void ensureCapacity(int minCapacity);
	virtual int indexOf(T element);
	virtual bool isEmpty();
	virtual int lastIndexOf(T element);
	virtual T remove(int index);
	virtual bool removeAll(List <T>*c);
	virtual bool retainAll(List <T>*c);
	virtual List<T>* subList(int fromIndex, int toIndex);
	virtual ArrayList<T> subArrayList(int fromIndex, int Index);
	virtual bool containsAll(List<T>*c);
	virtual T set(int index, T element);
	virtual int size();
	virtual T* toArray();
protected:
	void removeRange(int fromIndex, int toIndex);
	void initialize(int minCapacity);
	void shiftElements(int fromIndex, int shift);
	bool isValidIndex(int index)
	{
		return (index>=0 && index<_size);
	}
	int _step;
	int _size;
	int _capacity;
	T*  _arreglo;
};

//=========POR SI SON PUNTEROS==========//
template <class T>
class ArrayList<T*>:public List<T*>
{
    public:
        ArrayList();
        ArrayList(int initialCapacity);
        ArrayList(const ArrayList<T*> &c):_arreglo(0)
        {
            *this = c;
        }
        ArrayList(List <T*> *c);
        virtual ArrayList<T*>& operator=(const ArrayList<T*> &a);
        virtual T* operator[](int index) const;
        virtual T*& operator[](int index);
        virtual ~ArrayList() {delete []_arreglo;}

        virtual bool add(int index, T *element);//Inserta un elemento
        virtual bool add(T *element);
        virtual bool addAll(List<T*>*c);
        virtual bool addAll(int index, List<T*> *c);
        virtual void clear();//Elimina la lista, pero no los elementos
        virtual void clearAndDelete();
        virtual bool contains(T *element);//En objetos que estan en el Stack no tiene efecto
        virtual bool containsAll(List<T*>*c);
        virtual bool isEmpty();
        virtual T* remove(int index);
        virtual bool remove(T *element);
        virtual bool removeAll(List <T*>*c);
        virtual bool retainAll(List <T*>*c);
        virtual T* get(int index);
        virtual int indexOf(T *element);//Indice de una la primera ocurrencia
        virtual int lastIndexOf(T *element);
        virtual void removeAndDelete(int index);//Remueve y elimina el objeto segun el indice, desastrozo si el objeto es de la pila
        virtual T* set(int index, T* element);
        virtual void setAndDelete(int index, T*);
        virtual int size();
        virtual void ensureCapacity(int minCapacity);
        virtual T** toArray();
        virtual void trimToSize();
        virtual List<T*> *subList(int fromIndex, int toIndex);//IMPLEMENTAR ESTE
    protected:
        void removeRange(int fromIndex, int toIndex);
        void initialize(int minCapacity);
        void shiftElements(int fromIndex, int shift);
        bool isValidIndex(int index,bool final = false)
        {
            if (final)
                return (index>=0 && index<=_size);
            else
                return (index>=0 && index < _size);
        }
        int _step;
        int _size;
        int _capacity;
        T** _arreglo;
};

#include "ArrayList.cpp"

#endif /* ARRAYLIST_H_ */
