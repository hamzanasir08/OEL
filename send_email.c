#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void send_temp_warning_and_threat(const char *recipient, const char *sender, const char *logFilename, const char *temp_condition, double temp_c) {
    // Open the log file for appending
    printf("send function");
    FILE *logFile = fopen(logFilename, "a");
    if (logFile == NULL) {
        fprintf(stderr, "Failed to open log file %s for writing\n", logFilename);
        perror("fopen");
        return;
    }

    // Get the current timestamp
    time_t current_time;
    struct tm *timeinfo;
    char timestamp[64];
    time(&current_time);
    timeinfo = localtime(&current_time);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Append visibility information to the log file
    fprintf(logFile, "Timestamp: %s\n", timestamp);
    fprintf(logFile, "Temperature: %.2f degree\n", temp_c);
    //fprintf(logFile, "Visibility Condition: %s\n\n", visibility_condition);

    // Close the log file
    fclose(logFile);
    const char *threat_email_script_path;
    if (temp_c < 8.0){
    // Prepare the command to execute the threat email script
        threat_email_script_path = "./send_email_script_cold.sh";
    }
    else if (temp_c > 35.0){
        // Prepare the command to execute the threat email script
        threat_email_script_path = "./send_email_script_hot.sh";
    }
    
    char *command = (char *)malloc(512);  // Adjust the size accordingly
    if (command == NULL) {
        fprintf(stderr, "Failed to allocate memory for the command\n");
        return;
    }

    snprintf(command, 512, "%s '%s' '%s' '%s'", threat_email_script_path, recipient, sender, logFilename);

    // Execute the threat email script
    int result = system(command);

    // Check the result of the system command
    if (result == -1) {
        fprintf(stderr, "Failed to execute the threat email script\n");
        perror("system");
        free(command);  // Free allocated memory
        return;
    } else if (WIFEXITED(result) && WEXITSTATUS(result) != 0) {
        fprintf(stderr, "Email script exited with non-zero status: %d\n", WEXITSTATUS(result));

    }

    // Free allocated memory
    free(command);
}