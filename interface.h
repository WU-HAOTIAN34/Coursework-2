#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "book_management.h"


int covertInt(char* str);

int ifStrValid(char* str, int len);

int loadUser(FILE* file);

int storeUser(FILE* file);

void printBook(BookList* book);

void interface();

#endif