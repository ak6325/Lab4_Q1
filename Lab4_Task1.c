// Including Libraries for functions
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  

// Function to check if a string represents a valid float
int isValidFloat(const char *str) {
    char *endptr;  // Pointer to character after the number
    strtod(str, &endptr);  // Converts string to double
    return (*endptr == '\0');  // Valid if endptr points to null character
}

// Main function
int main() {
    FILE *inputFile, *outputFile;  // File pointers for input and output files
    char line[50];  // Buffer to store each line from the file
    int invalidCount = 0;  // Counter for invalid float values
    
    // Opens the input file
    inputFile = fopen("data.txt", "r");  // Opens file in read mode
    if (inputFile == NULL) {  // Checks if file opening has failed
        perror("Error opening input file");  // Prints error message
        return 1;  // Returns with error code
    }
    
    // Open the output file
    outputFile = fopen("valid_data.txt", "w");  // Opens file in write mode
    if (outputFile == NULL) {  // Checks if file opening failed
        perror("Error opening output file");  // Prints error message
        fclose(inputFile);  // Closes input file
        return 1;  // Returns with error code
    }
    
    // Reads each line in the file
    while (fgets(line, sizeof(line), inputFile) != NULL) {  // Reads line from input file
        // Removes any newline character from the line
        line[strcspn(line, "\n")] = '\0';  // Replaces newline with null character

        // Checks if line represents a valid float
        if (isValidFloat(line)) {
            fprintf(outputFile, "%s\n", line);  // Writes valid float to output file
        } else {
            invalidCount++;  // Increments invalid count
        }

        // Checks for read error
        if (ferror(inputFile)) {  // Checks if there was a read error
            perror("Error reading input file");  // Prints error message
            fclose(inputFile);  // Closes input file
            fclose(outputFile);  // Closes output file
            return 1;  // Returns with error code
        }
    }

    // Checks if end-of-file was reached
    if (!feof(inputFile)) {  // Checks if end of file was not reached
        perror("Error: unexpected end of file");  // Prints error message
    }

    // Closes both files
    fclose(inputFile);  // Closes input file
    fclose(outputFile);  // Closes output file

    // Prints the number of invalid values
    printf("There are %d invalid float values!\n", invalidCount);  // Prints invalid count

    return 0;  // Returns success code
}