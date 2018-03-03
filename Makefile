compile:
	make --directory=src

all: compile

test: compile
	$(shell diff -s `cat ./data/basic.in.txt | ./src/order-book-pricer 200` ./data/basic.out.txt)
