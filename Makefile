
.PHONY: all main clean
all: main

main:
	$(MAKE) -f src/make.mk

clean:
	$(MAKE) -f src/make.mk clean
