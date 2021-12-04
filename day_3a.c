#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    FILE* fp = fopen("day_3data.txt", "r");
    
    int total = 0;
    int slot_array[12];
    char binary_num[16];

    memset(slot_array, 0, sizeof(int) * 12);

    while (!feof(fp))
    {  
        fscanf(fp, "%s", binary_num);

        for (int i = 0; i < 12; i++)
        {
            if (binary_num[i] == '1')
                slot_array[i]++;
        }
        total++;
    }

    int gamma = 0;
    int epsilon = 0;
    int place_holder = pow(2,11);     // 2048 1024 512 256 128 64 32 16 8 4 2 1 
    
    for (int i = 0; i < 12; i++)
    {
        if (slot_array[i] > (total / 2))
            gamma += place_holder;
        else
            epsilon += place_holder;

        place_holder /= 2;    
    }
    printf("\n\n\t\tgamma x epsilon = %d\n\n", epsilon * gamma);

    fclose(fp);
    return 0;
}