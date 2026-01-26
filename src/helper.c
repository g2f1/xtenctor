#include <stdio.h>

//this function just print the help message
void print_desc(){
printf("Usage: xtenctor [OPTION]... FILE|DIR\n");
printf("Try 'xtenctor -h' for more information.\n");
}

void print_version(){
printf("xtenctor 1.0.0\n");
}

void print_help(void)
{
    printf(
        "xtenctor - File type detector using magic header\n\n"
        "Usage:\n"
        "  extenctor [OPTIONS] <file>\n"
        "  extenctor -r [OPTIONS] <directory>\n\n"
        "Options:\n"
        "  -h              Show this help message and exit\n"
        "  -v              Show program version and exit\n"
        "  -p              Print the current magic database and exit\n"
        "  -r              Enable directory mode (required for -o)\n"
        "  -i <db_file>    Load a custom magic database file\n"
        "  -o <out_file>   Write output to file (only valid with -r)\n\n"
        "  -d <out_file>   Write the content of the default database to the out_file using the format describing"

        "Examples:\n"
        "  extenctor sample.png                   Analyze a single file\n"
        "  extenctor -i mydb.txt -p               Print the loaded custom database\n"
        "  extenctor -r /path/to/dir              Scan all files in a directory\n"
        "  extenctor -r -o results.txt /dir       Scan directory and append results to file\n"
        "  extenctor -r -i custom_db.txt -o out.txt /dir   Use custom DB and save output\n\n"

        "Exit status:\n"
        "0        if everything is OK\n"
        "1        if the file signature don't match the extension\n"
        "2        if a problem\n\n"

        "Database file format:\n"
        "Rather then using the default database hardecoded in the source code,\n"
        "The user can use his own database by entering a file using the -i option\n\n"
        "The file follows this structure :\n\n"
         "<NUMBER_OF_EXTENSIONS>\n"
         "-<EXTENSION_1>\n"
         "<MAGIC_HEX> <OFFSET> <LENGTH>\n"
         "<MAGIC_HEX> <OFFSET> <LENGTH>\n"
         "...\n"
         "-<EXTENSION_2>\n"
         "<MAGIC_HEX> <OFFSET> <LENGTH>\n"
         "...\n"
         "-<EXTENSION_N>\n"
         "<MAGIC_HEX> <OFFSET> <LENGTH>\n\n"
    );
}

