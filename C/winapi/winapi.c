#include <stdio.h>
#include <windows.h>

typedef struct {
	int age;
	char name[32];
	float balance;
} person;

person newPerson = {31, "bernard black", 120.0};

void msgbx() {
	float balance = newPerson.balance;
	(balance >= 100) ? MessageBoxW(NULL, L"you have enough to enter the book shop!", L"COME IN!", MB_OK | MB_ICONINFORMATION) : MessageBoxW(NULL, L"you don't have enough to enter the book shop!", L"HALT!", MB_OK | MB_ICONHAND);
}

void userInfo() {
	printf("[+] %s, welcome!", newPerson.name);
	printf("\n[+] you are %d years old.", newPerson.age);
	printf("\n[!] let's see if you have enough to enter black books. currently it costs $100.");
	printf("\n[+] you have $%.2f dollars in your bank account.\n", newPerson.balance);
}

int main(void) {
	userInfo();
	msgbx();
	return EXIT_SUCCESS;
}
