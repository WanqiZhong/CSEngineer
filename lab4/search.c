#include <stdio.h>
#include <string.h>
#include "student.h"
#include "search.h"

int searchByName(STUDENT students[], int count, const char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int searchById(STUDENT students[], int count, const char* id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void displayStudent(const STUDENT* student) {
    printf("%-12s %-10s %-8.1f %-8.1f %-8.1f %-8.1f\n", 
           student->id, 
           student->name, 
           student->score.iCS, 
           student->score.PDP, 
           student->score.DS, 
           student->score.DL);
}