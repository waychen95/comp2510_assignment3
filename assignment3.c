#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

// Structure to hold employee information
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
} Employee;

// Function to compare two employee records for sorting
int compareEmployees(const void *a, const void *b) {
    const Employee *empA = (const Employee *)a;
    const Employee *empB = (const Employee *)b;
    
    // Compare names
    int nameComparison = strcmp(empA->name, empB->name);
    if (nameComparison != 0)
        return nameComparison;
    
    // If names are the same, compare IDs
    return empA->id - empB->id;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    // Open input file
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    // Open output file
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("Error: Could not open output file.\n");
        fclose(inputFile);
        return 1;
    }

    // Read input file line by line
    char line[256];
    Employee employees[1000]; // Assuming a maximum of 1000 employees
    int employeeCount = 0;
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        if (line[0] == 'E') // End designator reached
            break;

        // Parse line into employee ID, name, and salary
        int id;
        char name[MAX_NAME_LENGTH];
        float salary;
        if (sscanf(line, "%d,%[^,],%f", &id, name, &salary) == 3) {
            // Store employee record
            Employee emp;
            emp.id = id;
            strncpy(emp.name, name, MAX_NAME_LENGTH);
            emp.salary = salary;
            employees[employeeCount++] = emp;

            // Debugging output
            printf("Parsed: ID=%d, Name=%s, Salary=%.2f\n", id, name, salary);
        } else {
            printf("Error: Invalid input format for line: %s", line);
        }
    }

    // Sort employee records
    qsort(employees, employeeCount, sizeof(Employee), compareEmployees);

    // Write sorted records to output file
    for (int i = 0; i < employeeCount; i++) {
        fprintf(outputFile, "%d,%s,%.2f\n", employees[i].id, employees[i].name, employees[i].salary);
    }

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    printf("Employee records sorted and written to %s\n", argv[2]);

    return 0;
}
