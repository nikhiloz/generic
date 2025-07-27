#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

// Function prototypes
void demonstrate_basic_operations(void);
void demonstrate_min_max_operations(void);
void demonstrate_arithmetic_operations(void);
void demonstrate_bit_checks(void);
void demonstrate_value_exchange(void);
void demonstrate_advanced_operations(void);

int main() {
    printf("=== Bit Manipulation Operations Demonstration ===\n\n");

    demonstrate_basic_operations();
    demonstrate_min_max_operations();
    demonstrate_arithmetic_operations();
    demonstrate_bit_checks();
    demonstrate_value_exchange();
    demonstrate_advanced_operations();

    return 0;
}

void demonstrate_basic_operations(void) {
    printf("1. BASIC OPERATIONS\n");
    printf("-------------------\n");

    // Get the maximum integer
    int maxInt1 = ~(1U << 31);
    int maxInt2 = INT_MAX;  // Use standard constant instead of overflow-prone expression

    printf("Maximum integer values:\n");
    printf("  ~(1U << 31) = %d\n", maxInt1);
    printf("  INT_MAX (standard) = %d\n", maxInt2);

    // Get the minimum integer
    int minInt1 = 1U << 31;  // Use unsigned literal to avoid overflow

    printf("\nMinimum integer values:\n");
    printf("  (int)(1U << 31) = %d\n", minInt1);
    printf("  INT_MIN (standard) = %d\n", INT_MIN);

    // Get the maximum long
    long maxLong = LONG_MAX;  // Use standard constant
    printf("\nMaximum long value:\n");
    printf("  LONG_MAX (standard) = %ld\n", maxLong);

    printf("\n");
}

void demonstrate_arithmetic_operations(void) {
    printf("2. ARITHMETIC OPERATIONS\n");
    printf("------------------------\n");

    int n = 42;
    int m = 3;

    // Multiply by 2
    printf("n = %d\n", n);
    printf("Multiply by 2: n << 1 = %d\n", n << 1);

    // Divide by 2
    printf("Divide by 2: n >> 1 = %d\n", n >> 1);

    // Multiply by m-th power of 2
    printf("Multiply by 2^%d: n << %d = %d\n", m, m, n << m);

    // Divide by m-th power of 2
    printf("Divide by 2^%d: n >> %d = %d\n", m, m, n >> m);

    // Calculate 2^n (for small n)
    int power = 5;
    printf("Calculate 2^%d: 2 << (%d-1) = %d\n", power, power, 2 << (power - 1));

    printf("\n");
}

void demonstrate_bit_checks(void) {
    printf("3. BIT CHECKS AND TESTS\n");
    printf("-----------------------\n");

    int n = 15;  // 1111 in binary

    // Check odd number
    printf("n = %d (binary: ", n);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf(")\n");
    printf("Is odd: (n & 1) == 1 = %s\n", ((n & 1) == 1) ? "true" : "false");

    // Check whether factorial of 2 (power of 2)
    printf("Is power of 2: n > 0 && (n & (n - 1)) == 0 = %s\n",
           (n > 0 && (n & (n - 1)) == 0) ? "true" : "false");

    // Test with actual power of 2
    int power_of_2 = 16;
    printf("Testing %d: Is power of 2 = %s\n", power_of_2,
           (power_of_2 > 0 && (power_of_2 & (power_of_2 - 1)) == 0) ? "true" : "false");

    // Get the m-th bit of n (from low to high)
    int bit_position = 3;
    printf("Get bit %d of %d: (n >> (%d-1)) & 1 = %d\n",
           bit_position, n, bit_position, (n >> (bit_position - 1)) & 1);

    // Set the m-th bit of n to 0
    int cleared = n & ~(1 << (bit_position - 1));
    printf("Clear bit %d of %d: n & ~(1 << (%d-1)) = %d\n",
           bit_position, n, bit_position, cleared);

    printf("\n");
}

void demonstrate_min_max_operations(void) {
    printf("4. MIN/MAX AND COMPARISON OPERATIONS\n");
    printf("------------------------------------\n");

    int a = 25, b = 17;

    // Get absolute value
    printf("a = %d\n", a);
    printf("Absolute value: (a ^ (a >> 31)) - (a >> 31) = %d\n",
           (a ^ (a >> 31)) - (a >> 31));

    int negative = -15;
    printf("negative = %d\n", negative);
    printf("Absolute value: (negative ^ (negative >> 31)) - (negative >> 31) = %d\n",
           (negative ^ (negative >> 31)) - (negative >> 31));

    // Get max of two values
    printf("\na = %d, b = %d\n", a, b);
    int max_val = (b & ((a - b) >> 31)) | (a & (~(a - b) >> 31));
    printf("Max of a and b: %d\n", max_val);

    // Get min of two values
    int min_val = (a & ((a - b) >> 31)) | (b & (~(a - b) >> 31));
    printf("Min of a and b: %d\n", min_val);

    // Check whether both have the same sign
    printf("Same sign: (a ^ b) >= 0 = %s\n", ((a ^ b) >= 0) ? "true" : "false");

    int negative_b = -17;
    printf("a = %d, negative_b = %d\n", a, negative_b);
    printf("Same sign: (a ^ negative_b) >= 0 = %s\n",
           ((a ^ negative_b) >= 0) ? "true" : "false");

    // Get the average
    printf("Average of %d and %d: (a + b) >> 1 = %d\n", a, b, (a + b) >> 1);
    printf("Alternative average: ((a ^ b) >> 1) + (a & b) = %d\n",
           ((a ^ b) >> 1) + (a & b));

    printf("\n");
}

void demonstrate_value_exchange(void) {
    printf("5. VALUE EXCHANGE\n");
    printf("-----------------\n");

    int x = 42, y = 24;
    printf("Before exchange: x = %d, y = %d\n", x, y);

    // XOR swap
    x ^= y;
    y ^= x;
    x ^= y;

    printf("After XOR exchange: x = %d, y = %d\n", x, y);

    // Conditional exchange using XOR
    int condition_met = 1;  // Simulate condition
    printf("\nConditional exchange demonstration:\n");
    printf("Before: x = %d, y = %d\n", x, y);

    if (condition_met) {
        x = x ^ y ^ x;  // This effectively sets x = y
        // Note: The original formula x = a ^ b ^ x assumes x starts as either a or b
    }
    printf("After conditional operation: x = %d\n", x);

    printf("\n");
}

void demonstrate_advanced_operations(void) {
    printf("6. ADVANCED OPERATIONS\n");
    printf("----------------------\n");

    int n = 15;

    // Increment and decrement tricks
    printf("n = %d\n", n);
    printf("n + 1 using -~n: %d\n", -~n);
    printf("n - 1 using ~-n: %d\n", ~-n);

    // Get the contrast number (two's complement negation)
    printf("Negate %d using ~n + 1: %d\n", n, ~n + 1);
    printf("Negate %d using (n ^ -1) + 1: %d\n", n, (n ^ -1) + 1);

    // Modulo 2^n against m
    int mod_value = 8;  // 2^3
    printf("Modulo %d against %d: m & (n - 1) = %d\n",
           n, mod_value, n & (mod_value - 1));

    // Additional useful bit operations
    printf("\nAdditional operations:\n");

    // Count set bits (population count)
    int count = 0;
    int temp = n;
    while (temp) {
        count += temp & 1;
        temp >>= 1;
    }
    printf("Number of set bits in %d: %d\n", n, count);

    // Check if number is even or odd using bitwise AND
    printf("Is %d even? %s\n", n, (n & 1) ? "No" : "Yes");

    // Swap nibbles in a byte
    uint8_t byte = 0xAB;  // 10101011
    uint8_t swapped = ((byte & 0x0F) << 4) | ((byte & 0xF0) >> 4);
    printf("Original byte: 0x%02X, Swapped nibbles: 0x%02X\n", byte, swapped);

    printf("\n");
}
