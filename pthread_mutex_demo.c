/**
 * @file pthread_mutex_demo.c
 * @brief Demonstration of pthread mutex synchronization and thread safety
 * @author Development Team
 * @date Created: July 2025
 *
 * This program demonstrates:
 * - Creating and managing POSIX threads (pthreads)
 * - Mutex synchronization to protect shared resources
 * - Function pointers with thread functions
 * - Thread synchronization with pthread_join
 * - Proper resource cleanup and error handling
 *
 * The program creates two threads that modify a shared counter variable:
 * - Thread 1: Increments the counter in a loop
 * - Thread 2: Decrements the counter in a loop
 * Both threads use mutex locks to ensure thread-safe access to the shared counter.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*============================================================================
 * CONSTANTS AND CONFIGURATION
 *============================================================================*/

/** Number of iterations for counter manipulation loops */
#define LOOP_ITERATIONS 0x1FFFFFF  // Reduced for better demonstration

/** Number of worker threads */
#define NUM_THREADS 2

/** Thread identifiers for better tracking */
typedef enum {
    THREAD_INCREMENT = 0,
    THREAD_DECREMENT = 1
} thread_id_t;

/*============================================================================
 * GLOBAL VARIABLES
 *============================================================================*/

/**
 * @brief Shared counter variable accessed by multiple threads
 * @note Protected by mutex lock to ensure thread safety
 */
static volatile long shared_counter = 0;

/**
 * @brief Mutex lock for protecting shared resources
 * @note Must be initialized before use and destroyed after use
 */
static pthread_mutex_t counter_mutex;

/**
 * @brief Flag to indicate if mutex was successfully initialized
 */
static int mutex_initialized = 0;

/*============================================================================
 * FUNCTION PROTOTYPES
 *============================================================================*/

typedef void *(*thread_function_t)(void *);

static void *increment_thread_function(void *arg);
static void *decrement_thread_function(void *arg);
static int initialize_mutex(void);
static void cleanup_resources(void);
static void print_thread_info(const char *thread_name, long counter_value);

/*============================================================================
 * THREAD FUNCTION IMPLEMENTATIONS
 *============================================================================*/

/**
 * @brief Thread function that increments the shared counter
 * @param arg Thread argument (unused in this implementation)
 * @return NULL on completion
 *
 * This function:
 * 1. Acquires the mutex lock
 * 2. Increments the counter once initially
 * 3. Performs a loop of increments
 * 4. Prints the final counter value
 * 5. Releases the mutex lock
 */
static void *increment_thread_function(void *arg) {
    (void)arg; // Suppress unused parameter warning

    const char *thread_name = "INCREMENT_THREAD";
    printf("[%s] Starting execution\n", thread_name);

    // Acquire mutex lock for thread-safe access
    int lock_result = pthread_mutex_lock(&counter_mutex);
    if (lock_result != 0) {
        fprintf(stderr, "[%s] Failed to acquire mutex: %s\n",
                thread_name, strerror(lock_result));
        return NULL;
    }

    printf("[%s] Acquired mutex lock\n", thread_name);
    print_thread_info(thread_name, shared_counter);

    // Initial increment
    shared_counter++;

    // Perform increment loop
    printf("[%s] Starting increment loop (%d iterations)\n",
           thread_name, LOOP_ITERATIONS);

    for (long i = 0; i < LOOP_ITERATIONS; i++) {
        shared_counter++;

        // Optional: Add a small delay every million iterations for demonstration
        if (i % 1000000 == 0 && i > 0) {
            printf("[%s] Progress: %ld/%d iterations\n",
                   thread_name, i, LOOP_ITERATIONS);
        }
    }

    printf("[%s] Completed increment loop\n", thread_name);
    print_thread_info(thread_name, shared_counter);

    // Release mutex lock
    int unlock_result = pthread_mutex_unlock(&counter_mutex);
    if (unlock_result != 0) {
        fprintf(stderr, "[%s] Failed to release mutex: %s\n",
                thread_name, strerror(unlock_result));
    } else {
        printf("[%s] Released mutex lock\n", thread_name);
    }

    printf("[%s] Execution completed\n", thread_name);
    return NULL;
}

/**
 * @brief Thread function that decrements the shared counter
 * @param arg Thread argument (unused in this implementation)
 * @return NULL on completion
 *
 * This function:
 * 1. Acquires the mutex lock
 * 2. Increments the counter once initially
 * 3. Performs a loop of decrements
 * 4. Prints the final counter value
 * 5. Releases the mutex lock
 */
static void *decrement_thread_function(void *arg) {
    (void)arg; // Suppress unused parameter warning

    const char *thread_name = "DECREMENT_THREAD";
    printf("[%s] Starting execution\n", thread_name);

    // Acquire mutex lock for thread-safe access
    int lock_result = pthread_mutex_lock(&counter_mutex);
    if (lock_result != 0) {
        fprintf(stderr, "[%s] Failed to acquire mutex: %s\n",
                thread_name, strerror(lock_result));
        return NULL;
    }

    printf("[%s] Acquired mutex lock\n", thread_name);
    print_thread_info(thread_name, shared_counter);

    // Initial increment (same as original behavior)
    shared_counter++;

    // Perform decrement loop
    printf("[%s] Starting decrement loop (%d iterations)\n",
           thread_name, LOOP_ITERATIONS);

    for (long i = 0; i < LOOP_ITERATIONS; i++) {
        shared_counter--;

        // Optional: Add a small delay every million iterations for demonstration
        if (i % 1000000 == 0 && i > 0) {
            printf("[%s] Progress: %ld/%d iterations\n",
                   thread_name, i, LOOP_ITERATIONS);
        }
    }

    printf("[%s] Completed decrement loop\n", thread_name);
    print_thread_info(thread_name, shared_counter);

    // Release mutex lock
    int unlock_result = pthread_mutex_unlock(&counter_mutex);
    if (unlock_result != 0) {
        fprintf(stderr, "[%s] Failed to release mutex: %s\n",
                thread_name, strerror(unlock_result));
    } else {
        printf("[%s] Released mutex lock\n", thread_name);
    }

    printf("[%s] Execution completed\n", thread_name);
    return NULL;
}

/*============================================================================
 * UTILITY FUNCTIONS
 *============================================================================*/

/**
 * @brief Initialize the mutex with error checking
 * @return 0 on success, non-zero on failure
 */
static int initialize_mutex(void) {
    int result = pthread_mutex_init(&counter_mutex, NULL);
    if (result != 0) {
        fprintf(stderr, "Mutex initialization failed: %s\n", strerror(result));
        return result;
    }

    mutex_initialized = 1;
    printf("Mutex initialized successfully\n");
    return 0;
}

/**
 * @brief Clean up allocated resources
 */
static void cleanup_resources(void) {
    if (mutex_initialized) {
        int result = pthread_mutex_destroy(&counter_mutex);
        if (result != 0) {
            fprintf(stderr, "Mutex destruction failed: %s\n", strerror(result));
        } else {
            printf("Mutex destroyed successfully\n");
        }
        mutex_initialized = 0;
    }
}

/**
 * @brief Print thread information with counter value
 * @param thread_name Name of the thread for identification
 * @param counter_value Current value of the counter
 */
static void print_thread_info(const char *thread_name, long counter_value) {
    printf("[%s] Current counter value: %ld\n", thread_name, counter_value);
}

/*============================================================================
 * MAIN FUNCTION
 *============================================================================*/

/**
 * @brief Main function - demonstrates pthread mutex synchronization
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE on error
 */
int main(void) {
    printf("=======================================================\n");
    printf("    PTHREAD MUTEX SYNCHRONIZATION DEMONSTRATION\n");
    printf("=======================================================\n\n");

    printf("Initial shared counter value: %ld\n", shared_counter);
    printf("Loop iterations per thread: %d\n", LOOP_ITERATIONS);
    printf("Number of threads: %d\n\n", NUM_THREADS);

    // Initialize mutex
    if (initialize_mutex() != 0) {
        fprintf(stderr, "Failed to initialize mutex. Exiting.\n");
        return EXIT_FAILURE;
    }

    // Array of thread function pointers
    thread_function_t thread_functions[] = {
        increment_thread_function,
        decrement_thread_function
    };

    const char *thread_names[] = {
        "INCREMENT_THREAD",
        "DECREMENT_THREAD"
    };

    // Array to store thread identifiers
    pthread_t thread_ids[NUM_THREADS];
    int thread_creation_success = 1;

    printf("Creating threads...\n");

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        int result = pthread_create(&thread_ids[i], NULL, thread_functions[i], NULL);
        if (result != 0) {
            fprintf(stderr, "Failed to create %s: %s\n",
                    thread_names[i], strerror(result));
            thread_creation_success = 0;
            break;
        } else {
            printf("Created %s successfully (ID: %lu)\n",
                   thread_names[i], (unsigned long)thread_ids[i]);
        }
    }

    if (!thread_creation_success) {
        fprintf(stderr, "Thread creation failed. Cleaning up...\n");
        cleanup_resources();
        return EXIT_FAILURE;
    }

    printf("\nWaiting for threads to complete...\n");

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        void *thread_return_value;
        int result = pthread_join(thread_ids[i], &thread_return_value);
        if (result != 0) {
            fprintf(stderr, "Failed to join %s: %s\n",
                    thread_names[i], strerror(result));
        } else {
            printf("%s joined successfully\n", thread_names[i]);
        }
    }

    printf("\n=======================================================\n");
    printf("    THREAD EXECUTION SUMMARY\n");
    printf("=======================================================\n");
    printf("Final shared counter value: %ld\n", shared_counter);
    printf("Expected value (if perfectly synchronized): 2\n");
    printf("(Each thread increments once initially, then one increments\n");
    printf(" and the other decrements the same number of times)\n");

    // Cleanup resources
    cleanup_resources();

    printf("\n=======================================================\n");
    printf("    DEMONSTRATION COMPLETED SUCCESSFULLY\n");
    printf("=======================================================\n");

    return EXIT_SUCCESS;
}
