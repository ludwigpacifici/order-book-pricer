all: test

release:
	make --directory=.. $@

debug:
	make --directory=.. $@

test: release
	./compare.sh

perf: debug
	./perf.sh
