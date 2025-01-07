#include <stdio.h>
#include <string.h>
// Coded by Mr.Quantum (Darshan Patel)

int main()
{
    char str[1000];
    printf("Enter the address of the first file wihtout quotes (e.g: C:\\Mr_Quantum\\CS\\Quantumania_part1.txt): ");
    scanf("%[^\n]s", str);

    // replace backslashes with forward slashes
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\\')
        {
            str[i] = '/';
        }
        i++;
    }

    printf("Enter the Extension of the PartFinder file (e.g - .txt, .exe, .mp4): ");
    char strTemp[20];
    scanf("%99s", strTemp);

    char strPartFinder[1006];
    strcpy(strPartFinder, str);
    int j = 1005;
    while (1) // remove extension in file name and the concatenate the _part1
    {
        if (strPartFinder[j] == '.')
        {
            strPartFinder[j] = '\0';
            break;
        }
        j--;
    }

    strcat(strPartFinder, strTemp);

    FILE *ptr0; // original part-file
    ptr0 = fopen(str, "rb");
    if (ptr0 == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    char strOutput[1006];
    strcpy(strOutput, str);
    char *underscorePosition = strrchr(strOutput, '_');
    sprintf(underscorePosition, "_Joined%s", strTemp);
    printf("%s", strOutput);
    FILE *ptr1; // final whole single file
    ptr1 = fopen(strOutput, "wb");
    if (ptr1 == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    int part = 1;
    while (1)
    {
        int original = fgetc(ptr0); // EOF expands to -1 hence "int" is correct
        if (original == EOF)
        {
            fclose(ptr0);
            part++;
            char *underscorePosition = strrchr(strPartFinder, '_');
            sprintf(underscorePosition, "_part%d%s", part, strTemp);

            FILE *ptr0;
            ptr0 = fopen(strPartFinder, "rb");
            if (ptr0 == NULL)
            {
                break;
            }
            original = fgetc(ptr0);
        }

        char ch = (char)original;
        fwrite(&ch, 1, 1, ptr1);
    }

    fclose(ptr0);
    fclose(ptr1);

    printf("Sucess!");

    return 0;
}