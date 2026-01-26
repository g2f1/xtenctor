#ifndef EXTENCTOR_H_INCLUDED
#define EXTENCTOR_H_INCLUDED

#include <stdio.h>   // FILE
#include <stdbool.h> // bool
// Functions declaration
void bytes_to_hex(char *bytes, int len, char *hex); // convert from byte to hex, used to convert the extracted header from byte to hex
void print(char *smtg, int flag, FILE *F); // writes to a file or simply to std output if the output mode is set or not
void lower(char *p); // convert text to lower case for comparison. I steal this beautiful peace of code from stack overflow
void print_help(void); // print the help message for the tool
char *get_filename_ext(char *filename); // extract file's extension
char path_type(char *path); // returns a char indicating the type of the path provided in input(directory, file, other)
char *print_time_now(); // return a buffer containing the current time
int get_file_header(char *filename,char *buf,int len, int offset); // this fuction extracts the file header
bool is_empty(FILE *F); // verify if the file is empty
int check_file_magic(char *path, magic_db ext_db[], bool flag, FILE *F,int count); /* the most important function. It checks the extracted header from the file headers from the database
corresponding to the file initial extention. And it write the result in a given file or simply in the standard output*/
void print_magic_db(const magic_db *db, int count); // just printing the content of the database
int load_file(magic_db **ext_db_temp,char *fn,int *count); // load content of the database from the input file
void print_desc();
void print_version();
int dump_default_db(magic_db *db,char *file_name);


#endif // EXTENCTOR_H_INCLUDED
