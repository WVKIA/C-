
OBJS += main.o student.o
CC   = gcc

prog:$(OBJS)
	$(CC) $(OBJS) -o prog
main.o:student.h
student.o:student.h

clean:
	rm -rf *.o
