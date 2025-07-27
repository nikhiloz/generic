/**
 * @file c_language_features_demo.c
 * @brief Comprehensive demonstration of C language features and concepts
 * @author Development Team
 * @date Created: July 2025
 *
 * This file demonstrates various C programming concepts including:
 * - Command line argument processing
 * - Function pointers and arrays
 * - Bit manipulation operations
 * - Dynamic memory allocation
 * - Endianness detection
 * - Bit fields in structures
 * - Pointer operations and string handling
 * - Conditional expressions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*============================================================================
 * MACRO DEFINITIONS
 * Bit manipulation macros for common operations
 *============================================================================*/

/**
 * @brief Clear a specific bit in a variable
 * @param x Variable to modify
 * @param n Bit position to clear (0-based)
 * @note Uses do-while(0) idiom for safe macro expansion
 */
#define CLR_BIT(x,n) do {                   \
                       x &= (~(1 << n));   \
                     } while(0)

/**
 * @brief Set a specific bit in a variable
 * @param x Variable to modify
 * @param n Bit position to set (0-based)
 */
#define SET_BIT(x,n) x |= (1 << n)

/**
 * @brief Check if a specific bit is set
 * @param x Variable to check
 * @param n Bit position to check (0-based)
 * @return Non-zero if bit is set, 0 otherwise
 */
#define CHECK_BIT(x,n) ((x >> n) & 1)

/*============================================================================
 * FUNCTION PROTOTYPES AND IMPLEMENTATIONS
 *============================================================================*/

/**
 * @brief Wrapper function for malloc with type safety
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory, NULL on failure
 * @note In production code, should include error checking
 */
static void *malloc_wrapper(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed for %zu bytes\n", size);
    }
    return ptr;
}

/**
 * @brief Addition function for function pointer demonstration
 * @param x First operand
 * @param y Second operand
 * @return Sum of x and y
 */
static int add_numbers(int x, int y) {
    return x + y;
}

/**
 * @brief Subtraction function for function pointer demonstration
 * @param x First operand
 * @param y Second operand
 * @return Difference of x and y
 */
static int subtract_numbers(int x, int y) {
    return x - y;
}

/**
 * @brief Multiplication function for function pointer demonstration
 * @param x First operand
 * @param y Second operand
 * @return Product of x and y
 */
static int multiply_numbers(int x, int y) {
    return x * y;
}

/**
 * @brief Allocates memory and stores a value
 * @param val Value to store
 * @return Pointer to allocated integer containing val
 * @warning Caller is responsible for freeing the returned memory
 */
static int *create_heap_integer(int val) {
    int *ptr = (int *)malloc_wrapper(sizeof(int));
    if (ptr) {
        *ptr = val;
    }
    return ptr;
}

/**
 * @brief Demonstrates command line argument processing
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 */
static void demonstrate_command_line_args(int argc, char **argv) {
    printf("=== COMMAND LINE ARGUMENTS ===\n");
    printf("Total argument count: %d\n", argc);

    // Display all arguments
    for (int i = 0; i < argc; i++) {
        printf("  argv[%d]: %s\n", i, argv[i]);
    }

    if (argc == 1) {
        printf("No additional arguments provided.\n");
    }
    printf("\n");
}

/**
 * @brief Demonstrates function pointers and arrays of function pointers
 */
static void demonstrate_function_pointers(void) {
    printf("=== FUNCTION POINTERS ===\n");

    // Define function pointer type
    typedef int (*math_operation_t)(int, int);

    // Create array of function pointers
    math_operation_t operations[] = {
        add_numbers,
        subtract_numbers,
        multiply_numbers
    };

    const char *operation_names[] = {
        "Addition",
        "Subtraction",
        "Multiplication"
    };

    int a = 12, b = 4;

    printf("Operands: a = %d, b = %d\n", a, b);

    // Execute each operation
    for (size_t i = 0; i < sizeof(operations)/sizeof(operations[0]); i++) {
        int result = operations[i](a, b);
        printf("%s: %d\n", operation_names[i], result);
    }
    printf("\n");
}

/**
 * @brief Demonstrates bit manipulation operations
 */
static void demonstrate_bit_operations(void) {
    printf("=== BIT MANIPULATION ===\n");

    uint8_t value = 224; // Binary: 11100000
    printf("Initial value: %d (binary: ", value);

    // Print binary representation
    for (int i = 7; i >= 0; i--) {
        printf("%d", CHECK_BIT(value, i));
    }
    printf(")\n");

    // Clear bit 5 (6th bit from right, 0-indexed)
    printf("Clearing bit 5...\n");
    CLR_BIT(value, 5);
    printf("After clearing bit 5: %d (binary: ", value);
    for (int i = 7; i >= 0; i--) {
        printf("%d", CHECK_BIT(value, i));
    }
    printf(")\n");

    // Set bit 5 again
    printf("Setting bit 5...\n");
    SET_BIT(value, 5);
    printf("After setting bit 5: %d (binary: ", value);
    for (int i = 7; i >= 0; i--) {
        printf("%d", CHECK_BIT(value, i));
    }
    printf(")\n\n");
}

/**
 * @brief Demonstrates dynamic memory allocation
 */
static void demonstrate_dynamic_memory(void) {
    printf("=== DYNAMIC MEMORY ALLOCATION ===\n");

    // Allocate and use heap memory
    int *heap_value = create_heap_integer(150);
    if (heap_value) {
        printf("Original heap value: %d\n", *heap_value);
        (*heap_value)++; // Increment the value
        printf("After increment: %d\n", *heap_value);

        // Free the allocated memory
        free(heap_value);
        heap_value = NULL; // Prevent accidental reuse
        printf("Memory freed successfully.\n");
    }
    printf("\n");
}

/**
 * @brief Detects and displays system endianness
 */
static void demonstrate_endianness_detection(void) {
    printf("=== ENDIANNESS DETECTION ===\n");

    union {
        uint32_t integer;
        uint8_t bytes[4];
    } test_union;

    test_union.integer = 0x12345678;

    printf("Test value: 0x%08X\n", test_union.integer);
    printf("Byte order in memory: 0x%02X 0x%02X 0x%02X 0x%02X\n",
           test_union.bytes[0], test_union.bytes[1],
           test_union.bytes[2], test_union.bytes[3]);

    // Simple endianness test
    uint16_t test_value = 1;
    if (*(uint8_t*)&test_value == 1) {
        printf("System is Little Endian\n");
    } else {
        printf("System is Big Endian\n");
    }
    printf("\n");
}

/**
 * @brief Demonstrates bit fields in structures
 */
static void demonstrate_bit_fields(void) {
    printf("=== BIT FIELDS IN STRUCTURES ===\n");

    // Structure with bit fields
    struct bit_field_demo {
        unsigned int flag : 1;      // 1 bit for boolean flag
        unsigned int status : 2;    // 2 bits for status (0-3)
        unsigned int counter : 5;   // 5 bits for counter (0-31)
        unsigned int reserved : 8;  // 8 bits reserved for future use
    };

    struct bit_field_demo demo_struct = {0};

    // Set values
    demo_struct.flag = 1;
    demo_struct.status = 2;
    demo_struct.counter = 15;
    demo_struct.reserved = 0xFF;

    printf("Structure size: %zu bytes\n", sizeof(demo_struct));
    printf("flag (1 bit): %u\n", demo_struct.flag);
    printf("status (2 bits): %u\n", demo_struct.status);
    printf("counter (5 bits): %u\n", demo_struct.counter);
    printf("reserved (8 bits): 0x%02X\n", demo_struct.reserved);

    // Demonstrate overflow protection (intentional truncation for demonstration)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"
    demo_struct.counter = 35; // Will be truncated to 5 bits (35 & 0x1F = 3)
#pragma GCC diagnostic pop
    printf("counter after setting to 35: %u (truncated to 5 bits)\n", demo_struct.counter);
    printf("\n");
}

/**
 * @brief Demonstrates various pointer and string operations
 */
static void demonstrate_pointers_and_strings(void) {
    printf("=== POINTERS AND STRINGS ===\n");

    // Array of string literals (char pointers)
    const char *names[] = {"Alice", "Bob", "Charlie", "Diana"};
    size_t name_count = sizeof(names) / sizeof(names[0]);

    printf("Names array (string literals):\n");
    for (size_t i = 0; i < name_count; i++) {
        printf("  names[%zu]: %s (address: %p)\n", i, names[i], (void*)names[i]);
    }

    // Character array with string
    char greeting[] = "Hello, World!";
    char *greeting_ptr = greeting;

    printf("\nCharacter array and pointer:\n");
    printf("  Array content: %s\n", greeting);
    printf("  Via pointer: %s\n", greeting_ptr);
    printf("  Array address: %p\n", (void*)greeting);
    printf("  Pointer value: %p\n", (void*)greeting_ptr);

    // Modify string through pointer
    greeting_ptr[7] = 'C';
    printf("  After modification: %s\n", greeting);

    printf("\n");
}

/**
 * @brief Demonstrates conditional expressions and operators
 */
static void demonstrate_conditional_expressions(void) {
    printf("=== CONDITIONAL EXPRESSIONS ===\n");

    int values[] = {5, 10, 15, 20};
    size_t value_count = sizeof(values) / sizeof(values[0]);

    printf("Testing values against threshold (10):\n");
    for (size_t i = 0; i < value_count; i++) {
        // Ternary operator demonstration
        const char *comparison = (values[i] < 10) ? "LESS" :
                                (values[i] == 10) ? "EQUAL" : "GREATER";
        printf("  %d is %s than 10\n", values[i], comparison);
    }

    // Demonstrate short-circuit evaluation
    int x = 5, y = 0;
    printf("\nShort-circuit evaluation:\n");
    printf("x = %d, y = %d\n", x, y);

    // Safe division using short-circuit AND
    if (y != 0 && x / y > 2) {
        printf("Division result is greater than 2\n");
    } else {
        printf("Cannot divide by zero or result <= 2\n");
    }

    printf("\n");
}

/*============================================================================
 * MAIN FUNCTION
 *============================================================================*/

/**
 * @brief Main function - entry point of the program
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return EXIT_SUCCESS on successful execution
 */
int main(int argc, char **argv) {
    printf("=====================================================\n");
    printf("    C LANGUAGE FEATURES DEMONSTRATION PROGRAM\n");
    printf("=====================================================\n\n");

    // Demonstrate various C language features
    demonstrate_command_line_args(argc, argv);
    demonstrate_function_pointers();
    demonstrate_bit_operations();
    demonstrate_dynamic_memory();
    demonstrate_endianness_detection();
    demonstrate_bit_fields();
    demonstrate_pointers_and_strings();
    demonstrate_conditional_expressions();

    printf("=====================================================\n");
    printf("    DEMONSTRATION COMPLETED SUCCESSFULLY\n");
    printf("=====================================================\n");

    return EXIT_SUCCESS;
}
