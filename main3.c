#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Definición de estructura que se encarga de almacenar libros,
//nodos y lista enlazada para libros
typedef struct libro{ //los datos se encuentran en orden para facilitar lectura.
    char* titulo[128];
    char* autor[128];
    char* anio[4];
    char* est_num[2];
    char* est_sec[128];
    char* piso[2];
    char* edificio[128];
    char* sede[128];
} libro;
typedef struct nodo{
    struct libro data;
    struct nodo* next;
    struct nodo* prev;
}nodo;
typedef struct Lista{
    nodo* first; //puntero al primer elemento
    nodo* current; //elemento actual, usado para busquedas, actualizar y eliminar
    nodo* last; //x ultimo elemento
    int size; //x tamaño Lista
}Lista;
Lista* creaLista(){
    Lista* L= (Lista*)calloc(1,sizeof(Lista));
    L -> first = NULL;
    L -> current = NULL;
    L -> last = NULL;
    L -> size = 0;
    return L;
}
// Lista enlazada para secciones

typedef struct nodoSeccion{
    char est_sec[128];
    int nn;
    struct nodoSeccion* next;
    struct nodoSeccion* prev;
}nodoSeccion;

typedef struct ListaSeccion{
    nodoSeccion* first; //puntero al primer elemento
    nodoSeccion* current; //elemento actual
    nodoSeccion* last; //x ultimo elemento
    int size; //x 
}ListaSeccion;
ListaSeccion* creaListaSeccion(){
    ListaSeccion* LS= (ListaSeccion*)calloc(1,sizeof(ListaSeccion));
    LS -> first = NULL;
    LS -> current = NULL;
    LS -> last = NULL;
    LS -> size=0; //x 
    return LS;
}
int encuentraSeccion(ListaSeccion *LS, char *est_sec[128]){ 
  //determina si existe una secccion en la lista LS
  // retorna 0: Seccion existe en la lista LS / 1: Seccion no existe en la lista LS
  nodoSeccion* nodo;
  nodo = LS->first; /* punto de inicio el 1er elemento */
  while(nodo != NULL){
      if (!strcmp(nodo->est_sec, est_sec)) {
        LS->current = nodo;
        return 0; // se encuentra seccion en LS
      }
      nodo = nodo->next;
  }//
  return 1;   // no se encuentra seccion en LS
}

int insertSeccion(ListaSeccion* LS,  char* est_sec[128]){ 
  //agrega un elemento al final de la lista LS
  // retorna 0: Seccion agregada existosamente la lista LS / 1: Seccion no agregada ya existe en lista LS
  if (encuentraSeccion(LS, est_sec)) { //Si no existe se agrega
    nodoSeccion* newSec=(nodoSeccion*)calloc(1,sizeof(nodoSeccion));
    strcpy(newSec->est_sec, est_sec);
    newSec->next = NULL;
    newSec->prev = NULL;
    newSec->nn=LS->size;
    if(LS->first != NULL){ 
        LS->last->next = newSec;
        newSec->prev = LS->last;
        LS->last = newSec;
    }
    else {
        LS->first = newSec;
        LS->last  = newSec;
    }
    LS->current   = newSec;
    LS->size++;
    return 0;
  }
  return 1;
}
void listarSecciones(ListaSeccion* LS) {// Imprime listado de libros
  printf("Listado de Secciones\n\n");
  printf("Seccion\n");
  printf("-----------------------\n");
  int i=0;
  nodoSeccion* nodo;
  nodo = LS->first; /* punto de inicio el 1er elemento */ 
  while(nodo != NULL){
      i++;
      printf("%d %s \n", i, nodo->est_sec);
      nodo = nodo->next;
 }
  printf("----------------------\n");
}

void agregaSeccion(ListaSeccion* LS){ //agrega seccion en lista LS
    char est_secp[128];
    char str[128];
    char temp;
    printf("\nIngresar nueva seccion\n"); 
    printf("\nIngrese Estante Seccion (sin comillas): ");      
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",est_secp);
    //Agrega comillas a seccion
    snprintf(str, sizeof est_secp, "%s%s%s", "\"", est_secp,"\"" );
    if (!insertSeccion(LS, str)) {
      printf(" seccion insertada exitosamente");
    }
    else {
      printf("**No se pudo insertar seccion**  (Ya existe)");
    }
}

int encuentraSeccionLibro(Lista *L, char *est_sec[128]){ 
  //determina si existe una secccion en la lista L
  // retorna 0: Seccion existe en la lista L / 1: Seccion no existe en la lista L
  nodo* nodo;
  nodo = L->first; /* punto de inicio el 1er elemento */
  while(nodo != NULL){
      if (!strcmp(nodo->data.est_sec, est_sec)) {
        return 0; // se encuentra seccion en L
      }
      nodo = nodo->next;
  }//
  return 1;   // no se encuentra seccion en L
}
void eliminaNodoSeccion(ListaSeccion* LS){ //elimina el nodo apuntado por current en LS
    if(LS->current != NULL){ 
      if(LS->current == LS->first){ //Si el nodo a borrar es el primero 
        LS->first = LS->current->next;
      }
      else {
          if(LS->current == LS->last){ //Si el nodo a borrar es el ultimo
            LS->last->prev->next = NULL;
            LS->last = LS->last->prev;
          }
          else { //Borra nodo que no es primero ni ultimo
              LS->current->prev->next = LS->current->next;
              LS->current->next->prev = LS->current->prev;
          }
      free(LS->current);
    }
  }
}
void eliminaSeccion(Lista* L, ListaSeccion* LS){ //elimina seccion en lista LS
    char est_secp[128];
    char str[128];
    char temp;
    printf("\nEliminar seccion\n"); 
    printf("\nIngrese Estante Seccion (sin comillas): ");      
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",est_secp);
    //Agrega comillas a seccion
    snprintf(str, sizeof est_secp, "%s%s%s", "\"", est_secp,"\"" );
    if (encuentraSeccion(LS, str)) { //no existe 
      printf("**No se pudo eliminar seccion**  (No existe)"); 
    }
    else if (!encuentraSeccionLibro(L, str)) {
         printf("**No se pudo eliminar seccion**  (Existe libro en esa seccion)");
    }
    else {
          eliminaNodoSeccion(LS);
          printf(" seccion eliminada");
    }
}

void insertLibro(Lista* L, libro *datos){ //agrega un elemento al final de la lista
    nodo* newDato=(nodo*)calloc(1,sizeof(nodo));
    newDato->data = *datos;
    newDato->next = NULL;
    newDato->prev = NULL;
    if(L->first != NULL){ 
        L->last->next = newDato;
        newDato->prev = L->last;
        L->last = newDato;
    }
    else {
        L->first = newDato;
        L->last  = newDato;
    }
    L->current   = newDato;
    L->size++;
}
void eliminaNodo(Lista* L){ //elimina el nodo apuntado por current
    if(L->current != NULL){ 
      if(L->current == L->first){ //Si el nodo a borrar es el primero 
        L->first = L->current->next;
      }
      else {
          if(L->current == L->last){ //Si el nodo a borrar es el ultimo
            L->last->prev->next = NULL;
            L->last = L->last->prev;
          }
          else { //Borra nodo que no es primero ni ultimo
              L->current->prev->next = L->current->next;
              L->current->next->prev = L->current->prev;
          }
      free(L->current);
    }
  }
}
void listarLibros(Lista* L) {// Imprime listado de libros
  printf("Listado de libros\n");
  printf("  titulo,\tautor,\tanio,\testante_numero,\testante_seccion,\tpiso,\tedificio,\tsede,\n");
  printf("--------------------------------------------------\n");
  int i=0;
  nodo* nodo;
  nodo = L->first; /* punto de inicio el 1er elemento */
  while(nodo != NULL){
      i++;
      printf("%d ",i);
      printf("%s, ",nodo->data.titulo);
      printf("%s, ",nodo->data.autor);
      printf("%s, ",nodo->data.anio);
      printf("%s, ",nodo->data.est_num);
      printf("%s, ",nodo->data.est_sec);
      printf("%s, ",nodo->data.piso);
      printf("%s, ",nodo->data.edificio);
      printf("%s\n",nodo->data.sede);
      nodo = nodo->next;
 }
  printf("--------------------------------------------------\n");
}
void agregaLibro(Lista* L, ListaSeccion* LS){ //pide datos para agregas un libro
    char titulop[1024];
    char autorp[1024];
    char aniop[4];
    char est_nump[2];
    char est_secp[128];
    char pisop[2];
    char edificiop[128];
    char sedep[128];
    char temp;
    struct libro *datos=malloc(sizeof *datos); 
    printf("\nIngresar libro para agregar\n"); 
    printf("Ingrese Titulo: ");    
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",titulop);   

    printf("\nIngrese Autor(es) ");      
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",autorp);  //lee autor

    printf("\nIngrese Anio: ");      
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",aniop);     //lee anio

    printf("\nIngrese Estante num: ");      
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",est_nump);     

    printf("\nIngrese Estante Seccion: ");      
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",est_secp);     

    printf("\nIngrese Piso: ");      
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",pisop);     

    printf("\nIngrese Edificio: ");      
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",edificiop);     

    printf("\nIngrese Sede: ");      
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",sedep);     
    
    // Agrega comillas antes y despues de los campos de texto y los almacena en estructura
    snprintf(datos->titulo,  sizeof titulop,  "%s%s%s", "\"", titulop,"\"" );
    snprintf(datos->autor,   sizeof autorp,   "%s%s%s", "\"", autorp,"\"" );
    snprintf(datos->est_sec, sizeof est_secp, "%s%s%s", "\"", est_secp,"\"" );
    snprintf(datos->edificio,sizeof edificiop,"%s%s%s", "\"", edificiop,"\"" );
    snprintf(datos->sede,    sizeof sedep,    "%s%s%s", "\"", sedep,"\"" );
    strcpy(datos->anio, aniop);
    strcpy(datos->est_num, est_nump);
    strcpy(datos->piso, pisop);
    insertLibro(L, datos);
    insertSeccion(LS, est_secp);
}

void encuentraLibro(int *f, Lista *L, char *titulo[128], char *autor[128]){ 
  //determina si existe un libro en la lista
  nodo* nodo;
  *f=1;   // en caso no se encuentra
  nodo = L->first; /* punto de inicio el 1er elemento */
  while(nodo != NULL){
      if (!strcmp(nodo->data.titulo, titulo) && !strcmp(nodo->data.autor, autor)) {
        L->current = nodo;
        *f=0;
        break;  // se encuentra nodo
      }
      nodo = nodo->next;
  }//
}
void pideClaveLibro(char *titulo[1024], char *autor[1024]){ //pide datos clave del libro:Titulo y autor
    char titulop[1024];
    char autorp[1024];
    char  str[1024];
    char temp;
    printf("\n\nIngrese Datos clave del Libro\n"); 
    printf("Ingrese Titulo    (sin comillas): ");    
    scanf("%c",&temp); // temp limpia buffer de lectura previa
    scanf("%[^\n]",titulop); 
    printf("\nIngrese Autor(es) (sin comillas): ");      
    scanf("%c",&temp); // temp limpiabuffer de lectura previa
    scanf("%[^\n]",autorp);  //lee autor
    // agrega comillas a titulo y autor
    strcpy(str,"\"");
    strcat(str,titulop);
    strcat(str,"\"");
    strcpy(titulo,str);
    strcpy(autor,strcat(strcat(strcpy(str,"\""),autorp),"\""));
}
void buscarLibro(Lista* L){ // buscar un libro en la lista
    char titulop[1024];
    char autorp[1024];
    int f;
    pideClaveLibro(&titulop,&autorp);
    encuentraLibro(&f, L, &titulop, &autorp);
    if (f == 0) {
      printf("\nDatos Libro encontrado:");      
      printf("\nAnio: %s",            L->current->data.anio);
      printf("\nEstante num: %s",     L->current->data.est_num);
      printf("\nEstante Seccion: %s", L->current->data.est_sec);      
      printf("\nPiso: %s",            L->current->data.piso);
      printf("\nEdificio: %s",        L->current->data.edificio);      
      printf("\nSede: %s\n\n",        L->current->data.sede);
    }
    else {
      printf("\n** No existe libro **\n\n"); 
    }
}

void eliminaLibro(Lista* L){ //elimina libro de la lista
    char titulop[1024];
    char autorp[1024];
    int f;
    pideClaveLibro(&titulop,&autorp);
    encuentraLibro(&f, L, &titulop, &autorp);
    if (f == 0) {
      printf("\nEliminando Libro ");      
      printf("\nAnio: %s",            L->current->data.anio);
      printf("\nEstante num: %s",     L->current->data.est_num);
      printf("\nEstante Seccion: %s", L->current->data.est_sec);      
      printf("\nPiso: %s",            L->current->data.piso);
      printf("\nEdificio: %s",        L->current->data.edificio);      
      printf("\nSede: %s\n\n",        L->current->data.sede);
      eliminaNodo(L);
    }
    else {
      printf("\n** No existe libro **\n\n"); 
    }
}

void editaLibro(Lista* L){ //edita un libro
    char titulop[1024];
    char autorp[1024];
    char aniop[4];
    char est_nump[2];
    char est_secp[128];
    char pisop[2];
    char edificiop[128];
    char sedep[128];
    char temp;
    int f;
    pideClaveLibro(&titulop,&autorp);
    encuentraLibro(&f, L, &titulop, &autorp);
    if (f == 0) {
      printf("\nEditando Libro ");      
      printf("\nAnio: %s",            L->current->data.anio);
      printf("\nEstante num: %s",     L->current->data.est_num);
      printf("\nEstante Seccion: %s", L->current->data.est_sec); 
      printf("\nPiso: %s",            L->current->data.piso);
      printf("\nEdificio: %s",        L->current->data.edificio);
      printf("\nSede: %s\n\n",        L->current->data.sede);

      printf("\nIngrese nuevos valores ");      
      printf("\nIngrese Anio: ");      
      scanf("%c",&temp); // temp limpia buffer de lectura previa
      scanf("%[^\n]",aniop);     //lee anio

      printf("\nIngrese Estante num: ");      
      scanf("%c",&temp); // temp limpia buffer de lectura previa
      scanf("%[^\n]",est_nump);     

      printf("\nIngrese Estante Seccion: ");      
      scanf("%c",&temp); // temp limpia buffer de lectura previa
      scanf("%[^\n]",est_secp);     

      printf("\nIngrese Piso: ");      
      scanf("%c",&temp); // temp limpia buffer de lectura previa
      scanf("%[^\n]",pisop);     

      printf("\nIngrese Edificio: ");      
      scanf("%c",&temp); // temp limpia buffer de lectura previa
      scanf("%[^\n]",edificiop);     

      printf("\nIngrese Sede: ");      
      scanf("%c",&temp); // temp limpia buffer de lectura previa
      scanf("%[^\n]",sedep);     
    
    // Agrega comillas antes y despues de los campos de texto y los almacena en estructura
      snprintf( L->current->data.est_sec, sizeof est_secp, "%s%s%s", "\"", est_secp,"\"" );
      snprintf( L->current->data.edificio,sizeof edificiop,"%s%s%s", "\"", edificiop,"\"" );
      snprintf( L->current->data.sede,    sizeof sedep,    "%s%s%s", "\"", sedep,"\"" );
     
      strcpy(L->current->data.anio, aniop);
      strcpy( L->current->data.est_num, est_nump);
      strcpy( L->current->data.piso, pisop);
    }
    else {
      printf("\n** No existe libro **\n\n"); 
    }
}

void cambiarLibroSede(Lista* L){ //cambia libro de sede
    char titulop[1024];
    char autorp[1024];
    char sedep[128];
    char temp;
    int f;
    pideClaveLibro(&titulop,&autorp);
    encuentraLibro(&f, L, &titulop, &autorp);
    if (f == 0) {
      printf("\nCambiando Libro de Sede");      
      printf("\nAnio: %s",            L->current->data.anio);
      printf("\nEstante num: %s",     L->current->data.est_num);
      printf("\nEstante Seccion: %s", L->current->data.est_sec); 
      printf("\nPiso: %s",            L->current->data.piso);
      printf("\nEdificio: %s",        L->current->data.edificio);
      printf("\nSede: %s\n\n",        L->current->data.sede);

      printf("\nIngrese nueva Sede para este libro: ");      
      scanf("%c",&temp); // temp limpia buffer de lectura previa
      scanf("%[^\n]",sedep);     
    // Agrega comillas antes y despues de seccion
      snprintf( L->current->data.sede, sizeof sedep, "%s%s%s", "\"", sedep,"\"" );
    }
    else {
      printf("\n** No existe libro **\n\n"); 
    }
}

void cambiarLibroSeccion(Lista* L){ //cambia libro de sede
    char titulop[1024];
    char autorp[1024];
    char est_secp[128];
    char temp;
    int f;
    pideClaveLibro(&titulop,&autorp);
    encuentraLibro(&f, L, &titulop, &autorp);
    if (f == 0) {
      printf("\nCambiando Libro de Seccion");      
      printf("\nAnio: %s",            L->current->data.anio);
      printf("\nEstante num: %s",     L->current->data.est_num);
      printf("\nEstante Seccion: %s", L->current->data.est_sec); 
      printf("\nPiso: %s",            L->current->data.piso);
      printf("\nEdificio: %s",        L->current->data.edificio);
      printf("\nSede: %s\n\n",        L->current->data.sede);

      printf("\nIngrese nueva Seccion para este libro: ");      
      scanf("%c",&temp); // temp limpia buffer de lectura previa
      scanf("%[^\n]",est_secp);     
    // Agrega comillas antes y despues de seccion
      snprintf( L->current->data.est_sec, sizeof est_secp, "%s%s%s", "\"", est_secp,"\"" );
    }
    else {
      printf("\n** No existe libro **\n\n"); 
    }
}

void cambiarLibroPiso(Lista* L){ //cambia libro de sede
    char titulop[1024];
    char autorp[1024];
    char pisop[128];
    char temp;
    int f;
    pideClaveLibro(&titulop,&autorp);
    encuentraLibro(&f, L, &titulop, &autorp);
    if (f == 0) {
      printf("\nCambiando Libro de Piso");      
      printf("\nAnio: %s",            L->current->data.anio);
      printf("\nEstante num: %s",     L->current->data.est_num);
      printf("\nEstante Seccion: %s", L->current->data.est_sec); 
      printf("\nPiso: %s",            L->current->data.piso);
      printf("\nEdificio: %s",        L->current->data.edificio);
      printf("\nSede: %s\n\n",        L->current->data.sede);

      printf("\nIngrese nuevo Piso para este libro: ");      
      scanf("%c",&temp); // temp limpia buffer de lectura previa
      scanf("%[^\n]",pisop);     
      strcpy(L->current->data.piso, pisop);
    }
    else {
      printf("\n** No existe libro **\n\n"); 
    }
}

void leeCampoString(FILE* fp, char campo[]) {
  // restricciones: Largo maximo de un campo=1024
  int largoMax=1024;
  char texto[1024]="";
  int i=0;
  char caracter = fgetc(fp); // lee sgte caracter desde archivo
  if (caracter == ',') { // Salta coma de separacion de campos
    caracter = fgetc(fp);
  }
  texto[i]=caracter;
  caracter = fgetc(fp);
  i++;
  while(feof(fp) == 0 && caracter!='"' && caracter!='\n') {
    texto[i]=caracter;   //lee caracter por caracter y arma texto
    caracter = fgetc(fp);
    i++;
  }
  if (feof(fp) == 0) { // lee comillas finales del campo
    texto[i]=caracter;
    fgetc(fp);
  }
  strcpy(campo,texto);
}
void leeCampoNum(FILE* fp, char campo[]) {
  // restricciones: Largo maximo de un campo=1024
  int largoMax=1024;
  char texto[1024]="";
  int i=0;
  char caracter = fgetc(fp);
  while(feof(fp) == 0 && caracter!=',' && caracter!='\n') {
    texto[i]=caracter;
    caracter = fgetc(fp);
    i++;
  }
  strcpy(campo,texto);
}

int cargaArchivo(Lista* L, ListaSeccion* LS, char archivo[]){ //se ingresan los datos de manera automática a la lista
  FILE *fp; //puntero al archivo csv
//  fp=fopen("inventario.csv","r");//abre texto para lectyra
  fp=fopen(archivo,"r");//abre texto para lectyra
  if(fp==NULL){
        printf("ERROR en apertura de archivopara leer \n"); 
        exit(0); //si no se abre encuentra archivo se cierra el programa
  }
  printf("Leyendo archivo %s\n", archivo);
  char campo[1024]="";
  struct libro *datos=malloc(sizeof *datos); 
  while(feof(fp) == 0) {
     leeCampoString(fp, campo); //lee titulo
     strcpy(datos->titulo, campo);
     leeCampoString(fp, campo);  //lee autor
     strcpy(datos->autor, campo);
     leeCampoNum(fp, campo);     //lee anio
     strcpy(datos->anio, campo);
     leeCampoNum(fp, campo);     //lee estante num
     strcpy(datos->est_num, campo);
     leeCampoString(fp, campo);  //lee estante seccion
     strcpy(datos->est_sec,campo);
     leeCampoNum(fp, campo);     //lee piso
     strcpy(datos->piso, campo);
     leeCampoString(fp, campo);  //lee edificio
     strcpy(datos->edificio,campo);
     leeCampoString(fp, campo); //lee sede
     strcpy(datos->sede,campo);
     insertLibro(L, datos);

     insertSeccion(LS, datos->est_sec);
  }
  fclose(fp);
  return 0;
}

void grabaCampo(FILE* fp, char campo[]) {
  // restricciones: Largo maximo de un campo=1024
  for (int i=0; i < strlen(campo); i++) {
      fputc(campo[i], fp );
  }
}

int grabaArchivo(Lista* L, char archivo[]){ //se graba archivo
  FILE *fp; //puntero al archivo csv
  fp=fopen(archivo,"w");//abre texto para escribir
  if(fp==NULL){
        printf("ERROR en apertura de archivo para grabar %s \n", archivo); 
        exit(0);
  }
  printf("grabando archivo %s\n\n", archivo);
  nodo* nodo;
  nodo = L->first; /* punto de inicio el 1er elemento */
  while(nodo != NULL){
    grabaCampo(fp, nodo->data.titulo);
    fputc(',', fp );
    grabaCampo(fp, nodo->data.autor);
    fputc(',', fp );
    grabaCampo(fp, nodo->data.anio);
    fputc(',', fp );
    grabaCampo(fp, nodo->data.est_num);
    fputc(',', fp );
    grabaCampo(fp, nodo->data.est_sec);
    fputc(',', fp );
    grabaCampo(fp, nodo->data.piso);
    fputc(',', fp );
    grabaCampo(fp, nodo->data.edificio);
    fputc(',', fp );
    grabaCampo(fp, nodo->data.sede);
    if(nodo != L->last){ //escribe salto de linea si no es el ultimo
      fputc('\n', fp );
    }
    nodo = nodo->next; 
  }
  fclose(fp);
  return 0;
}

int menuPrincipal (Lista* L, Lista* LS){
    char temp;
    char op='1'; //Se declara variable opción (esta se usa como operador de switch)
    while(op!='0'){
        printf("\nBienvenido a la Biblioteca!\n");
        printf("       MENU\n");
        printf("1. Agregar libro\n");
        printf("2. Quitar libro\n");
        printf("3. Editar libro\n");
        printf("4. Buscar libro\n");
        printf("5. Listar libros\n");
        printf("6. Cambiar libro de sede\n");
        printf("7. Cambiar libro de seccion\n");
        printf("8. Cambiar libro de piso\n");
        printf("S. Menu Secciones\n");
        printf("E. Menu Sedes\n");
        printf("P. Menu Pisos\n");
        printf("0. Guardar y SALIR \n");
        printf(" Ingresa una opción: ");
        scanf(" %c",&op);
        op=toupper(op);
        switch(op){
            case '1':{
                agregaLibro(L, LS);//Agregar libro
                break; 
            }
            case '2':{ //Eliminar libro
                eliminaLibro(L);
                break;
            }
            case '3':{ //Editar Libro
                editaLibro(L);
                break;
            }
            case '4':{// BUSCAR
                buscarLibro(L);
                break;
            }
            case '5':{
              listarLibros(L);
              break;
            }
            case '6':{
              cambiarLibroSede(L);
              break;
            }
            case '7':{
              cambiarLibroSeccion(L);
              break;
            }
            case '8':{
              cambiarLibroPiso(L);
              break;
            }
            case 'S':{
              menuSecciones(L, LS);
              break;
            }
            case '0':{
              printf("Adios, gracias por participar\n");
              break;
            }
            default:{
              printf("*Opcion erronea, reingrese*\n\n");
              scanf("%c",&temp); //
            }
        }
    }
 return 0;   
}

int menuSecciones (Lista* L, Lista* LS){
    char temp;
    char op='1'; //Se declara variable opción (esta se usa como operador de switch)
    while(op!='0'){
        printf("\n\n   MENU SECCIONES\n");
        printf("1. Agregar Seccion\n");
        printf("2. Eliminar Seccion\n");
        printf("3. Listar Secciones\n");
        printf("0. Volver a Menu Principal\n");
        printf(" Ingresa una opción: ");
        scanf(" %c",&op);
        switch(op){
            case '1':{
                agregaSeccion(LS); //Agregar seccion en lista LS
                break; 
            }
            case '2':{ //Eliminar seccion
                eliminaSeccion(L, LS); //elimina seccion en LS siempre que no haya libro con esa seccion
                break;
            }
            case '3':{ //lista secciones
                listarSecciones(LS);
                break;
            }
            case '0':{
              break;
            }
            default:{
              printf("*Opcion erronea, reingrese*\n\n");
              scanf("%c",&temp); //
            }
        }
    }
 return 0;   
}
int main(int argc, char *argv[]) {
  if (argc < 2) {
     printf("*error* debe indicar nombre de archivo\n");
     return 1;
  }
  Lista* L = creaLista();
  ListaSeccion* LS = creaListaSeccion();
  cargaArchivo(L, LS, argv[1]);
  listarLibros(L);
  menuPrincipal(L, LS);
  grabaArchivo(L, argv[1]);
  return 0;
}