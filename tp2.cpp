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
 * Se crea una clase matriz que contendra a las distintas operaciones que se pueden realizar con las matrices
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

        /**
         * El formato ELLPACK consiste de dos matrices densas para representar a una matriz dispersa. Se tiene un maximo de valores k
         * por fila que NO SON NULOS, y las matrices de la representacion tienen tamaño m*k
         */
        void representacion(int k){
            //la k probablemente se use solo para imprimir, ya que todos los datos ya estan en los nodos (indice, elemento, etc)
            struct Nodo * lista=inicio_lista;
            int cont=0;
            cout<<"DATOS"<<endl;
            while(lista!=NULL){
                for(int i=0;i<M;i++){
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
            
            //hago esto 2 veces pq no se como imprimir juntos sin que sea un desastre si se les ocurre algo les voy a querer mucho
            cout<<"INDICES"<<endl;
            lista=inicio_lista;
            while(lista!=NULL){
                for(int i=0;i<M;i++){
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


};

int main(){
    matriz mat;
    //mat.mat_normal[M][N]= 

    mat.crearLinkedList();
    mat.representacion(3);
}
