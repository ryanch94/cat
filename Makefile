cat:
	mkdir build
	gcc cat.c -o build/cat

debug:
	mkdir build
	gcc cat.c -o build/cat -ggdb

clean:
	rm -r build