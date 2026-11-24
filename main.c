#include <stdio.h>
#include <string.h>
#include "studenthelp.h"

static void readLine(const char prompt[], char buf[], int size)
{
    int len;
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    len = (int)strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
        buf[len - 1] = '\0';
}

static int readInt(const char prompt[], int low, int high)
{
    char line[32];
    int value;
    while (1) {
        readLine(prompt, line, sizeof(line));
        if (sscanf(line, "%d", &value) == 1 && value >= low && value <= high)
            return value;
        printf("Invalid input. Enter a number from %d to %d.\n", low, high);
    }
}

static void readSubjects(char list[][MAX_SUBJECT_LENGTH], int *count, const char label[])
{
    char prompt[80];
    int i, n;

    sprintf(prompt, "How many subjects %s (0-%d): ", label, MAX_SUBJECTS);
    n = readInt(prompt, 0, MAX_SUBJECTS);
    for (i = 0; i < n; i++) {
        sprintf(prompt, "  Subject %d: ", i + 1);
        readLine(prompt, list[i], MAX_SUBJECT_LENGTH);
    }
    *count = n;
}

static void registerStudent(Student list[], int *count)
{
    Student s;
    char id[MAX_ID_LENGTH];

    if (*count >= MAX_STUDENTS) {
        printf("Student list is full.\n");
        return;
    }
    readLine("Enter student ID: ", id, MAX_ID_LENGTH);
    if (id[0] == '\0') {
        printf("ID cannot be empty.\n");
        return;
    }
    if (findStudent(list, *count, id) != -1) {
        printf("Duplicate ID! A student with this ID is already registered.\n");
        return;
    }
    strcpy(s.id, id);
    readLine("Enter name: ", s.name, MAX_NAME);
    readSubjects(s.teach, &s.teachCount, "can you teach");
    readSubjects(s.need, &s.needCount, "do you need help with");
    list[*count] = s;
    (*count)++;
    printf("Student registered successfully.\n");
}

static void printSubjects(char list[][MAX_SUBJECT_LENGTH], int count)
{
    int i;
    if (count == 0)
        printf("None");
    for (i = 0; i < count; i++)
        printf("%s%s", list[i], (i < count - 1) ? ", " : "");
}

static void displayAll(Student list[], int count)
{
    int i;
    if (count == 0) {
        printf("No students registered yet.\n");
        return;
    }
    printf("\n--- All Registered Students ---\n");
    for (i = 0; i < count; i++) {
        printf("%d) ID: %s | Name: %s\n", i + 1, list[i].id, list[i].name);
        printf("     Teaches: ");
        printSubjects(list[i].teach, list[i].teachCount);
        printf("\n     Needs:   ");
        printSubjects(list[i].need, list[i].needCount);
        printf("\n");
    }
}

static void updateStudent(Student list[], int count)
{
    char id[MAX_ID_LENGTH];
    int idx;

    readLine("Enter student ID to update: ", id, MAX_ID_LENGTH);
    idx = findStudent(list, count, id);
    if (idx == -1) {
        printf("Student not found.\n");
        return;
    }
    readLine("Enter new name: ", list[idx].name, MAX_NAME);
    readSubjects(list[idx].teach, &list[idx].teachCount, "can you teach");
    readSubjects(list[idx].need, &list[idx].needCount, "do you need help with");
    printf("Student profile updated successfully.\n");
}

static void removeStudent(Student list[], int *count)
{
    char id[MAX_ID_LENGTH];
    int idx, i;

    readLine("Enter student ID to remove: ", id, MAX_ID_LENGTH);
    idx = findStudent(list, *count, id);
    if (idx == -1) {
        printf("Student not found.\n");
        return;
    }
    for (i = idx; i < *count - 1; i++)
        list[i] = list[i + 1];
    (*count)--;
    printf("Student profile removed successfully.\n");
}

int main(void)
{
    Student list[MAX_STUDENTS];
    int count = 0, choice, idx;
    char buf[MAX_SUBJECT_LENGTH];
    char id[MAX_ID_LENGTH];

    do {
        printf("\n===== StudentHelp =====\n");
        printf("1. Register student\n");
        printf("2. Display all students\n");
        printf("3. Search teacher by subject\n");
        printf("4. Show matches for a student\n");
        printf("5. Show mutual study partners\n");
        printf("6. Update student profile\n");
        printf("7. Remove student profile\n");
        printf("0. Exit\n");
        choice = readInt("Enter choice: ", 0, 7);

        switch (choice) {
        case 1: registerStudent(list, &count); break;
        case 2: displayAll(list, count); break;
        case 3:
            readLine("Enter subject to search: ", buf, MAX_SUBJECT_LENGTH);
            searchTeacher(list, count, buf);
            break;
        case 4:
            readLine("Enter student ID: ", id, MAX_ID_LENGTH);
            idx = findStudent(list, count, id);
            if (idx == -1)
                printf("Student not found.\n");
            else
                showMatch(list, count, idx);
            break;
        case 5: showPartners(list, count); break;
        case 6: updateStudent(list, count); break;
        case 7: removeStudent(list, &count); break;
        case 0: printf("Goodbye!\n"); break;
        }
    } while (choice != 0);

    return 0;
}
