#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void addStudent();
void findStudentbyRollNumber();
void findStudentbyFirstName();
void findStudentInCourse();
void CountTotal();
void deleteStudent();
void UpdateStudent();
void clearInputBuffer();

// students
struct Student {
    char firstName[50];
    char lastName[50];
    int rollNumber;
    float gpa;
    int courseID[5];
    int numberCourses;
};

// global variables
struct Student st[100];
int count = 0;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice = 0;

    printf("*** Student Information Management System ***\n");

    do {
        printf("\n1. Add Student\n");
        printf("2. Find Student by Roll Number\n");
        printf("3. Find Student by First Name\n");
        printf("4. Find Student in a Course\n");
        printf("5. Count Total Students\n");
        printf("6. Delete Student\n");
        printf("7. Update Student Details\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                findStudentbyRollNumber();
                break;
            case 3:
                findStudentbyFirstName();
                break;
            case 4:
                findStudentInCourse();
                break;
            case 5:
                CountTotal();
                break;
            case 6:
                deleteStudent();
                break;
            case 7:
                UpdateStudent();
                break;
            case 8:
                printf("\nThanks for using our system! See you soon.\n");
                break;
            default:
                printf("\nInvalid choice! Please select 1 - 8.\n");
        }

    } while (choice != 8);

    return 0;
}

void addStudent() {
    if (count >= 100) {
        printf("\nError: Student database is full\n");
        return;
    }

    printf("\n*** Add new Student ***\n");

    int tempRoll;
    printf("\nEnter Roll Number: ");
    scanf("%d", &tempRoll);

    for (int i = 0; i < count; i++) {
        if (st[i].rollNumber == tempRoll) {
            printf("\nError: Roll number %d already exists!\n", tempRoll);
            return;
        }
    }

    st[count].rollNumber = tempRoll;
    clearInputBuffer();

    printf("Enter First Name: ");
    fgets(st[count].firstName, 50, stdin);
    st[count].firstName[strcspn(st[count].firstName, "\n")] = 0;

    printf("Enter Last Name: ");
    fgets(st[count].lastName, 50, stdin);
    st[count].lastName[strcspn(st[count].lastName, "\n")] = 0;

    printf("Enter CGPA: ");
    scanf("%f", &st[count].gpa);

    printf("Enter Number of Courses (max 5): ");
    scanf("%d", &st[count].numberCourses);

    if (st[count].numberCourses > 5) {
        st[count].numberCourses = 5;
    }

    for (int i = 0; i < st[count].numberCourses; i++) {
        printf("Enter Course ID %d: ", i + 1);
        scanf("%d", &st[count].courseID[i]);
    }
    
    count++;
    printf("\nStudent added successfully!\n");
}

void findStudentbyRollNumber() {
    if (count == 0) {
        printf("\nNo students found in the system!\n");
        return;
    }

    int roll;
    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (st[i].rollNumber == roll) {
            printf("\n--- Student Details ---\n");
            printf("Roll Number: %d\n", st[i].rollNumber);
            printf("First Name: %s\n", st[i].firstName);
            printf("Last Name: %s\n", st[i].lastName);
            printf("CGPA: %.2f\n", st[i].gpa);

            printf("Courses: ");
            for (int j = 0; j < st[i].numberCourses; j++) {
                printf("%d ", st[i].courseID[j]);
            }
            printf("\n----------------\n");
            return;
        }
    }

    printf("\nError: Student with Roll Number %d not found\n", roll);
}

void findStudentbyFirstName() {
    if (count == 0) {
        printf("\nNo students found in the system!\n");
        return;
    }

    char name[50];
    bool found = false;

    printf("\nEnter First Name to search: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(st[i].firstName, name) == 0) {
            printf("\n--- Student Details ---\n");
            printf("Roll Number: %d\n", st[i].rollNumber);
            printf("First Name: %s\n", st[i].firstName);
            printf("Last Name: %s\n", st[i].lastName);
            printf("CGPA: %.2f\n", st[i].gpa);
            printf("Courses: ");
            for (int j = 0; j < st[i].numberCourses; j++) {
                printf("%d ", st[i].courseID[j]);
            }
            printf("\n----------------\n");
            found = true;
        }
    }
    if (!found) {
        printf("\nError: No student with first name '%s' found\n", name);
    }
}

void findStudentInCourse() {
    if (count == 0) {
        printf("\nNo students found in the system!\n");
        return;
    }

    bool found = false;
    int searchCourse;

    printf("\nEnter Course ID to Search: ");
    scanf("%d", &searchCourse);

    printf("\n--- Students Enrolled in Course %d ---\n", searchCourse);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < st[i].numberCourses; j++) {
            if (st[i].courseID[j] == searchCourse) {
                printf("Roll Number: %d\n", st[i].rollNumber);
                printf("First Name : %s\n", st[i].firstName);
                printf("Last Name  : %s\n", st[i].lastName);
                printf("CGPA       : %.2f\n", st[i].gpa);
                printf("--------------------------------\n");
                found = true;
                break;
            }
        }
    }
    if (!found) {
        printf("\nNo students are currently enrolled in Course ID %d\n", searchCourse);
    }
}

void CountTotal() {
    printf("\nTotal Students: %d\n", count);
}

void deleteStudent() {
    if (count == 0) {
        printf("\nNo students found in the system!\n");
        return;
    }

    int roll;
    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &roll);

    int targetIndex = -1;

    for (int i = 0; i < count; i++) {
        if (st[i].rollNumber == roll) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) {
        printf("\nError: Student with Roll Number %d not found!\n", roll);
        return;
    }

    for (int j = targetIndex; j < count - 1; j++) {
        st[j] = st[j + 1];
    }

    count--;

    printf("\nStudent with Roll Number %d deleted successfully!\n", roll);
}

void UpdateStudent() {
    if (count == 0) {
        printf("\nNo students found in the system!\n");
        return;
    }

    int roll;
    printf("\nEnter Roll Number of student to update: ");
    scanf("%d", &roll);

    int targetIndex = -1;

    for (int i = 0; i < count; i++) {
        if (st[i].rollNumber == roll) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) {
        printf("\nError: Student with Roll Number %d not found!\n", roll);
        return;
    }

    int updateChoice;
    printf("\n*** Select Field to Update ***\n");
    printf("1. First Name\n");
    printf("2. Last Name\n");
    printf("3. Roll Number\n");
    printf("4. CGPA\n");
    printf("5. Course IDs\n");
    printf("Enter choice (1-5): ");
    scanf("%d", &updateChoice);

    switch (updateChoice) {
        case 1:
            printf("Enter New First Name: ");
            clearInputBuffer();
            fgets(st[targetIndex].firstName, 50, stdin);
            st[targetIndex].firstName[strcspn(st[targetIndex].firstName, "\n")] = 0;
            printf("\n>> First Name updated successfully!\n");
            break;

        case 2:
            printf("Enter New Last Name: ");
            clearInputBuffer();
            fgets(st[targetIndex].lastName, 50, stdin);
            st[targetIndex].lastName[strcspn(st[targetIndex].lastName, "\n")] = 0;
            printf("\n>> Last Name updated successfully!\n");
            break;

        case 3: {
            int newRoll;
            printf("Enter New Roll Number: ");
            scanf("%d", &newRoll);

            for (int i = 0; i < count; i++) {
                if (st[i].rollNumber == newRoll && i != targetIndex) {
                    printf("\nError: Roll Number %d is already assigned to another student!\n", newRoll);
                    return;
                }
            }
            st[targetIndex].rollNumber = newRoll;
            printf("\n>> Roll Number updated successfully!\n");
            break;
        }

        case 4:
            printf("Enter New CGPA: ");
            scanf("%f", &st[targetIndex].gpa);
            printf("\n>> CGPA updated successfully!\n");
            break;

        case 5:
            printf("Enter New Number of Courses (max 5): ");
            scanf("%d", &st[targetIndex].numberCourses);
            if (st[targetIndex].numberCourses > 5) {
                st[targetIndex].numberCourses = 5;
            }

            for (int j = 0; j < st[targetIndex].numberCourses; j++) {
                printf("Enter Course ID %d: ", j + 1);
                scanf("%d", &st[targetIndex].courseID[j]);
            }
            printf("\n>> Course IDs updated successfully!\n");
            break;

        default:
            printf("\nInvalid choice! Returning to main menu.\n");
            break;
    }
}