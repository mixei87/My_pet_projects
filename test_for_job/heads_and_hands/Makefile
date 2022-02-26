.PHONY: all clean rebuild

all: clean
	gcc -c random_arrays.c -o random_arrays.o
	gcc main.c random_arrays.o -o main.out	

clean:
	rm -rf *.o *.out

rebuild: clean all

git:
	git add .
	git status
	git commit -m'$(m)'
	git push origin master
