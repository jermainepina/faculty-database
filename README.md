# Faculty Database Management System

## Description

This Faculty Database Management System is a C-based application that allows users to manage a database of employees. The system supports functionalities such as adding new employees, searching for employees by ID or name, removing employees, retrieving a list of employees based on their position, and displaying the entire registry of employees.

## Features

- **Add Employee:** Add a new employee to the database.
- **Search Employee:** Search for an employee by their ID or name.
- **Remove Employee:** Remove an employee from the database by their ID.
- **Get Employees by Position:** Retrieve a list of employees based on their position.
- **Get Entire Registry:** Display the entire list of employees in the database.

## File Structure

- **employees.csv:** The CSV file where employee data is stored.
- **main.c:** The main program file containing the implementation of the Faculty Database Management System.

## Functions

### `void printEmployee(int id, const char* firstname, const char* lastname, int age, const char* position)`

Utility function that formats and prints employee information

- **Parameters:**
  - `id`: The employee ID to check.
  - `firstname`: The employee's first name.
  - `lastname`: The employee's last name.
  - `age`: The employee's age.
  - `position`: The employee's position.


### `int checkID(char* filename, int id)`

Checks if an employee ID already exists in the database.

- **Parameters:**
  - `filename`: The name of the file containing employee data.
  - `id`: The employee ID to check.
- **Returns:** `1` if the ID exists, `0` if it doesn't, `-1` if there's an error opening the file.


### `void addEmployee(char* filename, int id, char *firstname, char *lastname, int age, char *position)`

Adds a new employee to the database.

- **Parameters:**
  - `filename`: The name of the file to which the employee data will be added.
  - `id`: The employee ID.
  - `firstname`: The employee's first name.
  - `lastname`: The employee's last name.
  - `age`: The employee's age.
  - `position`: The employee's position.


### `void removeEmployee(char* filename, int id)`

Removes an employee from the database by their ID.

- **Parameters:**
  - `filename`: The name of the file from which the employee data will be removed.
  - `id`: The employee ID to remove.


### `void searchID(char* filename, int id)`

Searches for an employee by their ID and prints their details.

- **Parameters:**
  - `filename`: The name of the file containing employee data.
  - `id`: The employee ID to search for.


### `void searchName(char* filename, char *firstname, char *lastname)`

Searches for an employee by their name and prints their details.

- **Parameters:**
  - `filename`: The name of the file containing employee data.
  - `firstname`: The employee's first name.
  - `lastname`: The employee's last name.


### `void getPosition(char* filename, char *key)`

Retrieves and prints a list of employees based on their position.

- **Parameters:**
  - `filename`: The name of the file containing employee data.
  - `key`: The position to filter employees by.


### `void getRegistry(char* filename)`

Prints the entire registry of employees.

- **Parameters:**
  - `filename`: The name of the file containing employee data.

## How to Run

1. **Compile the Program:**
   ```
   gcc -o faculty_database main.c
   ```

2. **Run the Program:**
   ```
   ./faculty_database
   ```

3. **Follow the On-Screen Instructions:** Choose from the available options to manage the employee database.

## Sample `employees.csv` Format

```
ID,FirstName,LastName,Age,Position
1,john,doe,30,teacher
2,jane,smith,25,ta
3,bob,johnson,40,athletic
```

## Notes

- Ensure the `employees.csv` file is in the same directory as the executable.
- Ensure any names are inputted in all lowercase letters.
- Employee positions are case-sensitive.
- The program supports basic error handling for file operations and invalid inputs.
- Position abbreviations:
  - `ta` for Teaching Assistant
  - `athletic` for Athletic Staff

## License

This project is licensed under the MIT License. See the LICENSE file for details.

---

This README provides an overview of the Faculty Database Management System, explaining its features, functions, and usage. Follow the instructions to compile and run the program, and refer to the sample CSV format for correct data entry.
