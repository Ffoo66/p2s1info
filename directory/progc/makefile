all: c.exe

clean:
	rm *.exe

*.o: *.c
	gcc -c $< -o $@

c.exe: *.c
	gcc $^ -o $@

