#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct User 
{
    int id;
    char name[50];
    int age;
} User;


void readInput(char *text, void *variable, char specifier) 
{
    printf("%s", text);
    if (specifier == 'd') 
    {
        scanf("%d", (int *)variable);
    } else if (specifier == 's') 
    {
        scanf("%s", (char *)variable);
    }
}


void displayUser(User *user) 
{
    printf("%d\t%s\t%d\n", user->id, user->name, user->age);
}


bool alreadyExists(int userId) 
{
    FILE *file = fopen("user.txt", "r");
    if (!file) 
    {
        return false;
    }

    char character[100];
    User user;
    while (fgets(character, sizeof(character), file)) 
    {
        sscanf(character, "%d,%49[^,],%d", &user.id, user.name, &user.age);
        if (user.id == userId) 
        {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}


void createUser() 
{
    User user;
    FILE *file = fopen("user.txt", "a");
    if (!file) 
    {
        printf("Error opening file\n");
        return;
    }

    readInput("Enter User ID: ", &user.id, 'd');

    if (alreadyExists(user.id))
    {
        printf("Error: User ID already exists.\n");
        fclose(file);
        return;
    }

    readInput("Enter Name: ", user.name, 's');
    readInput("Enter Age: ", &user.age, 'd');

    fprintf(file, "%d,%s,%d\n", user.id, user.name, user.age);
    fclose(file);
    printf("User details created successfully.\n");
}


void readUsers() 
{
    FILE *file = fopen("user.txt", "r");
    if (!file) 
    {
        printf("No users found.\n");
        return;
    }

    char line[100];
    User user;
    printf("\nID\tName\tAge\n");
    printf("-------------------------\n");
    while (fgets(line, sizeof(line), file)) 
    {
        sscanf(line, "%d,%49[^,],%d", &user.id, user.name, &user.age);
        displayUser(&user);
    }

    fclose(file);
}


void updateUser() 
{
    int userId;
    bool userFound = false;
    User user;

    readInput("Enter the ID of the user to update: ", &userId, 'd');

    FILE *file = fopen("user.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (!file || !tempFile) 
    {
        printf("Error opening file!\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) 
    {
        sscanf(line, "%d,%49[^,],%d", &user.id, user.name, &user.age);
        if (user.id == userId && !userFound) 
        {
            userFound = true;
            readInput("Enter new Name: ", user.name, 's');
            readInput("Enter new Age: ", &user.age, 'd');
        }
        fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
    }

    fclose(file);
    fclose(tempFile);
    remove("user.txt");
    rename("temp.txt", "user.txt");

    if (userFound) 
    {
        printf("User updated successfully!\n");
    } else 
    {
        printf("User not found.\n");
    }
}


void deleteUser() 
{
    int userId;
    bool userFound = false;
    User user;

    readInput("Enter the ID of the user to delete: ", &userId, 'd');

    FILE *file = fopen("user.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (!file || !tempFile) 
    {
        printf("Error opening file!\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) 
    {
        sscanf(line, "%d,%49[^,],%d", &user.id, user.name, &user.age);
        if (user.id != userId) 
        {
            fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
        } else 
        {
            userFound = true;
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("user.txt");
    rename("temp.txt", "user.txt");

    if (userFound) 
    {
        printf("User deleted successfully!\n");
    } else 
    {
        printf("User not found.\n");
    }
}

int main() 
{
    int choice;

    while (true) 
    {
        printf("\nUser Management System\n");
        printf("1. Add New User\n");
        printf("2. Display All Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        readInput("Enter your choice: ", &choice, 'd');

        switch (choice) 
        {
            case 1:
                createUser();
                break;
            case 2:
                readUsers();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}
