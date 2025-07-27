/**
 * @file combined_hack_demo.c
 * @brief Combined demonstration of various C programming concepts and hacks
 * @author Development Team
 * @date Created: July 2025
 *
 * This file combines functionality from hack01.c, hack02.c, and hack03.c:
 * - Hexadecimal arithmetic and signed/unsigned operations (hack01.c)
 * - Mathematical series generation with alternating operations (hack02.c)
 * - Bit shifting operations and integer overflow behavior (hack03.c)
 *
 * Features demonstrated:
 * - Hexadecimal number handling and arithmetic
 * - User input with scanf
 * - Bit manipulation and shifting
 * - Integer overflow and underflow behavior
 * - Mathematical series generation
 * - Signed vs unsigned integer behavior
 * - Type casting and memory representation
 */

#include <stdio.h>
#include <stdint.h>
#include <limits.h>

/*============================================================================
 * FUNCTION PROTOTYPES
 *============================================================================*/

static void demonstrate_hex_arithmetic(void);
static void demonstrate_bit_operations(void);
static void demonstrate_series_generation(void);
static void generate_series(int n, int start);
static void interactive_input_demo(void);
static void demonstrate_overflow_behavior(void);
static void print_binary_representation(uint8_t value);

/*============================================================================
 * DEMONSTRATION FUNCTIONS
 *============================================================================*/

/**
 * @brief Demonstrates hexadecimal arithmetic operations (from hack01.c)
 * Shows signed arithmetic with hexadecimal constants and user input
 */
static void demonstrate_hex_arithmetic(void) {
    printf("=== HEXADECIMAL ARITHMETIC DEMONSTRATION ===\n");
    printf("Original hack01.c functionality\n\n");

    // Fixed values demonstration
    int a = 0x23;  // 35 in decimal
    int b = 0x33;  // 51 in decimal
    int c = a - b; // Should be -16

    printf("Fixed calculation:\n");
    printf("a = 0x%02X (%d decimal)\n", a, a);
    printf("b = 0x%02X (%d decimal)\n", b, b);
    printf("c = a - b = %d\n", c);
    printf("c in hex = 0x%X\n", c);

    printf("\n");
}

/**
 * @brief Demonstrates interactive input functionality
 * Allows user to input values and see the results
 */
static void interactive_input_demo(void) {
    printf("=== INTERACTIVE INPUT DEMONSTRATION ===\n");
    printf("Enter values to see hexadecimal arithmetic in action\n\n");

    int user_a, user_b;

    printf("Enter value of a (decimal): ");
    if (scanf("%d", &user_a) != 1) {
        printf("Invalid input for a, using default value 35\n");
        user_a = 35;
        // Clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("Enter value of b (decimal): ");
    if (scanf("%d", &user_b) != 1) {
        printf("Invalid input for b, using default value 51\n");
        user_b = 51;
        // Clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("\nResults:\n");
    printf("a = %d (0x%X)\n", user_a, user_a);
    printf("b = %d (0x%X)\n", user_b, user_b);
    printf("a - b = %d (0x%X)\n", user_a - user_b, user_a - user_b);
    printf("a + b = %d (0x%X)\n", user_a + user_b, user_a + user_b);
    printf("a * b = %d (0x%X)\n", user_a * user_b, user_a * user_b);

    printf("\n");
}

/**
 * @brief Demonstrates bit shifting and overflow behavior (from hack03.c)
 * Shows how bit operations work with different integer types
 */
static void demonstrate_bit_operations(void) {
    printf("=== BIT OPERATIONS AND OVERFLOW DEMONSTRATION ===\n");
    printf("Original hack03.c functionality\n\n");

    // Demonstrate bit shifting with uint8_t
    uint8_t i = 1;

    printf("Original bit shifting demonstration:\n");
    printf("i = %d (binary: ", i);
    print_binary_representation(i);
    printf(")\n");

    i = i << 8;  // This will overflow in uint8_t
    printf("After i << 8: i = %d (binary: ", i);
    print_binary_representation(i);
    printf(")\n");

    printf("Explanation: Shifting by 8 bits in an 8-bit type causes overflow\n");
    printf("The result is 0 because all bits are shifted out.\n\n");

    // Demonstrate signed arithmetic with specific values
    int8_t i1 = 0x23;  // 35 in decimal
    int8_t i2 = 0x33;  // 51 in decimal
    int8_t i3 = i1 - i2; // -16 in decimal

    printf("Signed 8-bit arithmetic:\n");
    printf("i1 = 0x%02X (%d)\n", i1, i1);
    printf("i2 = 0x%02X (%d)\n", i2, i2);
    printf("i3 = i1 - i2 = %d (0x%02X)\n", i3, *(uint8_t*)&i3);

    printf("Memory representation of i3: 0x%02X\n", *(uint8_t*)&i3);
    printf("Explanation: -16 in two's complement is 0xF0\n\n");
}

/**
 * @brief Print binary representation of an 8-bit value
 * @param value The value to print in binary
 */
static void print_binary_representation(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
}

/**
 * @brief Demonstrates mathematical series generation (from hack02.c)
 * Shows alternating operations to generate a number sequence
 */
static void demonstrate_series_generation(void) {
    printf("=== MATHEMATICAL SERIES GENERATION ===\n");
    printf("Original hack02.c functionality\n\n");

    printf("Generating series with 7 terms starting from 55:\n");
    printf("Algorithm: Alternates between subtracting 8 and multiplying by 2\n");
    printf("Series: ");
    generate_series(7, 55);
    printf("\n\n");

    // Demonstrate with different parameters
    printf("Generating series with 5 terms starting from 20:\n");
    printf("Series: ");
    generate_series(5, 20);
    printf("\n\n");

    printf("Generating series with 10 terms starting from 100:\n");
    printf("Series: ");
    generate_series(10, 100);
    printf("\n\n");
}

/**
 * @brief Generate a mathematical series with alternating operations
 * @param n Number of terms to generate
 * @param start Starting value for the series
 *
 * Algorithm:
 * - Print first term (start value)
 * - For odd iterations (i&1 == 1): subtract 8
 * - For even iterations (i&1 == 0): multiply by 2
 */
static void generate_series(int n, int start) {
    if (n <= 0) {
        printf("Invalid series length\n");
        return;
    }

    int i = 1;

    // Print first term
    printf("%d", start);

    // Generate remaining terms
    for (; n > 1; n--, i++) {
        if (i & 1) {  // Odd iteration
            start = start - 8;
        } else {      // Even iteration
            start = start * 2;
        }
        printf(", %d", start);
    }
}

/**
 * @brief Demonstrates various overflow and underflow behaviors
 * Shows what happens when operations exceed type limits
 */
static void demonstrate_overflow_behavior(void) {
    printf("=== INTEGER OVERFLOW/UNDERFLOW BEHAVIOR ===\n");
    printf("Demonstrating behavior at integer limits\n\n");

    // Demonstrate uint8_t overflow
    uint8_t max_uint8 = UINT8_MAX;
    printf("uint8_t overflow:\n");
    printf("UINT8_MAX = %d\n", max_uint8);
    printf("UINT8_MAX + 1 = %d (wraps to 0)\n", (uint8_t)(max_uint8 + 1));

    // Demonstrate int8_t overflow/underflow
    int8_t max_int8 = INT8_MAX;
    int8_t min_int8 = INT8_MIN;
    printf("\nint8_t overflow/underflow:\n");
    printf("INT8_MAX = %d\n", max_int8);
    printf("INT8_MAX + 1 = %d (wraps to %d)\n", (int8_t)(max_int8 + 1), (int8_t)(max_int8 + 1));
    printf("INT8_MIN = %d\n", min_int8);
    printf("INT8_MIN - 1 = %d (wraps to %d)\n", (int8_t)(min_int8 - 1), (int8_t)(min_int8 - 1));

    // Demonstrate bit shifting edge cases
    printf("\nBit shifting edge cases:\n");
    uint8_t shift_test = 1;
    for (int shift = 0; shift <= 8; shift++) {
        uint8_t result = shift_test << shift;
        printf("1 << %d = %d (binary: ", shift, result);
        print_binary_representation(result);
        printf(")\n");
    }

    printf("\n");
}

/*============================================================================
 * MAIN FUNCTION
 *============================================================================*/

/**
 * @brief Main function combining all hack demonstrations
 * @return 0 on successful execution
 */
int main(void) {
    printf("========================================================\n");
    printf("    COMBINED HACK DEMONSTRATIONS\n");
    printf("    Combining hack01.c, hack02.c, and hack03.c\n");
    printf("========================================================\n\n");

    // Demonstrate features from hack01.c
    demonstrate_hex_arithmetic();

    // Demonstrate features from hack03.c
    demonstrate_bit_operations();

    // Demonstrate features from hack02.c
    demonstrate_series_generation();

    // Additional demonstrations
    demonstrate_overflow_behavior();

    // Interactive portion (from hack01.c)
    interactive_input_demo();

    printf("========================================================\n");
    printf("    ALL DEMONSTRATIONS COMPLETED\n");
    printf("========================================================\n");
    printf("\nSummary of demonstrated concepts:\n");
    printf("1. Hexadecimal arithmetic and number representation\n");
    printf("2. Bit shifting operations and overflow behavior\n");
    printf("3. Mathematical series generation with alternating operations\n");
    printf("4. Signed vs unsigned integer behavior\n");
    printf("5. Integer overflow and underflow wrapping\n");
    printf("6. Memory representation of negative numbers\n");
    printf("7. Interactive user input handling\n");

    return 0;
}
