#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <jansson.h>
#include "send_email.h"
void convertFromJSON() {
        const char output_filename[20]="Karachi.txt";
      // Get the current date
        time_t current_time;
        struct tm *timeinfo;
        char date[11];  // Adjust the size accordingly
        time(&current_time);
        timeinfo = localtime(&current_time);

        // Format the date as a string
        strftime(date, sizeof(date), "%Y-%m-%d", timeinfo);
    FILE *json_file = fopen("JSON data.txt", "r");
    if (json_file == NULL) {
        fprintf(stderr, "Error opening the file for reading.\n");
        return; // Exit with an error code
    }

    // Determine the size of the file
    fseek(json_file, 0, SEEK_END);
    long json_file_size = ftell(json_file);
    fseek(json_file, 0, SEEK_SET);

    // Read the content of the file into a buffer
    char *json_data = (char *)malloc(json_file_size + 1);
    fread(json_data, 1, json_file_size, json_file);
    json_data[json_file_size] = '\0'; // Null-terminate the string

    // Close the file as you no longer need it
    fclose(json_file);

    // Parse the JSON data using Jansson
    json_error_t error;
    json_t *root = json_loads(json_data, 0, &error);

    // Check for JSON parsing errors
    if (!root) {
        fprintf(stderr, "JSON parsing error: %s\n", error.text);
        free(json_data);
        return; // Exit with an error code
    }

 // Extract specific values (humidity, temp_c, temp_f, condition, wind_kph, wind_dir)
json_t *current = json_object_get(root, "current");
if (current) {
    json_t *condition = json_object_get(current, "condition");
    json_t *humidity = json_object_get(current, "humidity");
    json_t *temp_c = json_object_get(current, "temp_c");
    json_t *temp_f = json_object_get(current, "temp_f");
    //json_t *lastUpdated = json_object_get(current, "last_updated");
    json_t *wind_kph = json_object_get(current, "wind_kph");
    json_t *wind_dir = json_object_get(current, "wind_dir");
    json_t *pressue_mb=json_object_get(current, "pressure_mb");

    if (condition && humidity && temp_c && temp_f && wind_kph && wind_dir && pressue_mb) {
        // Print or save the values as needed

        printf("\t\t\t\tCondition: %s\n", json_string_value(json_object_get(condition, "text")));
        printf("\t\t\t\tHumidity: %lld%%\n", (long long int)json_integer_value(humidity));
        printf("\t\t\t\tTemperature (C): %.1f\n", json_real_value(temp_c));
        printf("\t\t\t\tTemperature (F): %.1f\n", json_real_value(temp_f));
        printf("\t\t\t\tPressure: %.1f\n",json_real_value(pressue_mb));
        //printf("Last Updated: %s\n", json_string_value(lastUpdated));
        printf("\t\t\t\tWind Speed (kph): %.1f\n", json_real_value(wind_kph));
        printf("\t\t\t\tWind Direction: %s\n", json_string_value(wind_dir));
        
        
        // Write the values to another file
        FILE *output_file = fopen(output_filename, "a");
        if (output_file) {
            fprintf(output_file, "Date: %s\n",date);
            fprintf(output_file, "Condition: %s\n", json_string_value(json_object_get(condition, "text")));
            fprintf(output_file, "Humidity: %lld%%\n", (long long int)json_integer_value(humidity));
            fprintf(output_file, "Temperature (C): %.1f\n", json_real_value(temp_c));
            fprintf(output_file, "Temperature (F): %.1f\n", json_real_value(temp_f));
            fprintf(output_file, "Pressure: %.1f\n",json_real_value(pressue_mb));
            fprintf(output_file, "Wind Speed (kph): %.1f\n", json_real_value(wind_kph));
            fprintf(output_file, "Wind Direction: %s\n", json_string_value(wind_dir));
            fprintf(output_file,"\n\n");
            fclose(output_file);
        } else {
            fprintf(stderr, "Error opening the output file for writing.\n");
        }
        if (json_real_value(temp_c) <8.0  || json_real_value(temp_c) > 35.0){
    const char *warning_file = "warning_log.txt";
    const char *recipient_email = "aadi64499@gmail.com";
    const char *sender_email = "aadi64499@gmail.com";    
       
    
    send_temp_warning_and_threat(recipient_email, sender_email, warning_file, json_string_value(condition), json_real_value(temp_c));
        }
    }
    
}



    // Cleanup
    free(json_data);
    json_decref(root);

    return;
}