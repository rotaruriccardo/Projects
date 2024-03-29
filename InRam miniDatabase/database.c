#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "database.h"

//CREATE
Persona* create_persona(const char* name,const char* surname,const char* address, int age){
    Persona* p = (Persona*)malloc(sizeof(Persona));
    if(p == NULL) return NULL;
    strcpy(p->name, name);
    strcpy(p->surname, surname);
    strcpy(p->address, address);
    p->age = age;
    return p;
}
Persona* create_null_persona() {
    Persona* p = malloc(sizeof(Persona));
    if (p == NULL) {
        return NULL;
    }

    // Initialize all string members to null characters
    memset(p->name, 0, sizeof(p->name));
    memset(p->surname, 0, sizeof(p->surname));
    memset(p->address, 0, sizeof(p->address));

    // Set the age member to 0
    p->age = 0;

    return p;
}
Database* create_database(){
    Database *d = (Database*)malloc(sizeof(Database));
    if(d==NULL){
        printf("machevoi\n");
        return NULL;
    }
    d->address = NULL;
    d->age = NULL;
    d->name = NULL;
    d->surname = NULL;
    return d;
}
IndexNodeString* nodeStr_create(char* value, Persona* p){
    Persona* temp = copy(p);
    IndexNodeString *node = malloc(sizeof(IndexNodeString));
    node->left = NULL;
    node->right = NULL;

    // Allocate new memory for node->value and make a copy of the string
    node->value = strdup(value);
    if (node->value == NULL) {
        // Handle error here, for example, free the allocated memory and return NULL
        free(node);
        free_persona(temp);
        return NULL;
    }
    node->persona = temp;
    return node;
}
IndexNodeInt* nodeInt_create(int value, Persona* p){
    Persona* temp = copy(p);
    IndexNodeInt *node = malloc(sizeof(IndexNodeInt));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    node->persona = temp;
    return node;
}

//COPIA
Persona *copy(Persona *p) {
    Persona* newPers = create_null_persona();
    strcpy(newPers -> name , p -> name);
    strcpy(newPers -> surname , p -> surname);
    strcpy(newPers -> address , p -> address);
    newPers->age = p->age;
    return newPers;
}

//PRINT
void print_persona(Persona* p){
    if(p == NULL){
        //printf("errore: persona not found\n");
        return;
    }
    printf("NAME: %s\n",p->name);
    printf("SURNAME: %s\n",p->surname);
    printf("ADDRESS: %s\n",p->address);
    printf("AGE: %d\n",p->age);
}
void print_treeString(IndexNodeString* root){
    if(root == NULL){
        return;
    }
    print_treeString(root->left);
    printf("%s\n",root->value);
    print_treeString(root->right);
}
void print_treeInt(IndexNodeInt* root){
    if(root == NULL){
        return;
    }
    print_treeInt(root->left);
    printf("%d\n",root->value);
    print_treeInt(root->right);
}

//FREE
void free_persona(Persona* p){
    if(p != NULL){
        free(p);
    }
}
void free_nodeInt(IndexNodeInt* n){
    if(n != NULL){
        free_nodeInt(n->right);
        free_nodeInt(n->left);
        free_persona(n->persona);
        free(n);
    }
    return;
}
void free_nodeStr(IndexNodeString* n){
    if(n!=NULL){
        free_nodeStr(n->right);
        free_nodeStr(n->left);
        free(n->value);
        free_persona(n->persona);
        free(n);
    }
    return;
}
void free_database(Database* d){
    free_nodeStr(d->address);    
    free_nodeStr(d->name);
    free_nodeStr(d->surname);
    free_nodeInt(d->age);
    free(d);
    return;
}

//INSERT
void insert(Database *database, Persona *persona) {
    if (database == NULL || persona == NULL) {
        return;
    }  
    Persona* temp = copy(persona); //creo una copia di persona perchè non posso modificare l'originale
    if (temp == NULL) {
        printf("Failed to allocate memory for temp\n");
        return;
    }
    if (database->address == NULL && database->age == NULL && database->name == NULL && database->surname == NULL) {
        IndexNodeString *nodeAdd = nodeStr_create(temp->address, temp);
        IndexNodeString *nodeName = nodeStr_create(temp->name, temp);
        IndexNodeString *nodeSur = nodeStr_create(temp->surname, temp);
        IndexNodeInt *nodeAge = nodeInt_create(temp->age, temp);

        if (nodeAdd == NULL || nodeName == NULL || nodeSur == NULL || nodeAge == NULL) {
            printf("Failed to create index nodes\n");
            free(temp);
            return;
        }
        
        database->address = nodeAdd;
        database->name = nodeName;
        database->surname = nodeSur;
        database->age = nodeAge;
        return;
    }
    else {
        insertName(temp->name, database->name,temp);    //name
        insertName(temp->surname,database->surname,temp); //surname
        insertName(temp->address,database->address,temp); //address
        insertAge(temp->age,database->age,temp); //age
        //printf("Non so come comportarmi FINE\n");
    }
    free(temp);
}
void insertName(char* value, IndexNodeString* root, Persona* p){
    if(root==NULL) {
        return;
    }
    if(strcmp(value,root->value)==0){
        //nuova istanza di persona dentro quella già esistente
        printf("persona già inserita\n");
        return;
    }
    if(strcmp(value,root->value)<0){
        if(root->left==NULL){
            IndexNodeString* newNode = nodeStr_create(value,p);
            if(!newNode) {
                printf("Errore nella creazione del nodo\n");
                return;
            }
            root->left = newNode;
            return;
        }
        insertName(value,root->left,p);
        return;
    }
    if(root->right ==NULL){
        IndexNodeString* newNode = nodeStr_create(value,p);
        root->right = newNode;
        return;
    }
    insertName(value,root->right,p);
}
void insertAge(int value, IndexNodeInt* root, Persona* p){
    if(root==NULL) {
        return;
    }
    if(value == root->value){
        //nuova istanza di persona dentro quella già esistente
        printf("persona già inserita\n");
        return;
    }
    if(value < root->value){
        if(root->left==NULL){
            IndexNodeInt* newNode = nodeInt_create(value,p);
            if(!newNode) {
                printf("Errore nella creazione del nodo\n");
                return;
            }
            root->left = newNode;
            return;
        }
        insertAge(value,root->left,p);
        return;
    }
    if(root->right ==NULL){
        IndexNodeInt* newNode = nodeInt_create(value,p);
        root->right = newNode;
        return;
    }
    insertAge(value,root->right,p);
}

//FIND
Persona* findByName(Database * database, char * name){
    return findByNameAUX(database->name,name);
}
Persona* findByNameAUX(IndexNodeString* root, char* name){
    if(root==NULL){
        printf("Error: %s not found\n",name);
        return NULL;
    }
    if(strcmp(name, root->value) == 0){
        return root->persona;
    } else if(strcmp(name, root->value) < 0){
        return findByNameAUX(root->left,name);
    } else{
        return findByNameAUX(root->right,name);
    }
}
Persona* findByAgeAUX(IndexNodeInt* root,  int age){
    if(root==NULL){
        printf("Error: %d not found\n",age);
        return NULL;
    }
    if(age == root->value){
        return root->persona;
    } else if(age < root->value){
        return findByAgeAUX(root->left,age);
    } else{
        return findByAgeAUX(root->right,age);
    }
}
Persona* findBySurname(Database * database, char * surname){
    return findByNameAUX(database->surname,surname);
}
Persona* findByAddress(Database * database, char * address){
    return findByNameAUX(database->address,address);
}
Persona* findByAge(Database * database, int age){
    return findByAgeAUX(database->age,age);
}
