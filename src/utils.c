#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>
#include "magic_types.h"
//Convert byte to hex
void bytes_to_hex(char *bytes, int len, char *hex) {
    static const char hexmap[] = "0123456789ABCDEF";

    for (int i = 0; i < len; i++) {
        hex[i*2]     = hexmap[(bytes[i] >> 4) & 0xF];
        hex[i*2 + 1] = hexmap[bytes[i] & 0xF];
    }
    hex[len * 2] = '\0';
}

//This function is a flexible version of the standard printf. It write content either to a file or stdout
void print(char *smtg, int flag, FILE *F){
if(!flag){
printf("%s",smtg);
}
else{
fprintf(F,"%s",smtg);
}
}

//this function is used to lower chars
void lower(char *p)
{
for(;*p;p++){
*p=tolower(*p);
}
}

//Just print current time in formatted way
char *print_time_now(){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    static char buffer[21];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S\n", t);
    return buffer;
}

//Print the content of the database to the stdout
void print_magic_db(magic_db *db, int count)
{
    printf("Magic Database (%d entries):\n", count);
    printf("-----------------------------------------------------------\n");
    int i,j;
    for (i = 0; i < count; i++) {
    printf("[%d] Extension (%d entries): %-5s\n",i+1,db[i].nb_header,db[i].ext);

        for (j=0; j<db[i].nb_header ;j++){
            printf("    - Magic: %-12s | Length: %d bytes | offset :%d bytes\n",db[i].h[j].magic,db[i].h[j].magic_len,db[i].h[j].offset);
        }
        }

    printf("-----------------------------------------------------------\n");
}
