//
// Created by andrewms on 26.06.18.
//
#include <string_buffer.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 16

struct __StringBuffer{
    char * symbols;
    int length;
    int capacity;
};

// @todo error checks everywhere

static void StringBuffer_realloc(StringBuffer * self){
    self->capacity *= 2;
    char * newMemory = realloc(self->symbols, sizeof(char) * self->capacity);
    if(newMemory == NULL){
        abort();
    }
    self->symbols = newMemory;
}

StringBuffer * StringBuffer_new(void){
    StringBuffer * self = malloc(sizeof(StringBuffer));
    self->symbols = malloc(sizeof(char) * INITIAL_CAPACITY);
    self->capacity = INITIAL_CAPACITY;
    StringBuffer_clear(self);
    return self;
}

void StringBuffer_free(StringBuffer * self){
    free(self->symbols);
    free(self);
}

void StringBuffer_append(StringBuffer * self, const char * str){
    while(strlen(str) + self->length >= self->capacity - 1){
        StringBuffer_realloc(self);
    }
    strcat(self->symbols, str);
    self->length += strlen(str);
}

void StringBuffer_appendChar(StringBuffer * self, char ch){
    if(self->length + 1 >= self->capacity){
        StringBuffer_realloc(self);
    }
    self->symbols[self->length - 1] = ch;
    self->symbols[self->length] = '\0';
    self->length += 1;
}

void StringBuffer_clear(StringBuffer * self){
    self->symbols[0] = '\0';
    self->length = 1;

}

//https://stackoverflow.com/questions/37132549/implementation-of-strdup-in-c-programming

static char *ft_strdup(char *src)
{
    char *str;
    char *p;
    long len = 0;
    while (src[len]){
        len++;
    }
    str = malloc(len + 1);
    p = str;
    while (*src){
        *p++ = *src++;
    }
    *p = '\0';
    return str;
}

char * StringBuffer_toNewString(StringBuffer *self){
    char *str = self->symbols;
    return ft_strdup(str);
}

