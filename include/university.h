//
// Created by andrewms on 26.06.18.
//
#ifndef COUNTINUOUS_INTEGRATION_UNIVERSITY_H
#define COUNTINUOUS_INTEGRATION_UNIVERSITY_H

#include "list.h"

struct __Student{
    int id;
    int course;
    char * name;
    float score;
};

struct __Teacher{
    List * students;
};

typedef struct __Student Student;
typedef struct __Teacher Teacher;

Student * Student_new(int id, int course, char * name, float score);
Teacher * Teacher_new();
void Student_free(Student * self);
void Teacher_free(Teacher * self);

List * students_from_csv(char * csvString);
char * csv_from_students(List * students);
void add_students_to_teacher(Teacher * teacher, List * students);
List * get_top_students(Teacher * teacher, int n);

#endif //COUNTINUOUS_INTEGRATION_UNIVERSITY_H
