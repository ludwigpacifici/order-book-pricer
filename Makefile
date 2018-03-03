all: compile

compile:
	make --directory=src $@

test:
	make --directory=tests $@
