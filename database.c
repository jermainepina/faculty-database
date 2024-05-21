#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.csv"

// Utility function to print employee information
void printEmployee(int id, const char* firstname, const char* lastname, int age, const char* position) {
    char fullName[32];
    snprintf(fullName, sizeof(fullName), "%s %s", firstname, lastname);

    printf("| %-3d | %-20s | %-3d | %-18s |\n", id, fullName, age, position);
    printf("+-----+----------------------+-----+--------------------+\n");
}


// Check if employee ID exists
int checkID(char* filename, int id) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
        return -1;
    }

    char line[100];
    int currid;
    int idFound = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &currid);
        if (currid == id) {
            idFound = 1;
        }
    }

    return idFound;
    fclose(file);
}

// Add employee to file
void addEmployee(char* filename, int id, char *firstname, char *lastname, int age, char *position) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
    }

    fprintf(file, "%d,%s,%s,%d,%s\n", id, firstname, lastname, age, position);
    printf("\nEmployee added to database\n");
    fclose(file);
}

// Remove employee from file 
void removeEmployee(char* filename, int id) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
    }

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

    fclose(file);
    fclose(temp);

    if (idFound == 0) {
        printf("Error: Employee ID not found!\n");
        remove("temp.csv");
    } else {
        remove(filename);
        rename("temp.csv", filename);
        printf("\nEmployee with ID %d removed successfully\n", id);
    }
}

// Return information of employee given their ID
void searchID(char* filename, int id) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
        return;
    }

    char line[100];
    int currid;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &currid);
        if (currid == id) {
            char firstname[15];
            char lastname[15];
            char position[20];
            int age;
            sscanf(line, "%*d,%14[^,],%14[^,],%d,%19[^,\n]", firstname, lastname, &age, position);

            // Expand teaching assistant and athletic staff abbreviations
            if (strcmp(position, "ta") == 0) 
                strcpy(position, "teaching assistant");
            else if (strcmp(position, "athletic") == 0)
            strcpy(position, "athletic staff");
            
            printf("+-----+----------------------+-----+--------------------+\n");
            printf("| %-3s | %-20s | %-2s | %-18s |\n", "ID", "Name", "Age", "Position");
            printf("+-----+----------------------+-----+--------------------+\n");
            printEmployee(id, firstname, lastname, age, position);
            fclose(file);
            return;
        }
    }

    printf("Employee with ID %d not found.\n", id);
    fclose(file);
}

// Return information of employee given their Name
void searchName(char* filename, char *firstname, char *lastname) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
        return;
    }

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
                // Combine first and last name
                int length = strlen(firstname) + strlen(lastname) + 2;
                char name[length];
                strcpy(name, firstname);
                strcat(name, " ");
                strcat(name, lastname);

                // Expand teaching assistant and athletic staff abbreviations
                if (strcmp(position, "ta") == 0) 
                    strcpy(position, "teaching assistant");
                else if (strcmp(position, "athletic") == 0)
                    strcpy(position, "athletic staff");

                printf("+-----+----------------------+-----+--------------------+\n");
                printf("| %-3s | %-20s | %-2s | %-18s |\n", "ID", "Name", "Age", "Position");
                printf("+-----+----------------------+-----+--------------------+\n");
                printEmployee(id, firstname, lastname, age, position);
                printf("\nNOTE: Two or more employees may share the same name. Consider searching by ID to avoid incorrect employee.\n");
                fclose(file);
                return;
            }    
        }

    printf("Employee with name %s %s not found.\n", firstname, lastname);
    fclose(file);
}

// Get list of employees of certain position 
void getPosition(char* filename, char *key) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
    }

    printf("+-----+----------------------+-----+--------------------+\n");
    printf("| %-3s | %-20s | %-2s | %-18s |\n", "ID", "Name", "Age", "Position");
    printf("+-----+----------------------+-----+--------------------+\n");
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char firstname[15];
        char lastname[15];
        char position[20];
        int age, id;
        sscanf(line, "%d,%14[^,],%14[^,],%d,%19[^,\n]", &id, firstname, lastname, &age, position);
        if (strcmp(key, position) == 0) {
            // Combine first and last name
            int length = strlen(firstname) + strlen(lastname) + 2;
            char name[length];
            strcpy(name, firstname);
            strcat(name, " ");
            strcat(name, lastname);

            // Expand teaching assistant and athletic staff abbreviations
            if (strcmp(position, "ta") == 0) 
                strcpy(position, "teaching assistant");
            else if (strcmp(position, "athletic") == 0)
                strcpy(position, "athletic staff");

            printEmployee(id, firstname, lastname, age, position);
        }
    }
    
    fclose(file);
}

// Get entire registry of employees
void getRegistry(char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file!\n");
    }

    printf("+-------------------------------------------------------+\n");
    printf("| Employee registry:                                    |\n");
    printf("+-----+----------------------+-----+--------------------+\n");
    printf("| %-3s | %-20s | %-2s | %-18s |\n", "ID", "Name", "Age", "Position");
    printf("+-----+----------------------+-----+--------------------+\n");

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char firstname[15];
        char lastname[15];
        char position[20];
        int age, id;
        sscanf(line, "%d,%14[^,],%14[^,],%d,%19[^,\n]", &id, firstname, lastname, &age, position);
        // Combine first and last name
        int length = strlen(firstname) + strlen(lastname) + 2;
        char name[length];
        strcpy(name, firstname);
        strcat(name, " ");
        strcat(name, lastname);

        // Expand teaching assistant and athletic staff abbreviations
        if (strcmp(position, "ta") == 0) 
            strcpy(position, "teaching assistant");
        else if (strcmp(position, "athletic") == 0)
            strcpy(position, "athletic staff");

        printEmployee(id, firstname, lastname, age, position);
    }

    fclose(file);
}

int main() {
    // Example usage
    int choice;
    int id;
    int age;
    char firstname[15];
    char lastname[15];
    char *position;
    while (1) {
        printf("\nFaculty Database\n");
        printf("Available commands:\n");
        printf("1. Add employee to database\n");
        printf("2. Get employee information\n");
        printf("3. Get registry\n");
        printf("4. Get list of employees by position\n");
        printf("5. Remove employee\n");
        printf("6. Exit\n\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                // Add employee to database
                while (1) {
                    printf("Enter ID: ");
                    scanf("%d", &id);
                    
                    if (!checkID(FILENAME, id)) {
                        break;
                    } else printf("ERROR: ID taken\n");
                }
                printf("Enter name (first and last separated by a whitespace): ");
                scanf("%s %s", firstname, lastname);
                printf("Enter age: ");
                scanf("%d", &age);
                printf("List of available positions:\n* teacher\n* teaching assistant (input 'ta')\n* athletic staff (input 'athletic')\n* nurse\n* janitor\n* cook\n* principal\n\nInput position: ");
                scanf("%s", position);
                addEmployee(FILENAME, id, firstname, lastname, age, position);
                break;
            }
            case 2: {
                // Get employee from database
                printf("\nAvailable commands:\n");
                printf("1. Lookup by name:\n");
                printf("2. Lookup by ID:\n\n");
                scanf("%d", &choice);
                if (choice == 1) {
                    printf("Enter first name: ");
                    scanf("%s", firstname);
                    printf("Enter last name: ");
                    scanf("%s", lastname);
                    searchName(FILENAME, firstname, lastname);
                    break;
                } else if (choice == 2) {
                    printf("Enter ID: ");
                    scanf("%d", &id);
                    searchID(FILENAME, id);
                    break;
                }
            }
            case 3: {
                // Get entire registry
                getRegistry(FILENAME);
                break;
            }
            case 4: {
                // Get list of employees with specific position
                printf("List of available positions:\n* teacher\n* teaching assistant (input 'ta')\n* athletic staff (input 'athletic')\n* nurse\n* janitor\n* cook\n* principal\nInput position: ");
                scanf("%s", position);
                getPosition(FILENAME, position);
                break;
            }
            case 5: {
                // Delete employee from database
                printf("\nCAUTION: This will delete employee from database permanently\nEnter employee ID: ");
                scanf("%d", &id);
                removeEmployee(FILENAME, id);
                break;
            }
            case 6: {
                // Exit system
                printf("\nExiting... \n");
                return 0;
            }
            default: {
                // Invalid choice
                printf("\nInvalid choice.\n");
                break;
            }
        }
    }
    return 0;
}



