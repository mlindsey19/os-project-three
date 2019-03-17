#Mitch Lindsey
#cs 4760
#03-16-19

CC = cc
CFLAGS = -g -Wall

OBJ1 = master.o readFile.o checkArgs.o
OBJ2 = palin.o

TARGET1 = master
TARGET2 = palin 

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJ1)
	$(CC) $(CFLAGS -o $(TARGET1) $(OBJ1)
$(TARGET2): $(OBJ2)
	$(CC) $(CFLAGS -o $(TARGET2) $(OBJ2)


%.o: %.c *.h
	$(CC) $(CFLAGS) -c $*.c -o $*.o

clean:
	rm $(TARGET1) $(TARGET2) *.o output.txt
