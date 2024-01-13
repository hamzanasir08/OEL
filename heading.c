#include <stdio.h>
#include <stdlib.h>
void printCenteredHeading(const char *text) {
    int text_length = snprintf(NULL, 0, "%s", text);

    // Calculate spaces needed before and after the heading to center it
    int total_spaces = 80 - text_length; // Assuming the total width of your page is 80 columns
    int spaces_before = total_spaces / 2;
    int spaces_after = total_spaces - spaces_before;

    // Print the centered heading
    printf("\n╔");
    for (int i = 0; i < spaces_before; ++i) {
        printf("═");
    }
    printf(" %s ", text);
    for (int i = 0; i < spaces_after; ++i) {
        printf("═");
    }
    printf("╗\n\n");
}