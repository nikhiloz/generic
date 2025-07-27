/**
 * @file comprehensive_c_demo.c
 * @brief Comprehensive demonstration combining features from 5 generic C files
 * @author Development Team
 * @date Created: July 2025
 *
 * This file combines functionality from:
 * - generic.c: Basic C features, bit operations, data structures
 * - generic01.c: Advanced bit operations, function pointers, conditional compilation
 * - generic02.c: Multi-threading with simple counter operations
 * - generic03.c: Multi-threading with mutex synchronization
 * - generic05.c: System command execution (wget example)
 *
 * Features demonstrated:
 * - Command line argument processing
 * - Function pointers and arrays of function pointers
 * - Bit manipulation operations and macros
 * - Dynamic memory allocation
 * - Endianness detection
 * - Bit fields in structures
 * - Multi-threading with pthread
 * - Mutex synchronization
 * - Conditional compilation with preprocessor
 * - System command execution
 * - Pointer operations and string handling
 * - Advanced bit manipulation techniques
 */

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

/*============================================================================
 * CONFIGURATION AND FEATURE FLAGS
 *============================================================================*/

// Enable/disable different demonstration sections
#define ENABLE_BASIC_FEATURES     1
#define ENABLE_BIT_OPERATIONS     1
#define ENABLE_THREADING          1
#define ENABLE_ADVANCED_FEATURES  1
#define ENABLE_SYSTEM_COMMANDS    1

// Debug flags for conditional compilation (from generic01.c)
#define DEBUG 0x00 + 0x10 + 0x20 + 0x40

/*============================================================================
 * MACROS AND CONSTANTS
 *============================================================================*/

/** Clear a specific bit in a variable */
#define CLR_BIT(x,n) do {                   \
                       x &= (~(1 << n));   \
                     } while(0)

/** Set a specific bit in a variable */
#define SET_BIT(x,n) x |= (1 << n)

/** Check if a specific bit is set */
#define CHECK_BIT(x,n) ((x >> n) & 1)

/** Maximum thread count for demonstrations */
#define MAX_THREADS 4

/** Loop iterations for thread work simulation */
#define THREAD_WORK_ITERATIONS 0x1FFFFFF

/*============================================================================
 * GLOBAL VARIABLES FOR THREADING
 *============================================================================*/

/** Shared counter for thread demonstrations */
static volatile long shared_counter = 0;

/** Counter for job tracking */
static volatile int job_counter = 0;

/** Mutex for protecting shared resources */
static pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;

/*============================================================================
 * FUNCTION PROTOTYPES
 *============================================================================*/

// Basic mathematical operations
static int add_numbers(int a, int b);
static int subtract_numbers(int a, int b);
static int custom_function_call(int a, int(*func)(int, int));

// Memory management
static void *safe_malloc(size_t size);
static int *create_heap_value(int val);

// Threading functions
static void *increment_thread(void *arg);
static void *decrement_thread(void *arg);
static void *simple_job_thread(void *arg);

// Demonstration functions
static void demonstrate_basic_features(int argc, char **argv);
static void demonstrate_bit_operations(void);
static void demonstrate_function_pointers(void);
static void demonstrate_endianness(void);
static void demonstrate_bit_fields(void);
static void demonstrate_threading_simple(void);
static void demonstrate_threading_mutex(void);
static void demonstrate_system_commands(void);
static void demonstrate_pointer_operations(void);

// Utility functions
static void print_binary(uint8_t value);
static void print_separator(const char *title);
static int safe_system_command(const char *command);

/*============================================================================
 * BASIC MATHEMATICAL OPERATIONS
 *============================================================================*/

/**
 * @brief Add two integers
 */
static int add_numbers(int a, int b) {
    return a + b;
}

/**
 * @brief Subtract two integers
 */
static int subtract_numbers(int a, int b) {
    return a - b;
}

/**
 * @brief Call a function with same parameter twice
 */
static int custom_function_call(int a, int(*func)(int, int)) {
    return func(a, a);
}

/*============================================================================
 * MEMORY MANAGEMENT FUNCTIONS
 *============================================================================*/

/**
 * @brief Safe malloc wrapper with error checking
 */
static void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr && size > 0) {
        fprintf(stderr, "Memory allocation failed for %zu bytes\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/**
 * @brief Create an integer on the heap
 */
static int *create_heap_value(int val) {
    int *ptr = (int *)safe_malloc(sizeof(int));
    *ptr = val;
    return ptr;
}

/*============================================================================
 * THREADING FUNCTIONS
 *============================================================================*/

/**
 * @brief Thread function that increments shared counter
 */
static void *increment_thread(void *arg) {
    (void)arg; // Suppress unused parameter warning

    printf("[INCREMENT_THREAD] Starting\n");

    pthread_mutex_lock(&global_mutex);
    printf("[INCREMENT_THREAD] Acquired lock, counter = %ld\n", shared_counter);

    shared_counter++;
    for (long i = 0; i < THREAD_WORK_ITERATIONS; i++) {
        shared_counter++;
    }

    printf("[INCREMENT_THREAD] Final counter = %ld\n", shared_counter);
    pthread_mutex_unlock(&global_mutex);

    printf("[INCREMENT_THREAD] Released lock, exiting\n");
    return NULL;
}

/**
 * @brief Thread function that decrements shared counter
 */
static void *decrement_thread(void *arg) {
    (void)arg; // Suppress unused parameter warning

    printf("[DECREMENT_THREAD] Starting\n");

    pthread_mutex_lock(&global_mutex);
    printf("[DECREMENT_THREAD] Acquired lock, counter = %ld\n", shared_counter);

    shared_counter++;
    for (long i = 0; i < THREAD_WORK_ITERATIONS; i++) {
        shared_counter--;
    }

    printf("[DECREMENT_THREAD] Final counter = %ld\n", shared_counter);
    pthread_mutex_unlock(&global_mutex);

    printf("[DECREMENT_THREAD] Released lock, exiting\n");
    return NULL;
}

/**
 * @brief Simple job thread that simulates work
 */
static void *simple_job_thread(void *arg) {
    (void)arg; // Suppress unused parameter warning

    pthread_mutex_lock(&global_mutex);

    job_counter++;
    int current_job = job_counter;
    printf("\nJob %d started\n", current_job);

    // Simulate work
    for (unsigned long i = 0; i < (THREAD_WORK_ITERATIONS / 4); i++) {
        // Busy wait to simulate work
    }

    printf("Job %d finished\n", current_job);
    pthread_mutex_unlock(&global_mutex);

    return NULL;
}

/*============================================================================
 * UTILITY FUNCTIONS
 *============================================================================*/

/**
 * @brief Print binary representation of 8-bit value
 */
static void print_binary(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
}

/**
 * @brief Print section separator
 */
static void print_separator(const char *title) {
    printf("\n");
    printf("========================================\n");
    printf("    %s\n", title);
    printf("========================================\n");
}

/**
 * @brief Safely execute system command
 */
static int safe_system_command(const char *command) {
    if (!command) return -1;

    printf("Executing: %s\n", command);
    int result = system(command);

    if (result == -1) {
        printf("Command execution failed: %s\n", strerror(errno));
        return -1;
    }

    printf("Command completed with status: %d\n", WEXITSTATUS(result));
    return 0;
}

/*============================================================================
 * DEMONSTRATION FUNCTIONS
 *============================================================================*/

/**
 * @brief Demonstrate basic C features (from generic.c)
 */
static void demonstrate_basic_features(int argc, char **argv) {
    print_separator("BASIC C FEATURES");

    // Command line arguments
    printf("Command line arguments:\n");
    printf("Argument count: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("  argv[%d]: %s\n", i, argv[i]);
    }

    // Function pointer array
    printf("\nFunction pointer array demonstration:\n");
    typedef int (*math_func_t)(int, int);
    math_func_t operations[] = {add_numbers, subtract_numbers};

    printf("add_numbers(5, 3) = %d\n", operations[0](5, 3));
    printf("subtract_numbers(8, 3) = %d\n", operations[1](8, 3));

    // Custom function call demonstration
    printf("custom_function_call(5, add_numbers) = %d\n", custom_function_call(5, add_numbers));

    // Memory allocation
    printf("\nDynamic memory allocation:\n");
    int *heap_val = create_heap_value(150);
    printf("Original heap value: %d\n", *heap_val);
    (*heap_val)++;
    printf("After increment: %d\n", *heap_val);
    free(heap_val);
    printf("Memory freed\n");
}

/**
 * @brief Demonstrate bit operations (from generic.c and generic01.c)
 */
static void demonstrate_bit_operations(void) {
    print_separator("BIT OPERATIONS");

    // Basic bit manipulation
    int value = 224; // 11100000 in binary
    printf("Original value: %d (binary: ", value);
    print_binary((uint8_t)value);
    printf(")\n");

    CLR_BIT(value, 5);
    printf("After CLR_BIT(5): %d (binary: ", value);
    print_binary((uint8_t)value);
    printf(")\n");

    SET_BIT(value, 5);
    printf("After SET_BIT(5): %d (binary: ", value);
    print_binary((uint8_t)value);
    printf(")\n");

    // Advanced bit operations (from generic01.c)
    printf("\nAdvanced bit operations:\n");

    // XOR swap
    char a = 15, b = 240;
    printf("Before XOR swap: a=%d, b=%d\n", (uint8_t)a, (uint8_t)b);
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("After XOR swap: a=%d, b=%d\n", (uint8_t)a, (uint8_t)b);

    // Absolute value using bit operations
    int neg_val = -20;
    int abs_val = (neg_val ^ (neg_val >> 31)) - (neg_val >> 31);
    printf("Absolute value of %d using bit ops: %d\n", neg_val, abs_val);

    // Check if power of 2
    int test_val = 16;
    int is_power_of_2 = test_val > 0 ? (test_val & (test_val - 1)) == 0 : 0;
    printf("Is %d a power of 2? %s\n", test_val, is_power_of_2 ? "Yes" : "No");
}

/**
 * @brief Demonstrate function pointers (from generic01.c)
 */
static void demonstrate_function_pointers(void) {
    print_separator("FUNCTION POINTERS");

#if DEBUG & 0x2
    printf("Function pointer demonstration enabled\n");

    typedef int (*func_ptr)(int, int);
    func_ptr functions[4] = {add_numbers, subtract_numbers, NULL, NULL};

    int result = functions[0](2, 3);
    printf("Result of add: %d\n", result);
    printf("Result of subtract: %d\n", functions[1](5, 2));

    // Pass function pointer as argument
    result = custom_function_call(5, add_numbers);
    printf("Result of custom function call: %d\n", result);
#else
    printf("Function pointer demonstration disabled (DEBUG & 0x2 not set)\n");
#endif
}

/**
 * @brief Demonstrate endianness detection
 */
static void demonstrate_endianness(void) {
    print_separator("ENDIANNESS DETECTION");

#if DEBUG & 0x1
    printf("Endianness detection enabled\n");

    int test_value = 1;
    char byte_value = *(char *)&test_value;
    const char *endian_str = byte_value ? "Little Endian" : "Big Endian";
    printf("Machine is %s\n", endian_str);

    // Additional endianness test
    union {
        uint32_t integer;
        uint8_t bytes[4];
    } endian_test;

    endian_test.integer = 0x12345678;
    printf("Test value: 0x%08X\n", endian_test.integer);
    printf("Byte order: 0x%02X 0x%02X 0x%02X 0x%02X\n",
           endian_test.bytes[0], endian_test.bytes[1],
           endian_test.bytes[2], endian_test.bytes[3]);
#else
    printf("Endianness detection disabled (DEBUG & 0x1 not set)\n");
#endif
}

/**
 * @brief Demonstrate bit fields in structures
 */
static void demonstrate_bit_fields(void) {
    print_separator("BIT FIELDS");

    struct bit_field_struct {
        unsigned int flag1 : 1;
        unsigned int flag2 : 2;
        unsigned int counter : 5;
        unsigned int reserved : 8;
    };

    struct bit_field_struct demo = {0};

    demo.flag1 = 1;
    demo.flag2 = 2;
    demo.counter = 15;
    demo.reserved = 0xFF;

    printf("Bit field structure (size: %zu bytes):\n", sizeof(demo));
    printf("  flag1 (1 bit): %u\n", demo.flag1);
    printf("  flag2 (2 bits): %u\n", demo.flag2);
    printf("  counter (5 bits): %u\n", demo.counter);
    printf("  reserved (8 bits): 0x%02X\n", demo.reserved);

    // Test overflow
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"
    demo.counter = 35; // Will be truncated to 5 bits
#pragma GCC diagnostic pop
    printf("  counter after setting to 35: %u (truncated)\n", demo.counter);
}

/**
 * @brief Demonstrate pointer operations (from generic01.c)
 */
static void demonstrate_pointer_operations(void) {
    print_separator("POINTER OPERATIONS");

#if DEBUG & 0x4
    printf("Pointer operations demonstration enabled\n");

    int val1 = 10, val2 = 20;

    // Constant pointer
    int * const const_ptr = &val1;
    printf("Constant pointer value: %d\n", *const_ptr);
    *const_ptr = 40; // Allowed - can modify value
    printf("After modification: %d\n", *const_ptr);

    // Pointer to constant
    const int *ptr_to_const = &val2;
    printf("Pointer to constant value: %d\n", *ptr_to_const);
    ptr_to_const = &val1; // Allowed - can change pointer
    printf("After pointer change: %d\n", *ptr_to_const);

    // Array of string pointers
    printf("\nString pointer array:\n");
    const char *names[] = {"Alice", "Bob", "Charlie"};
    for (size_t i = 0; i < sizeof(names)/sizeof(names[0]); i++) {
        printf("  names[%zu]: %s\n", i, names[i]);
    }

    // Character array
    char message[] = "Hello World!";
    char *msg_ptr = message;
    printf("\nCharacter array: %s\n", message);
    printf("Via pointer: %s\n", msg_ptr);
#else
    printf("Pointer operations demonstration disabled (DEBUG & 0x4 not set)\n");
#endif
}

/**
 * @brief Demonstrate threading with simple jobs (from generic02.c)
 */
static void demonstrate_threading_simple(void) {
    print_separator("SIMPLE THREADING");

#if ENABLE_THREADING
    printf("Creating simple job threads...\n");

    pthread_t threads[2];

    // Reset job counter
    job_counter = 0;

    // Create threads
    for (int i = 0; i < 2; i++) {
        int result = pthread_create(&threads[i], NULL, simple_job_thread, NULL);
        if (result != 0) {
            fprintf(stderr, "Failed to create thread %d: %s\n", i, strerror(result));
            return;
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All simple jobs completed\n");
#else
    printf("Threading demonstration disabled\n");
#endif
}

/**
 * @brief Demonstrate threading with mutex synchronization (from generic03.c)
 */
static void demonstrate_threading_mutex(void) {
    print_separator("MUTEX SYNCHRONIZED THREADING");

#if ENABLE_THREADING
    printf("Creating synchronized threads...\n");

    pthread_t threads[2];
    typedef void *(*thread_func_t)(void *);
    thread_func_t thread_functions[] = {increment_thread, decrement_thread};

    // Reset shared counter
    shared_counter = 0;

    printf("Initial shared counter: %ld\n", shared_counter);

    // Create threads
    for (int i = 0; i < 2; i++) {
        int result = pthread_create(&threads[i], NULL, thread_functions[i], NULL);
        if (result != 0) {
            fprintf(stderr, "Failed to create thread %d: %s\n", i, strerror(result));
            return;
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final shared counter: %ld\n", shared_counter);
    printf("All synchronized threads completed\n");
#else
    printf("Threading demonstration disabled\n");
#endif
}

/**
 * @brief Demonstrate system command execution (from generic05.c)
 */
static void demonstrate_system_commands(void) {
    print_separator("SYSTEM COMMAND EXECUTION");

#if ENABLE_SYSTEM_COMMANDS
    printf("Demonstrating system command execution...\n");

    // Check if wget is available
    printf("Checking for wget availability...\n");
    int wget_available = (system("which wget > /dev/null 2>&1") == 0);

    if (wget_available) {
        printf("wget is available\n");
        printf("Original command from generic05.c:\n");
        printf("wget -O ffmpeg.tar.xz https://johnvansickle.com/ffmpeg/builds/ffmpeg-git-arm64-static.tar.xz\n");
        printf("(Command execution skipped to avoid unnecessary download)\n");
    } else {
        printf("wget is not available on this system\n");
        printf("Install wget to enable download functionality:\n");
        printf("  Ubuntu/Debian: sudo apt-get install wget\n");
        printf("  CentOS/RHEL: sudo yum install wget\n");
    }

    // Demonstrate other system commands
    printf("\nExecuting safe system commands:\n");
    safe_system_command("echo 'Hello from system command!'");
    safe_system_command("date");
    safe_system_command("uname -a");
#else
    printf("System command demonstration disabled\n");
#endif
}

/*============================================================================
 * MAIN FUNCTION
 *============================================================================*/

/**
 * @brief Main function combining all demonstrations
 */
int main(int argc, char **argv) {
    printf("================================================================\n");
    printf("    COMPREHENSIVE C PROGRAMMING DEMONSTRATION\n");
    printf("    Combining features from 5 generic C files\n");
    printf("================================================================\n");

    // Feature flags status
    printf("\nFeature flags status:\n");
    printf("  BASIC_FEATURES: %s\n", ENABLE_BASIC_FEATURES ? "ENABLED" : "DISABLED");
    printf("  BIT_OPERATIONS: %s\n", ENABLE_BIT_OPERATIONS ? "ENABLED" : "DISABLED");
    printf("  THREADING: %s\n", ENABLE_THREADING ? "ENABLED" : "DISABLED");
    printf("  ADVANCED_FEATURES: %s\n", ENABLE_ADVANCED_FEATURES ? "ENABLED" : "DISABLED");
    printf("  SYSTEM_COMMANDS: %s\n", ENABLE_SYSTEM_COMMANDS ? "ENABLED" : "DISABLED");
    printf("  DEBUG FLAGS: 0x%02X\n", DEBUG);

    // Run demonstrations
#if ENABLE_BASIC_FEATURES
    demonstrate_basic_features(argc, argv);
#endif

#if ENABLE_BIT_OPERATIONS
    demonstrate_bit_operations();
#endif

#if ENABLE_ADVANCED_FEATURES
    demonstrate_function_pointers();
    demonstrate_endianness();
    demonstrate_bit_fields();
    demonstrate_pointer_operations();
#endif

#if ENABLE_THREADING
    demonstrate_threading_simple();
    demonstrate_threading_mutex();
#endif

#if ENABLE_SYSTEM_COMMANDS
    demonstrate_system_commands();
#endif

    print_separator("DEMONSTRATION COMPLETED");
    printf("All enabled features have been demonstrated successfully.\n");
    printf("\nKey concepts covered:\n");
    printf("1. Command line argument processing\n");
    printf("2. Function pointers and arrays\n");
    printf("3. Bit manipulation operations\n");
    printf("4. Dynamic memory management\n");
    printf("5. Multi-threading with pthreads\n");
    printf("6. Mutex synchronization\n");
    printf("7. Conditional compilation\n");
    printf("8. System command execution\n");
    printf("9. Pointer operations and const correctness\n");
    printf("10. Bit fields and structures\n");
    printf("11. Endianness detection\n");
    printf("12. Advanced bit manipulation techniques\n");

    return EXIT_SUCCESS;
}
