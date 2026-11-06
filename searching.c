#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "types.h"

int search_database(const char *word)
{
    int index;
    char target[WORD_SIZE];
    mainnode_t *m;
    subnode_t *s;

    if (!word || !word[0]) return -1;
    strncpy(target, word, WORD_SIZE - 1);
    target[WORD_SIZE - 1] = '\0';

    for (int i = 0; target[i]; i++)
        target[i] = (char)tolower((unsigned char)target[i]);

    index = (target[0] >= 'a' && target[0] <= 'z') ? target[0] - 'a' : 26;
    for (m = hash_table[index].link; m; m = m->link) {
        if (strcmp(m->word, target) == 0) {
            printf("\nWord found: %s\n", m->word);
            printf("Files containing it:\n");
            for (s = m->sublink; s; s = s->link)
                printf("  %s -> %d occurrence(s)\n", s->f_name, s->word_count);
            return 0;
        }
    }
    return -1;
}
