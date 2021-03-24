#include <stdio.h>
#include <stdlib.h>

//Definición de estructura que se encarga de almacenar libros.
typedef struct libro{ //los datos se encuentran en orden para facilitar lectura.
    char* titulo;
    char* autor;
    int anio;
    int est_num;
    char* est_sec;
    int piso;
    char* edificio;
    char* sede;
} libro;

typedef struct nodo{
    void* data;
    struct nodo* next;
    struct nodo* prev;
}nodo;

typedef struct Lista{
    nodo* first; //puntero al primer elemento
    nodo* current; //elemento acgtual
}Lista;

Lista* creaLista(){
    Lista* L= (Lista*)calloc(1,sizeof(Lista));
    L -> first = NULL;
    L -> current = NULL;
    return L;
}

void* first(Lista* L){ //apunta al primer lugar de la lista
    if(L->first && L->first->data){
        L->current = L->first;
        return L->current->data;
    }
    return NULL;
}

void* next(Lista* L){
    if(L->current->next && L->current->next != L->current){
        L->current = L->current->next;
        return L->current->data;
    }
    return NULL;
}

void pushFront(Lista* L, void*data){ //agrega un elemento al comienzo de la lista
    nodo* newDato=(nodo*)calloc(1,sizeof(nodo));
    newDato->next=newDato;
    newDato->prev=newDato;
    if(L->first){
        newDato->next=L->first;
        newDato->prev=L->first->prev;
        L->first->prev->next = newDato;
        L->first->prev=newDato;
    }
    L->first = newDato;
}

void pushBack(Lista* L, void* data){//Se agrega elemento al final de la lista
    nodo* newDato = (nodo*)calloc(1,sizeof(nodo));
    if(!L->first){
        L->first = newDato;
        L->first->next=newDato;
        L->first->prev=newDato;
    }
    else{
        newDato->prev=L->first->prev;
        newDato->next=L->first;
        newDato->prev->next=newDato;
        newDato->next->prev=newDato;
    }
}

void popCurrent(Lista* L){ //se elimina un elemento en la pos actual
    nodo* del=L->current;
    if(del->prev){
        del->prev->next=del->next;
    }
    else{
        L->first=del->next;
    }
    if (del->next){
        del->next->prev = del->prev;
    }
    free(del); //libera la memoria de del (eliminando el dato)
}

void popBack(Lista* L){ //se elimina el ultimo elemento de la lista
    L->current=L->first;
	while(L->current->next!=NULL){
		L->current=L->current->next;
	}
	popCurrent(L);
}

void popFront(Lista* L){ //Se elimina el primer elemento de la lista
	L->current=L->first;
	L->first=L->current->next;
	popCurrent(L);
	L->current=L->first;
}

int cargaArchivo(void){
    FILE* fp; //Puntero archivo
}

void AutoSync(void* L){ //se ingresan los datos de manera automática a la lista
    FILE *fp; //puntero al archivo csv
    fp=fopen("inventario.csv","r");//abre texto para lectyra
    if(fp==NULL){
        printf("ERROR en apertura de archivo \n"); 
        exit(0); //si no se abre encuentra archivo se cierra el programa
    }
    //Falta ingresar los datos linea por linea a la lista.
}
/*

                        FIN declaración Structs y funciones de struct


*/



int menu (void){
    int op = 10; //Se declara variable opción (esta se usa como operador de switch)
    while(op!=0){
        printf("Bienvenido a la Biblioteca!");
        printf(" MENU: \n 1. Agregar Libro \n 2. Eliminar Libro \n 3. Agregar Sede \n 4. Editar Libro \n 5. Buscar \n 0. Guardar y SALIR \n");
        printf(" Inresa una opción: ");
        scanf("%i",&op);
        switch(op){
            case 1:{//Agregar libro
                    printf("\nIngresar libro para agregar: ");
               break; 
            }
            case 2:{ //Eliminar libro

                break;
            }
            case 3:{ //Agregar Sede

                break;
            }
            case 4:{ //Editar Libro

                break;
            }
            case 5:{// BUSCAR

                break;
            }
            case 0:{// GUARDAR Y SALIR

                break;
            }
            break;
        }
    }
    
}
int main (void){
    menu();
    return 0;
}