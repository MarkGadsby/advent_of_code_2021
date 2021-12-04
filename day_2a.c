#include <stdio.h>
#include <string.h>

#define MAX_STR 10

int main()
{
    int h_pos = 0;
    int depth = 0;

    char instruction[MAX_STR];
    int value = 0;

    FILE* fp = fopen("directions.txt", "r");
    
    while (!feof (fp))
    {  
        fscanf(fp,"%s", instruction);
        fscanf(fp,"%i", &value);

        if (strcmp(instruction, "forward") == 0)
        {
            h_pos += value;
        }
        else if (strcmp(instruction, "down") == 0)
        {
            depth += value;    
        }
        else if (strcmp(instruction, "up") == 0)
        {
            depth -= value;
        }
        //    printf("%s %s\t %s %i\n", "instruction = ", instruction, "value = ", value);
    }
    
    printf("%s %i\n\n", "\nThe new position is:", depth * h_pos);

    fclose(fp);
    return 0;
}