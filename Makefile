CFLAGS=-g -O2 -Wall -Wextra -D NDEBUG
INCLUDES=-I $(HOME)/local/include -L $(HOME)/local/lib

% : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< -lfort -lcsv
