//
// Created by andrewms on 26.06.18.
//

#include <university.h>
#include <list.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string_buffer.h>
#include <csv.h>

Student * Student_new(int id, int course, char * name, float score){
    Student * newStudent = malloc(sizeof(Student));
    newStudent->id = id;
    newStudent->course = course;
    newStudent->name = name;
    newStudent->score = score;
    return newStudent;
}

Teacher * Teacher_new(){
    Teacher * newTeacher = malloc(sizeof(Teacher));
    newTeacher->students = NULL;
    return newTeacher;
}

void Student_free(Student * self){
    free(self);
}

void Teacher_free(Teacher * self){
    if(self->students != NULL){
        for(int i = 0; i < List_count(self->students); i++){
            Student_free(List_at(self->students, i));
        }
    }
    free(self);
}

List * students_from_csv(char * csvString){
    List * rows = List_new();
    List * students = List_new();
    List * values = List_new();
    CsvTable * table = CsvTable_newFromString(csvString);
    CsvTable_rows(table, rows);
    for(int i = 0; i < List_count(rows); i++){
        CsvRow_values(List_at(rows, i), values);
        int id = atoi(List_at(values, 0));
        int course = atoi(List_at(values, 1));
        char * name = List_at(values, 2);
        float score = atof(List_at(values, 3));
        Student * stud = Student_new(id, course, name, score);
        List_add(students, stud);
        List_free(values);
        values = List_new();
    }
    List_free(values);
    List_free(rows);
    CsvTable_free(table);
    return students;
}

char * csv_from_students(List * students){
    if(students != NULL){
        StringBuffer * buffer = StringBuffer_new();
        for(int i = 0; i < List_count(students); i++){
            Student * student = List_at(students, i);
            char number[20];
            sprintf(number, "%d", student->id);
            StringBuffer_append(buffer, number);
            StringBuffer_appendChar(buffer, ',');
            sprintf(number, "%d", student->course);
            StringBuffer_append(buffer, number);
            StringBuffer_appendChar(buffer, ',');
            StringBuffer_append(buffer, student->name);
            StringBuffer_appendChar(buffer, ',');
            sprintf(number, "%f", student->score);
            StringBuffer_append(buffer, number);
            if(i != List_count(students) - 1){
                StringBuffer_appendChar(buffer, '\n');
            }
        }
        char * csvString = StringBuffer_toNewString(buffer);
        StringBuffer_free(buffer);
        return csvString;
    }
    return NULL;
}

void add_students_to_teacher(Teacher * teacher, List * students){
    teacher->students = students;
}

List * get_top_students(Teacher * teacher, int n){
    if(teacher != NULL && teacher->students != NULL){
        List * top = List_new();
        for(int i = 0; i < List_count(teacher->students) - 1; i++){
            for(int j = 0; j < List_count(teacher->students) - 1 - i; j++){
                if(((Student *)List_at(teacher->students, j))->score <
                   ((Student *)List_at(teacher->students, j + 1))->score){
                    Student * toReplace = List_removeAt(teacher->students, j);
                    List_insert(teacher->students, toReplace, j + 1);
                }
            }
        }
        for(int i = 0; i < n; i++){
            if(i < List_count(teacher->students)){
                Student * toInsert = List_at(teacher->students, i);
                List_add(top, toInsert);
            }
        }
        return top;
    }
    return NULL;
}