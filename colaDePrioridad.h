#ifndef COLA_PRIORIDAD
#define COLA_PRIORIDAD


template <typename T>
class Cola{
	public:
		Cola(): siguiente(NULL), ultimo(NULL){}
		~Cola(){
			Nodo* actual = siguiente;
			while(actual != NULL){
				Nodo* aux = actual ->sig;
				delete(actual);
				actual = aux;
			}
		}
		void agregar(T* elem){
			if(siguiente == NULL){
				siguiente = new Nodo(elem);
				ultimo = siguiente;
			}
			else{
				ultimo->sig= new Nodo(elem);
				ultimo= ultimo->sig;
			}
		}

		T* primero (){
			return siguiente->elem;
		}

		void avanzar(){
			Nodo* aux = siguiente;
			siguiente = siguiente->sig;
			delete(aux);
		}
		bool haySiguiente (){
			return siguiente!= NULL;
		}

	private:
		struct Nodo
		{
			Nodo(T* elem): elem(elem), sig (NULL){}
			T* elem;
			Nodo* sig;
		};

		Nodo* siguiente;
		Nodo* ultimo;
};

#endif