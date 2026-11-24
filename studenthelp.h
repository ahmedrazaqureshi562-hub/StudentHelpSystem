#ifndef STUDENTHELP_H
#define STUDENTHELP_H

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 5
#define MAX_NAME 50
#define MAX_SUBJECT_LENGTH 30
#define MAX_ID_LENGTH 15

typedef struct Student {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME];
    char teach[MAX_SUBJECTS][MAX_SUBJECT_LENGTH];
    int teachCount;
    char need[MAX_SUBJECTS][MAX_SUBJECT_LENGTH];
    int needCount;
} Student;

int findStudent(Student list[], int count, const char id[]);
void searchTeacher(Student list[], int count, char subject[]);
void showMatch(Student list[], int count, int index);
void showPartners(Student list[], int count);

#endif
