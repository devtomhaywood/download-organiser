#include <stdio.h>
#include <dirent.h>
#include "src/file.h"

int main() {
    char origin[] = "/Users/tomhaywood/Downloads/";
    char desintation[] = "/Users/tomhaywood/Documents/download-ordered/";

    file(origin, desintation);

    return 0;
}