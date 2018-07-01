//
// Created by andrewms on 01.07.18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include <list.h>
#include <stdbool.h>
#include <university.h>


START_TEST (students_from_csvString)
    {
        List * students = students_from_csv("1,3,Andrew,2.34");
        ck_assert_int_eq(List_count(students), 1);
        ck_assert_str_eq(((Student*)List_at(students, 0))->name, "Andrew");
        ck_assert_int_eq(((Student*)List_at(students, 0))->id, 1);
        Student_free(List_at(students, 0));
        List_free(students);
    }
END_TEST

START_TEST (teacher_with_students)
    {
        List * students = students_from_csv("1,3,Andrew,2.34\n2,2,Vasya,4.22");
        ck_assert_int_eq(List_count(students), 2);
        Teacher * teacher = Teacher_new();
        add_students_to_teacher(teacher, students);
        List * studs = teacher->students;
        ck_assert(studs);
        ck_assert_str_eq(((Student*)List_at(studs, 1))->name, "Vasya");
        ck_assert_int_ne(((Student*)List_at(studs, 1))->id, 3);
        Teacher_free(teacher);
    }
END_TEST


Suite *test_suite() {
    Suite *s = suite_create("University");
    TCase *tc_sample = tcase_create("Functions");
    //
    tcase_add_test(tc_sample, students_from_csvString);
    tcase_add_test(tc_sample, teacher_with_students);
    //
    suite_add_tcase(s, tc_sample);
    return s;
}

int main(void) {
    Suite *s = test_suite();
    SRunner *sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);  // important for debugging!
    srunner_run_all(sr, CK_VERBOSE);

    int num_tests_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return num_tests_failed;
}
