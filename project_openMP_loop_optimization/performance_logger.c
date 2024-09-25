#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "performance_logger.h"


#define FILE_NAME "performance.csv"

void appendToCSV(const char *programName, int threadsCount, double executionTime, const char *startDate, const char *endDate) {

    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "program_name%sthreads_count%sexecution_time%sstart_date%send_date\n", CSV_SEPARATOR, CSV_SEPARATOR, CSV_SEPARATOR, CSV_SEPARATOR);
    }

    fprintf(file, "%s%s%d%s%.2f%s%s%s%s\n", programName, CSV_SEPARATOR, threadsCount, CSV_SEPARATOR, executionTime, CSV_SEPARATOR, startDate, CSV_SEPARATOR, endDate);

    fclose(file);
}
