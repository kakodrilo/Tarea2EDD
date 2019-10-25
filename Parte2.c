#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*-------------------- INICIO DEL TDA POLINOMIO -----------------------*/

/*---Definicion de estructuras---*/

typedef struct elementos {        // Se define el tipo struct informacion para el campo
    int exponente;                // info de los nodos, contiene el exponente y el coeficiente
    int coeficiente;              // de cada monomio.
} elementos;

typedef struct n{                 // Se define el tipo struct nodo para los nodos del arbol
    elementos info;               // contiene la informacion y dos punteros, uno a cada hijo.
    struct n *hijoIzq;
    struct n *hijoDer;
} nodo;

typedef struct pa{                // Se define el tipo struct arbol, que contiene un puntero
    nodo *raiz;                   // a la raiz y la cantidad de nodos en el.
    int cant_nodos;
} p_arbol;

/*---Definicion de Funciones---*/

/*****
*
void iniciarArbol
******
*
funcion que inicia un arbol vacio, asigando valores a sus principales variables.
******
*
Input:
*
p_arbol *T : puntero tipo p_arbol el cual indica donde esta el arbol a iniciar.
*
.......
******
*
Returns:
*
void, no retorna nada pero nos inicia las principales variables de nuestra
      estructura ABB.
*****/

void iniciarArbol(p_arbol *T){
    T->raiz = NULL;
    T->cant_nodos = 0;
}

/*****
*
int Vacio
******
*
funcion para evaluar si un nodo esta vacio o en efecto si no esta apuntando
a nada.
******
*
Input:
*
nodo * T : puntero a un nodo del arbol
*
.......
******
*
Returns:
*
int , retorna 1 o 0 dependiendo si el nodo esta vacio o no respectivamente.
*****/

int Vacio(nodo *T) {
    return T == NULL;
}

/*****
*
void insertar
******
*
funcion que agrega un nodo con la informacion entregada a un arbol especifico,
el nodo sera insertado segun su exponente.
******
*
Input:
*
p_arbol *T : Puntero de tipo p_arbol que indica el arbol al que se agregara el nodo.

elementos info: struct de tipo elementos que contiene la informacion del nodo
                que se quiere agregar.
*
.......
******
*
Returns:
*
void, no retorna nada pero agrega el nodo al arbol entregado.
*****/

void insertar(p_arbol *T,elementos info){
    nodo *padre = NULL;                                                            // se definen dos punteros tipo nodo los cuales nos ayudaran
    nodo *actual = T->raiz;                                                        // a reccorrer el arbol.

    while (!Vacio(actual) && info.exponente != actual->info.exponente) {             // comenzamos a recorrer el arbol en hasta que el nodo actual
        padre = actual;                                                              // este vacio o el nodo ya se encuentre en el arbol
        if (info.exponente < actual->info.exponente) actual = actual->hijoIzq;
        else if (info.exponente > actual->info.exponente) actual = actual->hijoDer;
    }

    if(!Vacio(actual)) return;                                                      // si el nodo actual no esta vacio es porque el nodo ya esta
                                                                                    // en el arbol, por lo tanto no es necesario agrgarlo.

    if(Vacio(padre)){                                                               // si padre esta vacio quiere deceir que el arbol esta vacio
        T->raiz = (nodo *)malloc(sizeof(nodo));                                     // por lo tanto es necesario modificar la raiz.
        (T->raiz)->info = info;
        (T->raiz)->hijoIzq = (T->raiz)->hijoDer = NULL;
    }
    else if (info.exponente < padre->info.exponente) {                              // si el exponente a agregar es menor a al exponente del padre
        actual = (nodo *)malloc(sizeof(nodo));                                      // entonces se agrega un nuevo nodo en el lado izquiedo.
        padre->hijoIzq = actual;
        actual -> info = info;
        actual->hijoDer = actual->hijoIzq = NULL;
    }
    else if (info.exponente > padre->info.exponente) {                              // si el exponente a agregar es mayor al exponente del padre
        actual = (nodo *)malloc(sizeof(nodo));                                      // se agrega el nodo al lado derecho.
        padre->hijoDer = actual;
        actual->info = info;
        actual->hijoDer = actual->hijoIzq = NULL;
    }
    T->cant_nodos++;
}

/*****
*
void vaciarAux
******
*
funcion que libera los espacios de memoria desde un nodo especifico, para ello lo recorre
en post orden.
******
*
Input:
*
nodo *n : Puntero de tipo nodo en donde comenzara el recorrido en post orden

*
.......
******
*
Returns:
*
void, no retorna nada pero borra el arbol correspondiente al nodo entregado.
*****/


void vaciarAux(nodo *n) {
    if(n == NULL) return;
    vaciarAux(n->hijoIzq);
    vaciarAux(n->hijoDer);
    free((void *)n);
}

/*****
*
void vaciar
******
*
funcion que libera los espacios de memoria utilizados por el arbol, para ello
utiliza la funcion vaciarAux.
******
*
Input:
*
p_arbol *T : Puntero p_arbol que apunta al arbol que se desea vaciar.

*
.......
******
*
Returns:
*
void, no retorna nada pero borra el arbol entregado.
*****/

void vaciar(p_arbol *T) {
    vaciarAux(T->raiz);                                                             // se llama a la funcion vaciarAux, se le entrga la raiz
    T->raiz = NULL;                                                                 // del arbol. Ademas, cambiamos los valores del puntero a la
    T->cant_nodos = 0;                                                              // raiz y la cantidad de nodos en el arbol.
}

/*****
*
int buscarAux
******
*
funcion auxiliar para buscar el coeficiente segun el exponente, si el exponente
no esta en el arbol retorna 0.
******
*
Input:
*
nodo *n : Puntero de tipo nodo en donde comenzara la busqueda.

int ex : entero que indica el exponente del coeficiente buscado.

*
.......
******
*
Returns:
*
int, coeficiente segun el exponente entregado, 0 en caso de que no exista.
*****/

int buscarAux(nodo *n,int ex){
    if(n == NULL) return 0;
    if(n->info.exponente == ex) return n->info.coeficiente;
    if(ex < n->info.exponente) return buscarAux(n->hijoIzq,ex);
    else return buscarAux(n->hijoDer,ex);
}

/*****
*
int buscarCoeficiente
******
*
funcion que busca el coeficiente correspondiente al exponente entregado,
en caso de que este ultimo no exista retorna 0.
******
*
Input:
*
p_arbol *T : puntero al arbol en donde se desea buscar el coeficiente.

int pol : entero correspondiente al polinomio en donde se hara la busqueda.

int ex : entero correspondiente al exponente del que se desae buscar el coeficiente.

*
.......
******
*
Returns:
*
int, entero correspondiente al coeficiente del exponente entregado, retorna 0
     si el exponente no existe.
*****/

int buscarCoeficiente(p_arbol *T,int pol,int ex) {
    return buscarAux(T[pol].raiz,ex);                                             // se llama a la funcion buscarAux, se le entrega
}                                                                                 // la raiz del arbol para iniciar la busqueda.

/*****
*
void ver
******
*
fncion que edita la varible globla y, la cual guarda el maximo exponente
durante la busqueda.
******
*
Input:
*
elementos info : struct del tipo elementos que contiene el coeficiente y el exponente
a comparar.

*
.......
******
*
Returns:
*
void, no retorna nada pero edita la variable global que almacena el maximo exponente.
*****/

int y;  /* definimos una variable global para encontrar el maximo exponente*/

void ver(elementos info) {
    if (info.exponente>y) {
        y=info.exponente;
    }
}

/*****
*
void recorrer
******
*
funcion que recorre el arbol de un nodo especifico con la intencion de buscar
el maximo exponente.
******
*
Input:
*
nodo *n : nodo en donde se iniciara la busqueda.

*
.......
******
*
Returns:
*
void, no retorna nada pero edita la variable global y la cual guarda el valor
      del maximo exponente.
*****/

void recorrer(nodo *n) {                        //Funcion para encontrar el exponente maximo
    if (n != NULL) {
        recorrer(n->hijoDer);
        ver(n->info);
    }
}

/*****
*
float evaluar
******
*
funcion que evalua un polinomio segun valor entregado. Dentro de esta se utilizan
las funciones recorrer y buscarCoeficiente.
******
*
Input:
*
p_arbol *T : puntero al arreglo de arboles, contiene los polinomios.

int pol : entero correspondiente al polinomio en donde evaluara la variable entregada.

float x : float que corresponde a la variable a evaluar.

*
.......
******
*
Returns:
*
float, float con el resultado final de la evaluacion.
*****/

float evaluar(p_arbol *T,int pol,float x) {
    float b;
    y=0;                                                                            // Se inicia la variable global en 0
    int m;                                                                          // para buscar el maximo exponente.
    recorrer(T[pol].raiz);                                                          // Se recorre el arbol para buscar el maximo
    b = buscarCoeficiente(T, pol, y);                                               // para ello se le entrega la raiz del arbol.
    for(m=y;m>0;m--){
        b = b*x+buscarCoeficiente(T, pol,m-1);
    }
    return b;
}

//-------------------FIN DEL TDA---------------------------//

int main() {

    FILE *fp,*ff;                                                                   //definicion de variables a utilizar
    int cp,cn,i,k,pol;
    float x;
    p_arbol *pa;
    elementos info;
    char op[11];

    fp=fopen("entradaPolinomio.txt","r");                                           //apertura de archivo de entrada para eventual lectura
    if (fp==NULL) {
        printf("Error al abrir archivo de entrada\n");
        exit(1);
    }
    fscanf(fp,"%d",&cp);
    pa = (p_arbol *)malloc(sizeof(p_arbol)*cp);                                     //extraccion de datos e insercion en TDA-PolinomioArbol
    if (pa==NULL) {
        printf("Error de asigancion de memoria\n");
        exit(1);
    }
    for (i = 0; i < cp; i++) {
        iniciarArbol(&pa[i]);
        fscanf(fp,"%d",&cn);
        for (k = 0; k < cn; k++) {
            fscanf(fp,"%d %d",&info.exponente,&info.coeficiente);
            insertar(&pa[i],info);
        }
    }
    ff=fopen("salidaPolinomio.txt","w");                                            //apertura de archivo de salida para eventual escritura
    if (ff==NULL) {
        printf("Error al abir archivo de salida\n");
        exit(1);
    }
    while (!feof(fp)) {                                                             //lectura y proceso de operaciones segun el archivo de entrada
        fscanf(fp,"%s %d %f\n",op,&pol,&x);
        if (strcmp(op,"COEFICIENTE") == 0) {
            fprintf(ff,"%d\n",buscarCoeficiente(pa,pol,(int)x));
        }
        else if (strcmp(op,"EVALUAR") == 0) {
            fprintf(ff,"%f\n",evaluar(pa,pol,x));
        }
    }
    fclose(ff);                                                                     //cierre de archivos y liberacion de memoria utilizada
    fclose(fp);
    for (i = 0; i < cp; i++) {
        vaciar(&pa[i]);
    }
    free((void*)pa);

    return 0;
}
