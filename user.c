#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "book_management.h"
#include "interface.h"


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



int borrowBook(user* theUser) {
	int option,len;
	char enter[40];
	Book* query;
	Book* newBook;
	memset(enter, '\0', 40);
	printf("Plesse enter your option: ");
	scanf("%s", enter);
	option = (int)enter[0];
	if (strlen(enter) > 1 || (int)enter[0] < 49 || (int)enter[0]>57) {
		printf("Invalid entering.\n");
		return 0;
	}
	if (findBook(theUser->broBook, option) != NULL) {
		printf("You have borrowed this book.\n");
		return 0;
	}
	query = findBook(library->list, option);
	if ( query == NULL) {
		printf("The book does not exist.\n");
		return 0;
	}
	else {
		query->copies -= 1;
		if (theUser->bookNum == 0) {
			theUser->bookNum += 1;
			theUser->broBook = (Book*)malloc(sizeof(Book));
			theUser->broBook->id = query->id;
			strcpy(theUser->broBook->title, query->title);
			strcpy(theUser->broBook->authors, query->authors);
			theUser->broBook->year = query->year;
			theUser->broBook->copies = query->copies;
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
			newBook->id = query->id;
			newBook->year = query->year;
			newBook->copies = query->copies;
			len = strlen(query->title);
			newBook->title = (char*)malloc(sizeof(len + 1));
			memset(newBook->title, '\0', len + 1);
			strcpy(newBook->title, query->title);
			len = strlen(query->authors);
			newBook->authors = (char*)malloc(sizeof(len + 1));
			memset(newBook->authors, '\0', len + 1);
			strcpy(newBook->authors, query->authors);
			newBook->next = NULL;
			return 1;
		}
	}
}


void returnBook(user* theUser) {
	char id[10];

}