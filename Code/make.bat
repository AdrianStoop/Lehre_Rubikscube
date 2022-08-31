@echo off
del WinBex.bin

nasm -O32 -f bin boot.asm -o boot.bin
nasm -O32 -f aout kernel.asm -o k.o
nasm -O32 -f aout isr.asm -o w.o
nasm -O32 -f aout process.asm -o pr.o
nasm -O32 -f aout int32.asm -o n.o  

pause

gcc  -Wall -O  -c ckernel.c -o ck.o -O1   
gcc  -Wall -O  -c video.c -o vi.o -O1
gcc  -Wall -O  -c util.c -o ut.o -O1
gcc  -Wall -O  -c gdt.c -o g.o
gcc  -Wall -O  -c idt.c -o i.o
gcc  -Wall -O  -c isrs.c -o is.o	
gcc  -Wall -O  -c irq.c -o q.o
gcc  -Wall -O  -c timer.c -o ti.o 	
gcc  -Wall -O  -c keyboard.c -o key.o
gcc  -Wall -O  -c funktionen.c -o os.o 
gcc  -Wall -O  -c paging.c -o pa.o
gcc  -Wall -O  -c kmalloc.c -o km.o
gcc  -Wall -O  -c int32.c -o in.o
gcc  -Wall -O  -c rubiks.c -o r.o

pause

ld -T kernel.ld k.o w.o ck.o in.o vi.o g.o i.o is.o pr.o n.o q.o ut.o os.o ti.o key.o pa.o km.o r.o -o ckernel.bin --verbose
	
pause


copy /b boot.bin + ckernel.bin WinBex

pause

del *.o
del *.bin
rename WinBex WinBex.bin
exit
