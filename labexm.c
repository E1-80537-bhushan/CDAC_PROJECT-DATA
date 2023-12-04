#include <stdio.h>
#include <string.h>

#define MAX_NAMES 10
#define MAX_NAME_LENGTH 50

// Function to display all names
void displayNames(char names[MAX_NAMES][MAX_NAME_LENGTH], int count) {
    printf("Names:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", names[i]);
    }
}

// Function to find the row number of a given name
int findRow(char names[MAX_NAMES][MAX_NAME_LENGTH], int count, char *searchName) {
    for (int i = 0; i < count; i++) {
        if (strcmp(names[i], searchName) == 0) {
            return i;
        }
    }
    return -1; // Name not found
}

// Function to display each name in reverse order
void displayReverseNames(char names[MAX_NAMES][MAX_NAME_LENGTH], int count) {
    printf("Names in Reverse Order:\n");
    for (int i = 0; i < count; i++) {
        int len = strlen(names[i]);
        for (int j = len - 1; j >= 0; j--) {
            printf("%c", names[i][j]);
        }
        printf("\n");
    }
}

// Function to check for duplicate names
void checkDuplicates(char names[MAX_NAMES][MAX_NAME_LENGTH], int count) {
    printf("Duplicate Names:\n");
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(names[i], names[j]) == 0) {
                printf("%s\n", names[i]);
                break;
            }
        }
    }
}

// Function to count occurrences of a given character in each name
void countOccurrences(char names[MAX_NAMES][MAX_NAME_LENGTH], int count, char character) {
    printf("Occurrences of '%c' in Each Name:\n", character);
    for (int i = 0; i < count; i++) {
        int len = strlen(names[i]);
        int charCount = 0;
        for (int j = 0; j < len; j++) {
            if (names[i][j] == character) {
                charCount++;
            }
        }
        printf("%s: %d\n", names[i], charCount);
    }
}

// Function to sort names alphabetically
void sortNames(char names[MAX_NAMES][MAX_NAME_LENGTH], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(names[i], names[j]) > 0) {
                char temp[MAX_NAME_LENGTH];
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }
    printf("Names sorted alphabetically:\n");
    displayNames(names, count);
}

int main(int argc, char *argv[]) {
    if (argc != MAX_NAMES + 1) {
        printf("Please provide exactly %d names as command-line arguments.\n", MAX_NAMES);
        return 1;
    }

    char names[MAX_NAMES][MAX_NAME_LENGTH];

    for (int i = 1; i <= MAX_NAMES; i++) {
        strncpy(names[i - 1], argv[i], MAX_NAME_LENGTH);
    }

    int choice;
    char searchName[MAX_NAME_LENGTH];
    char character;

    do {
        printf("\nMenu:\n");
        printf("1. Display all names\n");
        printf("2. Find row number of a given name\n");
        printf("3. Display each name in reverse order\n");
        printf("4. Check duplicate names\n");
        printf("5. Count occurrences of a given character in each name\n");
        printf("6. Sort names alphabetically\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayNames(names, MAX_NAMES);
                break;
            case 2:
                printf("Enter a name to search: ");
                scanf("%s", searchName);
                int row = findRow(names, MAX_NAMES, searchName);
                if (row != -1) {
                    printf("Name '%s' found at row %d.\n", searchName, row + 1);
                } else {
                    printf("Name '%s' not found.\n", searchName);
                }
                break;
            case 3:
                displayReverseNames(names, MAX_NAMES);
                break;
            case 4:
                checkDuplicates(names, MAX_NAMES);
                break;
            case 5:
                printf("Enter a character: ");
                scanf(" %c", &character); // Note the space before %c to skip whitespace characters
                countOccurrences(names, MAX_NAMES, character);
                break;
            case 6:
                sortNames(names, MAX_NAMES);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

