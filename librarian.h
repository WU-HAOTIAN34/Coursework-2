#ifndef __LIBRARIAN_H__
#define __LIBRARIAN_H__
//  free a Book struct author title and itself
void freeNode(Book* book);

// free a list of book struct
void freeList(Book* list);

// free a list of  user struct
void freeUser(userList* list);

// the interface of seach book
void searchModel();

// the interface after librarian login
void librarianModel();

//chech if the book ID is valid
int checkID(char* id);
#endif