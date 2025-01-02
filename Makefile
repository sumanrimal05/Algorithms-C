# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source files
SRCS = Trees/binarySearchTree.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = Trees/binarySearchTree

# Dependencies (for automatic dependency management)
DEP := $(SRCS:.c=.d)

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to generate dependency files
%.d: %.c
	$(CC) -MM $(CFLAGS) $< > $@

# Include dependency files if they exist
-include $(DEP)

# Clean rule to remove the executable and object files
clean:
	rm -f $(TARGET) $(OBJS) $(DEP)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CFLAGS += -DDEBUG
debug: clean $(TARGET)

# Phony targets
.PHONY: all clean run debug
