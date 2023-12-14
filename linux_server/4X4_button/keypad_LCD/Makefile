
TARGET= keypad_v3
CC= gcc
OBJ= keypad_v3.o lcd1602.o
LFLAGS= -lwiringPi
CFLAGS= -c

all: $(TARGET)

$(TARGET): $(OBJ)
        $(CC) -o $(TARGET) $(OBJ) $(LFLAGS)

.o.c:
        $(CC) $(CFLAGS) $<

clean:
        rm -rf *.o $(TARGET)
~
