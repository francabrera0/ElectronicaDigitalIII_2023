#include <stdio.h>
#include <stdlib.h>
#include "pointers.h"

void printPointerTests(void){
    int a = 3; //variable entera con valor 3
    int *p; //puntero a una variable entera
    p=&a; //Ahora p le apunta a la dirección de memoria de a
    printf("Dirección de memoria de a: %p: \n", &a);
    printf("Valor del contenido de a: %d \n",a);
    printf("Valor contenido en la dirección de memoria donde apunta p: %d \n",*p);
    printf("Valor de la dirección de memoria a la que apunta p: %p \n",p); //Es igual a la dir de a (p->a)
    //Modificar el contenido de la direccion de memoria a la que apunta p
    *p=7;
    printf("Se modificó el valor-------------\n");
    printf("Valor del contenido de a: %d \n",a);
    printf("Valor contenido en la dirección de memoria donde apunta p: %d \n",*p);
}

void swapUse(void){
    int a=3;
    int b=6;
    printf("Valor de a: %d, valor de b: %d \n",a,b);
    swap(&a,&b);
    printf("Valor de a: %d, valor de b: %d \n",a,b);

}

//Al usar punteros trabajo sobre las direcciones de memoria de las variables y no sobre copias
void swap(int *a,int *b){
    int c; //variable temporal entera
    c=*a; 
    *a=*b; 
    *b=c;
}

/*Otro uso de los punteros es para resolver el problema de no conocer de antemano la memoria requerida. Para esto
 *se declaran punteros y luego se reserva memoria desde el sistema operativo.
 *
 * En cierto punto lo que se hace con punteros sería como el uso de arrays pero más eficiente en cuestiones
 * de memoria.
 *             Arreglos --> Es una declaración estática
 *			            --> Ocupa espacios de memoria hasta el fin de la ejecución 
 *			            --> Se almacena en el STACK (pila) lo que quiere decir que sigue un orden tanto para guardarse como para borrarse
 *			
 *	            Punteros--> Es una declaración dinámica (muy importante)
 *			            --> Puedo liberar espacios de memoria en cualquier momento de la ejecución
 * 			            --> Se almacenan en la HEAP (montón) se puede liberar en cualquier orden.
 *
 *  Para reservar memoria para los punteros:
 *      p=(int *) malloc(sizeof(int)*n);
 */

 //Función para demostrar el uso de malloc

 void allocation(void){
    int *p;
    int *q;
  
    p=(int *) malloc (sizeof(int)*1); //Reservo espacio de memoria del sistema operativo. Ahora p apunta a una dirección de memoria reservada para 						ser usada cuando sea necesario. (En la HEAP)
    *p=10; //Le asigno un valor de contenido a la dirección de memoria apuntada por p
  
    q=(int *) malloc (sizeof(int)*1);
    *q=3;
  
  printf("La dirección de memoria de p es: %p\n",p);
  printf("El valor de la dirección de memoria a la que apunta p es: %d \n",*p); //"10"
  printf("La dirección de memoria de q es: %p\n",q);
  printf("El valor de la dirección de memoria a la que apunta q es: %d \n",*q); //"10"
  
  free(p); //Libera la memoria reservada para el puntero p (muy importante)
  free(q); //Libera la memoria reservada para el puntero q (muy importante)
 }

//Si en la función malloc reservamos más espacios de memoria podemos acceder a los datos del puntero
//de dos formas diferentes, con sinntaxis de arreglos o aritmética de punteros

void arraySyntax(void){
    int *p;
    p=(int *) malloc (sizeof(int)*4); //Reserva espacio de memoria para 4 enteros.
    *p=10; //Le asigna el valor 10 al elemento que se encuentra en el primer espacio de memoria
  
    //Asigna valores a los espacios de memoria declarados dentro de los corchetes, al igual que en un arreglo
    p[0]=4;
    p[1]=5;
    p[2]=9;
    p[3]=21;
  
    //Muestra los valores de todos los espacios de memoria a los que apunta p
    for(int i=0; i<4; i++)
        printf("El valor de p en la posición %d es: %d \n",i,p[i]); //"4" "5" "9" "21" 
  
    free(p); //Libera los espacios de memoria a los que apunta p
}

void pointerArithmetic(void){
    int *p;
    p=(int *) malloc (sizeof(int)*4); //Reserva espacio de memoria para 4 enteros.
    *p=10; //Le asigna el valor 10 al elemento que se encuentra en el primer espacio de memoria
  
    //Cada numero suma un espacio de memoria, segun el tipo de dato es la cantidad de bytes que suma cada entero
    *(p+0)=4;
    *(p+1)=5;
    *(p+2)=9;
    *(p+3)=21;
  
  //Muestra los valores de todos los espacios de memoria a los que apunta p
    for(int i=0; i<4; i++)
        printf("El valor de p en la posición %d es: %d \n",i,p[i]); //"4" "5" "9" "21" 
  
    free(p); //Libera los espacios de memoria a los que apunta p
}

 
 
