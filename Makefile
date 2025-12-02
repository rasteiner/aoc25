CC = gcc
CFLAGS = -Wall -g -O2

SRCS = $(wildcard day*.c)
PROGS = $(patsubst %.c,%.exe,$(SRCS))
RUN_TARGETS = $(patsubst day%.c, run_day%, $(SRCS))

# make all / or just make
all: $(PROGS)

# make day01.exe
%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

# make run_day01
run_%: %.exe
	@echo Running $*...
	./$< $*.test.txt

run_all: $(RUN_TARGETS)


clean:
	del /Q *.exe 2>nul || true

.PHONY: clean