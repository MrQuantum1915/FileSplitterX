#include <stdio.h>
#include <string.h>
// Coded by Mr.Quantum (Darshan Patel)

int main()
{
    char str[1000];
    printf("Enter the address of file wihtout quotes (e.g: C:\\Mr_Quantum\\CS\\Quantumania.txt): ");
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

    FILE *ptr0;
    ptr0 = fopen(str, "rb");
    if (ptr0 == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    char str2[1006];
    strcpy(str2, str);
    int j = 1005;
    while (1) // remove extension in file name and the concatenate the _part1
    {
        if (str2[j] == '.')
        {
            str2[j] = '\0';
            break;
        }
        j--;
    }

    strcat(str2, "_part1");

    printf("Enter the Extension of the output file (e.g - .txt, .exe, .mp4): ");
    char strTemp[20];
    scanf("%99s", strTemp);
    strcat(str2, strTemp);

    long long sizeLimit = 0;
    printf("Enter the size limit of each file chunks from the file (in bytes) : ");
    scanf("%lld", &sizeLimit);

    FILE *ptr1;
    ptr1 = fopen(str2, "wb");
    if (ptr1 == NULL)
    {
        printf("Error opening new file!\n");
        fclose(ptr0);
        return 1;
    }
    int fileSize = 0;

    int part = 1;

    while (1)
    {
        if (fileSize == sizeLimit)
        {
            fileSize = 0;
            fclose(ptr1);
            part++;

            char *underscorePosition = strrchr(str2, '_');
            sprintf(underscorePosition, "_part%d%s", part, strTemp);

            // strrchr finds last occurence of a charcter, here '_'

            FILE *ptr1;
            ptr1 = fopen(str2, "wb");
            if (ptr1 == NULL)
            {
                printf("Error opening new file!\n");
                fclose(ptr0);
                return 1;
            }
        }

        int original = fgetc(ptr0); // EOF expands to -1 hence "int" is correct
        if (original == EOF)
        {
            break;
        }
        char ch = (char)original;
        fwrite(&ch, 1, 1, ptr1);
        fileSize++;
    }

    printf("Success\nFile Size = %d bytes", fileSize);
    fclose(ptr0);
    fclose(ptr1);
    return 0;
}