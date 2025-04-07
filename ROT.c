#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_MALLOC 1
#define ERR_FILE_NOT_FOUND 2

char *path_and_filename(int *error_code);
void ROT_over_file(int rot_num, FILE *func_file);


int main(void) {
    int error = 0;
    char *full_path = path_and_filename(&error);

    //check if full_patch is valid (have the path and not NULL)
    if (full_path == NULL) {
        switch (error) {
            case ERR_MALLOC:
                printf("Memory allocation error");
                break;
            case ERR_FILE_NOT_FOUND:
                printf("File not found");
            default:
                printf("Unknown error");
        }
        return 1;
    }

    FILE *file = fopen(full_path, "r+"); //"r+": Open the file for both reading and writing. The file must exist.
    if (file == NULL) {
        return ERR_FILE_NOT_FOUND;
    }

    int rot_times = 0;
    printf("Enter the number of rotation you want: ");
    scanf("%d", &rot_times);

    ROT_over_file(rot_times, file);
    
    return 0;
}
//
//
//
//
char *path_and_filename(int *error_code) {
    char path[101] = {0};
    char filename[31] = {0};

    printf("Enter Path and File-name, to execute Caesar Cipher on the File.\n");
    printf("Path: ");
    scanf("%100s", path); //scanf already adds \0
    printf("File: ");
    scanf("%30s", filename); //scanf already adds \0

    //Get length of path and file
    size_t path_len = strlen(path);
    size_t filename_len = strlen(filename);
    size_t total_len = (path_len + filename_len) + 2;

    char *p_and_t = malloc(total_len * sizeof(char)); //len for path and filename allocation
    if (p_and_t == NULL) {
        if (error_code != NULL) { //check if the pointer isn't pointing to anything
            *error_code = ERR_MALLOC;
        }
        return NULL;
    }

    memcpy(p_and_t, path, strlen(path));
    p_and_t[strlen(path)] = '\\';
    memcpy(p_and_t + strlen(path) + 1, filename, strlen(filename)); //the purpose of p_ant_t... at the start is to provide the memory addres, because memcpy works with memory not len (as 1st parameter)
    p_and_t[strlen(path) + 1 + strlen(filename)] = '\0';

    //set error_code to 0 if no error occurred
    if (error_code != NULL) {
        *error_code = 0;
    }

    // printf("FILE: %s\n", p_and_t);
    return p_and_t;
}
//
//
//
void ROT_over_file(int rot_num, FILE *func_file) {
    int ch;
    long pos;
    
    while ((ch = fgetc(func_file)) != EOF) {
        pos = ftell(func_file) - 1; //-1 to get to the char we just read
        if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' + rot_num) % 26 + 'a';
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' + rot_num) % 26 + 'A';
        }
        
        fseek(func_file, pos, SEEK_SET); // Go back to the character position

        fputc(ch, func_file); // Write the modified character

        fseek(func_file, pos + 1, SEEK_SET); // Move to the next character
    }
    fclose(func_file);
}