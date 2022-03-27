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



void borrowBook(user* theUser) {
	int option;
	char enter[40];
	Book* query;
	memset(enter, '\0', 40);
	printf("Plesse enter your option: ");
	scanf("%s", enter);
	option = (int)enter[0];
	if (strlen(enter) > 1 || (int)enter[0] < 49 || (int)enter[0]>57) {
		printf("Invalid entering.\n");
		return;
	}
	if (findBook(theUser->broBook, option) != NULL) {
		printf("You have borrowed this book.\n");
	}
	query = findBook(library->list, option);
	if ( query == NULL) {
		printf("The book does not exist.\n");
	}
	else {
		query->copies -= 1;

	}
}


void returnBook() {

}