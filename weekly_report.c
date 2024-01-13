#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 100

int main() {
    // Open the input file for reading
    FILE *inputFile = fopen("Karachi_avg.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open the output file for writing
    FILE *outputFile = fopen("report.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }
    for (int i=0;i<170;i++){
        fprintf(outputFile,"-");
    }
    fprintf(outputFile,"\n");
    for (int b=0;b<70;b++){
        fprintf(outputFile," ");
    }
    fprintf(outputFile,"Weekly Report\n");
    for (int i=0;i<170;i++){
        fprintf(outputFile,"-");
    }
    fprintf(outputFile,"\n");

    // Get the current date and time
    time_t currentTime;
    time(&currentTime);

    // Calculate the start time for the last seven days
    time_t sevenDaysAgo = currentTime - (7 * 24 * 3600);

    // Flag to indicate whether to copy lines
    int copyLines = 0;

    // Iterate through the file and copy data for the last seven days
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Check if the line contains the date
        if (strstr(line, "Date:") != NULL) {
            // Parse the date from the line
            int year, month, day;
            if (sscanf(line, "Date: %d-%d-%d", &year, &month, &day) == 3) {
                struct tm fileDate = {0};
                fileDate.tm_year = year - 1900;
                fileDate.tm_mon = month - 1;
                fileDate.tm_mday = day;

                // Convert file date to time_t for comparison
                time_t fileDateTime = mktime(&fileDate);

                // Check if the date is within the desired range
                copyLines = (fileDateTime >= sevenDaysAgo && fileDateTime <= currentTime);

                // Include the line in the report file with date
                if (copyLines) {
                    fprintf(outputFile, "Date: %d-%02d-%02d\n", year, month, day);
                }
            }
        } else if (copyLines) {
            // Include the line in the report file if copyLines is true
            fprintf(outputFile, "%s", line);
        }
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Report generated succesfully.\n");

    return 0;
}
