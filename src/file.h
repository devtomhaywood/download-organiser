#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "extension.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int file(char *originFilePath, char *destinationFilePath) 
{
    DIR *directory;
    struct dirent *entry;
    directory = opendir(originFilePath);
    char startPath[1024];
    char extPath[1024];
    char finalPath[1024];

    if (directory == NULL)
    {
        printf("Error opening directory.\n");
        return 1;
    }
    
    while ((entry = readdir(directory)) != NULL)
    {
        if (entry -> d_type == DT_REG)
        {
            const char* ext = getExtension(entry->d_name);
            struct stat st = {0};

            sprintf(startPath, "%s%s", originFilePath, entry->d_name);
            sprintf(extPath, "%s%s", destinationFilePath, ext);
            sprintf(finalPath, "%s/%s", extPath, entry->d_name);

            if (stat(extPath, &st) == -1) 
            {
                printf("Creating directory... %s\n", extPath);
                mkdir(extPath, 0700);
                printf("Directory succesfully created!\n");
                rename(startPath, finalPath);
                printf("File %s successfully moved to: %s\n", entry->d_name, finalPath);
                
            }
            else 
            {
                rename(startPath, finalPath);
                printf("File %s successfully moved to: %s\n", entry->d_name, finalPath);
            }
        }

        else if (entry -> d_type == DT_DIR)
        {
            struct stat st = {0};

            sprintf(startPath, "%s%s", originFilePath, entry->d_name);
            sprintf(extPath, "%s/%s", destinationFilePath, "folder");
            sprintf(finalPath, "%s/%s", extPath, entry->d_name);

            if (entry->d_name[0] != '.')
            {
                if (stat(extPath, &st) == -1) 
                {
                    printf("Creating directory... %s\n", extPath);
                    mkdir(extPath, 0700);
                    printf("Directory succesfully created!\n");
                    rename(startPath, finalPath);
                    printf("File %s successfully moved to: %s\n", entry->d_name, finalPath);
                    
                }
                else 
                {
                    rename(startPath, finalPath);
                    printf("File %s successfully moved to: %s\n", entry->d_name, finalPath);
                }
            }
        }
    }

    if (closedir(directory) == -1)
    {
        printf("Error closing directory.\n");
        return 1;
    }

    return 0;
}


