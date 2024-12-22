#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OPERATORS "*/+-"
#define ADD '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'
#define NULL_TERMINATOR '\0'

void readInput(char user_input[]) 
{
    printf("Enter an expression to be calculated: ");
    fgets(user_input, 100, stdin);
    char *iterator = user_input;
    while (*iterator != NULL_TERMINATOR) 
    {
        if (*iterator == '\n') 
        {
            *iterator = NULL_TERMINATOR;
            break;
        }
        iterator++;
    }
}

void removeWhitespaces(char user_input[]) 
{
    char *input_iterator = user_input;
    char *current_iterator = user_input;
    while (*input_iterator != NULL_TERMINATOR) 
    {
        if (*input_iterator != ' ') 
        {
            *current_iterator = *input_iterator;
            current_iterator++;
        }
        input_iterator++;
    }
    *current_iterator = NULL_TERMINATOR;
}

bool isDigitCharacter(char character) 
{
    return character >= '0' && character <= '9';
}

bool isOperator(char character) 
{
    char *op_iterator = OPERATORS;
    while (*op_iterator != NULL_TERMINATOR) 
    {
        if (character == *op_iterator) 
        {
            return true;
        }
        op_iterator++;
    }
    return false;
}

void validateInput(char user_input[]) 
{
    char *iterator = user_input;
    while (*iterator != NULL_TERMINATOR) 
    {
        if (!isDigitCharacter(*iterator) && !isOperator(*iterator)) 
        {
            printf("Error: Invalid character in expression.\n");
            exit(0);
        }
        iterator++;
    }
}

int computeOperation(int operand1, int operand2, char operator) 
{
    switch (operator) 
    {
        case ADD: return operand1 + operand2;
        case SUB: return operand1 - operand2;
        case MUL: return operand1 * operand2;
        case DIV:
            if (operand2 != 0) return operand1 / operand2;
            printf("Error: Division by zero.\n");
            exit(0);
        default:
            printf("Error: Unknown operator.\n");
            exit(0);
    }
}

int extractNumber(char user_input[], char **iterator) 
{
    int number = 0;
    while (isDigitCharacter(**iterator)) 
    {
        number = number * 10 + (**iterator - '0');
        (*iterator)++;
    }
    return number;
}

void accessOperator(int *numbers, int *num_idx, char *operators, int *op_idx)
{
    int operand2 = numbers[--(*num_idx)];
    int operand1 = numbers[--(*num_idx)];
    char operator = operators[--(*op_idx)];
    numbers[(*num_idx)++] = computeOperation(operand1, operand2, operator);
}

int evaluateExpression(char user_input[])
{
    int numbers[100];          
    char operators[100];      
    int num_idx = 0;          
    int op_idx = 0;           

    char *iterator = user_input; 
    while (*iterator != NULL_TERMINATOR) 
    {
        if (isDigitCharacter(*iterator)) 
        {
            numbers[num_idx++] = extractNumber(user_input, &iterator);
        } 
        else if (isOperator(*iterator)) 
        {
            if (*iterator == DIV) 
            {
                while (op_idx > 0 && operators[op_idx - 1] == DIV) 
                {
                    accessOperator(numbers, &num_idx, operators, &op_idx);
                }
                operators[op_idx++] = *iterator;
            }
            else if (*iterator == MUL) 
            {
                while (op_idx > 0 && operators[op_idx - 1] == MUL) 
                {
                    accessOperator(numbers, &num_idx, operators, &op_idx);
                }
                operators[op_idx++] = *iterator;
            }
            else if (*iterator == ADD) 
            {
                while (op_idx > 0 && (operators[op_idx - 1] == ADD || operators[op_idx - 1] == SUB || operators[op_idx - 1] == MUL || operators[op_idx - 1] == DIV)) 
                {
                    accessOperator(numbers, &num_idx, operators, &op_idx);
                }
                operators[op_idx++] = *iterator;
            }
            else if (*iterator == SUB) 
            {
                while (op_idx > 0 && (operators[op_idx - 1] == ADD || operators[op_idx - 1] == SUB || operators[op_idx - 1] == MUL || operators[op_idx - 1] == DIV)) 
                {
                    accessOperator(numbers, &num_idx, operators, &op_idx);
                }
                operators[op_idx++] = *iterator;
            }
            iterator++;
        } 
    }
    while (op_idx > 0) 
    {
        accessOperator(numbers, &num_idx, operators, &op_idx);
    }
    return numbers[0];
}

int main() 
{
    char user_input[100];
    readInput(user_input);
    removeWhitespaces(user_input);
    validateInput(user_input);
    int result = evaluateExpression(user_input);
    printf("Computed answer is: %d\n", result);
    return 0;
}
