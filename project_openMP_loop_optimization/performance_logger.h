#ifndef performance_logger_H
#define performance_logger_H

#define N 150000000
#define CSV_SEPARATOR "|"

void appendToCSV(const char *programName, int threadsCount, double executionTime, const char *startDate, const char *endDate);

#endif
