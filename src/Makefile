CC = gcc
CFLAGS = -Werror -Wextra -Wall -std=c11

FILE_NAME = Quest_2
TARGET_Q2 = ../build/$(FILE_NAME)

state_search: $(TARGET_Q2)

$(TARGET_Q2): state_search.o
	$(CC) $(CFLAGS) -o $@ $<

state_search.o: state_search.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: state_search clean

clean:
	rm -rf *.o