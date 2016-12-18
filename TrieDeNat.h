#ifndef Trie_Nat
#define	Trie_Nat

#include <iostream>
#include <math.h>
using namespace std;

class Tnat{
public:
	Tnat();
	Tnat(const Tnat & otro);
	~Tnat();
	void definir(int nat);
	bool definido(int nat);
	
private:
	struct Nodo{
		Nodo():valido(false), padre(NULL){
			for(int i=0; i<10; i++) digitos[i]=NULL;
		}
		Nodo(Nodo* p): valido(false), padre(p){
			for(int i=0; i<10; i++) digitos[i]=NULL;
		}
		bool valido;
		Nodo* padre;
		Nodo* digitos[10];
	};
	Nodo* raiz;
	int cantidad;
	void todosEnCero(int natAux []){
		for (int i=0; i<50; i++) natAux[i]=0;
	}
	void Aarray(int natAux [], int nat){
		int natActual=nat;
		int acumulador=nat%10;
		int i=0;
		while(natActual!=0){
			natAux[i]=acumulador;
			acumulador= acumulador* pow(10,i);
			natActual= natActual- acumulador;
			acumulador= natActual ;
			acumulador= acumulador / pow(10, i+1);
			acumulador= acumulador % 10;
			i++; 
		}
	}
	int largoDelNum(int natAux []){
		int i=49;
		while(natAux[i]==0){
			i--;
		}
		return i+1;
	}
	void BorrarTodo(Nodo* actual){
		if(actual != NULL){
			for(int i=0; i< 10; i++) BorrarTodo(actual->digitos[i]);
			delete (actual) ;
		}
	}
	

};
Tnat::Tnat(): cantidad(0){
	raiz=new Nodo();
}

Tnat::~Tnat(){
	BorrarTodo(raiz);
	raiz = NULL;
}


void Tnat::definir(int nat){
	int natAux[50];
	todosEnCero(natAux);
	Aarray(natAux, nat);
	int largo= largoDelNum(natAux);
	int i=0;
	Nodo* actual= raiz;
	while(largo>0){
		if(actual->digitos[natAux[i]]==NULL) actual->digitos[natAux[i]]=new Nodo(actual);
		actual= actual->digitos[natAux[i]];
		i++;
		largo --;
	}
	actual ->valido = true;
	cantidad ++;
}

bool Tnat::definido(int nat){
	Nodo* actual = raiz;
	int natAux[50];
	todosEnCero(natAux);
	Aarray(natAux, nat);
	int largo= largoDelNum(natAux);
	int i=0;
	while(largo > 0 && actual !=NULL){
		actual = actual->digitos[natAux[i]];
		i++;
		largo--;
	}
	if(actual== NULL) return false;
	else return actual->valido;

}

#endif