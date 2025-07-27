# C Programming Examples and Demonstrations

This repository contains various C programming examples and demonstrations of core language features.

## Files Overview

### Source Files

1. **`hack03.c`** - Original simple demonstration program
2. **`bit_operations.c`** - Comprehensive bit manipulation operations based on arithmetic tricks
3. **`c_language_features_demo.c`** - Improved and well-documented version of the original generic.c
4. **`pthread_mutex_demo.c`** - Improved version of generic03.c with proper thread synchronization
5. **`system_command_demo.c`** - Improved version demonstrating system command execution
6. **`combined_hack_demo.c`** - Combined functionality from hack01.c, hack02.c, and hack03.c
7. **`comprehensive_c_demo.c`** - **NEW**: Combined functionality from all 5 generic files

### Key Improvements Made

#### From `generic.c` to `c_language_features_demo.c`:

**Structure and Organization:**
- Added comprehensive file header with documentation
- Organized code into logical sections with clear separators
- Added function prototypes and proper documentation
- Improved variable naming and code formatting

**Enhanced Features:**
- Fixed memory allocation bug (was allocating 1 byte instead of sizeof(int))
- Added proper error handling for memory allocation
- Improved command line argument processing with bounds checking
- Added more function pointer examples (addition, subtraction, multiplication)
- Enhanced bit manipulation with CHECK_BIT macro
- Improved endianness detection with union-based approach
- Added comprehensive bit field demonstration
- Enhanced string and pointer demonstrations
- Added proper memory cleanup

**Code Quality:**
- Used proper return type for main() function
- Added const correctness where appropriate
- Improved error handling and edge cases
- Added comprehensive comments and documentation
- Used standard library constants (EXIT_SUCCESS)
- Added safer macro definitions

#### New Comprehensive Demo (`comprehensive_c_demo.c`):

**Combines Five Original Files:**
- **generic.c**: Basic C features, function pointers, bit operations, memory management
- **generic01.c**: Advanced bit operations, conditional compilation, pointer operations
- **generic02.c**: Simple multi-threading with job simulation
- **generic03.c**: Advanced multi-threading with mutex synchronization
- **generic05.c**: System command execution (wget example)

**Enhanced Features:**
- **Conditional Compilation**: Use DEBUG flags to enable/disable features
- **Feature Toggle System**: Enable/disable entire demonstration sections
- **Comprehensive Threading**: Both simple and mutex-synchronized threading
- **Advanced Bit Operations**: XOR swaps, absolute values, power-of-2 detection
- **System Integration**: Safe system command execution with error handling
- **Memory Safety**: Proper allocation, error checking, and cleanup
- **Educational Structure**: Clear section separation and detailed explanations

## Building the Project

### Prerequisites
- GCC compiler
- Make utility
- Standard C library

### Build Commands

```bash
# Build all targets
make all

# Build individual targets
make gen_app           # Original hack03 program
make bit_demo          # Bit operations demonstration
make c_features_demo   # C language features demonstration
make pthread_demo      # Pthread mutex demonstration
make system_demo       # System command execution demonstration
make combined_hack     # Combined hack demonstrations
make comprehensive_demo # Comprehensive demo (all 5 files combined)

# Clean build artifacts
make clean

# Run all demonstrations
make test

# Show help
make help
make c_features_demo   # C language features demonstration

# Clean build artifacts
make clean

# Run all demonstrations
make test

# Show help
make help
```

### Compiler Flags Used
- `-Wall -Wextra`: Enable comprehensive warnings
- `-std=c99`: Use C99 standard
- `-O2`: Enable optimizations
- `-g`: Include debugging information

## Program Demonstrations

### `comprehensive_demo` - **MAIN COMBINED PROGRAM**
Combines and demonstrates all features from 5 original files:
- **Basic C Features**: Command line args, function pointers, memory management
- **Bit Operations**: Manipulation, XOR swaps, absolute values, power-of-2 detection
- **Threading**: Both simple job threading and mutex-synchronized threading
- **Advanced Features**: Conditional compilation, pointer operations, bit fields
- **System Integration**: Safe command execution, endianness detection
- **Configurable**: Use DEBUG flags and feature toggles to control demonstrations

### `combined_hack`
Combines and demonstrates:
- **Hexadecimal arithmetic**: Operations with hex constants and user input
- **Mathematical series**: Alternating subtract-8 and multiply-by-2 operations
- **Bit operations**: Shifting, overflow behavior, and binary representation
- **Integer types**: Signed vs unsigned behavior, overflow/underflow wrapping
- **Interactive input**: Safe user input handling with validation
- **Memory representation**: How negative numbers are stored in memory

### `c_features_demo`
Demonstrates:
- Command line argument processing
- Function pointers and arrays of function pointers
- Bit manipulation operations
- Dynamic memory allocation with proper cleanup
- Endianness detection
- Bit fields in structures
- Pointer operations and string handling
- Conditional expressions and short-circuit evaluation

### `bit_demo`
Demonstrates:
- Mathematical operations using bit manipulation
- Min/max operations without conditionals
- Power-of-2 arithmetic shortcuts
- Bit checking and manipulation techniques
- Value exchange using XOR
- Two's complement operations

## Usage Examples

### Running with command line arguments:
```bash
./c_features_demo arg1 arg2 arg3
```

### Expected Output:
The programs will display organized sections demonstrating each feature with clear explanations and examples.

## Memory Management

All programs properly manage memory:
- Dynamic allocations are paired with corresponding free() calls
- Pointers are set to NULL after deallocation
- Error checking is performed for allocation failures

## Compatibility

- Compatible with C99 and later standards
- Tested on Linux systems
- Should work on most POSIX-compliant systems
- Endianness detection works on both little-endian and big-endian systems

## Educational Value

These programs serve as educational examples for:
- C programming best practices
- Memory management techniques
- Bit manipulation operations
- Function pointer usage
- Structure and union usage
- Cross-platform programming considerations
