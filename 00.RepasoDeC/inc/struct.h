#ifndef STRUCT_H_
#define STRUCT_H_

//Sin typedef
struct FECHA{
    int dia;
    int mes;
    int anio;
};

//Usando la palabra reservada typedef
typedef struct{
    int day;
    int month;
    int year;
} DATE;

typedef struct{
    char name[20];
    DATE dob;
    long int dni;
} PERSON;

void createDate(void);
void printDate(DATE *d);
void printPerson(PERSON *p);
void loadPs(PERSON *ps);
void printPs(PERSON *ps);
void useStructs(void);
#endif