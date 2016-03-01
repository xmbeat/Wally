/*
 * TreeSet.cpp
 *
 *  Created on: 19/07/2015
 *      Author: xmbeat
 */


#ifdef TREESET_H_
#include "TreeSet.h"

#define N_RED 0
#define N_BLACK 1
#ifndef NULL
#define NULL (void*)0
#endif


/*
 * Hace una rotación a la izquierda del nodo x, es necesario
 * que el nodo hijo derecho de x no sea nulo.
 */
template <class T>
void TreeSet<T>::leftRotation(void *nodeX){
	Node* x = (Node*) nodeX;
	Node* y = x->right;
	x->right = y->left;
	if (y->left != mNil){
		y->left->parent = x;
	}
	y->parent = x->parent;
	if(x->parent != mNil){
		if (x->parent->left == x){
			x->parent->left = y;
		}
		else{
			x->parent->right = y;
		}
	}
	else{
		mRoot = y;
	}
	y->left = x;
	x->parent = y;
}

/*
 * Hace una rotación a la derecha del nodo x, es necesario que
 * el nodo hijo izquierdo de x no sea nulo.
 */
template <class T>
void TreeSet<T>::rightRotation(void* nodeY){
	Node* y = (Node*)nodeY;
	Node* x = y->left;
	x->parent = y->parent; //x.parent = P
	y->left = x->right;
	if (y->parent != mNil){ //P.left || P.right = x
		if (y->parent->left == y){
			y->parent->left = x;
		}
		else{
			y->parent->right = x;
		}
	}
	else{ //No hay P, por lo tanto x es la raiz
		mRoot = x;
	}
	y->parent = x; //Y.parent = x
	if (x->right != mNil){
		x->right->parent = y; //β.parent = y
	}
	x->right = y; //x.right = Y
}

template <class T>
void TreeSet<T>::insertFixUp(void* nodo){
	Node* node = (Node*) nodo;
	while(node->parent->color == N_RED){
		Node* uncle;
		//Nodo padre es hijo izquierdo del nodo abuelo
		//(no hay que comprobar si existe el abuelo, ya que si el padre es rojo, entonces debe tener un padre negro)
		if (node->parent->parent->left == node->parent){
			uncle = node->parent->parent->right;
			//Si el tio es rojo, simplemente cambio de color al nodo padre, tio y abuelo
			//Como el abuelo se convierte en rojo, debemos corroborar que no viole la propiedad 4 (abuelo->parent != RED)
			//esto se logra en la siguiente iteración del bucle
			if (uncle->color == N_RED){
				uncle->color = N_BLACK;
				node->parent->color = N_BLACK;
				node = node->parent->parent;
				node->color = N_RED;
			}
			//El tio es negro, no podemos simplemente cambiar de color al padre, tio y abuelo, puesto que violarían la
			//propiedad 5
			else{
				//El nodo es hijo derecho, tengo que pasarlo al lado izquierdo para que queden tanto padre como hijo, del lado izquierdo
				//Y de esa manera hacer una rotación a la derecha.
				if (node->parent->right == node){
					leftRotation(node->parent);
					node = node->left;
				}
				node->parent->parent->color = N_RED;
				node->parent->color = N_BLACK;
				rightRotation(node->parent->parent);
			}
		}
		//Proceso simétrico
		else{
			uncle = node->parent->parent->left;
			if (uncle->color == N_RED){
				uncle->color = N_BLACK;
				node->parent->color = N_BLACK;
				node = node->parent->parent;
				node->color = N_RED;
			}
			else{
				if(node->parent->left == node){
					rightRotation(node->parent);
					node = node->right;
				}
				node->parent->parent->color = N_RED;
				node->parent->color = N_BLACK;
				leftRotation(node->parent->parent);
			}
		}
	}
	((Node*)mRoot)->color = N_BLACK;
}

template <class T>
void* TreeSet<T>::search(const T data){
	Node* aux = (Node*)mRoot;
	while(aux != mNil){
		int dif = mComparator(aux->data, data);
		//Encontramos al elemento
		if (dif == 0){
			break;
		}
		if (dif < 0){
			aux = aux->right;
		}
		else{
			aux = aux->left;
		}
	}
	return aux;
}

template <class T>
bool TreeSet<T>::insert(const T data){
	Node* aux = (Node*)mRoot;
	Node* parent = (Node*)mNil;
	int dif = 0;
	while(aux != mNil){
		dif = mComparator(data, aux->data);
		//Ya se había ingresado antes
		if (dif == 0){
			return 0;
		}
		parent = aux;
		if (dif < 0){
			aux = aux->left;
		}
		else{
			aux = aux->right;
		}
	}

	Node* node = new Node;
	if (parent != mNil){
		if(dif < 0){
			parent->left = node;
		}
		else{
			parent->right = node;
		}
	}
	else{
		mRoot = node;
	}
	node->data = data;
	node->parent = parent;
	node->left = (Node*)mNil;
	node->right = (Node*)mNil;
	node->color = N_RED;
	insertFixUp(node);
	mSize++;
	return 1;
}

template <class T>
void TreeSet<T>::transplant(void* nodeU, void* nodeV){
	Node* u = (Node*)nodeU;
	Node* v = (Node*)nodeV;
	if (u->parent == mNil){
		mRoot = v;
	}
	else if (u->parent->left == u){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

/*
 * regresa el elemento menor que se encuentra en este subarbol
 */
template <class T>
void* TreeSet<T>::minimum (void* nodo){
	Node*node = (Node*)nodo;
	while(node->left != mNil){
		node = node->left;
	}
	return node;
}
template <class T>
void TreeSet<T>::removeFixUp(void* nodo){
	Node* node = (Node*)nodo;
	while(node != mRoot && node->color == N_BLACK){
		if (node == node->parent->left){
			Node* hermano = node->parent->right;
			if (hermano->color == N_RED){
				hermano->color = N_BLACK;
				node->parent->color = N_RED;
				leftRotation(node->parent);
				hermano = node->parent->right;
			}
			if (hermano->left->color == N_BLACK && hermano->right->color == N_BLACK){
				hermano->color = N_RED;
				node = node->parent;
			}
			else{
				if (hermano->right->color == N_BLACK){
					hermano->left->color = N_BLACK;
					hermano->color = N_RED;
					rightRotation(hermano);
					hermano = node->parent->right;
				}
				hermano->color = node->parent->color;
				node->parent->color = N_BLACK;
				hermano->right->color = N_BLACK;
				leftRotation(node->parent);
				node = (Node*)mRoot;
			}

		}
		else{
			Node* hermano = node->parent->left;
			if (hermano->color == N_RED){
				hermano->color = N_BLACK;
				node->parent->color = N_RED;
				rightRotation(node->parent);
				hermano = node->parent->left;
			}
			if (hermano->left->color == N_BLACK && hermano->right->color == N_BLACK){
				hermano->color = N_RED;
				node = node->parent;
			}
			else{
				if (hermano->left->color == N_BLACK){
					hermano->right->color = N_BLACK;
					hermano->color = N_RED;
					leftRotation(hermano);
					hermano = node->parent->left;
				}
				hermano->color = node->parent->color;
				node->parent->color = N_BLACK;
				hermano->left->color = N_BLACK;
				rightRotation(node->parent);
				node = (Node*)mRoot;
			}
		}
	}
	node->color = N_BLACK;
}

template <class T>
T TreeSet<T>::remove(const T data){
	Node* node = (Node*)search(data);
	T ret = (T) node->data;
	Node* toFix = (Node*)NULL;
	if (node == mNil){
		//No se pudo remover, no existe
		return NULL;
	}

	char original_color = node->color;
	//Reemplazamos al nodo por su sucesor.
	//Si no tiene hijo izquierdo entonces simplemente cambiamos por su hijo derecho
	if (node->left == mNil){
		toFix = node->right;
		transplant(node, node->right);
	}
	else if(node->right == mNil){
		toFix = node->left;
		transplant(node, node->left);
	}
	else{
		Node* sucesor = (Node*)minimum(node->right);
		original_color = sucesor->color;
		toFix = sucesor->right;
		if (sucesor->parent == node){
			toFix->parent = sucesor;
		}
		else{
			transplant(sucesor, sucesor->right);
			sucesor->right = node->right;
			sucesor->right->parent = sucesor;
		}
		transplant(node, sucesor);
		sucesor->left = node->left;
		sucesor->left->parent = sucesor;
		sucesor->color = node->color;
	}
	if (original_color == N_BLACK){
		removeFixUp(toFix);
	}
	mSize--;
	return ret;
}
template <class T>
bool TreeSet<T>::contains(const T data){
	Node* node = (Node*)search(data);
	return node != mNil;
}

template <class T>
bool TreeSet<T>::get2(void* nodo, T* data, int index, int *current_index){
	Node* node = (Node*) nodo;
	if (node == mNil){
		return false;
	}
	int found = get2(node->left, data, index, current_index);
	if (found)
		return true;
	if (*current_index == index){
		*data = (T)node->data;
		return true;
	}
	else{
		*current_index += 1;
		return get2(node->right, data,index, current_index);
	}

}

template <class T>
T TreeSet<T>::getFromIndex(int index){
	T data = NULL;
	int n = 0;
	get2(mRoot, &data, index, &n);
	return data;
}

template <class T>
T TreeSet<T>::get(T data){
	Node *aux = (Node*)search(data);
	if (aux != mNil){
		return (T)aux->data;
	}
	else{
		return NULL;
	}
}

template <class T>
void TreeSet<T>::toArrayList2(void* nodo,  ArrayList<T> &array){
	Node* node = (Node*) nodo;
	if (node != mNil){
		toArrayList2(node->left, array);
		array.add((T) node->data);
		toArrayList2(node->right, array);
	}
}
template <class T>
ArrayList<T> TreeSet<T>::toArrayList(){
	if (mSize > 0){
		ArrayList<T> result;
		toArrayList2(mRoot, result);
		return result;
	}
	else{
		return ArrayList<T>();
	}
}




template <class T>
void TreeSet<T>::inordenDelete(void*nodo, bool delData){
	Node* parent = (Node*)nodo;
	if (parent != mNil ){
		Node* right = parent->right;
		inordenDelete(parent->left, delData);
		if (delData){
			delete (T)parent->data;
		}
		delete parent;
		inordenDelete(right, delData);
	}
}
template <class T>
void TreeSet<T>::clear(){
	if (mNil){
		inordenDelete(mRoot, false);
		mRoot = mNil;
		((Node*)mNil)->color = N_BLACK;
		mSize = 0;
	}
}

template <class T>
void TreeSet<T>::clearAndDelete(){
	if (mNil){
		inordenDelete(mRoot, true);
		mRoot = mNil;
		((Node*)mNil)->color = N_BLACK;
		mSize = 0;
	}
}
template <class T>
int TreeSet<T>::size(){
	return mSize;
}


template <class T>
TreeSet<T>::TreeSet(Comparator comparator){
	mComparator = comparator;
	mNil = new Node;
	mRoot = mNil;
	((Node*)mNil)->color = N_BLACK;
	mSize = 0;
}
template <class T>
TreeSet<T>::~TreeSet() {
	clear();
	delete (Node*) mNil;
}

#endif
