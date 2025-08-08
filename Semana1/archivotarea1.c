/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>

struct datos{
   char name[81];
   int age;
   int trabaja;
};

typedef struct datos Data;

int sitrabaja(int age, int trabaja){
    
    if(age>100)
    trabaja=0;
    
    return trabaja;
}
int main()
{ 
    int age;
    int tt;
    //struct datos p;
  //  struct datos a;
    Data p;
    Data a;
    
    p.age = 39;
    p.trabaja= 1;
    
    tt= sitrabaja(a.age, a.trabaja);
    printf("trabaja: %d\n", tt);
    
    strcpy(p.name, "Mi nombre");
    printf("nombre: %s\n", p.name);
    printf("age: %d\n", p.age);
    
    a=p;
     printf("nombre: %s\n", a.name);
    printf("age: %d\n", a.age);
    printf("trabaja: %d\n", a.trabaja);
    
    return 0;
}