#include <stdio.h>
#include <errno.h>

/*
gcc -Wall -o fileio fileio.c
*/

static FILE *f;

int get_vals(float *v1, float *v2, float *v3)
{
    f = fopen("/tmp/test.txt", "w+"); // read/write + create
    if (0 == f)
    {
        perror("Can't open file");
        return -1;
    }
    int rc = fscanf(f, "%f %f %f", v1, v2, v3);

    if (rc != 3)
    {
        fprintf(stderr, "Can't read all values: %d\n", rc);
        return -1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    float temperature, humidity, pressure;
    if (0 == get_vals(&temperature, &humidity, &pressure))
    {
        printf("Hello World\n");
    }
    else
    {
        printf("Can't fetch values from file\n");
    }
}