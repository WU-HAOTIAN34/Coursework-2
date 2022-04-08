#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "interface.h"
#include "book_management.h"
#include "user.h"



int main(int argc, char** argv) {
	int a, b;
	FILE* bookp;
	FILE* userp;
	// judge if the command line parameter is correct
	if ((argc != 3) || strcmp(argv[1], "book.txt") || strcmp(argv[2], "user.txt")) {
		printf("Error\nExpected use: ./library book.txt user.txt\n");
	}
	else {
		//judge if the files exist
		bookp = fopen(argv[1], "rb");
		userp = fopen(argv[2], "rb");
		if (bookp == NULL) {
			printf("Error\nFile book.txt doesn't exist.\n");
		}
		else if (userp == NULL) {
			printf("Error\nFile user.txt doesn't exist.\n");
		}
		else {
			//enter the program load file and build list
			member = (userList*)malloc(sizeof(userList));
			library = (BookList*)malloc(sizeof(BookList));
			a = load_books(bookp);
			b = loadUser(userp);
			fclose(bookp);
			fclose(userp);
			bookp = NULL;
			userp = NULL;
			if (a == 0 || b == 0) {
				printf("Error\nThe file has been modified or corrupted\n");
			}
			else {
				interface();
				// exit program store information and free list
				bookp = fopen("book.txt", "wb+");
				store_books(bookp);
				fclose(bookp);
				bookp = NULL;
				userp = fopen("user.txt", "wb+");
				storeUser(userp);
				fclose(userp);
				userp = NULL;
				freeList(library->list);
				free(library);
				freeUser(member);
				free(member);
			}
		}
	}
	return 0;
}


