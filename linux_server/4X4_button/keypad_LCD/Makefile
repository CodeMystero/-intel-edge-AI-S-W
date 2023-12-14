
TARGET= keypad
CC= gcc
OBJ= keypad.o lcd_config.o
LFLAGS= -lwiringPi
CFLAGS= -c

all: $(TARGET)

$(TARGET): $(OBJ)
        $(CC) -o $(TARGET) $(OBJ) $(LFLAGS)

.o.c:
        $(CC) $(CFLAGS) $<

clean:
        rm -rf *.o $(TARGET)

