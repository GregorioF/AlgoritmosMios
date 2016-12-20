#ifndef AVL_H 
#define AVL_H
#include <iostream>
#include "colaDePrioridad.h"

using namespace std;

namespace avl{

template <typename T, typename K >
class Dic{
public:

	/*******************************************************************************/
	Dic(){
		raiz = NULL;
		cant = 0 ;
	}
	/*******************************************************************************/
	~Dic(){
		destruir(raiz);
	}
	/*******************************************************************************/
	Dic(const Dic& otro);
	/*******************************************************************************/
	K Obtener(T clave){
		Nodo* actual = raiz;
		while(actual->elem != clave){
			if(actual->elem > clave ) actual= actual->izq;
			else actual = actual->der;
			if(actual == NULL){
				cout << "Buscaste un elemento que no pertenece al diccionario" << endl;
				actual = raiz;
				break;
			}
		}
		return actual->significado;
	}


	void Definir(T elem, K sign){
		cant++;
		if(raiz == NULL) raiz = new Nodo(NULL, elem, sign);
		else{
			Nodo* padre = raiz;
			Nodo* actual;
			
			if(padre->elem > elem) actual = padre->izq;
			else actual = padre->der;

			while(actual != NULL){
				padre = actual;
				if(padre->elem > elem) actual = padre->izq;
				else actual = padre->der;			
			}

			if(padre->elem > elem) 
				padre->izq = new Nodo(padre, elem, sign);
			
			else 
				padre->der = new Nodo(padre, elem, sign);
		
			//RECALCULO ALTURAS Y FB

			actual = padre;
			while(actual != NULL){
				actual -> h = max(altura(actual->izq), altura(actual->der))+1;
				if(fb(actual) == -2 || fb(actual) == 2) break;
				actual = actual->padre;
			}

			if(actual != NULL){
				if(fb(actual) < 0 ) rebalancearIzq(actual);
				else rebalancearDer(actual);
			}

		}
	}
	/*******************************************************************************/
	void Borrar(T elem){
		cant--;
		Nodo* actual = raiz;
		while(actual->elem != elem){
			if(elem > actual->elem) actual = actual->der;
			else actual = actual->izq;
			if(actual == NULL ) {
				cant++;
				cout << "Borraste un elemento que no esta en el diccionario"<<endl;
				break;
			}
		}
		if(actual != NULL){
		Nodo* n = actual->padre;   //N ES EL ULTIMO NODO DEL CUAL EMPIEZO A SUBIR Y RECORRO TODA LA RAMA AFECTADA
		Nodo* padre = actual->padre;
		if(actual == raiz ) eliminarRaiz(actual);
		else if(esHoja(actual)) eliminarHoja(actual);

		else if(tieneUnHijo(actual)) {
			eliminarConUnHijo(actual);
			if (esIzq(actual)) n = padre->izq;
			else n = padre->der;
		}

		else{
			Nodo* padre = actual->padre;
			Nodo* sucesor = proxSucesor(actual);

			sucesor->padre = actual->padre;
			if(esIzq(actual)) actual->padre->izq = sucesor;
			else actual->padre->der = sucesor;

			sucesor->izq = actual->izq;
			if(actual->izq !=NULL) actual->izq -> padre = sucesor;

			sucesor->der = actual->der;
			if(actual->der !=NULL) actual->der ->padre = sucesor;

			//el arbol ya esta sin el nodo que queria elminar, ahora qda rebalancear


			if(esIzq(actual))n = padre->izq;
			else n = padre->der;
			
			if(n->izq != NULL){
				n = n->izq;
				while(n->der != NULL) n = n->der;
				if(n ->izq != NULL) n = n->izq;
			}
		
		}

		delete(actual);

		//n = n->padre;
		while(n!=NULL){
			n->h = max( altura(n->izq), altura(n->der ))+1;
			if(fb(n)== -2) rebalancearIzq(n);
			if(fb(n)== 2 ) rebalancearDer(n);
			n = n->padre;
		}

		}
	}
	/*******************************************************************************/
	int size(){return cant;}
	/*******************************************************************************/


	void mostrar(){
		typename Dic<T,K>::IteradorBFS it = this->CrearIt();
		int niveles = 0;
		int cont=0 ;
		int i = 0;
		while(it.haySiguiente()){

			if(it.siguiente() != NULL) cout << it.siguiente()->elem << " ";
			else {
				cout << "N ";
				i++;
			}
			cont ++;
			if(cont == elevar(2,niveles)) {
				cout << "\n";
				if(i  == cont ) break;
				cont = 0;
				niveles++;
			
				i = 0;
			} 
			it.avanzar();
		}
		cout << "\n\n";
	}






private:	
/********************************************************************************************************/
//ESTRUCTURAS AUXILIARES
/********************************************************************************************************/


	struct Nodo
	{
		Nodo():padre(NULL), izq(NULL), der(NULL), h(1){}
		Nodo(Nodo* p, T & e, K & s): padre(p), izq(NULL), der(NULL), h(1), elem(e), significado(s){}

		T elem;
		K significado; 
		Nodo* padre;
		Nodo* izq;
		Nodo* der;
		int h;
	};

	
	Nodo* raiz;
	int cant;
	



	class IteradorBFS
	{
	public:
		IteradorBFS(){		}
		void avanzar(){
			Nodo* prim = camino.primero();
			if(prim != NULL){
				camino.agregar(prim->izq);
				camino.agregar(prim->der);
			}
			else{
				camino.agregar(NULL);
				camino.agregar(NULL);
			}
			camino.avanzar();
		}
		Nodo* siguiente(){
			return camino.primero();
		}
		bool haySiguiente(){
			return camino.haySiguiente();
		}


	private:
		IteradorBFS(Nodo* raiz){
			camino.agregar(raiz);
		}
		friend typename Dic<T,K>::IteradorBFS Dic<T,K>::CrearIt(); 

		Cola<Nodo> camino;
		
	};


	IteradorBFS CrearIt() {
		return IteradorBFS(raiz);
	}






	/*******************************************************************************/
	/*******************************************************************************/
	//OPERACIONES AUXILIARES
	/*******************************************************************************/
	/*******************************************************************************/


	bool esHoja(Nodo* n){
		return n->izq ==NULL && n->der == NULL;
	}

	bool tieneUnHijo(Nodo* n){
		return (n->izq == NULL && n->der !=NULL ) || (n->izq !=NULL && n->der ==NULL);
	}

	void eliminarRaiz(Nodo * n){
		int i =0 ;
	}

	void eliminarHoja(Nodo* actual){
		if(esIzq(actual)) actual->padre->izq = NULL;
		else actual->padre->der = NULL;
	}

	void eliminarConUnHijo(Nodo* actual){
		Nodo* padre = actual->padre;
		if(esIzq(actual)) padre->izq = actual->izq != NULL ? actual->izq : actual->der;
		else padre->der = actual->izq != NULL ? actual->izq : actual->der;
	}

	Nodo* proxSucesor(Nodo* a){
		Nodo * n = a->izq;
		while(n->der != NULL){
			n = n->der;
		}
		if(esHoja(n)) eliminarHoja(n);
		else eliminarConUnHijo(n);
		return n;
	}


	int elevar(int a, int b ){
		int res=a ;
		if(b == 0) return 1;
		for(int i = 1; i < b; i++ ) res = res*a;
		return res;
	}

	void destruir(Nodo* n){
		if(n != NULL){
			destruir(n->izq);
			destruir(n->der);
			delete(n);
		}
	}
	int fb(Nodo* n){
		return altura(n->der) - altura(n->izq);
	}
	int altura(Nodo* n){
		if(n == NULL) return 0;
		return n->h;
	}
	int max(int a, int b ){
		if(a>b)return a;
		return b;
	}

	bool esIzq(Nodo* n){
		if(n->padre->elem > n->elem) return true;
		return false;
	}

	bool esDer(Nodo* n){
		if(n->padre->elem >= n->elem) return true;
		return false;
	}

	void rebalancearIzq(Nodo* n){
		if(fb(n->izq) <= 0 ){
			Nodo* n2 = n->izq;

			n2->padre = n->padre;

			if(n->padre == NULL){n++; n--;}
			else if(esIzq(n)) n->padre->izq = n2;
			else n->padre->der = n2;

			n->izq = n2->der;
			if(n2->der != NULL ) n2->der->padre = n;
			
			n->padre = n2;
			n2->der = n;

			if(n == raiz) raiz = n2;

			n->h = max(altura(n->izq), altura(n->der))+1; 


		}
		else{
			//rotacion 1
			Nodo* n2 = n->izq;
			Nodo* n3 = n2->der;

			n3 -> padre = n2->padre;
			n2->padre->izq = n3;

			n2->der = n3->izq;
			if(n3->izq != NULL)n3->izq->padre = n2;
			
			n2->padre = n3;
			n3->izq = n2;

			n2->h = max(altura(n2->izq), altura(n2->der))+1;
			n3->h = max(altura(n3->izq), altura(n3->der))+1;

			//rotacion 2

			n2 = n->izq;

			n2->padre = n->padre;

			if(n->padre == NULL){n++; n--;}
			else if(esIzq(n)) n->padre->izq = n2;
			else n->padre->der = n2;

			n->izq = n2->der;
			if(n2->der != NULL)n2->der->padre = n;
			
			n->padre = n2;
			n2->der = n;

			n->h = max(altura(n->izq), altura(n->der))+1;
			if(n == raiz) raiz= n2;

		}
	}

	void rebalancearDer(Nodo* n){
		if(fb(n->der) >= 0 ){
			Nodo* n2 = n->der;

			n2->padre = n->padre;

			if(n->padre == NULL){n++; n--;}
			else if(esIzq(n)) n->padre->izq = n2;
			else n->padre->der = n2;

			n->der = n2->izq;
			if(n2->izq != NULL ) n2->izq->padre = n;
			
			n->padre = n2;
			n2->izq = n;

			if(n == raiz) raiz = n2;

			n->h = max(altura(n->izq), altura(n->der))+1; 


		}
		else{
			//rotacion 1
			Nodo* n2 = n->der;
			Nodo* n3 = n2->izq;

			n3 -> padre = n2->padre;
			n2->padre->der = n3;

			n2->izq = n3->der;
			if(n3->der != NULL)n3->der->padre = n2;
			
			n2->padre = n3;
			n3->der = n2;

			n2->h = max(altura(n2->izq), altura(n2->der))+1;
			n3->h = max(altura(n3->izq), altura(n3->der))+1;

			//rotacion 2

			n2 = n->der;

			n2->padre = n->padre;

			if(n->padre == NULL){n++; n--;}
			else if(esIzq(n)) n->padre->izq = n2;
			else n->padre->der = n2;

			n->der = n2->izq;
			if(n2->izq != NULL)n2->izq->padre = n;
			
			n->padre = n2;
			n2->izq = n;

			n->h = max(altura(n->izq), altura(n->der))+1;
			if(n == raiz) raiz= n2;



		
		}

	}

};


}


#endif