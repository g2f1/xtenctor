#include "magic_types.h"
#include <stdbool.h>
#include <stdio.h>
#include "xtenctor.h"
#include <string.h>
int check_file_magic(char *path, magic_db ext_db[], bool flag,FILE *F,int count) {
    int k = -1;
    char buf[50];
    /* 1. Get extension */
    char *ext = get_filename_ext(path);
    if (!ext || *(ext + 1) == '\0') {
        sprintf(buf,"%s: No extension\n",path);
        print(buf,flag,F);
        return 2;
    }
    ext++;  // skip '.'

    /* 2. Copy & lowercase extension */
    char ext_copy[8];
    strncpy(ext_copy, ext, sizeof(ext_copy) - 1);
    ext_copy[sizeof(ext_copy) - 1] = '\0';
    lower(ext_copy);

    /* 3. Find extension in database */
    for (int i = 0; i < count; i++) {
        if (strcmp(ext_copy, ext_db[i].ext) == 0) {
            k = i;
            break;
        }
    }
    if (k == -1) {
        sprintf(buf,"%s: Unknown extension (%s)\n",path,ext_copy);
        print(buf,flag,F);
        return 2;
    }



    /* 4. Read file header */
    for(int phi=0; phi<ext_db[k].nb_header; phi++){

    int ext_len = ext_db[k].h[phi].magic_len;
    int ext_off = ext_db[k].h[phi].offset;
    char buf1[ext_len];

    if (!get_file_header(path, buf1, ext_len, ext_off)) {
        perror(path);
        return -1;
    }

    /* 5. Convert header to hex */
    char hex[ext_len * 2 + 1];
    bytes_to_hex(buf1, ext_len, hex);
    /* 6. Compare magic */
    if (strcmp(ext_db[k].h[phi].magic, hex) == 0) {
        sprintf(buf,"%s: OK (%s)\n",path,ext_copy);
        print(buf,flag,F);
        return 0;

    }
    }
    sprintf(buf,"%s: NOT OK (%s)\n",path,ext_copy);
    print(buf,flag,F);
    return 1;
}
