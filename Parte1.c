#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---Definicion de estructuras---*/

typedef struct nodo{					// Se define el tipo struct nodo , contiene el exponente y el coeficiente
    int coeficiente;              		// de cada monomio. Además tiene 2 punteros, uno que apunta al siguiente nodo
    int exponente;						// y otro que apunta al nodo anterior (lista doblemente enlazada)
   	struct nodo* next;
	struct nodo* prev;
}nodo;

typedef struct lista{				   // Se define el tipo struct lista, contiene la cabeza, cola, el nodo actual en
	nodo *cabeza;				   	   // que se está y el tamaño de la lista
	nodo *cola;
	nodo *act;
	int tamano;
}lista;

/*---Definicion de Funciones---*/

/*****
*
void iniciarLista
******
*
funcion que inicia una lista vacia, asignando valores a sus principales variables.
******
*
Input:
*
lista *l : puntero tipo lista el cual apunta a una lista.
*
.......
******
*
Returns:
*
void, no retorna nada pero nos inicia las principales variables de nuestra
      estructura lista doblemente enlazada.
*****/

void iniciarLista(lista *l){
	l->cabeza=NULL;
	l->cola=NULL;
	l->act=NULL;
	l->tamano=0;
}

/*****
*
void agregar
******
*
funcion que agrega un nodo con la informacion entregada a una lista en especifica,
el nodo sera agregado al final de la lista.
******
*
Input:
*
int ex : Entero que indica el exponente del monomio a agregar (los nodos representan monomios)
int coef : Entero que indica el coeficiende del monomio a agregar
lista *l : Puntero de tipo lista que indica la lista a la que se agregara el nodo.
*
.......
******
*
Returns:
*
void, no retorna nada pero agrega el nodo a la lista entregada.
*****/

void agregar(int ex, int coef, lista *l){
    nodo *temp = (nodo*)malloc(sizeof(nodo));
    temp -> exponente = ex;																//Se crea un nodo el cual se le otorgan los datos
    temp -> coeficiente = coef;															// recibidos en el input (exponente y coeficiente)
    temp -> next = NULL;
	if (l->tamano != 0) {																// Hacemos que la cola apunte al nodo creado
		temp -> prev = l->cola;															// y luego el nodo creado pasa a ser la cola
  	l->cola->next = temp;
  	l->cola = temp;
	}
	else{
		l->cola = l->cabeza =temp;														// En caso de que la lista esté vacía, simplemente
	}																					// Hacemos que la cola y la cabeza apunte al nodo creado
    l->tamano ++;
}

/*****
*
void del
******
*
funcion que libera los espacios de memoria. (elimina los nodos)
******
*
Input:
*
lista *l : Puntero de tipo lista que apunta a la lista que se quiere borrar.

*
.......
******
*
Returns:
*
void, no retorna nada pero borra la lista correspondiente.
*****/

void del(lista *l) {
	int i;
	for (i = 0; i < l->tamano; i++) {									// para ello se va a la cola y luego al anterior a la cola, luego
		l->act=l->cola->prev;											// libera la memoria de la cola y vuelve un nodo atrás, así sucesivamente.
		free((void*)l->cola);
		l->cola=l->act;
	}
}

/*****
*
void siguiente
******
*
funcion que avanza al nodo siguiente de la lista desde la posicion actual (nodo act)
******
*
Input:
*
lista *l : Puntero de tipo lista, de la cual se quiere mover al siguiente nodo.

*
.......
******
*
Returns:
*
void, no retorna nada pero mueve el nodo act una posicion mas adelante.
*****/

void siguiente(lista *l){
    nodo *temp;
	temp = l->act->next;																//crea un nodo temporal para apuntar al siguiente del actual
	l->act = temp;																		// y luego el actual apunta al nodo guardado en el temporal.
}

/*****
*
int coeiciente
******
*
funcion que otorga el coeficiente pedido segun el exponente dado de un polinomio
especifico
******
*
Input:
*
lista *A : Arreglo del tipo lista donde se encuentran las listas que representan
a los polinomios obtenidos

*
.......
******
*
Returns:
*
int, retorna el coeficiente correspondiente.
*****/

int coeficiente(lista *A,int poli, int ex){
    int i, coef=0;
	(&A[poli])->act = (&A[poli])->cabeza;
    for(i=0;i<A[poli].tamano;i++){
        if(ex==(&A[poli])->act->exponente){												//Se recorre la lista usando la funcion "siguiente"
            return (&A[poli])->act->coeficiente;										// y se va comparando el exponente entregado con
        }																				// el del nodo actual.
        else{
            siguiente(&A[poli]);
        }
    }
	return coef;
}

/*****
*
int max
******
*
funcion que otorga el max exponente del polinomio (el nodo con el campo exponente mas
grande de la lista).
******
*
Input:
*
lista *A : Arreglo de tipo lista que contiene todas las listas obtenidas.
int poli : Entero que determina el polinomio del cual se quiere obtener el max exponente.
*
.......
******
*
Returns:
*
int, retorna el exponente mas grande del polinomio
*****/

int max(lista *A,int poli){
	int i,max=-1;
	if ((&A[poli])->act != (&A[poli])->cabeza){									//Se verifica que el nodo actual se encuentre
		(&A[poli])->act = (&A[poli])->cabeza;									// al inicio de la lista.
	}
	for(i=0;i<(&A[poli])->tamano;i++){
		if((&A[poli])->act->exponente>max){										//Se recorre la lista de manera que va revisando
			max = (&A[poli])->act->exponente;						 			// los exponentes, guardando el mayor.
		}
		siguiente(&A[poli]);
	}
	return max;

}

/*****
*
float evaluar
******
*
funcion que evalua el polinomio especificado con un valor determinado.
******
*
Input:
*
lista *A: Arreglo del tipo lista que contiene todas las listas obtenidas.

*
.......
******
*
Returns:
*
float, retorna el valor obtenido al evaluar el polinomio especificado con el valor
determinado.
*****/

float evaluar(lista *A, int poli, float x){
	float b;
	int m,maximo;
	maximo=max(A,poli);															 //Se obtiene el exponente maximo del polinomio
	b=coeficiente(A,poli,maximo);									 	         // con la funcion "max", luego guardamos el coeficiente
	for(m=maximo;m>0;m--){												 	     // que acompaña este exponente en b.
		b=b*x +coeficiente(A,poli,maximo-1);								     // Se hace un for desde el exponente mayor hasta 0, donde
	}											    				  	         // en cada iteracion se va realizando el algoritmo de Horner
	return b;																     // con la ayuda de la funcion "coeficiente"
}

//-------------------FIN DEL TDA---------------------------//

int main() {

	FILE *fp,*ff;                                                                  // Definicion de variables
	int cp,cm,ex,cf,i,k,pol;
	lista *pl;
	float x;
	char op[11];


	fp = fopen("entradaPolinomio.txt","r");                                        // apertura de archivo de entrada para eventual lectura
	if (fp==NULL) {
		printf("Error al abrir archivo de entrada\n");
		exit(1);
	}
	fscanf(fp,"%d",&cp);                                                           //extraccion de datos e insercion en nuestro TDA-PolinomioLista
	pl = (lista *)malloc(sizeof(lista)*cp);
	for (i = 0; i < cp; i++) {
		fscanf(fp,"%d",&cm);
		iniciarLista(&pl[i]);
		for (k = 0; k < cm; k++) {
			fscanf(fp,"%d %d",&ex,&cf);
			agregar(ex,cf,&pl[i]);
		}
	}
	ff=fopen("salidaPolinomio.txt","w");                                           // apertura archivo de salida para eventual escritura
	if (ff==NULL) {
		printf("Error al abrir archivo de salida\n");
		exit(1);
	}
	while (!feof(fp)) {                                                            // lectura y proceso de operaciones segun el archivo de entrada
		fscanf(fp,"%s %d %f\n",op,&pol,&x);
		if (strcmp(op,"COEFICIENTE")==0) {
			fprintf(ff, "%d\n",coeficiente(pl,pol,(int)x));
		}
		else if (strcmp(op,"EVALUAR")==0) {
			fprintf(ff, "%f\n",evaluar(pl,pol,x) );
		}
	}
	fclose(ff);                                                                    // cierre de archivos y liberacion de memoria usada
	fclose(fp);
	for (i = 0; i < cp; i++) {
		del(&pl[i]);
	}
	free((void*)pl);


	return 0;
}
