## ASSEMBLY CODE

In the assembly code below, we're going to do our first "hello world." In assembly, it's much more complicated to do even the *simplest* of tasks; hello world's included. Nevertheless, I'll try to explain everything that's happening here. I'd highly recommend checking out the first example before starting this one if you've never seen how assembly code functions - or especially if you don't know how system calls are made.

We'll dissect the assembly code, but also program a C-equivalent so that you can see how this gets translated to a relatively higher-level programming language.

```asm
section .text
	global _start ; define an entry point for our linker

section .data
	msg db "[+] cr0w waz here!", 0xa
	len equ $ - msg

_start:

; write the msg to stdout
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
```

Firstly, we start off by creating a `_start` and making it global; this is solely for the linker to be able to find the entry-point to our program. We could manually specify entrypoints to our compilers/linkers, but let's save ourselves the unnecessary headache(s).

Next, we create `.data` section in which we'll define our message along with it's length (which we'll see is required by the write() function).

## INSIDE OF `_START`

It's time for the juicy part. We have to remember the way that we do syscalls; first, we need to setup the arguments for the specific syscall we're trying to call; which, in this case, is [write()](https://x86.syscall.sh/). We can see that write() requires the following arguments to be setup on the stack before using it:

| **SYSCALL_NUMBER** | **SYSCALL_NAME** | **EAX** | **ARG 0 (EBX)**                | **ARG 1 (ECX)** | **ARG 2 (EDX)** |
|--------------------|------------------|---------|--------------------------------|-----------------|-----------------|
| 4                  | WRITE            | 4       | UNSIGNED INT (FILE DESCRIPTOR) | CHAR *BUF       | SIZE_T COUNT    |

## DISSECTING WRITE()

We can see, from the man page of write, that it does in fact need those arguments setup on the stack:

```bash
🦊 ~/programs ☻  man 2 write
```

```bash
write(2)                           System Calls Manual                           write(2)

NAME
       write - write to a file descriptor

LIBRARY
       Standard C library (libc, -lc)

SYNOPSIS
       #include <unistd.h>

       ssize_t write(int fd, const void buf[.count], size_t count);

DESCRIPTION
       write()  writes  up to count bytes from the buffer starting at buf to the file re‐
       ferred to by the file descriptor fd.
```

Ah. Just as we thought. So, we can see that write() is setup in the following way from the `SYNPOSIS` section of the manual page:

```c
write(int fd, const void buf[.count], size_t count);
```

Looks extremely familiar, doesn't it? Continuing... So, we know how this function is setup and what it requires; let's look at the assembly code:

We start by putting the length of our message into the `edx` register. The `edx` being the `ARG 2` value from the table above. Next, we put our actual message into `ecx`; `ecx` being the `ARG 1` value from the table above. Lastly, we put the file descriptor we want to write to; in this case, `stdout` which is just `1`. This gets put into the `ebx` register, `ebx` being the `ARG 0` from the table above.

| ASSEMBLY     | write(int fd, const void *buf, size_t count) |
|--------------|----------------------------------------------|
| mov edx, len | size_t count                                 |
| mov ecx, msg | char *buf                                    |
| mov ebx, 1   | int fd                                       |

> **Note**
> This is all the setup that's required! What we're going to see next is just a simple syscall which we already know how to do!

All that's left is to actually call the write() function! We do this (the same way we did with the exit() syscall from the first example) We start by moving the syscall number into the `eax` register and then calling the syscall interrupt; `0x80`! That's it!

## EXITING... GRACEFULLY

```asm
; gracefully exit
	xor ebx, ebx ; zero out the ebx register to get it ready for exit()
	xor eax, eax ; zero out for next syscall
	mov ebx, 0   ; exit status code (exit(0))
	mov eax, 1   ; syscall number (1 == sys_exit)
	int 0x80     ; call the syscall interrupt
```

In order to exit gracefully, we can incorporate our first example's assembly code into here! It's the same exact thing as the write() syscall, except exit() is *much* easier to setup. We start by putting the status code we want (we want a status code of `0` to indicate success) into the `ebx` register - which I've taken the liberty of XOR'ing just incase some random value was inside of it or something. Next, we populate the `eax` register with the syscall number we want to call. `exit()` is `1`, therefore, we'll put `1` into our `eax` register. I also just XOR'ed it just to have a clean slate for our next syscall. Finally, we use the system call interrupt; `0x80`! All that's left is to...

## COMPILE AND RUN

This is just the same ol' compilation steps from before. The process is as follows:

```bash
asm code -> compiler -> object file -> linker -> executable
```

```bash
🧿 ~/x86/hell0_world ↯  nasm -f elf32 hello_world.asm -o hello_world_assembly.o
```

With the object file created, we now use a linker in order to create an executable.

```bash
🧿 ~/x86/hell0_world ↯  ld -m elf_i386 hello_world_assembly.o -o hello_world_assembly
```

Finally, we should have our brand new executable which we can now run!

```bash
🧿 ~/x86/hell0_world ↯  ./hello_world_assembly
[+] cr0w waz here!

🧿 ~/x86/hell0_world ↯  echo $?
0
```

Perfect! We used the write() function from a system call and successfully exited the program (with an exit code of `0`)! For some fun, we can now take a look at the C-equivalent of this code.

## C-EQUIVALENT

Consider the following code:

```c
#include <stdio.h>

const char *msg = "[+] cr0w waz here!";

int main(void){
	write(1, msg, strlen(msg));
	exit(0);
}
```

And now, consider our assembly code:

```asm
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
```

Holy f*ck aren't we lucky that we have high-level languages?

> **Note**
> Try to see if you can see the similarities with the C code and the Assembly code. You can also experiment with putting these binaries inside of a debugger/disassembler for a more intuitive understanding!

In the C-code, we basically do what we did in assembly. We setup our message, call the write() function; tell write() to output to `stdout`, give it our message, and the length of the message. After calling write(), we also call exit() and supply it with a value of `0`. Let's compile the script and run it:

```bash
🧿 ~/x86/hell0_world ↯  gcc -m32 hello_world.c -o hello_world
```

```bash
🧿 ~/x86/hell0_world ↯  ./hello_world
[+] cr0w waz here!%

🧿 ~/x86/hell0_world ↯  echo $?
0
```

We get the same results as the assembly code!

> **Note**
> Technically, this isn't the EXACT same as the assembly code, if we wanted to make our C-code even closer to the assembly code, we could include `sys/syscall.h` and write our script in the following way (I personally think this isn't needed as we're just drawing comparisons for our different, yet similar programs):

```c
#include <unistd.h>
#include <sys/syscall.h>

const char *msg = "[+] cr0w waz here!";

int main(void){

	syscall(SYS_write, 1, msg, strlen(msg));
	syscall(SYS_exit, 0);
}
```

I really hope you found this as interesting as I did; and moreover, I hope you learned something! We just did our first hello world in assembly! 😄
