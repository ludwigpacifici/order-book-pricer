all: release

release:
	make --directory=src $@

debug:
	make --directory=src $@

test:
	make --directory=tests $@

perf:
	make --directory=tests $@
