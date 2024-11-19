#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
void removewhitespacesfromexpression(char input[]) {
    int start = 0, start1 = 0;
    while (input[start] != '\0') {
        if (!isspace(input[start])) {
            input[start1] = input[start]; 
            start1++;
        }
        start++;
    }
    input[start1] = '\0';
}

int maincalculation(int op1, int op2, char op) {
    if (op == '+') return op1 + op2; 
    if (op == '-') return op1 - op2;
    if (op == '*') return op1 * op2; 
    if (op == '/') {
        if (op2 != 0) {
            return op1 / op2; 
        }else{
        printf("Error:Division by zero.\n");
        exit(1); 
    }
    }
}

int mainoperation(char input[]) {
    int startnumber = 0, endnumber = 0, ans = 0;
    char op = 'x';
    int i = 0;
    while (isdigit(input[i])) {
        startnumber = startnumber * 10 + (input[i] - '0');
        i++;
    }
    while (input[i] != '\0') {
        if (strchr("*/+-",input[i])) {
            op = input[i];
            i++;
        } else {
            printf("Invalid expression.\n");
            return 0;
        }
        endnumber = 0;
        while (isdigit(input[i])) {
            endnumber = endnumber * 10 + (input[i] - '0');
            i++;
        }
        if (op == '*' || op == '/') {
            startnumber = maincalculation(startnumber, endnumber, op); 
        } else {
            ans += startnumber; 
            startnumber = endnumber;   
        }
    }
 ans += startnumber;
 return ans;
}
int main() {
    char inputexpression[100];

    printf("Enter a input expression to be calculated: ");
    fgets(inputexpression, sizeof(inputexpression), stdin);
    removewhitespacesfromexpression(inputexpression); 
    for (int i = 0; inputexpression[i] != '\0'; i++) {
        if (!isdigit(inputexpression[i]) && !strchr("*/+-", inputexpression[i])) {
            printf("Error: Invalid expression.\n");
            exit(1);
        }
    }
    int ans =mainoperation(inputexpression); 
    printf("Computed answer is : %d\n",ans);
     return 0; 
}
