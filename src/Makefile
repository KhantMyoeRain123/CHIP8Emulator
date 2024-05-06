
objects=main.o chip8.o reader.o

emulator.out: $(objects)
	clang $(objects) -o emulator

%.o:%.c
	clang -o $@ -c $<




