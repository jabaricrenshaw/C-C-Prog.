/********************************************
* JABARI CRENSHAW                           *
* CSC 60: PROF. SRIVATSA                    *
* WRITING TO FILE: UnBUFFERED APPLICATION   *
* 17 OCTOBER 2020                           *
********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main()
{

    //VARIABLE DECLARATION
    char operator, operand1, operand2, answer;
    int i, size;
    //NUMBER OF BYTES TO READ
    size = 4;

    //FILES TO READ AND WRITE
    int fd = open("mathquiz.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("ERROR OPENING FILE.");
        exit(1);
    }

    int fw = open("mathquiz_unbuffered_log.txt", O_WRONLY | O_CREAT);
    if (fw < 0)
    {
        perror("COULD NOT CREATE LOG FILE");
        exit(1);
    }

    //Loop is designed to read one charachter each execution
    //*One line of mathquiz.txt is 4 charachters
    //*Loop runtine is the number of bytes to read
    //*Reading 4 charachters will print the first line of mathquiz.txt
    for (i = 0; i <= size; i++)
    {
        switch (i)
        {
        case 1:
            read(fd, &operator, 1);
            write(fw, &operator, 1);
            break;
        case 2:
            lseek(fd, 1, 1);
            read(fd, &operand1, 1);
            write(fw, &operand1, 1);
            break;
        case 3:
            lseek(fd, 1, 1);
            read(fd, &operand2, 1);
            write(fw, &operand2, 1);
            break;
        case 4:
            lseek(fd, 1, 1);
            read(fd, &answer, 1);
            write(fw, &answer, 1);
            write(fw, "\n", 1);
            break;
        }
    }

    //CLOSING FILE DESCRIPTORS
    close(fd);
    close(fw);
    if (close(fd) < 0)
    {
        exit(1);
    }
    if (close(fw) < 0)
    {
        exit(2);
    }
}