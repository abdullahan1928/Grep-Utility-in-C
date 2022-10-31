#include "ANSI-color-codes.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_LENGTH 511

int main(int ac, char *av[])
{
    char lineBuffer[BUFFER_LENGTH + 1];
    FILE *fp = NULL;
    int count = 0;
    int lineNum = 1;

    if (ac < 3)
    {
        printf("A string to be matched and a filename is required.\n");
        return 0;
    }

    fp = fopen(av[2], "r");
    if (!fp)
    {
        fprintf(stderr, "Error - unable to open %s\n", av[2]);
        return 2;
    }

    int inputLen = strlen(av[1]);

    printf("-----------------\n");
    printf("Matching Strings\n");
    printf("-----------------\n");

    while (fgets(lineBuffer, BUFFER_LENGTH, fp))
    {
        if (strstr(lineBuffer, av[1]))
        {
            printf(BBLK "%d ", lineNum);
            printf(reset);
            int position = strstr(lineBuffer, av[1]) - lineBuffer;

            for (int i = 0; i < strlen(lineBuffer); i++)
            {
                if (i == position)
                {
                    for (int j = position; j < position + inputLen; j++)
                    {
                        printf(RED "%c", lineBuffer[j]);
                        printf(reset);
                    }
                    i += inputLen - 1;
                }
                else
                {
                    printf("%c", lineBuffer[i]);
                }
            }
            ++count;
        }

        lineNum++;
    }
    fclose(fp);

    printf("\n------------------");
    printf("\nNumber of Matches");
    printf("\n------------------\n");

    printf("Found %d matches!\n", count);

    return 0;
}
