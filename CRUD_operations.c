#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
typedef struct USER {
    int id;
    char name[50];
    int age;
} User;
void createUser() {
    User user;
    FILE *file = fopen("user.txt", "a");
    if (!file) {
        printf("Error opening file\n");
        return;
    }
    printf("Enter User ID: ");
    scanf("%d", &user.id);
    printf("Enter Name: ");
    scanf("%s", user.name);
    printf("Enter Age: ");
    scanf("%d", &user.age);
    fprintf(file, "%d,%s,%d\n", user.id, user.name, user.age);
    fclose(file);
    printf("User details created.\n");
}
void readUsers() {
    FILE *file = fopen("user.txt", "r");
    if (!file) {
        printf("No users found.\n");
        return;
    }
    char dest[100];
    printf("\nID\tName\tAge\n");
    printf("-------------------------\n");
    while (fgets(dest, 100, file)) {
        User user;
        sscanf(dest, "%d,%49[^,],%d", &user.id, user.name, &user.age);
        printf("%d\t%s\t%d\n", user.id, user.name, user.age);
    }
    fclose(file);
}
void updateUser() {
    int id;
    User user;
    int change = 0;
    printf("Enter the ID of the user to update: ");
    scanf("%d", &id);
    FILE *file = fopen("user.txt", "r");
    FILE *dummyFile = fopen("temp.txt", "w");
    if (!file || !dummyFile) {
        printf("Error opening file!\n");
        return;
    }
    char dest[100];
    while (fgets(dest, 100, file)) {
        sscanf(dest, "%d,%49[^,],%d", &user.id, user.name, &user.age);
        if (user.id == id) {
            change = 1;
            printf("Enter new Name: ");
            scanf("%s", user.name);
            printf("Enter new Age: ");
            scanf("%d", &user.age);
        }
        fprintf(dummyFile, "%d,%s,%d\n", user.id, user.name, user.age);
    }
    fclose(file);
    fclose(dummyFile);
    remove("user.txt");
    rename("temp.txt", "user.txt");
    if (change)
        printf("User updated successfully!\n");
    else
        printf("User not found.\n");
}
void deleteUser() {
    int id;
    User user;
    int change = 0;
    printf("Enter the ID of the user to delete: ");
    scanf("%d", &id);
    FILE *file = fopen("user.txt", "r");
    FILE *dummyFile = fopen("temp.txt", "w");
    if (!file || !dummyFile) {
        printf("Error opening file!\n");
        return;
    }
    char dest[100];
    while (fgets(dest, 100, file)) {
        sscanf(dest, "%d,%49[^,],%d", &user.id, user.name, &user.age);
        if (user.id != id) {
            fprintf(dummyFile, "%d,%s,%d\n", user.id, user.name, user.age);
        } else {
            change = 1;
        }
    }
    fclose(file);
    fclose(dummyFile);
    remove("user.txt");
    rename("temp.txt", "user.txt");
    if (change)
        printf("User deleted successfully!\n");
    else
        printf("User not found.\n");
}

int main() {
    int choice;
    while (true) {
        printf("\nUser Management System\n");
        printf("1. Add New User\n");
        printf("2. Display All Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createUser(); 
                    break;
            case 2: readUsers(); 
                    break;
            case 3: updateUser(); 
                    break;
            case 4: deleteUser(); 
                    break;
            case 5: exit(0);
            default: printf("Invalid choice,Please try again\n");
        }
    }
}
