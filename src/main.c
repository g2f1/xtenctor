#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include "magic_types.h"
#include "xtenctor.h"
#define DEFAULT_DB_COUNT 46



//Global variable
magic_db ext_db_defaut[] = {

    /* Executables & binaries */
    {"exe",   { {"4D5A", 0, 2} }, 1},
    {"dll",   { {"4D5A", 0, 2} }, 1},
    {"elf",   { {"7F454C46", 0, 4} }, 1},
    {"class", { {"CAFEBABE", 0, 4} }, 1},

    /* Archives */
    {"zip",   { {"504B0304", 0, 4}, {"504B0506", 0, 4} }, 2},
    {"rar",   { {"526172211A07", 0, 7}, {"526172211A0701", 0, 8} }, 2},
    {"7z",    { {"377ABCAF271C", 0, 6} }, 1},
    {"tar",   { {"7573746172", 257, 5} }, 1},
    {"gz",    { {"1F8B08", 0, 3} }, 1},
    {"bz2",   { {"425A68", 0, 3} }, 1},
    {"xz",    { {"FD377A585A", 0, 5} }, 1},

    /* Documents */
    {"pdf",   { {"25504446", 0, 4} }, 1},
    {"rtf",   { {"7B5C727466", 0, 5} }, 1},
    {"doc",   { {"D0CF11E0A1B11AE1", 0, 8} }, 1},
    {"xls",   { {"D0CF11E0A1B11AE1", 0, 8} }, 1},
    {"ppt",   { {"D0CF11E0A1B11AE1", 0, 8} }, 1},

    /* Office Open XML (ZIP-based) */
    {"docx",  { {"504B0304", 0, 4} }, 1},
    {"xlsx",  { {"504B0304", 0, 4} }, 1},
    {"pptx",  { {"504B0304", 0, 4} }, 1},

    /* Images */
    {"jpg",   { {"FFD8FFE0", 0, 4} }, 1},
    {"jpeg",   { {"FFD8FFE0", 0, 4} }, 1},
    {"png",   { {"89504E470D0A1A0A", 0, 8} }, 1},
    {"gif",   { {"474946383761", 0, 6}, {"474946383961", 0, 6} }, 2},
    {"bmp",   { {"424D", 0, 2} }, 1},
    {"tiff",  { {"49492A00", 0, 4}, {"4D4D002A", 0, 4} }, 2},
    {"ico",   { {"00000100", 0, 4} }, 1},
    {"webp",  { {"52494646", 0, 4} }, 1},

    /* Audio */
    {"mp3",   { {"494433", 0, 3}, {"FFFB", 0, 2} }, 2},
    {"wav",   { {"52494646", 0, 4} }, 1},
    {"flac",  { {"664C6143", 0, 4} }, 1},
    {"ogg",   { {"4F676753", 0, 4} }, 1},
    {"m4a",   { {"667479704D3441", 4, 7} }, 1},
    {"aac",   { {"FFF1", 0, 2}, {"FFF9", 0, 2} }, 2},

    /* Video */
    {"mp4",   { {"6674797069736F6D", 4, 8}, {"667479706D703432", 4, 8} }, 2},
    {"mkv",   { {"1A45DFA3", 0, 4} }, 1},
    {"avi",   { {"52494646", 0, 4} }, 1},
    {"mov",   { {"66747971742020", 4, 8} }, 1},
    {"webm",  { {"1A45DFA3", 0, 4} }, 1},
    {"flv",   { {"464C5601", 0, 4} }, 1},

    /* Text / scripts */
    {"html",  { {"3C68746D6C", 0, 5} }, 1},
    {"xml",   { {"3C3F786D6C", 0, 5} }, 1},
    {"json",  { {"7B", 0, 1} }, 1},
    {"sh",    { {"2321", 0, 2} }, 1},
    {"py",    { {"2321", 0, 2} }, 1},

    /* Disk / firmware */
    {"iso",   { {"4344303031", 32769, 5} }, 1},
    {"dmg",   { {"7801730D626260", 0, 7} }, 1}
};


int count=DEFAULT_DB_COUNT; // Global variable that stores the nuber of extension in the current choosen database

// Table of structre for the database
magic_db *ext_db=ext_db_defaut; // set ext_db to the default database


int main(int argc, char *argv[])
{
//Variables
    int mode_dir=0,mode_input_file=0,mode_output_file=0,mode_print=0; //vars to indicate the behaviour of the program
    int opt; //using with getopt to extract options from the command
    char *db_fn; // contains the name of the db file
    char *output_fn; // contains the name of the output file
    char *dump_file;
    char *path; // to get the the path of the file given as an input
    if(argc==1){
    print_desc();
    return 2;
    }

    while ((opt=getopt(argc,argv,":pd:hvri:o:"))!=-1){
    switch(opt)
    {
    case ':':print_desc();return 2; // In the case whrere an option is wrongly used
    case '?':printf("unknown option: %c\n", optopt);return 2; // In the case where an unknown option is detected
    case 'v':print_version();return 0; // version of the program
    case 'd':dump_file=optarg;return dump_default_db(ext_db,dump_file);
    case 'h':print_help();return 0; // help message
    case 'p':mode_print=1;break;
    case 'r':mode_dir=1;break;
    case 'i':mode_input_file=1;db_fn=optarg;break;
    case 'o':mode_output_file=1;output_fn=optarg;break;


    }
    }


    if(mode_input_file) //In case where the -i option is used. The user provide his own database
    {
       magic_db *ext_db_temp;
       int r = load_file(&ext_db_temp,db_fn,&count);
       if(r!=0)
       {
        printf("A problem occur while reaading the database file. Default db is used instead\n");
       }
       else
       {
        printf("DB is succefully loaded\n");
        ext_db=ext_db_temp;
       }
     }

    if(mode_print) // where the -p option is used
    {
    print_magic_db(ext_db,count); // print the content of the used database.
    return 0;
    }


    //Test if the option -r exists when using the -o option
    if((mode_dir==0) && (mode_output_file==1))
    {
     printf("You can't use the -o option without the -r option\n");return 2;
    }

    path=argv[optind]; // pass the name of the input file or the dir. optind is an integer generated with getopt representing the id of the input file
    char type_file=path_type(path); // to determine the type of the input file

    if(mode_dir==0)
    {
     if (type_file=='e')
     {
     printf("%s:Error while reading the file\n",path);
     return 2;
     }
     else if(type_file=='f')
     {
      printf("%s",print_time_now());
      return check_file_magic(path,ext_db,0,NULL,count);
     }
     else
     {
      printf("That's not a file\n");return 2;
     }
    }

    else
    {
     if (type_file=='e')
     {
      return 2;
     }
     else if(type_file=='d')
     {
      FILE *F=NULL;
      if(mode_output_file)
      {
       F=fopen(output_fn,"ab"); // open file for append in binary mode
       if(!F)
       {
        printf("Error while opening the output file\n");return 2;
       }
       if(!is_empty(F))
       {
        printf("Warning : File isn't empty, content will be appended to the end of the file\n");
       }
      }
    struct dirent *de;  // Pointer for directory entry
    DIR *dr = opendir(path);  // opendir() returns a pointer of DIR type.
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
     printf("A problem occurs while oppening the directory\n");
     return 2;
    }

    // for readdir()
    print(print_time_now(),mode_output_file,F);
    while ((de = readdir(dr)) != NULL)
    {
        if(de->d_type==8)// regular file
        {
         char fullpath[PATH_MAX];
         sprintf(fullpath,"%s/%s", path, de->d_name);//maybe snprintf
         check_file_magic(fullpath,ext_db,mode_output_file,F,count);
        }
    }
    if (F) fclose(F);
    closedir(dr);

    }
    else
    {
     printf("That's not a directory\n");return 2;
    }
    }
    free(ext_db);
    return 0;
}
