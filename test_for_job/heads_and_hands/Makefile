.PHONY: all

all: clean
	gcc -g -c random_arrays.c -o random_arrays.o
	gcc -g main.c random_arrays.o -o main.out
	./main.out

clean:
	rm -rf *.o *.out

git:
	git add .
	git status
	git commit -m'$(m)'
	git push origin master
