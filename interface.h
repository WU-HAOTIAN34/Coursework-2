#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "book_management.h"

// covert a string which contains some character number into int number
int covertInt(char* str);

//judge if the string is valid
//a valid string consists of letters. Don't have contiguous Spaces, 
//don't begin or end with space 
int ifStrValid(char* str, int len);

// load the imformation of users 
// return 0 if the file has been modified or corrupted
int loadUser(FILE* file);

// store the imformation of user to the file
int storeUser(FILE* file);

// print the book list 
void printBook(BookList* book);

// the register a user 
int registerModel();

// used for user login
int signModel();

// print the interface of the program
void interface();

#endif