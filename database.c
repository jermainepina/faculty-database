#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ID,
    NAME,
    AGE,
    POSITION
} Key;

typedef enum {
    JANITOR,
    TEACHING_ASSISTANT,
    TEACHER,
    COUNSELOR,
    NURSE,
    SECRETARY,
    PRINCIPAL
} Position;

typedef struct Employee {
    int id;
    char* name;
    int age;
    Position position;
} Employee;

void addEmployee(FILE *file, Employee) {

}

void removeEmployee(FILE *file, int id) {
    
}

void getEmployee(FILE *file, int id) {
    
}

void getList(FILE *file, Key key) {
    
}

void getRegistry(FILE *file) {
    
}

void main() {

}



