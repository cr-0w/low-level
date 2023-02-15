global _start
_start:
	mov eax, 1   ; exit syscall
	mov ebx, 42  ; exit code 42 -> exit codes can be any int from 0-255.
	int 0x80     ; sys call interrupt
