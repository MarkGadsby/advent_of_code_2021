#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int ROWS = 1000;
const int COLS = 12;

enum WhoWins 
{
    e_ones,
    e_zeros,
    e_deadheat,
};

enum Rating 
{
    e_Oxygen,
    e_CO2,
};

int convert_row_to_int(char row[COLS])
{
    int enumerator = 0;
    int place_value = 1;

    for (int i = COLS - 1; i >= 0; i--)
    {
        if (row[i] == '1')
            enumerator += place_value;

        place_value *= 2;
    }
    return enumerator;
}

bool one_row_left(char data_2d_array[ROWS][COLS], int* pRow)
{
    int row_counter = 0;
    int row_index = 0;

    for (int row = 0; row < ROWS; row++)
    {
        if (data_2d_array[row][0] != '-')
        {
            row_index = row;
            row_counter++;
        }
    }

    *pRow = row_index;
    return row_counter == 1;
} 

enum WhoWins find_most_common(char data_2d_array[ROWS][COLS], int col)
{
    int ones    = 0;
    int zeros   = 0;

    for (int row = 0; row < ROWS; row++)
    {
        if (data_2d_array[row][col] != '-')
        {
            if (data_2d_array[row][col] == '1')
                ones++;
            else 
                zeros++;
        }
    }

    if (ones == zeros)
        return e_deadheat;
    else if (ones < zeros)
        return e_zeros;
    else 
        return e_ones;
}

void blank_zero_row(char data_2d_array[ROWS][COLS], int working_col)
{
    for (int row = 0; row < ROWS; row++)
    {
        if (data_2d_array[row][working_col] == '0')
        {
            for (int col = 0; col < COLS; col++)
            {
                data_2d_array[row][col] = '-';
            }
        }
    }
}

void blank_one_row(char data_2d_array[ROWS][COLS], int working_col)
{
    for (int row = 0; row < ROWS; row++)
    {
        if (data_2d_array[row][working_col] == '1')
        {
            for (int col = 0; col < COLS; col++)
            {
                data_2d_array[row][col] = '-';
            }
        }
    }
}

int remove_from_array(char data_2d_array[ROWS][COLS], bool bMostCommon)
{
    int lastRowIndex = 0;

    for (int i = 0; i < COLS; i++)
    {
        if (one_row_left(data_2d_array, &lastRowIndex))
            return convert_row_to_int(data_2d_array[lastRowIndex]);

        switch (find_most_common(data_2d_array, i))
        {
            case e_ones:
            {
                if (bMostCommon)
                    blank_one_row(data_2d_array, i);
                else
                    blank_zero_row(data_2d_array, i);
                break;
            }
            case e_zeros:
            {
                if (bMostCommon)
                    blank_zero_row(data_2d_array, i);
                else
                    blank_one_row(data_2d_array, i);
                break;
            }
            case e_deadheat:
            {
                if (bMostCommon)
                    blank_one_row(data_2d_array, i);
                else
                    blank_zero_row(data_2d_array, i);
                break;
            }
        }
    }  
    if (one_row_left(data_2d_array, &lastRowIndex))
        return convert_row_to_int(data_2d_array[lastRowIndex]);
}

int main()
{
    FILE* fp = fopen("day_3data.txt", "r");

    // allocate a 2D array of bytes - Rows x Cols 
    char oxygen_data[ROWS][COLS];
    char CO2_data[ROWS][COLS];

    memset(oxygen_data, 0, ROWS * COLS);
    memset(CO2_data, 0, ROWS * COLS);

    int i = 0;

    while (!feof(fp))
    {  
        fscanf(fp, "%s", &(oxygen_data[i][0]));
        i++;
    }

    memcpy(CO2_data, oxygen_data, ROWS * COLS);

    int oxygen_generator_rating = remove_from_array(oxygen_data, e_Oxygen);
    int CO2_scrubber_rating = remove_from_array(CO2_data, e_CO2);
    
    printf("\n\n\toxygen_generator_rating:\t%d\n", oxygen_generator_rating);
    printf("\tCO2_scrubber_rating:\t\t%d\n", CO2_scrubber_rating);

    printf("\n\tLife Support Rating:\t\t%d\n\n\n", oxygen_generator_rating * CO2_scrubber_rating);

    fclose(fp);
    return 0;
}