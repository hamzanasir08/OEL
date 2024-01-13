#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    char date[11];
    char condition[20];
    int humidity;
    double temp_c;
    double temp_f;
    double pressure;
    double wind_speed_kph;
    char wind_direction[4];
} WeatherData;



struct Average{
    char date[11];
    double avg_temp_c;
    double avg_temp_f;
    double avg_humidity;
    double avg_pressure;
    double avg_wind_speed;
};
void getCurrentDate(char *currentDate) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(currentDate, 11, "%Y-%m-%d", tm_info);
}
void calculateAveragesAndWrite() {
    const char filename[20]="Karachi.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening the file for reading.\n");
        return;
    }

    WeatherData data;
    int count = 0;
    double total_temp_c = 0.0;
    double total_temp_f = 0.0;
    int total_humidity = 0;
    double total_pressure = 0.0;
    double total_wind_speed_kph = 0.0;

    char currentDate[11];
    getCurrentDate(currentDate);

    while (fscanf(file, "Date: %s\nCondition: %s\nHumidity: %d%%\nTemperature (C): %lf\nTemperature (F): %lf\nPressure: %lf\nWind Speed (kph): %lf\nWind Direction: %s\n\n",
                  data.date, data.condition, &data.humidity, &data.temp_c, &data.temp_f, &data.pressure, &data.wind_speed_kph, data.wind_direction) == 8) {
        if (strcmp(data.date, currentDate) == 0) {
            total_temp_c += data.temp_c;
            total_temp_f += data.temp_f;
            total_humidity += data.humidity;
            total_pressure += data.pressure;
            total_wind_speed_kph += data.wind_speed_kph;
            count++;
        }
    }

    if (count > 0) {
        // Calculate averages
        double avg_temp_c = total_temp_c / count;
        double avg_temp_f = total_temp_f / count;
        double avg_humidity = (double)total_humidity / count;
        double avg_pressure = total_pressure / count;
        double avg_wind_speed_kph = total_wind_speed_kph / count;

        // Print averages
        printf("Average Temperature (C) for %s: %.2f\n", currentDate, avg_temp_c);
        printf("Average Temperature (F) for %s: %.2f\n", currentDate, avg_temp_f);
        printf("Average Humidity for %s: %.2f%%\n", currentDate, avg_humidity);
        printf("Average Pressure for %s: %.2f\n", currentDate, avg_pressure);
        printf("Average Wind Speed (kph) for %s: %.2f\n", currentDate, avg_wind_speed_kph);

        
        
   
    // Uptading the average file i.e.Karachi_avg.txt
    const char *inputFileName = "Karachi_avg.txt";
    const char *newfilename = "new.txt";

    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening the input file.\n");
        return ;
    }

    FILE *outputFile = fopen(newfilename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening the output file.\n");
        fclose(inputFile);
        return ;
    }

    char currentDate[11];
    getCurrentDate(currentDate);

    struct Average avg_data;

    // Read the file and write entries with dates less than the current date to the new file
    while (fscanf(inputFile, "Date: %s\nAverage Temperature (C) : %lf\nAverage Temperature (F) : %lf\nAverage Humidity : %lf%%\nAverage Pressure : %lf\nAverage Wind Speed (kph) : %lf\n\n",
                  avg_data.date, &avg_data.avg_temp_c, &avg_data.avg_temp_f, &avg_data.avg_humidity, &avg_data.avg_pressure, &avg_data.avg_wind_speed) == 6) {
        if (strcmp(avg_data.date, currentDate) < 0) {
            fprintf(outputFile, "Date: %s\n", avg_data.date);
            fprintf(outputFile, "Average Temperature (C) : %.2f\n", avg_data.avg_temp_c);
            fprintf(outputFile, "Average Temperature (F) : %.2f\n", avg_data.avg_temp_f);
            fprintf(outputFile, "Average Humidity : %.2f%%\n", avg_data.avg_humidity);
            fprintf(outputFile, "Average Pressure : %.2f\n", avg_data.avg_pressure);
            fprintf(outputFile, "Average Wind Speed (kph) : %.2f\n\n", avg_data.avg_wind_speed);
            fprintf(outputFile,"\n");
        }
    }

    fclose(inputFile);
    fclose(outputFile);    
    fclose(file);
    FILE * final_file=fopen(newfilename,"a");
    if (final_file==NULL){
        fprintf(stderr, "Error opening the output file.\n");
        return;
    }
        fprintf(final_file, "Date: %s\n",currentDate);
        fprintf(final_file, "Average Temperature (C) : %.2f\n", avg_temp_c);
        fprintf(final_file, "Average Temperature (F) : %.2f\n", avg_temp_f);
        fprintf(final_file, "Average Humidity : %.2f%%\n", avg_humidity);
        fprintf(final_file, "Average Pressure : %.2f\n", avg_pressure);
        fprintf(final_file, "Average Wind Speed (kph) : %.2f\n", avg_wind_speed_kph);
        fprintf(final_file, "\n\n");
        fclose(final_file);
    remove(inputFileName);

    rename("new.txt",inputFileName);    
    return;
    //fclose(output);
}

}
