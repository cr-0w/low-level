#include <stdio.h>

int date; // set this to a number 1-7

int main(void) {
    
    switch(date) {
        case 1: 
            printf("[+] today is monday.\n");
            break;
        case 2:
            printf("[+] today is tuesday.\n");
            break;
        case 3:
            printf("[+] today is wednesday.\n");
            break;
        case 4: 
            printf("[+] today is thursday.\n");
            break;
        case 5:
            printf("[+] today is friday.\n");
            break;
        case 6:
            printf("[+] today is saturday.\n");
            break;
        case 7:
            printf("[+] today is sunday.\n");
            break;
        default:
            printf("[!] you didn't supply a number!\n");
            break;
    }

    return 0;
}

