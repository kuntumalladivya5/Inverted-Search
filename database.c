#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void display_database(void)
{
    int i, found = 0;
    printf("\n%-8s %-20s %-10s %-20s\n", "Index", "Word", "File count", "Filename : Count");
    printf("---------------------------------------------------------------------\n");

    for (i = 0; i < HASH_SIZE; i++) {
        mainnode_t *m;
        for (m = hash_table[i].link; m; m = m->link) {
            subnode_t *s;
            found = 1;
            printf("%-8d %-20s %-10d ", i, m->word, m->file_count);
            for (s = m->sublink; s; s = s->link)
                printf("%s : %d  ", s->f_name, s->word_count);
            printf("\n");
        }
    }
    if (!found)
        printf("Database is empty.\n");
}

int save_database(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int i;
    if (!fp) {
        perror(filename);
        return -1;
    }

    for (i = 0; i < HASH_SIZE; i++) {
        mainnode_t *m;
        for (m = hash_table[i].link; m; m = m->link) {
            subnode_t *s;
            fprintf(fp, "#%s", m->word);
            for (s = m->sublink; s; s = s->link)
                fprintf(fp, ";%s:%d", s->f_name, s->word_count);
            fputc('\n', fp);
        }
    }

    fclose(fp);
    return 0;
}

void free_database(void)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        mainnode_t *m = hash_table[i].link;
        while (m) {
            mainnode_t *nextm = m->link;
            subnode_t *s = m->sublink;
            while (s) {
                subnode_t *nexts = s->link;
                free(s);
                s = nexts;
            }
            free(m);
            m = nextm;
        }
        hash_table[i].link = NULL;
        hash_table[i].index = i;
    }
}
