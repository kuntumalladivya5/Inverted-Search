/*Name : K.Divya
DATE: 04/11/2026
Description : The Inverted Search Project is a file-based search engine developed using the C programming language. 
It uses an inverted index to store words and their corresponding file names, allowing users to search for a specific word across multiple files efficiently.

The project uses data structures such as hash tables, linked lists, and file handling to perform operations like creating a database, searching for words, updating the database, and displaying the search results.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

hashtable_t hash_table[HASH_SIZE];

static void print_menu(void)
{
    printf("\n========== INVERTED SEARCH MENU ==========\n");
    printf("1. Create database\n");
    printf("2. Display database\n");
    printf("3. Update database (add file)\n");
    printf("4. Search database\n");
    printf("5. Save database (backup)\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main(int argc, char *argv[])
{
    filenames_t *file_list = NULL;
    int choice, i, created = 0;
    char filename[FNAME_SIZE], word[WORD_SIZE];

    if (argc < 2) {
        printf("Usage: %s file1.txt [file2.txt ...]\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if (add_file_to_list(&file_list, argv[i]) != 0) {
            fprintf(stderr, "Could not add %s to file list.\n", argv[i]);
            return 1;
        }
    }

    printf("\nFiles passed through command line:\n");
    {
        filenames_t *p = file_list;
        while (p) {
            printf(" -> %s\n", p->filename);
            p = p->link;
        }
    }

    for (;;) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
        case 1:
            if (create_database(file_list) == 0) {
                created = 1;
                printf("Database created successfully.\n");
            } else {
                printf("Database creation failed. Check filenames.\n");
            }
            break;
        case 2:
            if (!created)
                printf("Create the database first (option 1).\n");
            else
                display_database();
            break;
        case 3:
            printf("Enter the filename to add: ");
            if (scanf("%255s", filename) != 1)
                break;
            if (update_database(filename) == 0) {
                created = 1;
                printf("File added to database successfully.\n");
            } else {
                printf("Could not add file. Check filename.\n");
            }
            break;
        case 4:
            printf("Enter word to search: ");
            if (scanf("%49s", word) != 1)
                break;
            if (!created)
                printf("Create the database first (option 1).\n");
            else if (search_database(word) != 0)
                printf("Word not found.\n");
            break;
        case 5:
            printf("Enter backup filename: ");
            if (scanf("%255s", filename) != 1)
                break;
            if (save_database(filename) == 0)
                printf("Database saved to %s\n", filename);
            else
                printf("Could not save database.\n");
            break;
        case 6:
            free_database();
            while (file_list) {
                filenames_t *tmp = file_list;
                file_list = file_list->link;
                free(tmp);
            }
            printf("Exiting.\n");
            return 0;
        default:
            printf("Invalid choice. Please enter 1-6.\n");
        }
    }

    free_database();
    while (file_list) {
        filenames_t *tmp = file_list;
        file_list = file_list->link;
        free(tmp);
    }
    return 0;
}
