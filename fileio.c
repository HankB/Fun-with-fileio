#include <stdio.h>
#include <errno.h>

/*
gcc -Wall -o fileio fileio.c
*/

static const char *file_name = "/tmp/test.txt";

/* open file to read values
    0 == success
    -1 == can't read three values
    errno == other file I/O problem
   close file if successfully opened.
*/
int get_vals(float *v1, float *v2, float *v3)
{
    FILE *f = fopen(file_name, "r"); // open for read

    if (0 == f)
    {
        perror("Can't open file for reading");
        return errno;
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

/* open file to store values
    0 == success
    errno == file I/O problem
   close file if successfully opened.
*/
int put_vals(float v1, float v2, float v3)
{
    FILE *f;
    f = fopen(file_name, "w"); // read/write + create
    if (0 == f)
    {
        perror("Can't open file for writing");
        return errno;
    }
    int rc = fprintf(f, "%f %f %f\n", v1, v2, v3);
    printf("put_vals() %d chars written\n", rc);
    fclose(f);
    if (rc > 0)
    {
        return 0;
    }
    else
    {
        return rc;
    }
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