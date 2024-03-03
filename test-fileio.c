#include <stdio.h>
#include <errno.h>

#include "fileio.h"
/*
gcc -Wall -o test-fileio test-fileio.c fileio.c
*/

// static const char *val_file_name = "/media/hbarta/test1/vals";
static const char *val_file_name = "/tmp/vals";

int main(int argc, char **argv)
{
    float temperature = 0, humidity = 1, pressure = 2;
    unsigned int count = 0;

    if (0 == get_vals(val_file_name, &temperature, &humidity, &pressure, &count))
    {
        printf("read %f, %f, %f, %d\n", temperature, humidity, pressure, count);
    }
    else
    {
        printf("Can't fetch values from file\n");
    }

    put_vals(val_file_name, temperature + 1, humidity + 1, pressure + 1, ++count);
}