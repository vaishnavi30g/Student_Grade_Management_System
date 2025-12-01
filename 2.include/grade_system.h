#ifndef STUDENT_GRADE_SYSTEM_H
#define STUDENT_GRADE_SYSTEM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// --- Constants ---
#define MAX_NAME_LEN 50
#define MAX_ADM_LEN 20
#define FILE_NAME "student_records.txt"

// --- Structures ---

typedef struct {
    char sub[30];
    float marks;
} Subject;

typedef struct {
    char name[MAX_NAME_LEN];
    int roll_No;
    char adm_No[MAX_ADM_LEN];
    char batch[40];
    char course[20];
    int subcount;
    Subject *subjects;
} Student;

// --- Function Prototypes ---

// Utility/Validation
void cleanInputBuffer(); 
int checkNameValidity(const char *name);
int checkIfNumeric(const char *ptr);
float enterCorrectMarks(const char *subname);
char getGrade(float percentage);

// Main System Logic
void handleStudentDetails(Student *s);
void showReportCard(const Student *s);
void freeStudentMemory(Student *s);
void saveStudentToFile(const Student *s);
void viewAllHistory(); 
void removeStudentRecord();

#endif
