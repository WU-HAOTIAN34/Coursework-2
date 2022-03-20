#include "book_management.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>


static Book* library;

int store_books(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	library = (Book*)malloc(sizeof(Book));
}


int load_books(FILE* file) {
	
}



int add_book(Book book) {
	Book* newBook= (Book*)malloc(sizeof(Book));
	newBook->next = book.next;
	book.next->before = newBook;
	book.next = newBook;
	newBook->before = book.before->next;
	


}



int remove_book(Book book) {
	if (book.before != NULL && book.next != NULL) {
		book.before->next = book.next;
		book.next->before = book.before;
	}
	else if (book.before == NULL && book.next == NULL) {
		
	}
	else if (book.before == NULL){
		
	}
	else if (book.next == NULL){
		
	}
	Book* delBook= &book;
	free(delBook);
	return 0;
}


BookList find_book_by_title(const char* title) {
	Book* query = library->next;
	int num = 1;
	while (query->next != NULL) {
		if (strcmp(query->title, title)) {
			BookList res = { &query, num };
			return res;
		}
		else {
			query = query->next;
			num++;
		}
	}
	BookList res = { NULL, 0 };
	return res;
}


BookList find_book_by_author(const char* author) {
	Book* query = library->next;
	int num = 1;
	while (query->next != NULL) {
		if (strcmp(query->authors, author)) {
			BookList res = { &query, num };
			return res;
		}
		else {
			query = query->next;
			num++;
		}
	}
	BookList res = { NULL, 0 };
	return res;

}



BookList find_book_by_year(unsigned int year) {
	Book* query = library->next;
	int num = 1;
	while (query->next != NULL) {
		if (query->year == year) {
			BookList res = { &query, num };
			return res;
		}
		else {
			query = query->next;
			num++;
		}
	}
	BookList res = { NULL, 0 };
	return res;

}

