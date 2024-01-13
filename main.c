#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "send_email.h"
#include "convert_from_json.h"
#include "current_date.h"
#include "calculate_averages.h"
#include "heading.h"


size_t WriteCallback(void *contents, size_t size, size_t nmemb, FILE *file) {
    size_t written = fwrite(contents, size, nmemb, file);
    return written;
}

int main() {
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "Error initializing libcurl.\n");
        return 1; // Exit with an error code
    }

    // Print a stylish centered heading for the city forecast
    printCenteredHeading("Karachi");
    
   

    FILE *json_file = fopen("JSON data.txt", "w");
    if (json_file == NULL) {
        fprintf(stderr, "Error opening the file for writing.\n");
        return 1; // Exit with an error code
    }
    
    curl_easy_setopt(curl, CURLOPT_URL, "https://weatherapi-com.p.rapidapi.com/current.json?q=Karachi");
    // Set the callback function
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    // Pass the file pointer to the callback function
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, json_file);
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: b3c9bcd2d4msh195c97f4e24953ap1b7c0djsn1a17ec6c5ab1");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    // Cleanup and close the file
    curl_easy_cleanup(curl);

    curl_global_cleanup();
    fclose(json_file);
    convertFromJSON();
    //calculate_Averages_of_oneday("Islamabad.txt");
    calculateAveragesAndWrite();
    return 0;
}
