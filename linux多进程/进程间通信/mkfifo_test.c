#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int accret = access("fifo1", F_OK);
    if (accret == -1)
    {
        int ret = mkfifo("fifo1", 0664);
        if (ret == -1)
        {
            perror("mkfifo");
            exit(0);
        }
    }

    return 0;
}