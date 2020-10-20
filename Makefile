TARGET	=	conv
OBJS	=	main.o \
			convert.o \
			solve.o \
			scanner.o \
			queue.o \
			stack.o
OPTIONS	=	-Wall -Wextra -g

all: $(TARGET)

%.o:%.c
	gcc $(OPTIONS) -c $< -o $@

$(TARGET): $(OBJS)
	gcc $(OPTIONS) -o $(TARGET) $(OBJS)

clean:
	-rm -rf $(TARGET) $(OBJS)
