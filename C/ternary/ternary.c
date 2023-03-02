#include <stdio.h>

typedef struct {
    int age;
    char name[12];
    float balance;
} person;

person newPerson = {20, "percible", 47.0};

void printPersonData() {
    printf("[+] welcome, %s!", newPerson.name);
    printf("\n[+] you are %d years old.", newPerson.age);
    printf("\n[+] your current bank balance is: $%.2f", newPerson.balance);

    (newPerson.age < 18) ? printf("\n[!] nuh-uh-uh. come back once you're 18.\n") : printf("\n[+] please make yourself at home :)\n");

}

int main(void) {
    printPersonData();
    return 0;
}
