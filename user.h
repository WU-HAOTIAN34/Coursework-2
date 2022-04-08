#ifndef __USER_H__
#define __USER_H__
#include "book_management.h"


// find the Book whose id == target id
//if find return its address, if don't return NULL
Book* findBook(Book* newBook, int id);

//print the borrowed book in the user struct
void printUserBook(user* user);

// borrow a book from the library
int borrowBook(user* theUser);

// return a book from the user's borrowed book list
int returnBook(user* theUser);

// the interface of the user
void userModel(user* signUser);



#endif
