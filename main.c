#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "interface.h"
#include "book_management.h"
#include "user.h"



int main() {
	FILE* fp;
	interface();
	printf("Ok");
	// store users' information and library information
	fp = fopen("book.txt", "wb+");
	store_books(fp);
	fclose(fp);
	fp = fopen("user.txt", "wb+");
	storeUser(fp);
	fclose(fp);
	fp = NULL;
	return 0;
}




