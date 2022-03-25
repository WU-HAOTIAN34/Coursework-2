#include "book_management.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>




int store_books(FILE* file) {
	int len;
	Book* newBook = library->list;
	fwrite(&(library->length), sizeof(int), 1, file);
	while (newBook != NULL) {
		fwrite(&(newBook->id), sizeof(unsigned int), 1, file);
		len = strlen(newBook->title);
		fwrite(&(len), sizeof(int), 1, file);
		fwrite(newBook->title, sizeof(char), len, file);
		fwrite(&(len), sizeof(int), 1, file);
		len = strlen(newBook->authors);
		fwrite(newBook->authors, sizeof(char), len, file);
		fwrite(newBook->year, sizeof(unsigned int), 2, file);
		newBook = newBook->next;
	}
}


int load_books(FILE* file) {
	int len, i;
	Book* newBook;
	library = (BookList*)malloc(sizeof(BookList));
	fread(&(library->length), sizeof(int), 1, file);
	library->list = (Book*)malloc(sizeof(Book));
	newBook = library->list;
	for (i = 0; i < library->length; i++) {
		fread(&(newBook->id), sizeof(unsigned int), 1, file);
		fread(&(len), sizeof(int), 1, file);
		newBook->title = (char*)malloc(sizeof(char) * (len + 1));
		memset(newBook->title, '\0', len + 1);
		fread(newBook->title, sizeof(char), len, file);
		fread(&(len), sizeof(int), 1, file);
		newBook->authors = (char*)malloc(sizeof(char) * (len + 1));
		memset(newBook->authors, '\0', len + 1);
		fread(newBook->authors, sizeof(char), len, file);
		fread(&(newBook->year), sizeof(unsigned int), 2, file);
	}
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

