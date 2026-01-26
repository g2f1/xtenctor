#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "magic_types.h"
struct stat path_stat; // structre to store the ouput of stat

//This function is used to extract the extension for the file name
char *get_filename_ext(char *filename){
return strrchr(filename, '.');
}

char path_type(char *path){

if (stat(path, &path_stat) != 0) {
        return 'e';
    }

    if (S_ISREG(path_stat.st_mode)) {
        return 'f';
    } else if (S_ISDIR(path_stat.st_mode)) {
        return 'd';
    }
    return 'o';
}



//Extract the file's header
int get_file_header(char *filename,char *buf,int len, int offset)
{
    FILE *f = fopen(filename, "rb");
    if (!f) return 0;
    fseek(f,offset,SEEK_SET);
    int r = fread(buf, 1, len, f);
    fclose(f);

    return r == len;
}

//verify if the file is empty
bool is_empty(FILE *F){
fseek(F,0,SEEK_END);
return (ftell(F) == 0) ? 1 : 0;
}

int load_file(magic_db **ext_db_temp,char *fn, int *count){
    FILE *fptr = fopen(fn, "r");
    if (!fptr) {
        return 1;
    }

    char line[20];

    // --- Step 1: read the number of extensions ---
    if (!fgets(line, sizeof(line), fptr)) {
        return 1;
    }
    int total_extensions = atoi(line);
    magic_db *db = malloc(total_extensions*sizeof(magic_db));
    int ext_count = 0;
    magic_db *current_ext = NULL;

    // --- Step 2: read the rest of the file ---
    while (fgets(line, sizeof(line), fptr)) {
        // trim newline
        line[strcspn(line, "\r\n")] = 0;

        if (line[0] == '-') {
            // new extension
            if (ext_count >= total_extensions) {
                break;
            }
            current_ext = &db[ext_count++];
            strncpy(current_ext->ext, line + 1, sizeof(current_ext->ext) - 1);
            current_ext->ext[sizeof(current_ext->ext) - 1] = '\0';
            current_ext->nb_header = 0;
        } else if (current_ext != NULL) {
            // parse header line
            if (current_ext->nb_header >= MAX_HEADER) {
                continue;
            }
            header *h = &current_ext->h[current_ext->nb_header];
            if (sscanf(line, "%19s %d %d", h->magic, &h->offset, &h->magic_len) == 3) {
                current_ext->nb_header++;
            } else {
                return 1;
            }
        }
    }
    *count=ext_count;
    *ext_db_temp=db;
    fclose(fptr);
    return 0;
    }


int dump_default_db(magic_db *db,char *file_name){
FILE *F = fopen(file_name,"a");
if (!F){
printf("Error : Can't open %s\n",file_name);
return 2;
}
else if(!is_empty(F)){
printf("Error : File is not empty, please provide an empty file\n");
return 2;
}

else{
fprintf(F,"%d\n",46);
for(int i=0; i<46; i++){
fprintf(F,"-%s\n",db[i].ext);
for (int j=0; j<db[i].nb_header; j++){
fprintf(F,"%s %d %d\n",db[i].h[j].magic,db[i].h[j].offset,db[i].h[j].magic_len);
}
}
}
fclose(F);
return 0;
}
