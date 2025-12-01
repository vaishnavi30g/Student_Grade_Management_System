#include "student_grade_system.h" // Include the header file to access definitions

// --- Utility/Validation Functions ---

void cleanInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int checkNameValidity(const char *name) {
    if (strlen(name) == 0) return 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha((unsigned char)name[i]) && !isspace((unsigned char)name[i])) {
            return 0;
        }
    }
    return 1;
}

int checkIfNumeric(const char *ptr) {
    char temp[50];
    strncpy(temp, ptr, 50);
    temp[49] = '\0';
    
    temp[strcspn(temp, "\n")] = '\0'; 

    if (strlen(temp) == 0) return 0;

    for (int i = 0; temp[i] != '\0'; i++) {
        if (!isdigit((unsigned char)temp[i])) return 0;
    }
    return 1;
}

float enterCorrectMarks(const char *subname) {
    char buffer[50];
    float marks = 0.0f;
    int valid = 0;

    do {
        printf("Enter marks for %s (0-100): ", subname);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;

            int isFloat = 1;
            int dotCount = 0;
            int len = strlen(buffer);
            
            if (len == 0) isFloat = 0;

            for (int i = 0; i < len; i++) {
                if (!isdigit((unsigned char)buffer[i])) {
                    if (buffer[i] == '.' && dotCount == 0) {
                        dotCount++;
                    } else {
                        isFloat = 0;
                        break;
                    }
                }
            }
            
            if (isFloat) {
                marks = atof(buffer);
                if (marks >= 0.0f && marks <= 100.0f) {
                    valid = 1;
                } else {
                    printf("  [Error] Marks must be between 0 and 100.\n");
                }
            } else {
                printf("  [Error] Invalid input. Please enter numbers only.\n");
            }
        } else {
             break;
        }
    } while (!valid);
    
    return marks;
}

char getGrade(float percentage) {
    if (percentage >= 90.0f) return 'A';
    else if (percentage >= 80.0f) return 'B';
    else if (percentage >= 70.0f) return 'C';
    else if (percentage >= 60.0f) return 'D';
    else if (percentage >= 50.0f) return 'E';
    else return 'F';
}

// --- Main System Logic Functions ---

void handleStudentDetails(Student *s) {
    char buffer[100];
    int valid = 0;

    printf("\n--- ENTER NEW STUDENT DETAILS ---\n");

    do {
        printf("Enter Name (Alphabets and spaces only): ");
        if (fgets(s->name, MAX_NAME_LEN, stdin) != NULL) {
            s->name[strcspn(s->name, "\n")] = 0;
            if (checkNameValidity(s->name)) valid = 1;
            else printf("Error: Name must only contain letters and spaces.\n");
        } else break;
    } while (!valid);

    valid = 0;
    do {
        printf("Enter Admission Number (Numeric, max %d digits): ", MAX_ADM_LEN - 1);
        if (fgets(s->adm_No, MAX_ADM_LEN, stdin) != NULL) {
            s->adm_No[strcspn(s->adm_No, "\n")] = 0;
            if (checkIfNumeric(s->adm_No)) valid = 1;
            else printf("Error: Admission Number must be numeric.\n");
        } else break;
    } while (!valid);

    valid = 0;
    do {
        printf("Enter Roll Number (1-1000): ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (checkIfNumeric(buffer)) {
                s->roll_No = atoi(buffer);
                if (s->roll_No > 0 && s->roll_No <= 1000) valid = 1;
                else printf("Error: Roll Number must be in range 1-1000.\n");
            } else printf("Error: Invalid input. Digits only.\n");
        } else break;
    } while (!valid);

    printf("Enter Batch (e.g., 2023-2027): ");
    fgets(s->batch, 40, stdin);
    s->batch[strcspn(s->batch, "\n")] = 0;

    printf("Enter Course: ");
    fgets(s->course, 20, stdin);
    s->course[strcspn(s->course, "\n")] = 0;

    valid = 0;
    do {
        printf("\nHow many subjects to add? (1-10): ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (checkIfNumeric(buffer)) {
                int count = atoi(buffer);
                if (count > 0 && count <= 10) {
                    s->subcount = count;
                    valid = 1;
                } else {
                    printf("Error: Subject count must be between 1 and 10.\n");
                }
            } else {
                printf("Error: Invalid input. Enter a number.\n");
            }
        } else break;
    } while (!valid);

    s->subjects = (Subject*)malloc(s->subcount * sizeof(Subject));
    if (s->subjects == NULL) {
        printf("Memory Allocation Failed!\n");
        exit(1);
    }

    for (int i = 0; i < s->subcount; i++) {
        printf("\n-- Subject %d --\n", i + 1);
        printf("  Name: ");
        fgets(s->subjects[i].sub, 30, stdin);
        s->subjects[i].sub[strcspn(s->subjects[i].sub, "\n")] = 0;

        s->subjects[i].marks = enterCorrectMarks(s->subjects[i].sub);
    }
}

void showReportCard(const Student *s) {
    printf("\n");
    printf("           STUDENT REPORT CARD           \n");
    printf("\n");
    printf(" Name        : %-30s\n", s->name);
    printf(" Admission # : %-15s   Roll No : %d\n", s->adm_No, s->roll_No);
    printf(" Course      : %-15s   Batch   : %s\n", s->course, s->batch);
    printf("----------------------------------------------\n");
    printf(" %-25s | %-10s \n", "SUBJECT", "MARKS");
    printf("----------------------------------------------\n");

    float total = 0.0f;
    for (int i = 0; i < s->subcount; i++) {
        printf(" %-25s | %-10.2f \n",
               s->subjects[i].sub,
               s->subjects[i].marks);
        total += s->subjects[i].marks;
    }
    float percentage = (total / (s->subcount * 100.0f)) * 100.0f;
    char overallGrade = getGrade(percentage);

    printf("----------------------------------------------\n");
    printf(" Total Marks : %.2f / %.2f\n", total, (float)s->subcount * 100.0f);
    printf(" Percentage  : %.2f%%\n", percentage);
    printf(" OVERALL GRADE : %c\n", overallGrade);
    printf("\n");
}

void saveStudentToFile(const Student *s) {
    FILE *fp = fopen(FILE_NAME, "a");

    if (fp == NULL) {
        printf("\n[Error] Could not open file for writing.\n");
        return;
    }
    float total = 0.0f;
    for (int i = 0; i < s->subcount; i++) total += s->subjects[i].marks;
    float percent = (total / ((float)s->subcount * 100.0f)) * 100.0f;
    char overallGrade = getGrade(percent);

    fprintf(fp, "==============================================\n");
    fprintf(fp, "Name: %s | Roll: %d | Adm: %s\n", s->name, s->roll_No, s->adm_No);
    fprintf(fp, "Batch: %s | Course: %s\n", s->batch, s->course);
    fprintf(fp, "Subjects:\n");
    for (int i = 0; i < s->subcount; i++) {
        fprintf(fp, " - %s: %.2f\n", s->subjects[i].sub, s->subjects[i].marks);
    }
    fprintf(fp, "Percentage: %.2f%% | GRADE: %c\n", percent, overallGrade);
    fprintf(fp, "==============================================\n\n");

    fclose(fp);
    printf("\n[Success] Data Automatically Saved to '%s'\n", FILE_NAME);
}

void viewAllHistory() {
    FILE *fp = fopen(FILE_NAME, "r");
    int ch;

    if (fp == NULL) {
        printf("\n[Info] No records file found. Try creating a record first.\n");
        return;
    }

    printf("\n--- LOADING ALL SAVED RECORDS ---\n");
    while ((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    printf("\n--- END OF RECORDS ---\n");

    fclose(fp);
}

void removeStudentRecord() {
    FILE *fp, *ft;
    char admToDelete[MAX_ADM_LEN];
    char buffer[512];
    int found = 0;

    printf("\n--- DELETE STUDENT RECORD ---\n");
    printf("Enter Admission Number of the student to delete: ");
    
    if (fgets(admToDelete, MAX_ADM_LEN, stdin) == NULL) return;
    admToDelete[strcspn(admToDelete, "\n")] = 0;

    if (strlen(admToDelete) == 0) {
        printf("[Error] Admission Number cannot be empty.\n");
        return;
    }

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("\n[Info] No records file found or error opening file.\n");
        return;
    }

    ft = fopen("temp_records.txt", "w");
    if (ft == NULL) {
        printf("[Error] Could not create temporary file.\n");
        fclose(fp);
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, "==============================================") != NULL) {
            
            if (fgets(buffer, sizeof(buffer), fp) == NULL) break; 
            
            char *admPtr = strstr(buffer, "Adm: ");
            
            if (admPtr != NULL) {
                admPtr += 5; 
                char currentAdm[MAX_ADM_LEN];
                sscanf(admPtr, "%s", currentAdm); 

                if (strcmp(currentAdm, admToDelete) == 0) {
                    found = 1;
                    printf("[Match Found] Deleting record for Admission #%s...\n", admToDelete);
                    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
                        if (strstr(buffer, "==============================================") != NULL) {
                            break;
                        }
                    }
                    continue;
                }
            }
            
            fprintf(ft, "==============================================\n");
            fprintf(ft, "%s", buffer);
            
        } else {
            fprintf(ft, "%s", buffer);
        }
    }

    fclose(fp);
    fclose(ft);

    if (found) {
        if (remove(FILE_NAME) != 0) {
            printf("[Fatal Error] Could not delete original file.\n");
            return;
        }
        
        if (rename("temp_records.txt", FILE_NAME) != 0) {
            printf("[Fatal Error] Could not rename temporary file.\n");
            return;
        }
        printf("[Success] Record with Admission #%s deleted successfully.\n", admToDelete);
    } else {
        remove("temp_records.txt");
        printf("[Info] No record found with Admission #%s.\n", admToDelete);
    }
}

void freeStudentMemory(Student *s) {
    if (s->subjects != NULL) {
        free(s->subjects);
        s->subjects = NULL;
    }
}
