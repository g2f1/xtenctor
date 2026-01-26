#ifndef MAGIC_TYPES_H_INCLUDED
#define MAX_HEADER 10
#define MAGIC_TYPES_H_INCLUDED
typedef struct {
char magic[20];
int offset;
int magic_len;
}header;

typedef struct {
char ext[8];
header h[MAX_HEADER];
int nb_header;
} magic_db; // structre for the database content

#endif // MAGIC_TYPES_H_INCLUDED
