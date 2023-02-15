### START WITH `ASSEMBLY` CODE; THIS CODE WILL JUST ALTER THE EXIT CODE OF THE PROGRAM UPON EXITING.

```asm
global _start
_start:
	mov eax, 1    ; exit syscall
	mov ebx, 42   ; exit code (can be any int from 0-255)
	int 0x80      ; syscall interrupt
```

In the code above, we can see that we're:

- moving the value of `1` into the `eax` register.
- moving the value of `42` into the `ebx` register.
- using the `int` instruction with a value of `0x80`.

Let's start by explaining each of these steps. The `int` instruction stands for an `interrupt` instruction. Basically, when the CPU encounters this instruction, it hands off control to an interrupt handler; the interrupt that we chose, `0x80`, is responsible for [system calls](https://www.geeksforgeeks.org/introduction-of-system-call/) (`syscalls`) on Linux. The type of system call that we will run will depend on the value inside of `eax` which, in this case, is `1`. From a [system call table](https://faculty.nps.edu/cseagle/assembly/sys_call.html) (in x86), we can see that the `1 system call` belongs to `sys_exit`. If we look at the `man` pages for `exit()`, we can see how this works:

```bash
cr0w@blackbird: ~
ζ ›› man exit
```

```bash
exit(3)                                 Library Functions Manual                                 exit(3)

NAME
       exit - cause normal process termination

LIBRARY
       Standard C library (libc, -lc)

SYNOPSIS
       #include <stdlib.h>

       [[noreturn]] void exit(int status);

DESCRIPTION
       The  exit()  function  causes normal process termination and the least significant byte of status
       (i.e., status & 0xFF) is returned to the parent (see wait(2)).

[SNIP ...]
```

As we can see from the man pages, this standard C function, will simply just exit a process and the exit code that appears after process termination, denotes how the process ended. For example, typically, an exit status of 0 means that a process ended successfully/gracefully. An exit status code of 1 (or any non-zero integer up to 255 for that matter) denotes some sort of failure. We can actually even see this inside of the man pages for some other well-known commands like `ls`:

```bash
[SNIP ...]

   Exit status:
       0      if OK,

       1      if minor problems (e.g., cannot access subdirectory),

       2      if serious trouble (e.g., cannot access command-line argument).

[SNIP ...]
```
So, we know that `int 0x80` is the interrupt to perform system calls, and we know that this `int` instruction looksat the `eax` register in order to figure out *what* syscall it will be performing, in this case, it's `sys_exit` and which in 32-bit, is denoted by the syscall number `1`; hence, `mov eax, 1`.

Finally, let's address the integer `42` being moved into `ebx`. If we look back at the syscall table, we can see that `sys_exit` requires another register to work. This register is the `ebx` register and it takes an integer value, which in our case, is `42`. which will be the status code for the exit system call! So, basically, we're effectively just doing this:

```c
exit(42)
```

Very cool stuff! Now, let's move on to compiling and linking the assembly code.

### TURN THE ASSEMBLY CODE INTO AN `OBJECT FILE`

```bash
cr0w@blackbird: ~/programs/x86
ζ ›› nasm -f elf32 ex-1.asm -o ex-1.o
```

### USE A `LINKER` ON THE OBJECT FILE AND CREATE AN `ELF` FILE

```bash
cr0w@blackbird: ~/programs/x86
ζ ›› ld -m elf_i386 ex-1.o -o ex-1
```

### RUN THE PROGRAM AND NOTE THE `EXIT CODE`

```bash
cr0w@blackbird: ~/programs/x86
ζ ›› ./ex-1
```

After running this, we should be able to examine the exit code (which we can do with the `echo $?` command - which just holds the exit code of the previously terminated process) and we should see that, if everything worked as intended, our exit code should be `42`.

```bash
cr0w@blackbird: ~/programs/x86
ζ ›› echo $?
42
```

Et viola! We have `42` : ) This is a very very glossed over example, I know. I am just trying to champion the idea of a syscall and how to perform a super basic one - before we move on to our hello world.
