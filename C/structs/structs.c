#include <stdio.h>

typedef struct {
    int age;
    char name[12];
    float balance;
} person;

person newPerson = {72, "percible", 47.0};

void printPersonData() {
    printf("[+] welcome, %s!", newPerson.name);
    printf("\n[+] you are %d years old.", newPerson.age);
    printf("\n[+] your current bank balance is: $%.2f", newPerson.balance);
}

int main(void) {
    printPersonData();
    return 0;
}
