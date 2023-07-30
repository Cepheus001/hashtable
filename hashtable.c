#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10


typedef struct person{
    char name[MAX_NAME];
    int age;
    struct person *next;
} person;

person * hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i=0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

bool init_hash_table() {
    for (int i=0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void print_table() {
    printf("---START---\n");
    for (int i=0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t%s\n", i);
            person *tmp = hash_table[i];
            while (tmp != NULL) {
                printf("%s \n", tmp->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("---END---\n");
}

bool hash_table_insert(person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

person *hash_table_lookup(char *name) {
    int index = hash(name);
    person *tmp = hash_table[index];
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
        tmp = tmp->next;
    }
    return tmp;
}

person *hash_table_delete(char *name) {
    int index = hash(name);
    person *tmp = hash_table[index];
    person *prev = NULL;
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL ) return NULL;
    if (prev == NULL) {
        hash_table[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    return tmp;
}

int main() {

    init_hash_table();

    person Jacob = {.name="Jacob", .age=256};
    person Sven = {.name="Sven", .age=75};
    person Marie = {.name="Marie", .age=26};
    person Scott = {.name="Scott", .age=21};
    person Rob = {.name="Rob", .age=43};
    person Sophia = {.name="Sophia", .age=27};
    person John = {.name="John", .age=26};
    person Alma = {.name="Alma", .age=19}; 

    hash_table_insert(&Jacob);
    hash_table_insert(&Sven);
    hash_table_insert(&Marie);
    hash_table_insert(&Scott);
    hash_table_insert(&Rob);
    hash_table_insert(&Sophia);
    hash_table_insert(&John);
    hash_table_insert(&Alma);

    print_table();

    
    person *tmp = hash_table_lookup("Marie");
    if (tmp == NULL) {
        printf("User not found!\n");
    } else {
        printf("Found %s.\n", tmp->name);
    }

    tmp = hash_table_lookup("Scott");
    if (tmp == NULL) {
        printf("User not found!\n");
    } else {
        printf("Found %s.\n", tmp->name);
    }

    hash_table_delete("Marie");
    tmp = hash_table_lookup("Marie");
     if (tmp == NULL) {
        printf("User not found!\n");
    } else {
        printf("Found %s.\n", tmp->name);
    }
   
    print_table();


    /*printf("Jacob => %u\n", hash("Jacob"));
    printf("Sven => %u\n", hash("Sven"));
    printf("Marie => %u\n", hash("Marie"));
    printf("Scott => %u\n", hash("Scott"));
    printf("Rob => %u\n", hash("Rob"));
    printf("Roberto => %u\n", hash("Roberto"));
    printf("Sophia => %u\n", hash("Sophia"));
    printf("John => %u\n", hash("John"));
    printf("Alma => %u\n", hash("Alma"));
    printf("Sarra => %u\n", hash("Sarra")); */
    return 0;
}