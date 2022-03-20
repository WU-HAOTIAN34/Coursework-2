#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "book_management.h"


void signModule() {
	char ID[10];
	char password[8];
	char* a = &ID[0];
	/*int ID, password;*/
	int i;
	printf("Please enter your ID number(8-digit-number): ");
	scanf("%s", a);
	/*while()
	scanf("%c%c%c%c%c%c%c%c", a, a + 1, a + 2, a + 3, a + 4, a + 5, a + 6, a + 7, a + 8);
	for (i = 0; i < 8; i++) {
		if ((int)ID[i] < 48 || (int)ID[i] >57) {
			printf("adadad");
			break;
		}
	}*/
	

	/*printf("Please enter your password(8-digit-number): ");
	scanf("%d", &password);*/

}


int main() {
	/*signModule();*/
	char a[12] = "edadeadadagg";
	int i;
	i = strspn(a, "abcdefghijklmnop\0");
	printf("%d", i);
	return 0;
}