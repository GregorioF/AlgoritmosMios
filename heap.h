#ifndef Heap_h
#define Heap_h

#include <iostream>

bool tieneDosHijos(int a, int n){
	return a*2+2 < n;
}

int Der(int a){
	return (2*a)+2;
}

int Izq(int a){
	return (2*a)+1;
}
int Padre(int a){
	if(a%2==0) return (a/2) -1;
	else return a/2;
}
void swap(int &a, int & b){
	int aux= a;
	a=b;
	b=aux;
}

void subir(int a [], int posNum){
	
	while(posNum != 0){
		int padre= Padre(posNum);
		if(a[padre] > a[posNum]) {
			swap(a[padre], a[posNum]);
			posNum=padre;
		}
		else break;
	}
}

// abja el primer elemento del arreglo al que seria su posicione en el heap
// pre{a tiene q ser heap}
void bajar(int a[], int n){
	
	int posNum=0;
	while(tieneDosHijos(posNum, n)){
		int izq= Izq(posNum);
		int der= Der(posNum);		
		//si no esta en la posicion correcta
		if(a[izq]< a[posNum] || a[der]< a[posNum]){
			if( a[izq] > a[der]){
				swap(a[der], a[posNum]);
				posNum= der;
			}
			else{
				swap(a[izq], a[posNum]);
				posNum=izq;
			}

		}
		// si esta en la posicion correcta ya me salgo
		else break;
	}
	// evaluo el caso de q haya salido del while pero sin alcanzar la posicion correcta
	if(Izq(posNum) < n && Der(posNum) >= n){
		int izq= Izq(posNum);
		if(a[posNum] > a[izq]){
			swap (a[izq], a[posNum]);
		}
	}
}
/*
void heapify(int a [], int n){
	int final=0;
	while(final< n){
		subir(a, final);
		final ++;
	}
}
*/


bool tieneUnSoloHijo(int i, int n ){
	return Izq(i) == n-1;
}

void arreglarInv(int * a, int n , int i ){
	if( tieneUnSoloHijo(i, n) )
		if(a[Izq(i)] > a[i]) swap(a[Izq(i)], a[i]);
	
	else if(tieneDosHijos(i, n)){
		while(tieneDosHijos(i, n) && ( a[Izq(i)] > a[i] ||  a[Der(i)] > a[i] ) ){
			if(a[Izq(i)] > a[i]) {
				swap(a[Izq(i)], a[i]);
				i = Izq(i);
			}
			if(a[Der(i)] > a[i]){
				swap(a[Der(i)], a[i]);
				i = Der(i);
			}
		}

	}
}
void heapify(int* a, int n){
	int current = n/2;
	while(current >=  0){
		arreglarInv(a, n, current);
		current--;
	}
}


void heapSort(int a[], int n){
	heapify(a, n);
	int aux[n];
	int j=n;
	for(int i=0; i<n; i++){
		aux[i]= a[0];
		swap(a[0], a[j-1]);
		//std::cout << "\n"<< std::endl;
			
		j--;
		bajar(a,j);

	}
	/*std::cout << "\n"<< std:: endl;
	for(int i=0; i<n; i++) std::cout << aux[i] << ", " ;
	*/

}


#endif