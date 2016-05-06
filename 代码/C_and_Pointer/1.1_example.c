#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_COLS 20
#define MAX_INPUT 1000

int read_column_number (int colums[],int max);
void readrrange(char * output, char const *input, int n_columns ,int const columns[]);

int main()
{
    int n_columns;
    int columns[MAX_COLS];
    char input[MAX_INPUT];
    char output[MAX_INPUT];

    n_columns = read_column_number(columns,MAX_COLS);

    while(scanf("%s",&input) != 0)
    {
        printf("Original input :%s\n",input);
        readrrange(output, input ,n_columns, columns);
        printf("Readrrange line: %s\n",output);
    }
    return EXIT_SUCCESS;

}

int read_column_number(int columns[],int max)
{
    int num = 0;
    int ch;

    while(num < max && scanf("%d",&columns[num]) == 1 && columns[num] >= 0)
    {
        num += 1;
    }
    if(num % 2 != 0)
    {
        puts("Last column number is not paried.");
        exit(EXIT_FAILURE);
    }
    while((ch = getchar()) != EOF && ch != '\n')
    {
        continue    ;
    }
    return num;

}

void readrrange(char *output, char const *input, int n_columns, int const columns[])
{
    int col;
    int output_col;
    int len;

    len = strlen(input);
    output_col = 0;

    for(col= 0 ;col < n_columns; col+=2)
    {
        int nchars = columns[col + 1] - columns[col] +1;
        if(columns[col] >= len || output_col == MAX_INPUT -1)
        {
            break;
        }
        if(output_col + nchars > MAX_INPUT - 1)
        {
            nchars = MAX_INPUT - output_col -1;
        }
        strncpy(output + output_col, input + columns[col],nchars);
        output_col += nchars;
    }
    output[output_col] = '\0';
}
