#include <stdio.h>

#define HUGE 100000;

int main()
{
    FILE* fp = fopen("day_1data.txt", "r");

    int prev = HUGE;
    int curr = 0;
    int count = 0;
 
    while (!feof (fp))
    {  
        fscanf (fp, "%d", &curr);

        if (curr > prev)
            count++;
        
        prev = curr;
    }
    
    printf("%s %i", "The total is: ", count);

    fclose(fp);
    return 0;
}