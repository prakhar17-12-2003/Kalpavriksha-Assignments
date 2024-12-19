#include<stdio.h>
#include<stdlib.h> 
#include<stdbool.h>

#define OPERATORS "*/+-"  

void readInput(char user_input[]) 
{
    printf("Enter a expression to be calculated: ");
    fgets(user_input,100,stdin);
    //If i press enter after typing input,it adds \n in string and gives error
    // here need to replace \n by null  character
     for (int i = 0; user_input[i] != '\0'; i++)
    {
        if (user_input[i] == '\n') 
        {
            user_input[i] = '\0';
            break;
        }
    }
}


void removeWhitespaces(char user_input[]) 
{
    int iterator_input = 0, iterator_current = 0;
    while (user_input[iterator_input] != '\0') 
    {
        if (user_input[iterator_input] != ' ') 
        {
            user_input[iterator_current++] = user_input[iterator_input];
        }
        iterator_input++;
    }
    user_input[iterator_current] = '\0';
}


bool isDigit(char ch) 
{
    if(ch>='0' && ch<='9')
    {
        return true;
    }
    return false;
}


bool isOperator(char ch) 
{
    for (int i=0; OPERATORS[i]!='\0';i++)
    {
        if (ch==OPERATORS[i]) 
        {
            return true;
        }
    }
    return false;
}


void checkInput(char user_input[]) 
{
    for (int i = 0; user_input[i] != '\0'; i++) 
    {
        if (!isDigit(user_input[i]) && !isOperator(user_input[i])) 
        {
            printf("Error: Invalid character in expression.\n");
            exit(0);
        }
    }
}


int checkPrecedence(char op)
{
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
}


int computeOpeartions(int operand1, int operand2, char operator) 
{
    if (operator == '+')      return operand1 + operand2; 
    else if (operator == '-') return operand1 - operand2;
    else if (operator == '*') return operand1 * operand2; 
    else if (operator == '/') 
    {
        if (operand2 != 0) 
        {
            return operand1 / operand2; 
        }
        else
        {
        printf("Error:Division by zero.\n");
        exit(0); 
        }
    }
}


int traverseNumber(char user_input[], int *iterator) 
{
    int num = 0;
    while (isDigit(user_input[*iterator])) 
    {
        num = num * 10 + (user_input[*iterator] - '0');
        (*iterator)++;
    }
    return num;
}


void accessOpeartor(int *numbers, int *num_idx, char *operators, int *op_idx)
{
    int operand2 = numbers[--(*num_idx)];
    int operand1 = numbers[--(*num_idx)];
    char operator = operators[--(*op_idx)];
    numbers[(*num_idx)++] = computeOpeartions(operand1, operand2, operator);
}


int evaluateExpression(char user_input[])
{
    int numbers[100];          
    char operators[100];      
    int num_idx = 0;      
    int op_idx = 0;   

    int iterator = 0;         

    while (user_input[iterator] != '\0') 
    {
        if (isDigit(user_input[iterator])) 
        {
            numbers[num_idx++] = traverseNumber(user_input, &iterator);
        } 
        else if (isOperator(user_input[iterator])) 
        {
            while (op_idx > 0 && checkPrecedence(operators[op_idx - 1]) >= checkPrecedence(user_input[iterator]))
            {
                accessOpeartor(numbers, &num_idx, operators, &op_idx);
            }
            operators[op_idx++] = user_input[iterator];
            iterator++;
        } 
    }
    while (op_idx > 0) 
    {
        accessOpeartor(numbers, &num_idx, operators, &op_idx);
    }
    return numbers[0];
}


int main() {
    char user_input[100];
    readInput(user_input);
    removeWhitespaces(user_input);
    checkInput(user_input);
    int ans_computed = evaluateExpression(user_input);
    printf("Computed answer is : %d\n",ans_computed);
    return 0;
}
