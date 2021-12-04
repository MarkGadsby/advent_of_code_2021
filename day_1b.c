#include <stdio.h>

#define HUGE 10000;

struct Ladder
{
    int t;
    int m;
    int b;
};

int main()
{
    FILE* fp = fopen("input.txt", "r");

    struct Ladder prev;
    struct Ladder curr;

    prev.t = HUGE;
    prev.m = HUGE;
    prev.b = HUGE;

    curr.t = HUGE;
    curr.m = HUGE;
    curr.b = HUGE;

    int reading = 0;
    int count = 0;
 
    while (!feof (fp))
    {  
        fscanf (fp, "%d", &reading);

        prev.t = curr.t;
        prev.m = curr.m;
        prev.b = curr.b;
        curr.t = curr.m;
        curr.m = curr.b;
        curr.b = reading;

        if ((curr.t + curr.m + curr.b) > (prev.t + prev.m + prev.b))
            count++;
    }
    
    printf("%s %i", "The total is: ", count);

    fclose(fp);
    return 0;
}