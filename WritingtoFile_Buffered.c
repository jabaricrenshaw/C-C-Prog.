/********************************************
* JABARI CRENSHAW                           *
* CSC 60: PROF. SRIVATSA                    *
* WRITING TO FILE: BUFFERED APPLICATION     *
* 17 OCTOBER 2020                           *
********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main()
{
    //NUMBER OF BYTES TO READ
    int size, i;
    size = 8;

    //FILE POINTERS
    FILE *fp = fopen("mathquiz.txt", "r");
    if (fp == NULL)
    {
        printf("ERROR OPENING FILE");
        exit(1);
    }
    FILE *fw = fopen("mathquiz_buffered_log.txt", "w");

    //VARIABLE DECLARATIONS
    char operator;
    unsigned char operand1, operand2, answer;

    //Loop is designed to read 4 charachters per execution.
    //*One line of mathquiz.txt is 4 chatachters.
    //*Loop runtime in this case is equal to the number of charachters to read divided by 4.
    //*Reading 8 charachters will print 2 lines from mathquiz.txt to the log
    for (i = 0; i < (size / 4); i++)
    {
        fscanf(fp, "%c ", &operator);
        fprintf(fw, "%c", operator);

        fscanf(fp, "%c %c %c ", &operand1, &operand2, &answer); //NEEDS TO BE CHANGED TO %HHU
        fprintf(fw, "%c %c %c\n", operand1, operand2, answer);  //NEEDS TO BE CHANGED TO %HHU
    }

    //CLOSING THE  OPEN FILE DESCRIPTORS
    fclose(fp);
    if (fclose(fp) < 0)
    {
        exit(1);
    }
    fclose(fw);
    if (fclose(fw) < 0)
    {
        exit(2);
    }
}