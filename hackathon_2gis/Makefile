.PHONY: all push

all:
	g++ find_substrings.cpp -o a.out
	./a.out
push:
	git add .
	git status
	git commit -m'$(m)'
	git push origin master
