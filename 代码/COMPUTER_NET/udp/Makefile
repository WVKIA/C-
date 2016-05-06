OBJS +=main.o admin.o
CC = gcc
prog:$(OBJS)
	$(CC) $(OBJS) -o prog
main.o:msg.h admin.h

admin.o:admin.h

clean:
	rm -rf *.o

