#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#define N_PS 4



//Función para notar la diferencia al usar typedef
void createDate(void){
    DATE d1; //No es necesario explicitar el typedef struct ya que está definido 
    struct FECHA f1;
}

//Imprime una struct del tipo DATE
void printDate(DATE *d){
     printf("dia:%d - mes:%d - anio:%d\n",d->day,d->month,d->year);
}

//Imprime los datos de una persona
void printPerson(PERSON *p){
    printf("nombre %s,dni %ld,nac:",p->name,p->dni);
    printDate(&(p->dob));
}

//Carga peronas con el mismo nombre pero diferente dni y fecha
void loadPs(PERSON *ps){
     int i;
     for(i=0;i<N_PS;i++){
        strcpy((ps+i)->name,"Luisa Castro");
        (ps+i)->dni=10998760+i;
        (ps+i)->dob.day=10+i;
        (ps+i)->dob.month=2;
        (ps+i)->dob.year=1980;
     }
}

//Imprime todas las personas
void printPs(PERSON *ps){
     int i;
     for(i=0;i<N_PS;i++){
         printPerson(ps+i);
     }
}

void useStructs(void){
    DATE d1, d2; //Define las variables de tipo fecha (estructuras)
    PERSON p1; //Define la variable de tipo persona (estructura)
    PERSON *pp1; //Puntero a una persona
           
    pp1=(PERSON *)malloc(sizeof(PERSON)); //Aloca memoria en la heap del tamaño de una persona

    d1.day=12; //Asigna valores a f1
    d1.month=3;
    d1.year=1999;
     
    //Aigno los valores de p1
    strcpy(p1.name,"Juan Lopez"); //Cadena de caracteres por eso necesito string copy
    p1.dni=12445099; //Operador punto .
    p1.dob.day=1;
    p1.dob.month=12;
    p1.dob.year=1999;

    //Asigno los valores de p2	
    strcpy(pp1->name,"Luisa Castro"); //Operador flecha para punteros ->
    pp1->dni=10998760; 
    pp1->dob.day=10; //Operador flecha seguido de operador punto
    pp1->dob.month=2;
    pp1->dob.year=1980;
    printPerson(&p1);
    printPerson(pp1);

    pp1->dob=d1;
    printPerson(pp1);
    
    free(pp1);

}