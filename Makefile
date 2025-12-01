CC = gcc
CFLAGS = -Wall -g -O2

day01: day01.c
	$(CC) $(CFLAGS) -o day01.exe day01.c

clean:
	del /Q day01.exe 2>nul || true

.PHONY: clean