#include <stdio.h>
#include <stdlib.h>
#include "database.h"

int main(int argc, char** argv){

    //CREATE    
    Database* d = create_database();
    Persona* p = create_persona("Giorgio","Malgioglio","via Capocroce",20);
    Persona* p2 = create_persona("Mario","Merola", "Via Aprile",35);
    Persona* p3 = create_persona("Luca","De Luca","via Mango",100);
    //print_persona(p);
    //print_persona(p2);
    insert(d,p);
    insert(d,p2);
    insert(d,p3);

    //PRINT
    // print_treeString(d->address);
    // print_treeInt(d->age);
    // print_treeString(d->name);
    // print_treeString(d->surname);

    Persona* persN = findByName(d, "Giorgio");
    print_persona(persN);
    printf("\n");
    Persona* persA = findByAddress(d,"via Aprile");
    print_persona(persA);
    printf("\n");
    Persona* persS = findBySurname(d,"De Luca");
    print_persona(persS);
    printf("\n");
    Persona* persAge = findByAge(d,20);
    print_persona(persAge);
    printf("\n");
    //FREE
    free_database(d);
    free_persona(p);
    free_persona(p2);
    free_persona(p3);
    
    return 0;

}