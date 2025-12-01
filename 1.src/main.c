#include "student_grade_system.h" // Include the header to access structs and functions

int main() {
    // Student structure definition is now inherited from the header
    Student std;
    std.subjects = NULL;
    
    int choice;
    do {
        printf("\n=====================================\n");
        printf("       STUDENT GRADE SYSTEM          ");
        printf("\n=====================================\n");
        printf("1. Create New Student Record\n");
        printf("2. Print Report Card (Current Session)\n");
        printf("3. View All Saved Records (History)\n");
        printf("4. Delete Student Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        char choiceBuffer[10];
        if (fgets(choiceBuffer, sizeof(choiceBuffer), stdin) != NULL) {
            if (checkIfNumeric(choiceBuffer)) {
                choice = atoi(choiceBuffer);
            } else {
                choice = 0;
            }
        } else {
            choice = 5;
        }

        switch (choice) {
            case 1:
                if (std.subjects != NULL) {
                    printf("\n[Info] Clearing current memory for new entry...\n");
                    freeStudentMemory(&std);
                }
                handleStudentDetails(&std);
                saveStudentToFile(&std);
                break;
            case 2:
                if (std.subjects != NULL) {
                    showReportCard(&std);
                } else {
                    printf("\nERROR, No record in memory to print\n");
                }
                break;
            case 3:
                viewAllHistory();
                break;
            case 4:
                removeStudentRecord();
                break;
            case 5:
                printf("\n**\n");
                printf(" Thank you for using the Student Record System!   \n");
                printf(" All your data has been safely stored.           \n");
                printf(" Have a wonderful day!                           \n");
                printf("\n");
                freeStudentMemory(&std);
                break;
            default:
                printf("Invalid choice. Choose a number between 1 to 5\n");
        }
    } while (choice != 5);

    return 0;
}
