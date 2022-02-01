#include <stdio.h>
#include <string.h>
#include <math.h>

const int ROWS = 1000;
const int COLS = 12;

int FindMostCommon(char data_2d_array[ROWS][COLS], int col)
{
    int ones = 0;
    for (int row = 0; row < ROWS; row++)
    {
        if (data_2d_array[row][col] == '1')
            ones++;
    }

    if (ones == (ROWS / 2))
        return 2;
    else if (ones < (ROWS / 2))
        return 0;
    else 
        return 1;
}

int main()
{
    FILE* fp = fopen("day_3data.txt", "r");

    // allocate a 2D array of bytes - Rows x Cols 
    char data_2d_array[ROWS][COLS];
    memset(data_2d_array, 0, ROWS * COLS);
    int i = 0;

    while (!feof(fp))
    {  
        fscanf(fp, "%s", &(data_2d_array[i][0]));
        i++;
    }

    for (int row = 0; row < ROWS; row++)
    {
        printf("%d\t",row);

        for (int col = 0; col < COLS; col++)
            printf("%c",data_2d_array[row][col]);
      
        printf("\n");
    }

    for (int i = 0; i < COLS; i++)
    {
        printf("%d\t%d\n",i, FindMostCommon(data_2d_array, i));
    }
    
    fclose(fp);
    return 0;
}