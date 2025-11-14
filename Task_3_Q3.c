#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to validate if a name contains only printable, non-numeric characters
int isValidName(const char *name) {
    // Check if name is empty
    if (name == NULL || strlen(name) == 0) {
        return 0;
    }
    
    // Check each character in the name
    for (int i = 0; name[i] != '\0'; i++) {
        // Check if character is printable
        if (!isprint(name[i])) {
            return 0;
        }
        // Check if character is a digit
        if (isdigit(name[i])) {
            return 0;
        }
    }
    
    return 1; // Name is valid
}

int main() {
    FILE *file;
    char line[200];
    char name[100];
    int mark;
    int validCount = 0;
    int corruptedCount = 0;
    int totalMarks = 0;
    int result;
    
    // Open the file
    file = fopen("students.txt", "r");
    
    // Handle file I/O errors
    if (file == NULL) {
        printf("Error: Could not open file 'students.txt'\n");
        printf("Please ensure the file exists in the same directory as this program.\n");
        return 1;
    }
    
    // Display success message
    printf("File 'students.txt' opened successfully.\n\n");
    
    printf("VALID RECORDS\n");
    
    // Read records line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        // Try to parse name and mark from the line
        result = sscanf(line, "%s %d", name, &mark);
        
        // Check if we successfully read both name and mark, and name is valid
        if (result == 2 && isValidName(name)) {
            // Record is valid
            validCount++;
            totalMarks += mark;
            printf("%s %d\n", name, mark);
        } else {
            // Record is corrupted
            corruptedCount++;
        }
    }
    
    // Close the file
    fclose(file);
    
    // Display summary statistics
    printf("\nSUMMARY\n");
    printf("Total valid records: %d\n", validCount);
    printf("Total corrupted records: %d\n", corruptedCount);
    
    // Calculate and display average mark if there are valid records
    if (validCount > 0) {
        double average = (double)totalMarks / validCount;
        printf("Average mark of valid records: %.2f\n", average);
    } else {
        printf("No valid records found. Cannot calculate average.\n");
    }
    
    return 0;
}
