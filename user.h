#ifndef __USER_H__
#define __USER_H__


#include "book_management.h"



Book* findBook(Book* newBook, int id);
void userModel(user* signUser);
void freeSpace(Book* book);


#endif
