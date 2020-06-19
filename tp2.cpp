#include <cstdlib>
#include <iostream>

using namespace std;

#define M 8
#define N 7

/**
 *Se crea un struct Nodo que se utilizara para la lista enlazada que representara a la matriz en su formato ELLPACK 
 */
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

/**
 * Se hace un merge sort para ordenar la lista enlazada con los datos de la matriz transpuesta
*/
Nodo* SortedMerge(Nodo* a, Nodo* b); 
void division(Nodo* source, Nodo** frontRef, Nodo** backRef);

void MergeSort(Nodo** cabezaRef){ 
    Nodo* cabeza = *cabezaRef; 
    Nodo* a; 
    Nodo* b; 
  
    /* Caso base -- longitud 0 o 1 */
    if ((cabeza == NULL) || (cabeza->sgte == NULL)) { 
        return; 
    } 
  
    division(cabeza, &a, &b); 
  
    MergeSort(&a); 
    MergeSort(&b); 
    *cabezaRef = SortedMerge(a, b); 
} 

Nodo* SortedMerge(Nodo* a, Nodo* b) { 
    Nodo* result = NULL; 
  
    /* Casos base */
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 

    if (a->pos_fila <= b->pos_fila) { 
        result = a; 
        result->sgte = SortedMerge(a->sgte, b); 
    }else if(a->pos_fila == b->pos_fila){
        if(a->pos_columna <= b->pos_columna){
            result=a;
            result->sgte = SortedMerge(a->sgte,b);
        }else{
            result = b; 
            result->sgte = SortedMerge(a, b->sgte);
        }
    }else { 
        result = b; 
        result->sgte = SortedMerge(a, b->sgte); 
    } 
    return (result); 
} 

void division(Nodo* source, Nodo** frontRef, Nodo** backRef){ 
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
 
    *frontRef = source; 
    *backRef = len->sgte; 
    len->sgte = NULL; 
} 

/**
 * Se crea una clase matriz que contfinra a las distintas operaciones que se pueden realizar con las matrices
*/
class matriz{
    public:
        int mat_normal[M][N]={ 
        {0 , 2 , 0 , 0 , 0 , 0 , 4 }, 
        {0 , 8 , 9 , 0 , 0 , 1 , 0 },
        {0 , 0 , 0 , 3 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 0 , 0 , 0 },
        {5 , 0 , 0 , 0 , 0 , 6 , 0 },
        {1 , 2 , 0 , 0 , 0 , 0 , 0 },
        {4 , 0 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 7 , 0 , 0 , 11 , 0 }
        }; //el array que contiene la matriz dispersa
        struct Nodo *inicio_lista= NULL; //el puntero al nodo en el que inicia la lista enlazada

        void crearLinkedList(){
            int i,j;
            //se recorre la matriz buscando elementos que no sean 0 para agregarlos a la lista enlazada
            for(i=0;i<M;i++){
                for(j=0;j<N;j++){
                    if(mat_normal[i][j]!=0){
                        crear_nodo(&inicio_lista,mat_normal[i][j],i,j);
                    }
                }
            }
        };

        int find_k(){
            struct Nodo *lista=inicio_lista;
            int cont,i,k=0;
            for(i=0;lista!=NULL;i++){
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

        /**
         * El formato ELLPACK consiste de dos matrices densas para representar a una matriz dispersa. Se tiene un maximo de valores k
         * por fila que NO SON NULOS, y las matrices de la representacion tienen tamaño m*k
         */
        void representacion(struct Nodo *inicio_lista, int fila){
            //la k probablemente se use solo para imprimir, ya que todos los datos ya estan en los nodos (indice, elemento, etc)
            struct Nodo * lista=inicio_lista;
            int cont=0,k;
            k=find_k();

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
            
            //hago esto 2 veces pq no se como imprimir juntos sin que sea un desastre si se les olistare algo les voy a querer mucho
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
        }

        struct Nodo * transpuesta(){
            //para obtener la matriz transpuesta basta simplemente con intercambiar las filas con las columnas. Por ej, si un elemento estaba 
            //en i=2 j=3, en la transpuesta esta en i=3 j=2

            struct Nodo * lista = inicio_lista;
            struct Nodo * transpuesta = NULL;
            while(lista!=NULL){
                crear_nodo(&transpuesta, lista->valor, lista->pos_columna, lista->pos_fila);
                lista=lista->sgte;
            }

            MergeSort(&transpuesta);

            return transpuesta;
        }


};

int main(){
    matriz mat;

    mat.crearLinkedList();
    mat.representacion(mat.inicio_lista, 8);

    cout<<"TRANSPUESTA"<<endl;
    struct Nodo * transp;
    transp=mat.transpuesta();
    mat.representacion(transp,7);

}        
