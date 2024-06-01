#include <stdio.h>
#include <string.h>

const char *getExtension(char *filename)
{
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}