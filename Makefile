# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
LDFLAGS = -L/usr/local/lib -lm -lpthread

# Source files and objects
SOURCES = bit_operations.c c_language_features_demo.c pthread_mutex_demo.c system_command_demo.c combined_hack_demo.c comprehensive_c_demo.c
OBJECTS = $(SOURCES:.c=.o)

# Target executables
TARGETS = bit_demo c_features_demo pthread_demo system_demo combined_hack comprehensive_demo

# Default target
all: $(TARGETS)
	@echo "=============================="
	@echo "   BUILD COMPLETED SUCCESSFULLY"
	@echo "=============================="

# Pattern rule for object files
%.o: %.c
	@echo "Compiling $<..."
	$(CC) -c -o $@ $< $(CFLAGS)

# Bit operations demo
bit_demo: bit_operations.o
	@echo "----Linking bit_demo----"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# C language features demo
c_features_demo: c_language_features_demo.o
	@echo "----Linking c_features_demo----"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# Pthread mutex demo
pthread_demo: pthread_mutex_demo.o
	@echo "----Linking pthread_demo----"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# System command demo
system_demo: system_command_demo.o
	@echo "----Linking system_demo----"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# Combined hack demo
combined_hack: combined_hack_demo.o
	@echo "----Linking combined_hack----"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# Comprehensive demo combining all 5 files
comprehensive_demo: comprehensive_c_demo.o
	@echo "----Linking comprehensive_demo----"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# Clean build artifacts
clean:
	@echo "----Cleaning----"
	rm -f $(OBJECTS) $(TARGETS)

# Install target (optional)
install: $(TARGETS)
	@echo "----Installing----"
	cp $(TARGETS) /usr/local/bin/

# Run tests
test: $(TARGETS)
	@echo "----Running tests----"
	./bit_demo
	@echo "----Running C features demo----"
	./c_features_demo
	@echo "----Running pthread demo----"
	./pthread_demo
	@echo "----Running system command demo----"
	./system_demo
	@echo "----Running combined hack demo----"
	./combined_hack
	@echo "----Running comprehensive demo----"
	./comprehensive_demo

# Show help
help:
	@echo "Available targets:"
	@echo "  all                - Build all targets (default)"
	@echo "  bit_demo           - Build the bit operations demo"
	@echo "  c_features_demo    - Build the C language features demo"
	@echo "  pthread_demo       - Build the pthread mutex demo"
	@echo "  system_demo        - Build the system command demo"
	@echo "  combined_hack      - Build the combined hack demonstrations"
	@echo "  comprehensive_demo - Build the comprehensive demo (all 5 files)"
	@echo "  clean              - Remove build artifacts"
	@echo "  install            - Install executables to /usr/local/bin"
	@echo "  test               - Run all demo programs"
	@echo "  help               - Show this help message"

# Declare phony targets
.PHONY: all clean install test help




