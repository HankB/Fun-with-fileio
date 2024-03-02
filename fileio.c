#include <stdio.h>
#include <errno.h>

/*
gcc -Wall -o fileio fileio.c
*/

int get_vals(float *v1, float *v2, float *v3)
{
    FILE *f;
    f = fopen("/tmp/test.txt", "r"); // read/write + create
    if (0 == f)
    {
        perror("Can't open file for reading");
        return -1;
    }
    int rc = fscanf(f, "%f%f%f", v1, v2, v3);
    fclose(f);

    if (rc != 3)
    {
        fprintf(stderr, "Can't read all values: %d\n", rc);
        return -1;
    }
    return 0;
}

int put_vals(float v1, float v2, float v3)
{
    FILE *f;
    f = fopen("/tmp/test.txt", "w"); // read/write + create
    if (0 == f)
    {
        perror("Can't open file for reading");
        return -1;
    }
    int rc = fprintf(f, "%f %f %f\n", v1, v2, v3);
    printf("put_vals() %d chars written\n", rc);
    fclose(f);
    return rc;
}

int main(int argc, char **argv)
{
    float temperature = 0, humidity = 1, pressure = 2;
    if (0 == get_vals(&temperature, &humidity, &pressure))
    {
        printf("read %f, %f, %f\n", temperature, humidity, pressure);
    }
    else
    {
        printf("Can't fetch values from file\n");
    }

    put_vals(temperature + 1, humidity + 1, pressure + 1);
}