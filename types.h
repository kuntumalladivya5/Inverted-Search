#ifndef TYPES_H
#define TYPES_H

#define HASH_SIZE 27
#define WORD_SIZE 50
#define FNAME_SIZE 256
#define DB_FILE "database.txt"

typedef struct subnode {
    int word_count;
    char f_name[FNAME_SIZE];
    struct subnode *link;
} subnode_t;

typedef struct mainnode {
    int file_count;
    char word[WORD_SIZE];
    struct mainnode *link;
    subnode_t *sublink;
} mainnode_t;

typedef struct hashtable {
    int index;
    mainnode_t *link;
} hashtable_t;

typedef struct file {
    char filename[FNAME_SIZE];
    struct file *link;
} filenames_t;

extern hashtable_t hash_table[HASH_SIZE];

int add_file_to_list(filenames_t **head, const char *filename);
int create_database(filenames_t *head);
int update_database(const char *filename);
void display_database(void);
int search_database(const char *word);
int save_database(const char *filename);
void free_database(void);

#endif
