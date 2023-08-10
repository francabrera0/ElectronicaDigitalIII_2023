## Electrónica Digital III - UNC - FCEFyN

# Repaso de C

### Pasos para compilar el proyecto

    Para poder compilar y correr los programas que se encuentran en este directorio, será necesario tener instalado cmake y make. Para distribuciones de linux basadas en Debian:

```bash
sudo apt install cmake make
```

    Una vez con esto instalado, dirigirse al directorio 00.RepasoDeC, allí se encontrará lo siguiente:

```bash
CMakeLists.txt  inc  README.md  src
```

- **CMakeLists.txt:** Archivo de configuración para cmake.

- **inc:** Directorio en el que se encuentran los archivos .h

- **src:** Directorio en el que se encuentran los archivos .c

- **README.md:** Markdown con explicaciones (este archivo)

    Una vez en este directorio, crear una nueva carpeta llamada `build` y digirirse a la misma:

```bash
mkdir build && cd build 
```

    Luego ejecutar los siguientes comandos:

```bash
cmake ..
make
```

    Una vez hecho esto, veremos que se generaron los archivos ejecutables para poder correrlos.

    El ejecutable Main, contendrá las llamadas a todas las funciones definidas para poder analizar sus salidas.

## Estructura de un programa en C

   Un programa en C consta de una o más funciones, la función principal se llama `main()` y es obligatorio definirla. Esta función es el punto de entrada de ejecución del programa.

```c
#include <stdio.h>

int main(int argc, char const *argv[]) {

    printf("Hello world!\n");
    return 0;

}
```

    En este ejemplo básico de un programa en C podemos distinguir dos partes principales:

- **Header:** compuesta por la directiva #include que especifica la orden de leer un archivo de texto especificado en el nombre que sigue a la misma y reemplazar esta línea por el contenido de dicho archivo. En este caso, se hace uso del header stdio.h para la definición de la función `printf()`. Esto se verá con mayor detalle más adelante.

- **Definición de la función main():** Cómo toda función, main() se define con su nombre, tipo de retorno y parámetros. 

- **Implementación de la función:** Luego de la definición de la función, se encuentra su implementación. Este conjunto de sentencias se encuentra delimitado por dos llaves `{}`. 

¿Por qué `main()` retorna un valor de tipo int? 

    La función `main()` se define como int y retorna un valor de 0 como un estándar para indicar el estado de finalización de un programa. Cuándo un programa termina su ejecución, generalmente devuelve un valor conocido como "Código de retorno", este valor es utilizado por el sistema operativo para saber si el programa se completó correctamente o si ocurrió algún error durante la ejecución.

    Por ejemplo, en linux podemos ver esto de la siguiente manera:

```bash
╭─francabrera@ASUS ~/Documents/ElectronicaDigitalIII/ElectronicaDigitalIII_2023/00.RepasoDeC/build
╰─$ ls
CMakeCache.txt  CMakeFiles  cmake_install.cmake  helloWorld  Makefile
╭─francabrera@ASUS ~/Documents/ElectronicaDigitalIII/ElectronicaDigitalIII_2023/00.RepasoDeC/build
╰─$ ./helloWorld 
Hello World!
╭─francabrera@ASUS ~/Documents/ElectronicaDigitalIII/ElectronicaDigitalIII_2023/00.RepasoDeC/build 
╰─$ echo $?                                        
0
```

    Con `echo $?` podemos ver el valor de retorno del último comando que se corrió.

## Funciones

    El código de un programa escrito en C se divide en diferentes funciones. Las funciones suelen encapsular una o más operaciones de las que se deriva un resultado. Para ejecutar esta operacón, las funciones pueden precisar la invocación de otras funciones (o incluso de ellas mismas como es el caso de las funciones recursivas).

    Las funciones en un programa son entidades que, dado un conjunto de datos (parámetros), se les realiza operaciones concretas y se espera obtener un resultado. Lo ideal es dividir tareas complejas en porciones más simples que se implementan como funciones. 

    El dividir el código en diferentes funciones ayuda mucho con la organización y legibilidad del código.

### Definición de una función

    Las funciones en C tienen el siguiente formato

```c
<returnType> functionName (<param1Type> param1, <param2Type> param2,...){

    /*Function body*/

}
```

    Cuando se define una función con algún tipo de retorno, es necesario implementar un return que devuelva algún dato de este tipo. En caso de no necesitar retornar un valor, puede definirse la función del tipo `void`.

## Header files

    Una buena forma de organizar un programa en C es haciendo uso de archivos de encabezado o header files. 

    Un header file contiene, normalmente, una declaración directa de clases, subrutinas, variables u otros identificadores. Esto nos permite, separar nuestro código en diferentes componentes de menor tamaño y luego hacer uso de esas definiciones en otros archivos.

    Para incluir un header file en nuestro fuente se hace con la directiva de preprocesamiento `#include`que lo que hace es, buscar el archivo cuyo nombre se le indica y reemplazar esta línea por el contenido del archivo.

```c
/**
 * Al utilizar #include <> el compilador buscará el archivo en las
 * rutas predeterminadas del sistema o directorios de inclusión
 * espec
*/
#include <stdio.h> 

/**
 * Al utilizar #include "" el compilador buscará el archivo primro en el 
 * directorio actual del archivo fuente (.c) que lo est
 *
 */
#include "header.h"
```

### Esquema de directorios

    Una forma básica de organizar un proyecto en C, es creando los directorios `src`donde se encuentran todos los archivos fuente .c y otro directorio `inc`donde se encuentran los archivos de cabecera.

    Veamos un ejemplo básico de esto

```c
/*@file: header1.h*/
#ifndef HEADER_1_H /*Guarda para evitar múltiples inclusiones*/
#define HEADER_1_H

int sum(int a, int b);

#endif /*HEADER_1_H*/
```

```c
/*@file: header1.c*/
#include "../inc/header1.h"

int sum(int a, int b) {
    return (a+b);
}
```

```c
/*@file: main1.c*/
#include <stdio.h>
#include "../inc/header1.h"

int main(int argc, char const *argv[])
{
    int op1 = 10;
    int op2 = 20;

    int result = sum(op1, op2);

    printf("El resultado es %d\n", result);

    return 0;
}
```

    En estos archivos, podemos ver que en header1.h se define la función, en header1.c se encuentra la definición y en main1.c se hace uso de esta función.

    Notese que al incluir el header file se usa el path "../inc/header1.h" como dirección relativa al archivo.

## Tipos de datos

    Ver archivos `dataType.h`y `dataType.c`, en la función definida en el archivo .c, se puede ver una forma de conocer el tamaño de cada tipo de datos, para observar la salida de esta función, ejecutar el binario Main en la carpeta build (ver sección sobre compilación del proyecto).

## Punteros

    Ver archivos `pointers.c` y `pointers.h`.

    Los punteros, son uno de los aspectos más importantes de la programación en C, pero también uno de los más complejos de dominar. Los punteros permiten manipular la memoria del ordenador de forma eficiente. Dos conceptos fundamentales para comprender el funcionamiento de punteros son:

- El tamaño de las variables y su posición en memoria

- Todo dato está almacenado a partir de una dirección de memoria. Esta dirección puede ser obtenida y manipulada como un dato más.



    Los punteros son también una de las fuentes de errores más frecuentes. Dado que se manipula la memoria directamente, el diseño de programas con punteros requiere una meticulosidad muy elevada. 

    Básicamente, un puntero es una variable que guarda la dirección de una posición de memoria.



### Declaración de punteros

    Para declarar un puntero a una variable se utiliza `*`. Es necesario especificar el tipo de dato y el nombre del puntero. Por ejemplo, para definir un puntero a un entero:

```c
int pointer *;
```

    Si solo lo definimos, no podemos asegurar cuál será el contenido de esta variable.

    Para comprender mejor su uso, podemos analizar la función `printPointerTests()`definida en el archivo pointers.c

```c
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
```



### Uso de punteros

#### Paso de parámetros por referencia

    Uno de los usos más comunes de punteros es para hacer pasajes de parámetros por referencia y no por valor.

    Al hacer pasaje de parámetros por valor, lo que se hace es dar una "copia" de esas variables a la función, y por lo tanto no se modificará el valor del parámetro que fue pasado. Un típico ejemplo es el caso de una función de swap entre dos números.

    Si definimos una función swap del siguiente modo:

```c
#include <stdio.h>

void swap(int a, int b) {
  int c;
  c=a;
  a=b;
  b=c;
}

int main() {

  int a = 10;
  int b = 20;
  printf("a = %d, b = %d\n", a, b);
  
  swap(a,b);
  
  printf("a = %d, b = %d\n", a, b);
  
  return 0;
}
```

    Observaremos que nos datos a y b no fueron intercambiados debido a que el cambio se hizo sobre copias locales de las variables en la función swap.

    Si ahora, usamos pasaje de parámetros por referencia:

```c
#include <stdio.h>

void swap(int *a, int *b) {
  int c;
  c=*a;
  *a=*b;
  *b=c;
}

int main() {

  int a = 10;
  int b = 20;
  printf("a = %d, b = %d\n", a, b);
  
  swap(&a,&b);
  
  printf("a = %d, b = %d\n", a, b);
  
  return 0;
}
```

    Veremos que los datos fueron intercambiados, debido a que se trabajó directamente sobre las direcciones de memoria de estas variables.

    Correr estos códigos en ([C debugger - C Tutor - Learn C programming by visualizing code](https://pythontutor.com/c.html#mode=edit)) para una mejor visualización.

#### Reserva de memoria dinámica

    Ver función `allocation()` definida en el archivo pointers.c.

#### Listas enlazadas

    Ver archivo `linkedList.c` en el directorio src.

## Structs

    Ver archivo struct.c para ver la definición y uso de las estructuras.

    Las estructuras (structs) son colecciones de variables de diferentes tipos de datos con un solo nombre. El tamaño de una struct, es AL MENOS la suma de los elementos que la componen.



## Union

    Las definiciones de "union" es similar a la de "struct". La diferencia entre las dos es que en una estructura, los miembros ocupan diferentes áreas de memoria, pero en una unión, los miembros ocupan la misma área de memoria. Cuando se crea una unión, el compilador crea una variable lo suficientemente grande para guardar el tipo de dato más grande de la unión. Por ejemplo:

```c
union {
    int i;
    double d;
} u;
```

    El programador puede acceder a través de "u.i" o de "u.d" pero no de ambos al mismo tiempo. Como "u.i" y "u.d" ocupan la misma memoria, modificar el valor de uno, modifica el otro, algunas veces de maneras impredecibles.

    El siguiente código muestra la diferencia entre estructuras y uniones

```c
#include <stdio.h>
#include <string.h>

union frases 
{
    char mensajes[50];
    char ayudas[50];
    char lineas[50];
} palabra;

struct comparte
{
    char mensajes[50];
    char ayudas[50];
    char lineas[50];
}Sistema;


int main(int argc, char** argv)
{
    printf("Tamaño de union: %lu\n", sizeof(palabra));
    strcpy(palabra.mensajes, "Primer Mensaje");
    strcpy(palabra.ayudas, "Una Ayuda");
    
    printf("1- %s\n", palabra.mensajes);
    printf("2- %s\n", palabra.ayudas);

    printf("Tamaño de estructura: %lu\n", sizeof(Sistema));    
    strcpy(Sistema.mensajes, "Primer Mensaje");
    strcpy(Sistema.ayudas, "Una Ayuda");
    
    printf("1- %s\n", Sistema.mensajes);
    printf("2- %s\n", Sistema.ayudas);
    
    
    return 0;
}
```



## Operadores

### Operadores aritméticos

| Símbolo | Descripción    | Ejemplo |
|:------- | -------------- | ------- |
| +       | Suma           | a + b   |
| -       | Resta          | a - b   |
| *       | Multiplicación | a * b   |
| /       | División       | a / b   |
| %       | Módulo         | a % b   |

    El operador módulo, se utiliza para calcular el resto del coeficiente entre dos enteros.



### Operadores relacionales

| Símbolo | Descripción       | Ejemplo |
| ------- | ----------------- | ------- |
| <       | Menor que         | a < b   |
| >       | Mayor que         | a > b   |
| <=      | Menor o igual que | a <= b  |
| >=      | Mayor o igual que | a >= b  |
| ==      | Igual que         | a == b  |
| !=      | Distinto que      | a != b  |



### Operadores lógicos

| Símbolo | Descripción    | Ejemplo         |
| ------- | -------------- | --------------- |
| &&      | Y (AND)        | (a>b) && (c<d)  |
| |\|     | O (OR)         | (a>b) \|| (c<d) |
| !       | Negación (NOT) | !(a>b)          |



### Operadores a nivel de bits

    Estos operadores muestran una de las armas más potentes del lenguaje C , la de poder manipulear INTERNAMENTE , es decir bit a bit , las variables.
    Debemos anticipar que estos operadores sólo se aplican a variables del tipo char, short, int y long y NO pueden ser usados con float ó double.
    Sabemos que las computadoras guardan los datos organizados en forma digital, en
bytes, formado por números binarios de 8 bits y como se vió anteriormente cuando se
analizó el tamaño de las variables, cada una ocupa una diferente cantidad de bits.
    Para el manejo de dichos bits , contamos con los operadores descriptos en la siguiente tabla:

| Símbolo | Descripción             | Ejemplo |
| ------- | ----------------------- | ------- |
| &       | Y (AND) bit a bit       | a & b   |
| |       | O (OR) inclusiva        | a \| b  |
| ^       | XO (XOR) exclusiva      | a ^ b   |
| <<      | Rotación a la izquierda | a << b  |
| >>      | Rotación a la derecha   | a >> b  |
| ~       | Complemento a uno       | ~a      |



```c
#include <stdio.h>
#include <stdint.h>


int main() {
  uint8_t a = 0xe; //1110
  uint8_t b = 0x9; //1001
  
  uint8_t andResult = a & b;
  uint8_t orResult = a | b;
  uint8_t xorResult = a ^ b;
  uint8_t shiftLeft = a << 1; //Shift a la izquierda en un lugar
  uint8_t shiftRight = a >> 1; //Shift a la derecha en un lugar
  uint8_t complement = ~a;
  
  
  return 0;
}
```
