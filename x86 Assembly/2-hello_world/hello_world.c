#include <stdio.h>

const char *msg = "[+] cr0w waz here!";

int main(void){
	write(1, msg, strlen(msg));
	exit(0);
}
