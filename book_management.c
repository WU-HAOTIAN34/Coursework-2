#define _CRT_SECURE_NO_WARNINGS
#include "book_management.h"
#include "interface.h"
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



int add_book(Book book) {
	int len;
	Book* newBook = library->list;
	char id[10], year[10], copies[10], title[100], author[100];
	memset(id, '\0', 10);
	memset(year, '\0', 10);
	memset(copies, '\0', 10);
	memset(title, '\0', 100);
	memset(author, '\0', 100);
	printf("Please enter the ID (A number less than five digits and don't start with 0): ");
	scanf("%s", id);
	if ((int)id[0] == 48 || strspn(id, "0123456789") != strlen(id) || strlen(id) >= 5 || strlen(id) <= 0) {
		printf("Invalid id, fail to add.\n");
		return 0;
	}
	else {
		book.id = covertInt(id);
	}
	printf("Please enter the title: ");
	scanf("%s", title);
	if (!(ifStrValid(title, strlen(title)))){
		printf("Ivalid title, fail to add.\n");
		return 0;
	}
	printf("Please enter the author: ");
	scanf("%s", author);
	if (!(ifStrValid(author, strlen(author)))) {
		printf("Ivalid author, fail to add.\n");
		return 0;
	}
	printf("Please enter the year (A number less than five digits and don't start with 0): ");
	scanf("%s", year);
	if ((int)year[0] == 48 || strspn(year, "0123456789") != strlen(year) || strlen(year) >= 5 ||
		strlen(year) <= 0) {
		printf("Invalid year, fail to add.\n");
		return 0;
	}
	else {
		book.year = covertInt(year);
		if (book.year > 2022) {
			printf("Invalid year, fail to add.\n");
			return 0;
		}
	}
	printf("Please enter the copies (Less than 1000): ");
	scanf("%s", copies);
	if ((int)copies[0] == 48 || strspn(copies, "0123456789") != strlen(copies) || 
		strlen(copies) >= 4 || strlen(copies) <= 0) {
		printf("Invalid copies, fail to add.\n");
		return 0;
	}
	else {
		book.copies = covertInt(copies);
		if (book.copies >= 1000) {
			printf("Invalid copies, fail to add.\n");
			return 0;
		}
	}
	while (newBook->next != NULL) {
		newBook = newBook->next;
	}
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;
	newBook->id = book.id;
	len = strlen(title);
	newBook->title = (char*)malloc(sizeof(char) * (len + 1));
	memset(newBook->title, '\0', len + 1);
	strcpy(newBook->title, title);
	len = strlen(author);
	newBook->authors = (char*)malloc(sizeof(char) * (len + 1));
	memset(newBook->authors, '\0', len + 1);
	strcpy(newBook->authors, author);
	newBook->year = book.year;
	newBook->copies = book.copies;
	newBook->next = NULL;
	return 1;
}



int remove_book(Book book) {
	char id[10];
	Book* temp;
	Book* newBook = library->list;
	memset(id, '\0', 10);
	printf("Please enter the ID: ");
	scanf("%s", id);
	if ((int)id[0] == 48 || strspn(id, "0123456789") != strlen(id) || strlen(id) >= 5 || strlen(id) <= 0) {
		printf("Invalid id\n");
		return 0;
	}
	else {
		book.id = covertInt(id);
	}
	if (newBook->next == NULL) {
		if (newBook->id == book.id) {
			library->length -= 1;
			library->list = NULL;
			free(newBook->authors);
			free(newBook->title);
			free(&newBook);
			return 1;
		}
		else {
			printf("The book doesn't exist.");
			return 0;
		}
	}
	else {
		if (newBook->id == book.id) {
			library->length -= 1;
			library->list = newBook->next;
			free(newBook->authors);
			free(newBook->title);
			free(&newBook);
			return 1;
		}
		while (newBook->next != NULL) {
			if (newBook->next->id == book.id) {
				temp = newBook->next;
				newBook->next = newBook->next->next;
				free(temp->authors);
				free(temp->title);
				free(temp);
			}
		}
	}


}



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

