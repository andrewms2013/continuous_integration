//
// Created by andrewms on 26.06.18.
//
#ifndef COUNTINUOUS_INTEGRATION_STRING_BUFFER_H
#define COUNTINUOUS_INTEGRATION_STRING_BUFFER_H

typedef struct __StringBuffer StringBuffer;

StringBuffer * StringBuffer_new(void);
void StringBuffer_free(StringBuffer * self);

void StringBuffer_append(StringBuffer * self, const char * str);
void StringBuffer_appendChar(StringBuffer * self, char ch);
void StringBuffer_clear(StringBuffer * self);
char * StringBuffer_toNewString(StringBuffer * self);

#endif //COUNTINUOUS_INTEGRATION_STRING_BUFFER_H
