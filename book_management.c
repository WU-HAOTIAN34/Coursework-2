#define _CRT_SECURE_NO_WARNINGS
#include "book_management.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>




int store_books(FILE* file) {
	int len;
	Book* newBook = library->list;
	fwrite(&library->length, sizeof(unsigned int), 1, file);
	while (newBook != NULL) {
		fwrite(&(newBook->id), sizeof(unsigned int), 1, file);
		len = strlen(newBook->title);
		fwrite(&(len), sizeof(int), 1, file);
		fwrite(newBook->title, sizeof(char), len, file);
		len = strlen(newBook->authors);
		fwrite(&(len), sizeof(int), 1, file);
		fwrite(newBook->authors, sizeof(char), len, file);
		fwrite(&(newBook->year), sizeof(unsigned int), 2, file);
		newBook = newBook->next;
	}
}



int load_books(FILE* file) {
	int len, i;
	Book* newBook;
	fread(&(library->length), sizeof(unsigned int), 1, file);
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
		if (i == library->length - 1) {
			newBook->next = NULL;
			break;
		}
		else {
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
		}
	}
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

