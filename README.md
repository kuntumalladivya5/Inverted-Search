# Inverted Search Project Description

PROJECT OVERVIEW:

The Inverted Search project is designed to create an efficient search system that indexes words from multiple text files. It uses an inverted index data structure to store words along with the names of files in which they appear and the frequency of their occurrence.

This project helps users search for specific words across multiple files quickly without scanning each file repeatedly.

OBJECTIVE:
The main objective of this project is to implement an efficient file-searching mechanism using data structures such as hash tables and linked lists.

KEY FEATURES:
- File Validation: Validates input files and checks whether they are accessible.
- Database Creation: Creates an inverted index database from multiple text files.
- Word Indexing: Stores unique words and their corresponding file details.
- Search Operation: Searches for a specific word and displays the files in which it occurs.
- Update Database: Updates the index when new files are added.
- Save and Display: Saves the indexed database to a file and displays the stored information.
Technologies Used
- Programming Language: C
- Data Structures: Hash Table, Singly Linked List
- File Handling: File I/O Operations
- Concepts: Dynamic Memory Allocation, String Manipulation, Pointers
  
WORKING PRINCIPLE:
The project follows these steps:
1. Read multiple text files.
2. Extract words from each file.
3. Store each unique word in a hash table.
4. Maintain a linked list of file names and word frequencies.
5. Allow users to search for words efficiently.
6. Display the search results with file names and occurrence counts.
