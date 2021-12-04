#include <stdio.h>
#include <string.h>

int main()
{
    FILE* fp = fopen("binary.txt", "r");
    
    int total = 0;
    int slot_0 = 0;
    int slot_1 = 0;
    int slot_2 = 0;
    int slot_3 = 0;
    int slot_4 = 0;

    char binary_chars[12000];
    char bucket[13];
    int indexer = 0;

    while (!feof (fp))
    {  
        fscanf(fp, "%s", bucket);
        strcpy(&(binary_chars[indexer]), bucket);
        
        indexer += 12;
    }

//    printf("%s", binary_chars);

    for (int i = 0; i < 12000; i++)
    {
        if ((i % 5) == 0)
        {
            if (binary_chars[i] == '0')
                slot_0++;
        }
        if ((i % 5) == 1)
        {
            if (binary_chars[i] == '0')
                slot_1++;
        }
        if ((i % 5) == 2)
        {
            if (binary_chars[i] == '0')
                slot_2++;
        }
        if ((i % 5) == 3)
        {
            if (binary_chars[i] == '0')
                slot_3++;
        }
        if ((i % 5) == 4)
        {
            if (binary_chars[i] == '0')
                slot_4++;
        }

        printf("%c", binary_chars[i]);
 
    }

    printf("\nSlot 1\t%d\n", slot_0);
    printf("Slot 2\t%d\n", slot_1);
    printf("Slot 3\t%d\n", slot_2);
    printf("Slot 4\t%d\n", slot_3);
    printf("Slot 5\t%d\n", slot_4);

    int gamma = 0;
    int epsilon = 0;

    if (slot_0 > 1200)
        gamma += 16;
    else
        epsilon += 16;

    if (slot_1 > 1200)
        gamma += 8;
    else
        epsilon += 8;

    if (slot_2 > 1200)
        gamma += 4;
    else
        epsilon += 4;

    if (slot_3 > 1200)
        gamma += 2;
    else
        epsilon += 2;

    if (slot_4 > 1200)
        gamma += 1;
    else
        epsilon += 1;

    printf("\n\tgamma = %d\n", gamma);
    printf("\tepsilon = %d\n", epsilon);


    printf("\n\n%d\n", epsilon * gamma);

    fclose(fp);
    return 0;
}