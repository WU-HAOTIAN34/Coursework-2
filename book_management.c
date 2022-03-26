#define _CRT_SECURE_NO_WARNINGS
#include "book_management.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>




int store_books(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	int len;
	Book* newBook = library->list;
	fwrite(&library->length, sizeof(unsigned int), 1, file);   // write the book number
	while (newBook != NULL) {
		// write id
		fwrite(&(newBook->id), sizeof(unsigned int), 1, file);
		// write title
		len = strlen(newBook->title);  // obtain the length of title
		// write the length because loading the title need to know the length of the string		
		fwrite(&(len), sizeof(int), 1, file);   
		fwrite(newBook->title, sizeof(char), len, file);  // write title
		//   write author
		len = strlen(newBook->authors);
		fwrite(&(len), sizeof(int), 1, file);
		fwrite(newBook->authors, sizeof(char), len, file);
		// year and copies
		fwrite(&(newBook->year), sizeof(unsigned int), 2, file);
		newBook = newBook->next;
	}
	return 1;
}



int load_books(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	int len, i;
	Book* newBook;
	fread(&(library->length), sizeof(unsigned int), 1, file);
	library->list = (Book*)malloc(sizeof(Book));
	newBook = library->list;
	for (i = 0; i < library->length; i++) {
		//load book id
		fread(&(newBook->id), sizeof(unsigned int), 1, file);
		// load title
		fread(&(len), sizeof(int), 1, file);        // obtain the length of title
		newBook->title = (char*)malloc(sizeof(char) * (len + 1)); //open space +1 because need an end character \0
		memset(newBook->title, '\0', len + 1);        //   initialize by '\0'
		fread(newBook->title, sizeof(char), len, file);   //load
		//   load author
		fread(&(len), sizeof(int), 1, file);
		newBook->authors = (char*)malloc(sizeof(char) * (len + 1));
		memset(newBook->authors, '\0', len + 1);
		fread(newBook->authors, sizeof(char), len, file);
		// year and copies
		fread(&(newBook->year), sizeof(unsigned int), 2, file);
		       // judge if is the last one 
		if (i == library->length - 1) {
			newBook->next = NULL;
			break;
		}
		else {
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
		}
	}
	return 1;
}



//int add_book(Book book) {
//	Book* query = library->list;
//	while (query->next != NULL) {
//		query = query->next;
//	}
//	query->next = (Book*)malloc(sizeof(Book));
//
//}
//
//
//
//int remove_book(Book book) {
//	int ID = 0;
//	Book* list = &library;
//	do {
//
//	} while (list->next->next != NULL);
//	return 0;
//}
//


BookList find_book_by_title(const char* title) {
	int i, len;
	int num = 0;
	BookList* res = (BookList*)malloc(sizeof(BookList));
	res->list = (Book*)malloc(sizeof(Book));
	Book* newBook = res->list;
	newBook->next = NULL;
	res->list = NULL;
	Book* query = library->list;
	while (query != NULL) {
		if (strcmp(query->title, title)) {
			newBook->id = query->id;
			len = strlen(query->title);
			newBook->title = (char*)malloc(sizeof(len + 1));
			memset(newBook->title, '\0', len + 1);
			strcpy(newBook->title, query->title);
			len = strlen(query->authors);
			newBook->authors = (char*)malloc(sizeof(len + 1));
			memset(newBook->authors, '\0', len + 1);
			strcpy(newBook->authors, query->authors);
			newBook->year = query->year;
			newBook->copies = query->copies;
			num++;
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
			newBook->next = NULL;
		}
		query = query->next;
	}
	res->length = num;
	return *res;
}



BookList find_book_by_author(const char* author) {
	int i, len;
	int num = 0;
	BookList* res = (BookList*)malloc(sizeof(BookList));
	res->list = (Book*)malloc(sizeof(Book));
	Book* newBook = res->list;
	newBook->next = NULL;
	res->list = NULL;
	Book* query = library->list;
	while (query != NULL) {
		if (strcmp(query->authors, author)) {
			newBook->id = query->id;
			len = strlen(query->title);
			newBook->title = (char*)malloc(sizeof(len + 1));
			memset(newBook->title, '\0', len + 1);
			strcpy(newBook->title, query->title);
			len = strlen(query->authors);
			newBook->authors = (char*)malloc(sizeof(len + 1));
			memset(newBook->authors, '\0', len + 1);
			strcpy(newBook->authors, query->authors);
			newBook->year = query->year;
			newBook->copies = query->copies;
			num++;
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
			newBook->next = NULL;
		}
		query = query->next;
	}
	res->length = num;
	return *res;
}



BookList find_book_by_year(unsigned int year) {
	int i, len;
	int num = 0;
	BookList* res = (BookList*)malloc(sizeof(BookList));
	res->list = (Book*)malloc(sizeof(Book));
	Book* newBook = res->list;
	newBook->next = NULL;
	res->list = NULL;
	Book* query = library->list;
	while (query != NULL) {
		if (query->year == year) {
			newBook->id = query->id;
			len = strlen(query->title);
			newBook->title = (char*)malloc(sizeof(len + 1));
			memset(newBook->title, '\0', len + 1);
			strcpy(newBook->title, query->title);
			len = strlen(query->authors);
			newBook->authors = (char*)malloc(sizeof(len + 1));
			memset(newBook->authors, '\0', len + 1);
			strcpy(newBook->authors, query->authors);
			newBook->year = query->year;
			newBook->copies = query->copies;
			num++;
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
			newBook->next = NULL;
		}
		query = query->next;
	}
	res->length = num;
	return *res;
}

