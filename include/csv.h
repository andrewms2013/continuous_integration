//
// Created by andrewms on 26.06.18.
//

#ifndef COUNTINUOUS_INTEGRATION_CSV_H
#define COUNTINUOUS_INTEGRATION_CSV_H

#include <list.h>

typedef struct __CsvTable CsvTable;
typedef struct __CsvRow   CsvRow;

CsvRow * CsvRow_new(void);
void CsvRow_clear(CsvRow * self);
void CsvRow_free(CsvRow * self);
void CsvRow_add(CsvRow * self, const char * value);
void CsvRow_values(CsvRow * self, List * values);

CsvTable * CsvTable_new(void);
void CsvTable_clear(CsvTable * self);
void CsvTable_free(CsvTable * self);
void CsvTable_add (CsvTable * self, CsvRow * row);
void CsvTable_rows(CsvTable * self, List * rows);

CsvRow *   CsvRow_newFromString(const char * csvString);
CsvTable * CsvTable_newFromString(const char * csvString);
char *     CsvTable_toNewString  (CsvTable * self);

static void List_copyTo(List*self, List*dest);

#endif //COUNTINUOUS_INTEGRATION_CSV_H
