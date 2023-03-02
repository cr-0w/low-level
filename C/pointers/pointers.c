#include <stdio.h>

void pointerMagic() {
    int *null = NULL;
    int number = 666;
    char *str = "crow";
    int *address = &number;
    printf("[*] char 'str' set to (%s)", str);
    printf("\n[*] int 'number' set to (%d)", number);
    printf("\n[*] pointer to 'number' set to 'address' (*address = &number)");
    printf("\n[+] NULL pointer '*null' ---> (0x%x) [using hexadecimal format string]", &null);
    printf("\n[+] address of chararray ---> (0x%x) [using hexadecimal format string]", str, &str);
    printf("\n[+] address of int (%d) ---> (0x%x) [using hexadecimal format string]", number, &address);
    printf("\n[+] NULL pointer '*null' ---> (%p) [using pointer format string]", &null);
    printf("\n[+] address of int (%d) ---> (%p) [using pointer format string]", number, &address);
    printf("\n[+] address of chararray ---> (%p) [using pointer format string]\n", str, &str);
}

int main(int argc, char *argv[]) {
    pointerMagic();   
    return 0;
}
