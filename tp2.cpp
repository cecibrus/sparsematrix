#include <cstdlib>
#include <iostream>

using namespace std;

#define M 4
#define N 5

/*Se crea un struct Nodo que se utilizara para la lista enlazada que representara a la representacion 
 en su formato ELLPACK */
struct Nodo{
    int pos_columna;
    int pos_fila;
    int valor;
    struct Nodo *sgte;
};

void crear_nodo(struct Nodo **primero, int elemento, int fila, int columna){
    struct Nodo *aux;
    aux=*primero;
    if(aux==NULL){ //la lista esta vacia, no hay ningun Nodo aun
        //se crea un nuevo Nodo con memoria dinamica
        aux=(struct Nodo *)malloc(sizeof(struct Nodo));
        aux->valor=elemento;
        aux->pos_fila=fila;
        aux->pos_columna=columna;
        aux->sgte=NULL;
        *primero=aux;
    }else{
        while (aux->sgte!=NULL){ //se busca el ultimo elemento de la lista para agregar el nuevo Nodo al final de esta
            aux=aux->sgte;
        } //cuando se encuentra, se agrega el nuevo nodo al final de la lista
        struct Nodo *f;
        f=(struct Nodo *) malloc(sizeof(struct Nodo));
        f->valor=elemento;
        f->pos_fila=fila;
        f->pos_columna=columna;
        f->sgte=NULL;
        aux->sgte=f;
    }
}

//declaraciones de las funciones para poder utilizarlas mas abajo antes de que sean definidas
Nodo* sort(Nodo* a, Nodo* b); 
void division(Nodo* source, Nodo** frente, Nodo** fondo);

// Se hace un merge sort para ordenar la lista enlazada con los datos de la representacion transpuesta
void mergeSort(Nodo** comienzo){ 
    Nodo* cabeza = *comienzo; 
    Nodo* a; 
    Nodo* b; 
  
    if ((cabeza == NULL) || (cabeza->sgte == NULL)) { 
        return; 
    } 
  
    division(cabeza, &a, &b); 
  
    mergeSort(&a); 
    mergeSort(&b); 
    *comienzo = sort(a, b); 
} 

Nodo* sort(Nodo* a, Nodo* b) { 
    Nodo* res = NULL; 
  
    /* Casos base */
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 

    if (a->pos_fila <= b->pos_fila) { 
        res = a; 
        res->sgte = sort(a->sgte, b); 
    }else if(a->pos_fila == b->pos_fila){
        if(a->pos_columna <= b->pos_columna){
            res=a;
            res->sgte = sort(a->sgte,b);
        }else{
            res = b; 
            res->sgte = sort(a, b->sgte);
        }
    }else { 
        res = b; 
        res->sgte = sort(a, b->sgte); 
    } 
    return (res); 
} 

void division(Nodo* source, Nodo** frente, Nodo** fondo){ 
    Nodo* rap; 
    Nodo* len; 
    len = source; 
    rap = source->sgte; 
 
    while (rap != NULL) { 
        rap = rap->sgte; 
        if (rap != NULL) { 
            len = len->sgte; 
            rap = rap->sgte; 
        } 
    } 
 
    *frente = source; 
    *fondo = len->sgte; 
    len->sgte = NULL; 
} 


//Se crea una clase matriz que contiene a las distintas operaciones que se pueden realizar con las matrices
class matriz{
    public:
        struct Nodo *inicio_lista= NULL; //el puntero al nodo en el que inicia la lista enlazada
        //metodos
        void crearLinkedList(int mat_normal[M][N]);
        int find_k(Nodo * lista_inicio, int fila);
        void representacion(struct Nodo *inicio_lista, int fila);
        struct Nodo * transpuesta();
        void obtener_fila(struct Nodo * inicio_lista, int fila);
        void obtener_columna(struct Nodo * inicio_lista, int col);

};

void matriz:: crearLinkedList(int mat_normal[M][N]){
    int i,j;
    //se recorre la representacion buscando elementos que no sean 0 para agregarlos a la lista enlazada
    for(i=0;i<M;i++){
        for(j=0;j<N;j++){
            if(mat_normal[i][j]!=0){
                crear_nodo(&inicio_lista,mat_normal[i][j],i,j);
            }
        }
    }
};


int matriz :: find_k(Nodo * lista_inicio, int fila){
    struct Nodo *lista= lista_inicio;
    int cont,i,k=0;
    for(i=0;i<fila;i++){
        cont=0;
        while (lista!=NULL && lista->pos_fila==i){
            cont++;
            lista=lista->sgte;
        }
        if(cont>k){
            k=cont;
        }
    }
    return k;
};

/*El formato ELLPACK consiste de dos matrices densas para representar a una representacion dispersa.
Se tiene un maximo de valores k por fila que NO SON NULOS, y las matrices de la representacion tienen tamaÃ±o m*k
*/
void matriz :: representacion(struct Nodo *inicio_lista, int fila){
    struct Nodo * lista=inicio_lista;
    int cont=0,k;
    k=find_k(inicio_lista, fila);
    //cout<<"esta es k"<<k<<endl;

    cout<<"DATOS"<<endl;
    while(lista!=NULL){
        for(int i=0;i<fila;i++){
            for(cont=0;cont<k;cont++){
                if(lista==NULL || (lista->pos_fila)>i){
                    cout<<"*"<<" ";
                }else{
                    cout<<lista->valor<<" ";
                    lista=lista->sgte;
                }
            }
            cout<<endl;
        }
     }
            
    cout<<"INDICES"<<endl;
    lista=inicio_lista;
    while(lista!=NULL){
        for(int i=0;i<fila;i++){
            for(cont=0;cont<k;cont++){
                if(lista==NULL || (lista->pos_fila)>i){
                    cout<<"*"<<" ";
                }else{
                    cout<<lista->pos_columna<<" ";
                    lista=lista->sgte;
                }
            }
            cout<<endl;
        }
    }
};


struct Nodo * matriz :: transpuesta(){

    struct Nodo * lista = inicio_lista;
    struct Nodo * transpuesta = NULL;
    while(lista!=NULL){
        crear_nodo(&transpuesta, lista->valor, lista->pos_columna, lista->pos_fila);
        lista=lista->sgte;
    }

    mergeSort(&transpuesta);

    return transpuesta;
}

/*La funcion obtener_fila, recibe como parametros una representacion y un entero fila, e  
imprime la fila asociada correspondiente a la matriz dispersa*/
void matriz :: obtener_fila(struct Nodo * inicio_lista, int fila){
    int i;
    struct Nodo * lista= inicio_lista;
    int vector[N]= {0,0,0,0,0};//ceramos el vector de manera que vamos modificando solo las posiciones con los datos 
     // utiles de la representacion correspondiente a la fila
    while(lista!=NULL){
        if(fila==lista->pos_fila){
            vector[lista->pos_columna] =lista->valor;
            lista=lista->sgte;
        }else{
            lista=lista->sgte;
        }
    }
    cout << "LA FILA " << fila << "  ESTA ASOCIADA A\t";
    for(i=0; i<N; i++){
        cout << vector[i] << "\t";
    }
}

/*La funcion obtener_columna, recibe como parametros una representacion y un entero col, e  
imprime la columna asociada correspondiente a la matriz dispersa*/
void matriz:: obtener_columna(struct Nodo * inicio_lista, int col){
    int i;
    struct Nodo * lista= inicio_lista;
    int vector[M]= {0,0,0,0}; //ceramos el vector de manera que vamos modificando solo las posiciones con los datos
       //utiles de la representacion correspondiente a la columna
    while(lista!=NULL){
        if(col==lista->pos_columna){
            vector[lista->pos_fila] =lista->valor;
            lista=lista->sgte;
        }else{
            lista=lista->sgte;
        }
    }
    cout << "\n\nLA COLUMNA " << col << "  ESTA ASOCIADA A\n";
    for(i=0; i<M; i++){
        cout << vector[i] << endl;
    }
}

//P R O G R A M A     P R I N C I P A L 
int main(){

    int mat_normal[M][N]={ 
        {0 , 0 , 3 , 0 , 4 }, 
        {0 , 0 , 5 , 7 , 0 }, 
        {0 , 0 , 0 , 0 , 0 }, 
        {0 , 2 , 6 , 0 , 0 } 
    };

    matriz mat;

    mat.crearLinkedList(mat_normal);
    cout << "REPRESENTACION DE LA MATRIZ DISPERSA\n";
    mat.representacion(mat.inicio_lista, M);
    
    cout<<"\n\nREPRESENTACION DE LA TRANSPUESTA\n";
    struct Nodo * transp;
    transp=mat.transpuesta();
    mat.representacion(transp,N);
    cout << endl;
    mat.obtener_fila(mat.inicio_lista, 3);
    mat.obtener_columna(mat.inicio_lista, 4);
    return 0;
}
