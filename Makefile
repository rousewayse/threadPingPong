build: main.o
	gcc -pthread main.o -o exec.bin
%.o: %.c
	gcc -c -pthread $<
clean:
	rm *.o exec.bin
