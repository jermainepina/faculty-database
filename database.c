#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.csv"

// Add employee to file 
void addEmployee(char* filename, int id, char *firstname, char *lastname, int age, char *position) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
    }

    fprintf(file, "%d,%s,%s,%d,%s\n", id, firstname, lastname, age, position);

    fclose(file);
}

// Remove employee from file 
void removeEmployee(char* filename, int id) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
    }

    // TODO: remove employee based on id (print)

    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("Error: Unable to create temporary file!\n");
        fclose(file);
        return;
    }

    char line[50];
    int currid;
    int idFound = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &currid);
        if (currid != id) {
            fputs(line, temp);
        } else idFound = 1;
    }

    if (idFound == 0) {
        printf("Error: Employee ID not found!\n");
        fclose(file);
        fclose(temp);
        remove("temp.csv");
    } else {

        fclose(file);
        fclose(temp);

        remove(filename);
        rename("temp.csv", filename);
        printf("Removed successfully\n");
    }
}

// Return information of employee given their ID
void searchID(char* filename, int id) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
        return;
    }

    // TODO: get employee based on id (print)
    char line[100];
    int currid;
    int idFound = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &currid);
        if (currid == id) {
            char firstname[15];
            char lastname[15];
            char position[20];
            int age;
            sscanf(line, "%*d,%14[^,],%14[^,],%d,%19[^,\n]", firstname, lastname, &age, position);
            printf("ID: %d\nName: %s %s\nAge: %d\nPosition: %s\n", id, firstname, lastname, age, position);
            idFound = 1;
            break;
        }
    }

    if (!idFound) {
        printf("Employee with ID %d not found.\n", id);
    }

    fclose(file);
}

// Return information of employee given their Name
void searchName(char* filename, char *firstname, char *lastname) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
        return;
    }

    // TODO: get employee based on id (print)
    char line[100];
    int nameFound = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char currfirst[15];
        char currlast[15];
        char position[20];
        int age, id;
        sscanf(line, "%d,%14[^,],%14[^,],%d,%19[^,\n]", &id, currfirst, currlast, &age, position);
        if (strcmp(currfirst, firstname) == 0)
            if (strcmp(currlast, lastname) == 0) {
                printf("NOTE: Two or more employees may share the same name. Consider searching by ID to avoid incorrect employee.\nID: %d\nName: %s %s\nAge: %d\nPosition: %s\n", id, firstname, lastname, age, position);
                nameFound = 1;
                break;
            }    
        }

    if (!nameFound) {
        printf("Employee with ID %s %s not found.\n", firstname, lastname);
    }

    fclose(file);
}

// Get list of employees of certain position 
void getPosition(char* filename, char *key) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
    }

    // TODO: get list of employees based on key (print)
    printf("+-----+----------------------+-----+--------------------+\n");
    printf("| %-3s | %-20s | %-2s | %-18s |\n", "ID", "Name", "Age", "Position");
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char firstname[15];
        char lastname[15];
        char position[20];
        int age, id;
        sscanf(line, "%d,%14[^,],%14[^,],%d,%19[^,\n]", &id, firstname, lastname, &age, position);
        if (strcmp(key, position) == 0) {
            strcat(firstname, " ");
            char *name = strcat(firstname, lastname);
            printf("+-----+----------------------+-----+--------------------+\n");
            printf("| %-3d | %-20s | %-3d | %-18s |\n", id, name, age, position);
        }
    }
    printf("+-----+----------------------+-----+--------------------+\n");
    
    fclose(file);
}

// Get entire registry of employees
void getRegistry(char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
    }

    // TODO: get list of employees (print)
    printf("+-----+----------------------+-----+--------------------+\n");
    printf("| %-3s | %-20s | %-2s | %-18s |\n", "ID", "Name", "Age", "Position");
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char firstname[15];
        char lastname[15];
        char position[20];
        int age, id;
        sscanf(line, "%d,%14[^,],%14[^,],%d,%19[^,\n]", &id, firstname, lastname, &age, position);
        strcat(firstname, " ");
        char *name = strcat(firstname, lastname);
        printf("+-----+----------------------+-----+--------------------+\n");
        printf("| %-3d | %-20s | %-3d | %-18s |\n", id, name, age, position);
    }
    printf("+-----+----------------------+-----+--------------------+\n");
    
    fclose(file);
}

int main() {
    // Example usage
    addEmployee(FILENAME, 1, "Johnnnn", "Doe", 38, "Teacher");
    addEmployee(FILENAME, 2, "Bob", "Smith", 35, "Counselor");
    addEmployee(FILENAME, 3, "Jane", "Doe", 24, "Teacher");
    addEmployee(FILENAME, 4, "George", "Bush", 70, "Principal");
    addEmployee(FILENAME, 5, "Tom", "Brady", 46, "Janitor");
    searchName(FILENAME, "Bob", "Smith");

    return 0;
}



