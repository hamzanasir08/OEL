#ifndef CALCULATE_AVERAGES_H
#define CALCULATE_AVERAGES_H

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

typedef struct {
    char date[11];
    double avg_temp_c;
    double avg_temp_f;
    double avg_humidity;
    double avg_pressure;
    double avg_wind_speed;
} Average;
void getCurrentDate(char *currentDate);
void calculateAveragesAndWrite();

#endif  // CALCULATE_AVERAGES_H
