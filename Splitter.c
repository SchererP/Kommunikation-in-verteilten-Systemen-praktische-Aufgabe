#include"Splitter.h"

int main(int argc, char** argv) {
    FILE* input = NULL, *output = NULL;
    time_t sigDiff, lastTime, currentTime; //Signifikanter Unterschied
    int rtt_pre, rtt_post, c = 0;
    char* filename = NULL;

    if (argc != 4) { //Überprüfung, ob genügend Argumente übergeben wurden
        fprintf(stderr, "Fehler: zu wenige Kommandozeilenargumente\n");
        return EXIT_FAILURE;
    }

    if (NULL == (filename = malloc((strlen(argv[2])+8)*sizeof(char)))) {
        perror("Fehler bei der Speicherallokation");
        return EXIT_FAILURE;
    }

    sprintf(filename, "%s%i", argv[2], c++);

    if (NULL == (input = fopen(argv[1], "r")) || NULL == (output = fopen(filename, "w+"))) { //Öffnen der Dateien
        perror("Fehler beim Oeffnen der Datei");
        return EXIT_FAILURE;
    }

    sscanf(argv[3], "%ld", &sigDiff); //Einlesen der Differenz

    if (fscanf(input, "%*d %d.%d %ld\n", &rtt_pre, &rtt_post, &lastTime) > 0) {
        fprintf(output, "%d.%d\n", rtt_pre, rtt_post);
    }

    while (fscanf(input, "%*d %d.%d %ld\n", &rtt_pre, &rtt_post, &currentTime) > 0) {
        if ((currentTime - lastTime) > sigDiff) {
            fclose(output);
            sprintf(filename, "%s%i", argv[2], c++);
            if (NULL == (output = fopen(filename, "w+"))) {
                perror("Fehler beim Oeffen der Datei");
                return EXIT_FAILURE;
            }
        }
        fprintf(output, "%d.%d\n", rtt_pre, rtt_post);
        lastTime = currentTime;
    }
    free(filename);

    fclose(input); //Schließend der Dateien
    fclose(output);

    return EXIT_SUCCESS;
}
