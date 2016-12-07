#include "TimeSelect.h"

int main(int argc, char** argv) {
    FILE* input = NULL, *output = NULL;
    time_t begin, end, current;
    struct tm rohdaten;
    char buffer[255];
    int ping_nr = 0, ping_pre, ping_post;

    if (argc != 3) { //Kontrolle, ob Kommandozeilenargumente korrekt übergeben wurden
        fprintf(stderr, "Usage: %s inputfile outputfile\n",argv[0]);
        return EXIT_FAILURE;
    }

    if (NULL == (input = fopen(argv[1], "r")) || NULL == (output = fopen(argv[2], "w+"))) {
        return EXIT_FAILURE;
    }

    /*Einlesen der Zeitangaben*/

    printf("Input the time in the following format: h:m:s_dd/mm/yyyy\nPlease type in the start time: ");
    scanf("%d:%d:%d_%d/%d/%d", &(rohdaten.tm_hour), &(rohdaten.tm_min), &(rohdaten.tm_sec), &(rohdaten.tm_mday), &(rohdaten.tm_mon), &(rohdaten.tm_year));

    rohdaten.tm_mon--; //Dekrementiere, um das Format zu erfüllen
    rohdaten.tm_year -= 1900;

    rohdaten.tm_wday = 0; //Initialisierung der nicht verwendeten Felder
    rohdaten.tm_yday = 0;
    rohdaten.tm_isdst = 0;

    begin = mktime(&rohdaten);
    
    printf("Please type in the end time: ");
    scanf("%d:%d:%d_%d/%d/%d", &(rohdaten.tm_hour), &(rohdaten.tm_min), &(rohdaten.tm_sec), &(rohdaten.tm_mday), &(rohdaten.tm_mon), &(rohdaten.tm_year));

    rohdaten.tm_mon--; //Dekrementiere, um das Format zu erfüllen
    rohdaten.tm_year -= 1900;

    rohdaten.tm_wday = 0; //Initialisierung der nicht verwendeten Felder
    rohdaten.tm_yday = 0;
    rohdaten.tm_isdst = 0;

    end = mktime(&rohdaten);

    while (NULL != fgets(buffer, 255, input)) { //Iteration über die geparste Eingabe
        sscanf(buffer, "%*d %d.%d %ld\n", &ping_pre, &ping_post, &current);
        if (current > begin && current < end) { //Überprüfung, ob Bereiche gültig ist
            fprintf(output, "%i %i.%i %li\n", ping_nr++, ping_pre, ping_post, current); //Schreibe Zeile in den output
        }
    }

    fclose(input); //Schließen der Dateien
    fclose(output);

    return EXIT_SUCCESS;
}
