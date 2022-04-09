#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "book_management.h"
#include "interface.h"
#include "librarian.h"


// find the Book whose id == target id
//if find return its address, if don't return NULL
Book* findBook(Book* newBook, int id) {
	Book* res = NULL;
	while (newBook != NULL) {
		if (newBook->id == id) {
			res = newBook;
			break;
		}
		newBook = newBook->next;
	}
	return res;
}


//print the borrowed book in the user struct
void printUserBook(user* user) {
	int i;
	Book* newBook = user->broBook;
	printf("\nID     Title                         Author               Year\n\n");
	for (i = 0; i < user->bookNum; i++) {
		printf("%-7d%-30s%-21s%-14d\n", newBook->id, newBook->title,
			newBook->authors, newBook->year);
		newBook = newBook->next;
	}
}


// borrow a book from the library
int borrowBook(user* theUser) {
	int option;
	char enter[40];		// recive the entering 
	Book* query;		// match book in the library
	Book* newBook;		// new book node in user
	memset(enter, '\0', 40);
	printBook(library);
	printf("\nPlesse enter the ID you want to borrow: ");
	scanf("%[^\n]s", enter);
	getchar();
	if (checkID(enter)) {
		printf("\033[47;31mInvalid Id, fail to brorrow.\033[0m\n");
		printf("Expected ID: a number less than 5 digits. Don't start with 0,\ndon't start or end with a space.\n");
		return 0;
	}
	option = covertInt(enter);
	// judge if have borrowed the book
	if (findBook(theUser->broBook, option) != NULL) {
		printf("\033[47;31mYou have borrowed this book.\033[0m\n");
		return 0;
	}
	// judge the book if exists and if the copy == 0 then obtain its address
	query = findBook(library->list, option);
	if (query == NULL) {
		printf("\033[47;31mThis book does not exist.\033[0m\n");
		return 0;
	}
	else {
		if (query->copies == 0) {
			printf("\033[47;31mThis book has been checked out.\033[0m");
			return 0;
		}
		// copy the book to the user's borrowed list
		query->copies -= 1;
		if (theUser->bookNum == 0) {
			theUser->bookNum += 1;
			theUser->broBook = (Book*)malloc(sizeof(Book));
			copyNode(theUser->broBook, query);
			printf("\nBorrow book successfully!\n");
			return 1;
		}
		else {
			theUser->bookNum += 1;
			newBook = theUser->broBook;
			while (newBook->next != NULL) {
				newBook = newBook->next;
			}
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
			copyNode(newBook, query);
			printf("\nBorrow book successfully!\n");
			return 1;
		}
	}
}


// return a book from the user's borrowed book list
int returnBook(user* theUser) {
	char id[100];
	int option;
	Book* temp;
	Book* query = library->list;
	Book* newBook = theUser->broBook;
	memset(id, '\0', 100);
	printf("\nPlease enter the ID you want to return: ");
	scanf("%[^\n]s", id);
	getchar();
	if (checkID(id)) {
		printf("\033[47;31mInvalid Id, fail to return.\033[0m\n");
		printf("Expected ID: a number less than 5 digits. Don't start with 0,\ndon't start or end with a space.\n");
		return 0;
	}
	else {
		option = covertInt(id);
	}
	// judge if is the first node
	if (newBook->next == NULL) {
		if (newBook->id == option) {
			theUser->bookNum -= 1;
			theUser->broBook = NULL;
			freeNode(newBook);
			printf("\nReturn successfully!\n");
			while (query != NULL) {
				if (query->id == option) {
					query->copies += 1;
				}
				query = query->next;
			}
			return 1;
		}
		else {
			printf("\033[47;31mThis book doesn't exist.\033[0m\n");
			return 0;
		}
	}
	else {
		if (newBook->id == option) {
			theUser->bookNum -= 1;
			theUser->broBook = newBook->next;
			freeNode(newBook);
			printf("\nReturn successfully!\n");
			while (query != NULL) {
				if (query->id == option) {
					query->copies += 1;
				}
				query = query->next;
			}
			return 1;
		}
		// judge if is the last node
		while (newBook->next != NULL) {
			if (newBook->next->id == option) {
				if (newBook->next->next == NULL) {
					theUser->bookNum -= 1;
					freeNode(newBook->next);

					newBook->next = NULL;
					printf("\nReturn successfully!\n");
					while (query != NULL) {
						if (query->id == option) {
							query->copies += 1;
						}
						query = query->next;
					}
					return 1;
				}
				else {
					// among the list
					theUser->bookNum -= 1;
					temp = newBook->next;
					newBook->next = newBook->next->next;
					free(temp);
					printf("\nReturn successfully!\n");
					while (query != NULL) {
						if (query->id == option) {
							query->copies += 1;
						}
						query = query->next;
					}
					return 1;
				}

			}
			newBook = newBook->next;
		}
		printf("\033[47;31mThis book doesn't exist.\033[0m\n");
		return 0;
	}

}



// the interface of the user
void userModel(user* signUser) {
	BookList* book = (BookList*)malloc(sizeof(BookList));
	char enter[100];
	int option = 0;
	memset(enter, '\0', 100);
	while (option != 6) {
		printf("\nPlease choose an option: \n\n1. Borrow book\n2. Return book\n");
		printf("3. Search for books\n4. Display all books\n5. Show my books\n6. Quit\nOption: ");
		scanf("%[^\n]s", enter);
		getchar();
		option = (int)enter[0];
		if (strlen(enter) > 1 || option <= 48 || option >= 55) {
			printf("\033[47;31mSorry, the option you entered was invalid, please try again.\033[0m\n");
		}
		else {
			option -= 48;
			switch (option)
			{
			case 1:
				borrowBook(signUser);
				break;
			case 2:
				if (signUser->bookNum == 0) {
					printf("\nYou haven't borrowed any books yet.\n");
				}
				else {
					printUserBook(signUser);
					returnBook(signUser);
				}
				break;
				break;
			case 3:
				searchModel();
				break;
			case 4:
				printBook(library);
				break;
			case 5:
				if (signUser->bookNum == 0) {
					printf("\nYou haven't borrowed any books yet.\n");
				}
				else {
					book->length = signUser->bookNum;
					book->list = signUser->broBook;
					printUserBook(signUser);
				}
				break;
			case 6:
			default:
				break;
			}
		}
	}
	return;
}
