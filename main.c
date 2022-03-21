#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "book_management.h"






void registerModule(user* a) {
	user* list = a->next;
	user* newUser;
	char ID[40];
	char password[40];
	while (1) {
		printf("Please enter your ID number(8-digit-number): ");
		scanf("%s", ID);
		if (strspn(ID, "0123456789") == strlen(ID) && strlen(ID) == 8) {
			break;
		}
		else {
			printf("Format error, please enter again!\n");
		}
		while (list->next != NULL) {
			if (strcmp(list->ID, ID)) {
				printf("The ID already exists.");
				break;
			}
		}
	}
	printf("Ok\n");
	while (1) {
		printf("Please enter your password(8-digit-number): ");
		scanf("%s", password);
		if (strspn(password, "0123456789") == strlen(password) && strlen(password) == 8) {
			printf("Ok\n");
			break;
		}
		else {
			printf("Format error, please enter again!\n");
		}
	}
	while (list->next != NULL) {
		list = list->next;
	}
	newUser = (user*)malloc(sizeof(user));
	list->next = newUser;
	strcpy(newUser->ID, ID);
	strcpy(newUser->password, password);
	newUser->broBook = NULL;
	newUser->next = NULL;
	printf("Congratuulations. You have registered successfully!\n");



}

void signModule(user* a) {
	user* list = a->next;
	user* newUser;
	char enterID[40];
	char enterpassword[40];       // Receive the entered ID and password
	char password[9];
	while (1) {
		printf("Please enter your ID number(8-digit-number): ");
		scanf("%s", enterID);
		if (strspn(enterID, "0123456789") == strlen(enterID) && strlen(enterID) == 8) {
			break;
		}
		else {
			printf("Format error, please enter again!\n");
		}
		while (list->next != NULL) {
			if (strcmp(list->ID, enterID)) {
				strcmp(password, list->password);
				break;
			}
		}
		printf("The ID doesn't exist.");
	}
	while (1) {
		printf("Please enter your password(8-digit-number): ");
		scanf("%s", password);
		if (strspn(password, "0123456789") == strlen(password) && strlen(password) == 8) {
			printf("Ok\n");
			break;
		}
		else {
			printf("Format error, please enter again!\n");
		}
		if (strcmp(password, enterpassword)) {			
			return;
		}
		else {
			printf("Icorrect password, please enter again.");
		}
	}
}


int main() {
	signModule();
	library = (Book*)malloc(sizeof(Book));
	/*char a[12] = "edadeadadagg";
	int i;
	i = strspn("ababababababab", "abcdefghijklmnop\0");
	printf("%d", i);*/
	return 0;
}