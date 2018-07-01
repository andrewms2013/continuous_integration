//
// Created by andrewms on 26.06.18.
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <csv.h>
#include <string_buffer.h>

struct __CsvTable{
    List* rows;
};

struct __CsvRow{
    List* values;
};

CsvRow * CsvRow_new(void){
    CsvRow * self = malloc(sizeof(CsvRow));
    if(self == NULL){
        fprintf(stderr, "Out of memory");
        abort();
    }
    self->values = List_new();
    return self;
}

void CsvRow_clear(CsvRow * self){
    while(List_count(self->values) != 0){
        char * value = List_removeAt(self->values, 0);
        free(value);
    }
}

void CsvRow_free(CsvRow * self){
    if(self == NULL){
        return;
    }
    List_free(self->values);
    free(self);
}

void CsvRow_add(CsvRow * self, const char * value){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    List_add(self->values, (void*)value);
}

void CsvRow_values(CsvRow * self, List * values){
    if(self == NULL || values == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    List * vals = self->values;
    for (int i = 0; i < List_count(vals); i++){
        void * value = List_at(vals, i);
        List_add(values, value);
    }
}

CsvTable * CsvTable_new(void){
    CsvTable * self = malloc(sizeof(CsvTable));
    if(self == NULL){
        fprintf(stderr, "Out of memory");
        abort();
    }
    self->rows = List_new();
    return self;
}

void CsvTable_clear(CsvTable * self){
    while(List_count(self->rows) != 0){
        CsvRow * row = List_removeAt(self->rows, 0);
        CsvRow_clear(row);
        CsvRow_free(row);
    }
}

void CsvTable_free(CsvTable * self){
    if(self == NULL){
        return;
    }
    List_free(self->rows);
    free(self);
}

void CsvTable_add (CsvTable * self, CsvRow * row){
    if(self == NULL || row == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    List_add(self->rows, row);
}

void CsvTable_rows(CsvTable * self, List * rows){
    if(self == NULL || rows == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    List_copyTo(self->rows, rows);
}

CsvTable * CsvTable_newFromString(const char * csvString){
    if(csvString == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    CsvTable * t = CsvTable_new();
    CsvRow * row = CsvRow_new();
    StringBuffer * value = StringBuffer_new();
    while(1){
        char ch = *csvString;
        if(ch == '\0'){
            CsvRow_add(row, StringBuffer_toNewString(value));
            StringBuffer_clear(value);
            CsvTable_add(t, row);
            break;
        }
        else if(ch == ','){
            CsvRow_add(row, StringBuffer_toNewString(value));
            StringBuffer_clear(value);
        }
        else if(ch == '\n'){
            CsvRow_add(row, StringBuffer_toNewString(value));
            StringBuffer_clear(value);
            CsvTable_add(t, row);
            row = CsvRow_new();
        }
        else{
            StringBuffer_appendChar(value, ch);
        }
        csvString++;
    }
    StringBuffer_free(value);
    return t;
}

CsvRow * CsvRow_newFromString(const char * csvString){
    if(csvString == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    CsvRow * row = CsvRow_new();
    StringBuffer * value = StringBuffer_new();
    while(1){
        char ch = *csvString;
        if(ch == '\0'){
            CsvRow_add(row, StringBuffer_toNewString(value));
            StringBuffer_clear(value);
            break;
        }
        else if(ch == ','){
            CsvRow_add(row, StringBuffer_toNewString(value));
            StringBuffer_clear(value);
        }
        else{
            StringBuffer_appendChar(value, ch);
        }
        csvString++;
    }
    StringBuffer_free(value);
    return row;
}

char * CsvTable_toNewString(CsvTable * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    StringBuffer *sb = StringBuffer_new();
    int nrows = List_count(self->rows);
    for(int ri = 0; ri < nrows; ri++){
        CsvRow * row = List_at(self->rows, ri);
        int nvalues = List_count(row->values);
        for(int vi = 0; vi < nvalues; vi++){
            char * value = List_at(row->values, vi);
            StringBuffer_append(sb, value);
            if(vi != nvalues - 1){
                StringBuffer_append(sb, ",");
            }
        }
        if(ri != nrows - 1){
            StringBuffer_append(sb, "\n");
        }
    }
    char * result = StringBuffer_toNewString(sb);
    StringBuffer_free(sb);
    return result;
}

static void List_copyTo(List *self, List *dest) {
    if(self == NULL || dest == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    for(int i = 0; i < List_count(self); i++) {
        void *value = List_at(self, i);
        List_add(dest, value);
    }
}