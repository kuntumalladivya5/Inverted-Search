#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"

static int hash_index(const char *word)
{
    unsigned char c = (unsigned char)tolower((unsigned char)word[0]);
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    return 26;
}

static void normalize(char *word)
{
    size_t i;
    for (i = 0; word[i]; i++)
        word[i] = (char)tolower((unsigned char)word[i]);
}

static mainnode_t *find_main(int index, const char *word)
{
    mainnode_t *p = hash_table[index].link;
    while (p) {
        if (strcmp(p->word, word) == 0)
            return p;
        p = p->link;
    }
    return NULL;
}

static int insert_word(const char *word, const char *filename)
{
    int index = hash_index(word);
    mainnode_t *main = find_main(index, word);
    subnode_t *sub;

    if (!main) {
        main = calloc(1, sizeof(*main));
        if (!main) return -1;
        strncpy(main->word, word, WORD_SIZE - 1);
        main->link = hash_table[index].link;
        hash_table[index].link = main;
    }

    for (sub = main->sublink; sub; sub = sub->link) {
        if (strcmp(sub->f_name, filename) == 0) {
            sub->word_count++;
            return 0;
        }
    }

    sub = calloc(1, sizeof(*sub));
    if (!sub) return -1;
    strncpy(sub->f_name, filename, FNAME_SIZE - 1);
    sub->word_count = 1;
    sub->link = main->sublink;
    main->sublink = sub;
    main->file_count++;
    return 0;
}

int add_file_to_list(filenames_t **head, const char *filename)
{
    filenames_t *node, *p;
    if (!head || !filename) return -1;

    for (p = *head; p; p = p->link)
        if (strcmp(p->filename, filename) == 0)
            return 0;

    node = calloc(1, sizeof(*node));
    if (!node) return -1;
    strncpy(node->filename, filename, FNAME_SIZE - 1);

    if (!*head) {
        *head = node;
    } else {
        p = *head;
        while (p->link) p = p->link;
        p->link = node;
    }
    return 0;
}

static int index_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    char word[WORD_SIZE];
    int result = 0;

    if (!fp) {
        perror(filename);
        return -1;
    }

    while (fscanf(fp, "%49s", word) == 1) {
        size_t n = strlen(word);
        while (n > 0 && ispunct((unsigned char)word[n - 1]))
            word[--n] = '\0';
        {
            size_t start = 0;
            while (word[start] && ispunct((unsigned char)word[start]))
                start++;
            if (start > 0)
                memmove(word, word + start, strlen(word + start) + 1);
        }
        if (!word[0]) continue;
        normalize(word);
        if (insert_word(word, filename) != 0) {
            result = -1;
            break;
        }
    }

    fclose(fp);
    return result;
}

int create_database(filenames_t *head)
{
    filenames_t *p;
    free_database();
    for (p = head; p; p = p->link) {
        if (index_file(p->filename) != 0)
            return -1;
    }
    return 0;
}

int update_database(const char *filename)
{
    return index_file(filename);
}
