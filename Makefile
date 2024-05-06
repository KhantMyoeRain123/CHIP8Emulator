
objects=main.o chip8.o

emulator.out: $(objects)
	clang $(objects) -o emulator

%.o:%.c
	clang -o $@ -c $<




