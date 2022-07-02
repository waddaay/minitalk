RM = rm -f
CC = cc
CFLAGS = -Wall -Werror -Wextra

OBJ := client.o server.o client_bonus.o server_bonus.o

all: client server

bonus: client_bonus server_bonus

client: client.o
	$(CC) $(CFLAGS) -o client $<

server: server.o
	$(CC) $(CFLAGS) -o server $<

client_bonus: client_bonus.o $(LIB)
	$(CC) $(CFLAGS) -o client $< 

server_bonus: server_bonus.o $(LIB)
	$(CC) $(CFLAGS) -o server $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) client server


re: fclean all