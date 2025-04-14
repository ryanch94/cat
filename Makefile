cat:
	mkdir -p build
	gcc cat.c -o build/cat -Wall

debug:
	mkdir -p build
	gcc cat.c -o build/cat -ggdb -Wall

clean:
	rm -r build
