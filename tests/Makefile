all: test

release:
	make --directory=.. $@

debug:
	make --directory=.. $@

test:
	./compare.sh

perf:
	./$@.sh

time:
	./$@.sh

clean:
	rm -rf *.svg out.folded perf.data perf.data.old
