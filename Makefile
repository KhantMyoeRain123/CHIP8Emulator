
objects=main.o chip8.o

emulator: $(objects)
	clang $(objects) -o emulator

%.o:%.c
	clang -o $@ -c $<




