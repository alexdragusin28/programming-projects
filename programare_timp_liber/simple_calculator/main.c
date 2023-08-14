#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main()
{
    int values;
    float value[100];
    char operators[99];
    float answer;

    printf("How many values do you want to calculate?: ");
    scanf("%d", &values);
    printf("\n");
    if(values<2 || values>100)
    {
        printf("Error! Please, enter another value between 2 and 100: \n");
        scanf("%d", &values);
    }

    printf("Enter the values and operators: \n\n");

    for(int i=0; i<values; i++)
    {
        scanf("%f", &value[i]);
        if(i<values-1)
        {
            scanf("%c", &operators[i]);
        }
    }
    answer=value[0]; // raspunsul initial va fi intotdeauna prima valoare citita de la tastatura ----- doar daca avem + sau -
    for(int i=0;i<values-1;i++)
    {
        switch(operators[i])
        {
        case '+':

            if(operators[i+1]=='*')
            {
                float aux_value=value[i+1]*value[i+2];
                i++;
                // am facut aceasta conditie "generala" pe care o vom folosi in toate cazaurile care au + sau - in fata;
                while(i<values-2 && (operators[i+1] == '^' || operators[i+1] == '*' || operators[i+1] == '/'))
                {
                    if(operators[i+1] == '^')
                        aux_value=pow(aux_value, value[i+2]);
                    else if(operators[i+1] == '*')
                        aux_value*=value[i+2];
                    else if(operators[i+1] == '/')
                        aux_value/=value[i+2];
                    i++;
                }
                answer=answer+aux_value;
            }
            else if(operators[i+1]=='/')
            {
                float aux_value=value[i+1]/value[i+2];
                i++;
                while(i<values-2 && (operators[i+1] == '^' || operators[i+1] == '*' || operators[i+1] == '/'))
                {
                    if(operators[i+1] == '^')
                        aux_value=pow(aux_value, value[i+2]);
                    else if(operators[i+1] == '*')
                        aux_value*=value[i+2];
                    else if(operators[i+1] == '/')
                        aux_value/=value[i+2];
                    i++;
                }
                answer=answer+aux_value;
            }
            else if(operators[i+1]=='^')
            {
                float aux_value=pow(value[i+1], value[i+2]);
                i++;
                while(i<values-2 && (operators[i+1] == '^' || operators[i+1] == '*' || operators[i+1] == '/'))
                {
                    if(operators[i+1] == '^')
                        aux_value=pow(aux_value, value[i+2]);
                    else if(operators[i+1] == '*')
                        aux_value*=value[i+2];
                    else if(operators[i+1] == '/')
                        aux_value/=value[i+2];
                    i++;
                }
                answer=answer+aux_value;
            }
            else
            {
                answer+=value[i+1];
            }
            break;
        case '-':
            if(operators[i+1]=='*')
            {
                float aux_value=value[i+1]*value[i+2];
                i++;
                while(i<values-2 && (operators[i+1] == '^' || operators[i+1] == '*' || operators[i+1] == '/'))
                {
                    if(operators[i+1] == '^')
                        aux_value=pow(aux_value, value[i+2]);
                    else if(operators[i+1] == '*')
                        aux_value*=value[i+2];
                    else if(operators[i+1] == '/')
                        aux_value/=value[i+2];
                    i++;
                }
                answer=answer-aux_value;
            }
            else if(operators[i+1]=='/')
            {
                float aux_value=value[i+1]/value[i+2];
                i++;
                while(i<values-2 && (operators[i+1] == '^' || operators[i+1] == '*' || operators[i+1] == '/'))
                {
                    if(operators[i+1] == '^')
                        aux_value=pow(aux_value, value[i+2]);
                    else if(operators[i+1] == '*')
                        aux_value*=value[i+2];
                    else if(operators[i+1] == '/')
                        aux_value/=value[i+2];
                    i++;
                }
                answer=answer-aux_value;
            }
            else if(operators[i+1]=='^')
            {
                float aux_value=pow(value[i+1], value[i+2]);
                i++;
                while(i<values-2 && (operators[i+1] == '^' || operators[i+1] == '*' || operators[i+1] == '/'))
                {
                    if(operators[i+1] == '^')
                        aux_value=pow(aux_value, value[i+2]);
                    else if(operators[i+1] == '*')
                        aux_value*=value[i+2];
                    else if(operators[i+1] == '/')
                        aux_value/=value[i+2];
                    i++;
                }
                answer=answer-aux_value;
            }
            else
            {
                answer-=value[i+1];
            }
            break;
        case '*':
                if(i==0)
                    answer=value[i]*value[i+1];
                else if(operators[i-1] == '*')
                    answer=answer*value[i+1];
                else if(operators[i-1] == '/')
                    answer=answer*value[i+1];
                else if(operators[i-1] == '^')
                    answer=answer*value[i+1];
                else answer=answer+value[i]*value[i+1];
            break;
        case '/':
                if(i==0)
                    answer=value[i]/value[i+1];

                if(operators[i-1] == '*')
                    answer=answer/value[i+1];
                else if(operators[i-1] == '/')
                    answer=answer/value[i+1];
                else if(operators[i-1] == '^')
                    answer=answer/value[i+1];
                else answer=answer+value[i]/value[i+1];
            break;
        case '^':
                if(operators[i-1] == '+')
                    answer+=pow(value[i],value[i+1]);
                else if(operators[i-1] == '-')
                    answer-=pow(value[i],value[i+1]);
                else answer=pow(answer, value[i+1]);
            break;
        default: printf("Invalid operator");
    }
    }
    for(int i=0;i<values;i++)
    {   if(i<values-1)
            printf("%.2f %c ", value[i], operators[i]);
        else printf("%.2f ", value[i]);
        if(i==values-1)
            printf(" = %.2f", answer);
    }
    return 0;
}
