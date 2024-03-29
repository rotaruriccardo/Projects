
// This represent a record in the only schema of this database
struct Persona {
    char name[20];
    char surname[50];
    char address[100];
    int age;
};

typedef struct Persona Persona;

// This is a node of an index that hold a string
typedef struct IndexNodeString {
    char * value;
    Persona *persona;
    struct IndexNodeString * left;
    struct IndexNodeString * right;
} IndexNodeString;

// This is a node of an index that hold an int
typedef struct IndexNodeInt {
    int value;
    Persona *persona;
    struct IndexNodeInt * left;
    struct IndexNodeInt * right;
} IndexNodeInt;

// A database hold a set of records and a set of indexes
typedef struct {
    IndexNodeString * name;
    IndexNodeString * surname;
    IndexNodeString * address;
    IndexNodeInt * age;
} Database;

// TODO implement the following methods
// The method return a Persona or NULL 

//AUX
void print_treeString(IndexNodeString* root);
void print_treeInt(IndexNodeInt* root);
void print_persona(Persona* p);
Persona* create_persona(const char* name,const char* surname,const char* address, int age);
Persona* create_null_persona();
Database* create_database();
IndexNodeInt* nodeInt_create(int value, Persona* p);
IndexNodeString* nodeStr_create(char* value, Persona* p);
Persona *copy(Persona *p);
void free_nodeInt(IndexNodeInt* n);
void free_nodeStr(IndexNodeString* n);
void free_database(Database* d);
void free_persona(Persona* p);
void insertName(char* value, IndexNodeString* root, Persona* p);
void insertAge(int value, IndexNodeInt* root, Persona* p);
Persona* findByNameAUX(IndexNodeString* root, char* name);
Persona* findByAgeAUX(IndexNodeInt* root,  int age);

//DEFAULT
void insert(Database * database, Persona * persona);
Persona* findByName(Database * database, char * name);
Persona* findBySurname(Database * database, char * surname);
Persona* findByAddress(Database * database, char * address);
Persona* findByAge(Database * database, int age);