#include "Parser.h"

int parse(FILE*, char*);

int main (int argc, char* argv[])
{
  FILE* filetoparse = NULL;
  if (argc!=3)
  {
    printf("Usage: %s FileToParse ParsedFile\n",argv[0] );
    return EXIT_FAILURE;
  }

  if (NULL == (filetoparse=fopen(argv[1],"r")))
  {
    printf("Invalid FileToParse\n");
    return EXIT_FAILURE;
  }
  if (parse(filetoparse,argv[2]))
  {
    printf("Failed to Parse\n");
    return EXIT_FAILURE;
  }
  fclose(filetoparse);
  return EXIT_SUCCESS;
}

int parse(FILE* input, char* output) {
    FILE* parsedfile = NULL;
    int milsec, nanosec, counter = 0;
    long unixtime;
    char buffer[255];

    if(NULL == (parsedfile = fopen(output, "w+"))) //Öffnen der zu schreibenden Datei
    {
      return EXIT_FAILURE;
    }

    while(NULL != fgets(buffer, 255, input)) { //Iteration über die Zeilen
        if (2 == sscanf(buffer,"%*d bytes from %*d.%*d.%*d.%*d: seq=%*d ttl=%*d time=%d.%d ms\n",&milsec,&nanosec)) { //Überprüfe auf Ping-Zeile
            fprintf(parsedfile, "%i %i.%i %ld\n",counter++, milsec, nanosec, unixtime); //Schreibe Ping-Nr. und RTT in Datei
        }
        else {
            sscanf(buffer, "%ld", &unixtime); //potentielles Einlesen der Unixzeit
        }
    }

    return EXIT_SUCCESS;
}
