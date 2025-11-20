#include <stdio.h>    
#include <string.h>   
#include <ctype.h>    

// Function to validate if a name contains only printable, non-numeric characters
// Parameters: const char *name - pointer to the string to validate 
// Returns: 1 if valid, 0 if invalid
int isValidName(const char *name) {
    // Check if name is empty or NULL pointer
    // strlen(name) returns the length of the string (number of characters)
    if (name == NULL || strlen(name) == 0) {
        return 0; // Return 0 to indicate invalid name
    }
    
    // Loop through each character in the name string
    // The loop continues until we reach '\0' (null terminator that marks end of string)
    for (int i = 0; name[i] != '\0'; i++) {
        // isprint() checks if character is a printable character (ASCII 32-126)
        // Printable characters include letters, digits, punctuation, and space
        // The ! (NOT operator) reverses the result
        if (!isprint(name[i])) {
            return 0; // Return 0 if we find a non-printable character
        }
        
        // isdigit() checks if character is a numeric digit ('0' through '9')
        // Returns non-zero value if character is a digit, 0 otherwise
        if (isdigit(name[i])) {
            return 0; // Return 0 if we find a digit (names shouldn't contain numbers)
        }
    }
    
    return 1; // If we passed all checks, return 1 to indicate the name is valid
}

int main() {
    // Declare file pointer to handle file operations
    FILE *file;
    
    // Buffer to store each line read from the file (max 200 characters)
    char line[200];
    
    // Array to store the student name extracted from each line (max 100 characters)
    char name[100];
    
    // Variable to store the mark (score) for each student
    int mark;
    
    // Counter for valid (correctly formatted) records
    int validCount = 0;
    
    // Counter for corrupted (incorrectly formatted) records
    int corruptedCount = 0;
    
    // Accumulator to store the sum of all marks for average calculation
    int totalMarks = 0;
    
    // Variable to store the return value of sscanf (number of successfully read items)
    int result;
    
    // Open the file named "students.txt" in read mode ("r")
    // fopen returns a file pointer if successful, NULL if it fails
    file = fopen("students.txt", "r");
    
    // Check if file opening failed (file pointer is NULL)
    // This happens when file doesn't exist or we lack read permissions
    if (file == NULL) {
        printf("Error: Could not open file 'students.txt'\n");
        printf("Please ensure the file exists in the same directory as this program.\n");
        return 1; // Return 1 to indicate program terminated with an error
    }
    
    // Display success message to confirm file was opened successfully
    printf("File 'students.txt' opened successfully.\n\n");
    
    // Print header for the valid records section
    printf("VALID RECORDS\n");
    
    // Main file reading loop - continues until end of file (EOF) is reached
    // fgets() reads one line at a time from the file into the 'line' buffer
    // fgets returns NULL when it reaches the end of file or encounters an error
    while (fgets(line, sizeof(line), file) != NULL) {
        // sscanf() parses the line string and extracts formatted data
        // Format: "%s %d" means read a string (no spaces) then an integer
        // Returns the number of items successfully read and assigned
        result = sscanf(line, "%s %d", name, &mark);
        
        // Check if exactly 2 items were read (name and mark) AND the name passes validation
        // result == 2 ensures both name and mark were successfully parsed
        // isValidName(name) returns 1 if name contains only valid characters
        if (result == 2 && isValidName(name)) {
            // This is a valid record, so increment the valid counter
            validCount++;
            
            // Add this student's mark to the running total for average calculation
            totalMarks += mark;
            
            // Display the valid student name and mark to the console
            printf("%s %d\n", name, mark);
        } else {
            // If it couldn't read both fields OR name is invalid, count as corrupted
            // Corrupted records are not displayed, only counted
            corruptedCount++;
        }
    }
    
    // Close the file to free system resources and ensure data is properly written
    // Always close files after no more using them
    fclose(file);
    
    // Print header for the summary statistics section
    printf("\nSUMMARY\n");
    
    // Display the total number of valid records processed
    printf("Total valid records: %d\n", validCount);
    
    // Display the total number of corrupted records encountered
    printf("Total corrupted records: %d\n", corruptedCount);
    
    // Only calculate average if there is at least one valid record
    // This prevents division by zero error
    if (validCount > 0) {
        // Cast totalMarks to double to perform floating-point division
        // Without the cast, integer division would truncate the decimal part
        double average = (double)totalMarks / validCount;
        
        // Display average with 2 decimal places using %.2f format specifier
        printf("Average mark of valid records: %.2f\n", average);
    } else {
        // If no valid records exist, inform user that average cannot be calculated
        printf("No valid records found. Cannot calculate average.\n");
    }
    
    return 0; // Return 0 to indicate successful program completion
}
