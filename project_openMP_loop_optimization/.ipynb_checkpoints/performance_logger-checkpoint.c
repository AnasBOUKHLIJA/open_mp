#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "performance_logger.h"
#include <string.h>

#define FILE_NAME "performance.csv"

void appendToCSV(const char *programName, const char *startDate, const char *endDate, int threadsCount, double executionTime, const char *thread_times) {

    // Open the file in append mode
    // --------------------------------------------------------------------
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        perror("Error opening the file");
        return;
    }

    // Check if the file is empty (to add the header)
    // --------------------------------------------------------------------
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "program_name%sstart_date%send_date%sthreads_count%sexecution_time%sthread_times\n", CSV_SEPARATOR, CSV_SEPARATOR, CSV_SEPARATOR, CSV_SEPARATOR, CSV_SEPARATOR);
    }

    // Append data
    // --------------------------------------------------------------------
    fprintf(file, "%s%s%s%s%s%s%d%s%f%s%s\n", programName, CSV_SEPARATOR, startDate, CSV_SEPARATOR, endDate, CSV_SEPARATOR, threadsCount, CSV_SEPARATOR, executionTime, CSV_SEPARATOR, thread_times);

    // Close the file
    // --------------------------------------------------------------------
    fclose(file);
}
