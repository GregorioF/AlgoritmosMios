#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "avl.h"
#include "colaDePrioridad.h"
using namespace avl;
using namespace std;
int main(){
/*
	Dic<int> a ;
	int a1 = 5;
	int a2 = 2;
	int a3 = 6;
	int a4 = 3;
	int a5 = 1;
	int a6 = 0;

	a.Add (a1);
	a.Add (a2);
	a.Add (a3);
	a.Add (a4);
	a.Add (a5);
	a.Add (a6);
*/
	Dic<int> b;
	int b1 = 5;
	int b2 = 2;
	int b3 = 10;
	int b4 = 6;
	int b5 = 13;
	int b6 = 7;
	int b7 = 9;
	int b8 = 8;

	b.Add(b1);
	b.Add(b2);
	b.Add(b3);
	b.Add(b4);
	b.Add(b5);
	b.Add(b6);
	b.Add(b7);
	b.Add(b8);

	//b.Add(b4);
	b.mostrar();


	b.Delete(b7);
	//b.Delete(b8);
	b.Delete(b5);
	b.mostrar();
	b.Delete(2);	
	b.mostrar();
	b.Delete(5);
	b.mostrar();
	b.Delete(10);
	b.mostrar();
//	cout << "\n";

//	cout << "\n";

//	cout << "\n";


    return 0;
}
