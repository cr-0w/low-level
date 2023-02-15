section .text
	global _start

section .data
	msg db "[+] cr0w waz here!", 0xa
	len equ $ - msg

_start:

;write the msg to stdout
	mov edx, len ; message length
	mov ecx, msg ; message to write
	mov ebx, 1   ; file descriptor (stdout == 1)
	mov eax, 4   ; syscall number (4 == sys_write)
	int 0x80     ; call the syscall interrupt

; gracefully exit
	xor ebx, ebx ; zero out the ebx register to get it ready for exit()
	xor eax, eax ; zero out for next syscall
	mov ebx, 0   ; exit status code (exit(0))
	mov eax, 1   ; syscall number (1 == sys_exit)
	int 0x80     ; call the syscall interrupt
