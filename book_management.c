#include "book_management.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>




int store_books(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	library = (Book*)malloc(sizeof(Book));
}


int load_books(FILE* file) {
	
}



int add_book(Book book) {
	Book* list = &library;
	Book* newBook = &book;
	int ID = 0;
	do {
		list = list->next;
		ID++;
	} while (list->next != NULL);
	list->next = newBook;
	newBook->id = ID;
	newBook->next = NULL;
	return 1;
}



int remove_book(Book book) {
	int ID = 0;
	Book* list = &library;
	do {

	} while (list->next->next != NULL);
	return 0;
}


BookList find_book_by_title(const char* title) {
	Book* query = library->next;
	Book* newBook;
	int num = 0;
	char bookTitle[30];
	printf("Please enter the title you want to find: ");
	scanf("%s", bookTitle);
	BookList* res = (BookList*)malloc(sizeof(BookList));
	
	if (library->next == NULL) {
		res->list = NULL;
		res->length = 0;
	}
	else {
		
		do {
			query = query->next;
			if (strcmp(query->title, title)) {
				num++;
				newBook = (Book*)malloc(sizeof(Book));
				res->list = newBook;
				newBook->id = num;
				newBook->copies = query->copies;
				newBook->year = query->year;
				strcpy(newBook->authors, query->authors);
				strcpy(newBook->title, query->title);
				newBook->next = NULL;

			}
		} while (query->next != NULL);
	}
	return *res;
}


BookList find_book_by_author(const char* author) {
	Book* query = library->next;
	Book* newBook;
	int num = 0;
	char bookTitle[30];
	printf("Please enter the title you want to find: ");
	scanf("%s", bookTitle);
	BookList* res = (BookList*)malloc(sizeof(BookList));

	if (library->next == NULL) {
		res->list = NULL;
		res->length = 0;
	}
	else {

		do {
			query = query->next;
			if (strcmp(query->title, title)) {
				num++;
				newBook = (Book*)malloc(sizeof(Book));
				res->list = newBook;
				newBook->id = num;
				newBook->copies = query->copies;
				newBook->year = query->year;
				strcpy(newBook->authors, query->authors);
				strcpy(newBook->title, query->title);
				newBook->next = NULL;

			}
		} while (query->next != NULL);
	}
	return *res;

}



BookList find_book_by_year(unsigned int year) {
	Book* query = library->next;
	Book* newBook;
	int num = 0;
	char bookTitle[30];
	printf("Please enter the title you want to find: ");
	scanf("%s", bookTitle);
	BookList* res = (BookList*)malloc(sizeof(BookList));

	if (library->next == NULL) {
		res->list = NULL;
		res->length = 0;
	}
	else {

		do {
			query = query->next;
			if (strcmp(query->title, title)) {
				num++;
				newBook = (Book*)malloc(sizeof(Book));
				res->list = newBook;
				newBook->id = num;
				newBook->copies = query->copies;
				newBook->year = query->year;
				strcpy(newBook->authors, query->authors);
				strcpy(newBook->title, query->title);
				newBook->next = NULL;

			}
		} while (query->next != NULL);
	}
	return *res;

}

