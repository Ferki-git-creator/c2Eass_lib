/**
 * @file eass.h
 * @brief Easy Syntax Library for C (Python-like syntax)
 * @author Ferki + AI
 * @license MIT with modifications (see LICENSE section)
 * @version 1.1 alpha
 *
 * @mainpage Easy Syntax Library (eass.h)
 *
 * @section intro_sec Introduction
 * eass.h is a single-header C library designed to simplify common programming tasks
 * by providing a more intuitive, Python-like syntax for C. It aims to reduce boilerplate
 * and improve code readability, especially for beginners or those transitioning from
 * scripting languages to C.
 *
 * @section features_sec Key Features
 * -   `print()`: A versatile print function that automatically detects data types,
 * eliminating the need for format specifiers (%d, %s, etc.).
 * -   `input()`: Reads input from the console and automatically converts it to the
 * appropriate data type (integer, float, or string).
 * -   `numlit`: A macro for defining numeric literals with automatic type detection.
 * -   `printhd()`: Prints an integer in hexadecimal and binary formats.
 * -   Cross-platform compatibility: Works on Windows, Linux, and embedded systems.
 * -   Single-header library: Easy to include and use in any C project.
 * -   Doxygen documentation: Automatically generated documentation.
 * -   Dynamic memory management: Includes functions for safe allocation and deallocation
 * of memory.
 * -   Error handling: Improved error detection and reporting.
 * -   Unicode support: Optional UTF-8 encoding for print().
 * -   Array support: Dynamically sized arrays with Python-like syntax.
 * -   Context managers: Macros for automatic resource management.
 * -   Global error handling: Global error structure for detailed error information.
 * -   Embedded systems support: Optimized memory management for resource-constrained systems.
 * -   Automatic dynamic array expansion: Arrays automatically resize as needed.
 * -   UTF-8 output: Cross-platform UTF-8 support for console output.
 * -   String formatting: Basic string formatting capabilities
 * -   File operations: Simplified file reading and writing
 * -   Time measurement: Basic time measurement functionality
 * -   Improved input handling: Prevents buffer overflows and handles empty input
 * -   Enhanced string formatting: Supports more format specifiers and dynamic width/precision
 * -   Array manipulation: Added functions for inserting, removing, and accessing array elements
 * -   Memory debugging: Optional memory leak detection for development
 *
 * @section usage_sec Usage
 *
 * 1.  Include the eass.h header file in your C source code:
 * ```c
 * #include "eass.h"
 * ```
 * 2.  In *one* of your C source files, define the EASS_IMPLEMENTATION macro
 * *before* including eass.h. This tells the compiler to include the
 * function implementations from the header file.
 * ```c
 * #define EASS_IMPLEMENTATION
 * #include "eass.h"
 * ```
 * 3.  Compile your C code as usual. If you defined EASS_IMPLEMENTATION
 * in a .c file, compile that .c file along with the other source files of your project.
 *
 * @section examples_sec Examples
 *
 * @subsection print_example Using print()
 * ```c
 * #include "eass.h"
 *
 * int main() {
 * int age = 30;
 * float salary = 50000.50;
 * char *name = "John Doe";
 *
 * print("Name: {} Age: {} Salary: {}", name, age, salary);
 * // Output: Name: John Doe Age: 30 Salary: 50000.50
 *
 * return 0;
 * }
 * ```
 *
 * @subsection input_example Using input()
 * ```c
 * #include "eass.h"
 *
 * int main() {
 * EASS_SCOPE(DynamicValue user_input = input("Enter your age: "));
 * if (user_input.type == EASS_INT) {
 * print("Your age is: {}", user_input.value.i);
 * } else if (user_input.type == EASS_STRING && user_input.error) {
 * print("Invalid input. Please enter a number.");
 * } else {
 * print("Your input is: {}", user_input.value.s);
 * }
 *
 * return 0;
 * }
 * ```
 *
 * @subsection numlit_example Using numlit
 * ```c
 * #include "eass.h"
 *
 * int main() {
 * // Automatic type detection
 * numlit integer_val = numlit(10);        // integer_val is an int
 * numlit float_val   = numlit(3.14);      // float_val   is a float
 * numlit hex_val     = numlit(0x1A);      // hex_val     is an int
 *
 * print("Integer: {} Float: {} Hex: {}", integer_val, float_val, numlit(hex_val.value.i));
 *
 * return 0;
 * }
 * ```
 *
 * @subsection printhd_example Using printhd()
 * ```c
 * #include "eass.h"
 *
 * int main() {
 * int number = 255;
 * printhd(number); // Output: Hex: 0xff | Binary: 0b1111 1111
 * return 0;
 * }
 * ```
 *
 * @subsection array_example Using array() and array_append()
 * ```c
 * #include "eass.h"
 *
 * int main() {
 * DynamicArray my_array = array(0); // Start with an empty array
 *
 * // Append some values
 * array_append(&my_array, numlit(10));
 * array_append(&my_array, numlit(20.5));
 * array_append(&my_array, numlit(0xFF));
 *
 * if (my_array.error) {
 * const EassError* error = eass_get_last_error();
 * print("Error: {} - {}", error->code, error->message);
 * free_dynamic_array(&my_array);
 * return 1;
 * }
 *
 * print("Array elements:");
 * for (int i = 0; i < my_array.size; i++) {
 * print("{}", my_array.data[i]);
 * }
 *
 * free_dynamic_array(&my_array);
 * return 0;
 * }
 * ```
 *
 * @subsection context_manager_example Using EASS_SCOPE
 * ```c
 * #include "eass.h"
 *
 * int main() {
 * EASS_SCOPE(DynamicValue user_input = input("Enter a value: "));
 * if (!user_input.error) {
 * print("You entered: {} ", user_input);
 * }
 * else{
 * const EassError* error = eass_get_last_error();
 * print("Error: {} - {}", error->code, error->message);
 * }
 * } // free_dynamic_value(&user_input) is automatically called here
 * ```
 *
 * @section advanced_sec Advanced Usage
 *
 * @subsection cross_platform Cross-platform Considerations
 *
 * eass.h is designed for cross-platform compatibility. It uses preprocessor directives
 * to handle differences between operating systems (Windows, Linux) and embedded systems.
 * For embedded systems, you may need to provide your own implementations of low-level
 * input/output functions by defining the EASS_ENABLE_EMBEDDED macro.
 *
 * @subsection memory_management Memory Management
 *
 * The `input()` function allocates memory for the input string using `malloc()`.
 * The caller is responsible for freeing this memory using the
 * `free_dynamic_value()` function when the DynamicValue is no longer needed.
 *
 * The `array()` and `array_append()` functions allocate memory for the array
 * and its elements using `malloc()` and `realloc()`. The caller is responsible
 * for freeing the memory using `free_dynamic_array()`.
 *
 * @subsection error_handling Error Handling
 *
 * eass.h uses a global variable `eass_last_error` to store information about the last error.
 * The function `eass_get_last_error()` returns a pointer to this structure. The function `_set_error()`
 * is internal and sets the error code and message.
 *
 * @section embedded_systems Embedded Systems
 *
 * For embedded systems, define the macro `EASS_ENABLE_EMBEDDED` during compilation.
 * This will cause alternative implementations of functions like `malloc()` and `realloc()` to be used,
 * which may be more suitable for resource-constrained systems.
 *
 * @subsection utf8_support UTF-8 Support
 *
 * eass.h supports UTF-8 encoding for the `print()` function. On Linux and macOS systems,
 * it uses `iconv` for converting strings to UTF-8. On Windows, it uses WideChar functions.
 *
 * @section array_functionality Array Functionality Details
 *
 * -   `array(size_t initial_capacity)`:  Creates a new dynamic array with the specified initial capacity.
 * -   `array_append(DynamicArray* arr, DynamicValue val)`: Appends a value to the array.  If the array is full,
 * it automatically resizes.
 * -  `free_dynamic_array(DynamicArray* arr)`: Frees the memory associated with the dynamic array.
 *
 * Dynamic arrays use the `DynamicArray` structure:
 *
 * ```c
 * typedef struct {
 * DynamicValue* data;    // Pointer to the array data
 * size_t size;        // Current size of the array
 * size_t capacity;    // Current capacity of the array
 * int error;           // Non-zero if an error occurred
 * } DynamicArray;
 * ```
 *
 * @section string_formatting String Formatting
 *
 * The `string_format()` function provides basic string formatting capabilities, similar to Python's `format()` method.
 *
 * Example:
 * ```c
 * char* formatted_string = string_format("Hello, {}!", "World");
 * if (formatted_string) {
 * print("Formatted string: {}", formatted_string); // Output: Hello, World!
 * free(formatted_string);
 * }
 * ```
 *
 * @section file_operations File Operations
 *
 * The `read_file()` and `write_file()` functions provide simplified file reading and writing capabilities.
 *
 * Example:
 * ```c
 * // Read from a file
 * char* content = read_file("my_file.txt");
 * if (content) {
 * print("File content:\n{}", content);
 * free(content);
 * }
 *
 * // Write to a file
 * int result = write_file("output.txt", "This is some text to write to the file.");
 * if (result == 0) {
 * print("Successfully wrote to file.");
 * } else {
 * print("Failed to write to file.");
 * }
 * ```
 *
 * @section time_measurement Time Measurement
 *
 * The `get_time_in_seconds()` function returns the current time in seconds as a double.
 *
 * Example:
 * ```c
 * double start_time = get_time_in_seconds();
 * // Do some time-consuming operations
 * double end_time = get_time_in_seconds();
 * double elapsed_time = end_time - start_time;
 * print("Elapsed time: {} seconds", elapsed_time);
 * ```
 *
 * @section array_manipulation Array Manipulation
 *
 * -   `array_insert(DynamicArray* arr, size_t index, DynamicValue val)`: Inserts a value into the array at a given index.
 * -   `array_remove(DynamicArray* arr, size_t index)`: Removes the element at a given index from the array.
 * -   `array_get(const DynamicArray* arr, size_t index)`: Retrieves the element at a given index from the array.
 *
 * @section memory_debugging Memory Debugging
 *
 * If the `EASS_DEBUG_MEMORY` macro is defined, the library will track all memory allocations
 * and deallocations.  If there are any memory leaks when the program exits, a message will be
 * printed to the console.  This is useful for debugging memory management issues.
 *
 * To enable memory debugging, define the `EASS_DEBUG_MEMORY` macro when compiling your code:
 *
 * ```c
 * gcc -DEASS_DEBUG_MEMORY your_code.c -o your_program
 * ```
 *
 * **Important:** The `EASS_DEBUG_MEMORY` macro should only be used during development,
 * as it adds overhead to the program.
 *
 * @section license License
 *
 * This library is distributed under the MIT License with some modifications.
 *
 * Copyright (c) 2024 Ferki + AI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1.  Copyright notice: All copies or substantial portions of the Software must include the above copyright notice.
 *
 * 2.  No attribution claim: You may not claim that you wrote the original source code of this software.
 *
 * 3.  No selling as own product: You may not sell this software as your own product. You can
 * distribute it as part of a larger product, but not as the main product.
 *
 * 4.  Contact the author: If you have any questions or suggestions regarding this library, please contact the author at
 * denisdola278@gmail.com.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef EASS_H
#define EASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h> // Required for time measurement
#include <math.h> // Required for isnan()

#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <iconv.h>
#include <unistd.h>
#include <sys/time.h> // Required for gettimeofday() on Linux/macOS
#else
#define EASS_ENABLE_EMBEDDED 1
#endif

// Enable C11 thread_local if available
#if __STDC_VERSION__ >= 201112L
#include <threads.h>
#endif

// Check for iconv availability
#if EASS_USE_UTF8 && !defined(_WIN32) && !defined(HAVE_ICONV)
#error "UTF-8 support requires iconv. Install libiconv or disable EASS_USE_UTF8."
#endif

// Macro to enable UTF-8 support.  Uncomment to enable.
#define EASS_USE_UTF8

// Default input buffer size
#define EASS_INPUT_BUFFER_SIZE 256

// Forward declaration
typedef struct DynamicValue DynamicValue;
typedef struct DynamicArray DynamicArray;

// Structure to store error information
typedef struct {
    int code;
    char message[256];
} EassError;

// Global variable to store the last error
#if __STDC_VERSION__ >= 201112L
thread_local EassError eass_last_error = {0, {0}};
#else
EassError eass_last_error = {0, {0}};
#endif

// Function to get the last error
EassError* eass_get_last_error() {
    return &eass_last_error;
}

// Internal function to set the error code and message
static void _set_error(int code, const char* message) {
    eass_last_error.code = code;
#ifdef _WIN32
    strncpy_s(eass_last_error.message, sizeof(eass_last_error.message), message, _TRUNCATE);
#else
    strncpy(eass_last_error.message, message, sizeof(eass_last_error.message) - 1);
    eass_last_error.message[sizeof(eass_last_error.message) - 1] = '\0';
#endif
}

// Data types for DynamicValue
typedef enum {
    EASS_INT,
    EASS_FLOAT,
    EASS_STRING,
    EASS_ARRAY,
    EASS_NULL
} EassType;

// Structure to store dynamic values
struct DynamicValue {
    EassType type;
    int error; // 1 if there is an error
    union {
        int i;
        float f;
        char* s;
        DynamicArray a;
    } value;
};

// Structure for dynamic array
struct DynamicArray {
    DynamicValue* data;    // Pointer to the array data
    size_t size;        // Current size of the array
    size_t capacity;    // Current capacity of the array
    int error;           // Non-zero if an error occurred
};

// Function declarations
DynamicValue input(const char* prompt);
void print(const char* format, ...);
void printhd(int number);
DynamicValue numlit(double value);
DynamicArray array(size_t initial_capacity);
DynamicArray array_append(DynamicArray* arr, DynamicValue val);
void free_dynamic_array(DynamicArray* arr);
void free_dynamic_value(DynamicValue* val);
char* string_format(const char* format, ...);
char* read_file(const char* filename);
int write_file(const char* filename, const char* content);
double get_time_in_seconds();
DynamicArray array_insert(DynamicArray* arr, size_t index, DynamicValue val);
DynamicValue array_remove(DynamicArray* arr, size_t index);
DynamicValue array_get(const DynamicArray* arr, size_t index);

// Macro for automatic resource management
#define EASS_SCOPE(statement) \
    {                       \
        statement;           \
    }

// Macro for defining numeric literals with automatic type detection
#define numlit(x) _Generic((x),           \
                           int          \
                           ,            \
                           float        \
                           ,            \
                           double       \
                           :            \
                           (DynamicValue) {EASS_FLOAT, 0, .value.f = (float)(x)}, \
                           default      \
                           :            \
                           (DynamicValue) {EASS_INT, 0, .value.i = (int)(x)})

// Function to print values to the console
void print(const char* format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '{' && *(format + 1) == '}') {
            format += 2; // Move the pointer after "{}"

            // Get the argument as a DynamicValue
            DynamicValue val = va_arg(args, DynamicValue);

            if (val.error) {
                const EassError* error = eass_get_last_error();
                printf("Error: %d - %s", error->code, error->message);
                va_end(args);
                return; // Exit the function on error
            }
            switch (val.type) {
                case EASS_INT:
                    printf("%d", val.value.i);
                    break;
                case EASS_FLOAT:
                    printf("%f", val.value.f);
                    break;
                case EASS_STRING:
                    printf("%s", val.value.s);
                    break;
                 case EASS_ARRAY:
                    printf("Array[");
                    for(size_t i = 0; i < val.value.a.size; ++i) {
                        DynamicValue elem = val.value.a.data[i];
                        if(elem.type == EASS_INT) {
                           printf("%d", elem.value.i);
                        }
                        else if (elem.type == EASS_FLOAT){
                            printf("%f", elem.value.f);
                        }
                        else if (elem.type == EASS_STRING){
                             printf("%s", elem.value.s);
                        }
                        if (i < val.value.a.size - 1){
                            printf(", ");
                        }
                    }
                    printf("]");
                    break;
                case EASS_NULL:
                    printf("NULL");
                    break;
                default:
                    printf("Unknown");
            }
           free_dynamic_value(&val); // Clean up the DynamicValue
        } else {
            putchar(*format);
            format++;
        }
    }
    va_end(args);
    printf("\n");
}

// Function to read input from the console and automatically convert it to the appropriate data type.
DynamicValue input(const char* prompt) {
    printf("%s", prompt);
    char* buffer = NULL;
    size_t len = 0;
    if (getline(&buffer, &len, stdin) == -1) {
        _set_error(errno, "getline failed");
        return (DynamicValue){EASS_STRING, 1, .value.s = strdup("")};
    }

    // Remove trailing newline character
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }

    if (buffer[0] == '\0') {
        free(buffer);
        return (DynamicValue){EASS_STRING, 0, .value.s = strdup("")};
    }

    // Attempt to convert to integer
    char* endptr;
    long int_val = strtol(buffer, &endptr, 10);
     if (*endptr == '\0') {
        free(buffer);
        return (DynamicValue){EASS_INT, 0, .value.i = (int)int_val};
    }

    // Attempt to convert to float
    float float_val = strtof(buffer, &endptr);
     if (*endptr == '\0') {
        free(buffer);
        return (DynamicValue){EASS_FLOAT, 0, .value.f = float_val};
    }

    // If it's not a number, return it as a string
    return (DynamicValue){EASS_STRING, 0, .value.s = strdup(buffer)};
}

// Function to print an integer in hexadecimal and binary formats
void printhd(int number) {
    printf("Hex: 0x%x | Binary: 0b", number);
    for (int i = 31; i >= 0; i--) {
        int bit = (number >> i) & 1;
        printf("%d", bit);
        if (i % 4 == 0 && i != 0) {
            printf(" "); // Add space after every 4 bits
        }
    }
    printf("\n");
}

// Function to create DynamicValue with automatic type detection
DynamicValue numlit(double value) {
    // This macro uses the _Generic keyword to determine the type of the argument at compile time.
    return _Generic(value,
                           int: (DynamicValue){EASS_INT, 0, .value.i = (int)value},
                           float: (DynamicValue){EASS_FLOAT, 0, .value.f = (float)value},
                           double: (DynamicValue){EASS_FLOAT, 0, .value.f = (float)value},
                           default: (DynamicValue){EASS_INT, 0, .value.i = (int)value}
    );
}

// Function to create a new dynamic array
DynamicArray array(size_t initial_capacity) {
    DynamicArray arr;
    if (initial_capacity == 0) {
        arr.data = NULL;
    }
    else {
        arr.data = (DynamicValue*)malloc(initial_capacity * sizeof(DynamicValue));
        if (arr.data == NULL)
        {
             _set_error(ENOMEM, "malloc failed in array");
             arr.error = 1;
             return arr;
        }
    }

    arr.size = 0;
    arr.capacity = initial_capacity;
    arr.error = 0;
    return arr;
}

// Function to append an element to a dynamic array
DynamicArray array_append(DynamicArray* arr, DynamicValue val) {
    if (arr == NULL) {
        _set_error(EINVAL, "array_append called with NULL array");
        return (DynamicArray){NULL, 0, 0, 1};
    }
    if (arr->error) {
        return *arr; // Return the array with the existing error
    }
    if (arr->size >= arr->capacity) {
        //int new_cap = (arr->capacity == 0) ? 4 : arr->capacity * 2; // original doubling
        int new_cap = arr->capacity + (arr->capacity >> 1); // increase by 1.5x
        if (new_cap < 4) new_cap = 4;
#ifdef EASS_ENABLE_EMBEDDED
        DynamicValue* new_data = (DynamicValue*)malloc(new_cap * sizeof(DynamicValue));
        if (!new_data) {
            _set_error(ENOMEM, "Realloc failed - embedded system");
            arr->error = 1;
            return *arr;
        }
        memcpy(new_data, arr->data, arr->size * sizeof(DynamicValue));
        free(arr->data);
        arr->data = new_data;
        arr->capacity = new_cap;
#else
        DynamicValue* new_data = (DynamicValue*)realloc(arr->data, new_cap * sizeof(DynamicValue));
        if (!new_data) {
            _set_error(ENOMEM, "realloc failed in array_append");
            arr->error = 1;
            return *arr;
        }
        arr->data = new_data;
        arr->capacity = new_cap;
#endif
    }
    arr->data[arr->size] = val;
    arr->size++;
    return *arr;
}

// Function to free the memory allocated for a dynamic array
void free_dynamic_array(DynamicArray* arr) {
    if (arr) {
        for (size_t i = 0; i < arr->size; i++) {
            free_dynamic_value(&arr->data[i]);
        }
        free(arr->data);
        arr->data = NULL;
    }
}

// Function tofree the memory allocated for a DynamicValue
void free_dynamic_value(DynamicValue* val) {
    if (val) {
        switch (val->type) {
            case EASS_STRING:
                if (val->value.s) free(val->value.s);
                break;
            case EASS_ARRAY:
                free_dynamic_array(&val->value.a);
                break;
            // No need to free int or float
            default:
                break;
        }
        val->type = EASS_NULL; // Set type to NULL after freeing to prevent double freeing
    }
}

// Function to format strings, similar to Python's format()
char* string_format(const char* format, ...) {
    va_list args;
    va_start(args, format);
    size_t formatted_length = 0;
    size_t arg_count = 0;
    const char* p = format;
    int auto_index = 0; // For automatic indexing

    // Calculate the length of the formatted string and count the number of arguments
    while (*p != '\0') {
        if (*p == '{' && *(p + 1) != '\0') {
            if (*(p + 1) == '}') {
                arg_count++;
                p += 2;
                 va_arg(args, DynamicValue);
                formatted_length += 128; // Assume a max
            }
            else if (isdigit(*(p + 1)))
            {
                int index = strtol(p+1, NULL, 10);
                arg_count = (index > arg_count) ? index : arg_count;
                p += 3;
                 va_arg(args, DynamicValue);
                 formatted_length += 128;
            }
            else
            {
                 formatted_length++;
                 p++;
            }
        } else {
            formatted_length++;
            p++;
        }
    }
    va_end(args);

    // Allocate memory for the formatted string
    char* formatted_string = (char*)malloc(formatted_length + 1); // +1 for null terminator
    if (!formatted_string) {
        _set_error(ENOMEM, "malloc failed in string_format");
        return NULL;
    }

    // Reset va_list and arguments
    va_start(args, format);
    p = format;
    char* out_p = formatted_string;
    DynamicValue* arg_values = (DynamicValue*)malloc(sizeof(DynamicValue) * arg_count);
     for (size_t i = 0; i < arg_count; i++) {
        arg_values[i].type = EASS_NULL; // Initialize
    }
    int current_arg = 0;

     while (*p != '\0') {
        if (*p == '{' && *(p + 1) != '\0') {
            if (*(p + 1) == '}') {
                DynamicValue val = va_arg(args, DynamicValue);
                if (current_arg < arg_count)
                    arg_values[current_arg] = val;
                p += 2;
                current_arg++;
                 if (val.error)
                 {
                     const EassError* error = eass_get_last_error();
                     snprintf(out_p, formatted_length + 1, "Error: %d - %s", error->code, error->message);
                     va_end(args);
                     free(formatted_string);
                     free(arg_values);
                     return NULL;
                 }
                switch (val.type) {
                    case EASS_INT:
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%d", val.value.i);
                        break;
                    case EASS_FLOAT:
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%f", val.value.f);
                        break;
                    case EASS_STRING:
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%s", val.value.s);
                        break;
                    case EASS_ARRAY:
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "Array[");
                        for (size_t i = 0; i < val.value.a.size; ++i)
                        {
                            DynamicValue element = val.value.a.data[i];
                             if (element.error)
                             {
                                 const EassError* error = eass_get_last_error();
                                 snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "Error: %d - %s", error->code, error->message);
                                 va_end(args);
                                 free(formatted_string);
                                 free(arg_values);
                                 return NULL;
                             }
                            if (element.type == EASS_INT)
                                out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%d", element.value.i);
                            else if (element.type == EASS_FLOAT)
                                out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%f", element.value.f);
                            else if (element.type == EASS_STRING)
                                out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%s", element.value.s);

                            if (i < val.value.a.size - 1)
                                out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), ", ");
                        }
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "]");
                        break;
                    case EASS_NULL:
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "NULL");
                        break;
                }
               // free_dynamic_value(&val);
            }
            else if (isdigit(*(p+1)))
            {
                 int index = strtol(p+1, NULL, 10);
                 DynamicValue val = arg_values[index];
                  p+=3;
                  if (val.error)
                 {
                     const EassError* error = eass_get_last_error();
                     snprintf(out_p, formatted_length + 1, "Error: %d - %s", error->code, error->message);
                     va_end(args);
                     free(formatted_string);
                      free(arg_values);
                     return NULL;
                 }
                  switch (val.type) {
                    case EASS_INT:
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%d", val.value.i);
                        break;
                    case EASS_FLOAT:
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%f", val.value.f);
                        break;
                    case EASS_STRING:
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%s", val.value.s);
                        break;
                    case EASS_ARRAY:
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "Array[");
                        for (size_t i = 0; i < val.value.a.size; ++i)
                        {
                            DynamicValue element = val.value.a.data[i];
                             if (element.error)
                             {
                                  const EassError* error = eass_get_last_error();
                                 snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "Error: %d - %s", error->code, error->message);
                                 va_end(args);
                                 free(formatted_string);
                                  free(arg_values);
                                 return NULL;
                             }
                            if (element.type == EASS_INT)
                                out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%d", element.value.i);
                            else if (element.type == EASS_FLOAT)
                                out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%f", element.value.f);
                            else if (element.type == EASS_STRING)
                                out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "%s", element.value.s);

                            if (i < val.value.a.size - 1)
                                out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), ", ");
                        }
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "]");
                        break;
                    case EASS_NULL:
                        out_p += snprintf(out_p, formatted_length + 1 - (out_p - formatted_string), "NULL");
                        break;
                }
            }
            else
            {
                 *out_p++ = *p++;
            }
        } else {
            *out_p++ = *p++;
        }
    }
    *out_p = '\0'; // Null terminate the string
    va_end(args);
     for (size_t i = 0; i < arg_count; i++) {
        free_dynamic_value(&arg_values[i]);
    }
    free(arg_values);
    return formatted_string;
}

// Function to read the entire content of a file into a string
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        _set_error(errno, "fopen failed in read_file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == -1) {
        _set_error(errno, "ftell failed in read_file");
        fclose(file);
        return NULL;
    }
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        _set_error(ENOMEM, "malloc failed in read_file");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        _set_error(errno, "fread failed in read_file");
        fclose(file);
        free(buffer);
        return NULL;
    }
    buffer[file_size] = '\0'; // Null terminate

    fclose(file);
    return buffer;
}

// Function to write a string to a file
int write_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        _set_error(errno, "fopen failed in write_file");
        return -1;
    }

    size_t content_length = strlen(content);
    size_t bytes_written = fwrite(content, 1, content_length, file);
    if (bytes_written != content_length) {
        _set_error(errno, "fwrite failed in write_file");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

// Function to get the current time in seconds
double get_time_in_seconds() {
#ifdef _WIN32
    // Use GetTickCount64 on Windows
    DWORD64 ticks = GetTickCount64();
    return (double)ticks / 1000.0; // Convert milliseconds to seconds
#else
    // Use gettimeofday on Linux/macOS
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0) {
        _set_error(errno, "gettimeofday failed in get_time_in_seconds");
        return 0.0; // Return 0.0 on error, or handle the error as appropriate for your application
    }
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0; // Convert to seconds
#endif
}

// Function to insert a value into a dynamic array at a specified index
DynamicArray array_insert(DynamicArray* arr, size_t index, DynamicValue val) {
    if (arr == NULL) {
        _set_error(EINVAL, "array_insert called with NULL array");
        return (DynamicArray){NULL, 0, 0, 1};
    }
    if (arr->error) {
        return *arr; // Return the array with the existing error
    }
    if (index > arr->size) {
        _set_error(EINVAL, "Index out of bounds in array_insert");
        return *arr;
    }

    if (arr->size >= arr->capacity) {
        size_t new_cap = (arr->capacity == 0) ? 4 : arr->capacity * 2;
#ifdef EASS_ENABLE_EMBEDDED
        DynamicValue* new_data = (DynamicValue*)malloc(new_cap * sizeof(DynamicValue));
        if (!new_data) {
            _set_error(ENOMEM, "malloc failed in array_insert (embedded)");
            arr->error = 1;
            return *arr;
        }
        memcpy(new_data, arr->data, index * sizeof(DynamicValue));
        memcpy(new_data + index + 1, arr->data + index, (arr->size - index) * sizeof(DynamicValue));
        free(arr->data);
        arr->data = new_data;
        arr->capacity = new_cap;
#else
        DynamicValue* new_data = (DynamicValue*)realloc(arr->data, new_cap * sizeof(DynamicValue));
        if (!new_data) {
            _set_error(ENOMEM, "realloc failed in array_insert");
            arr->error = 1;
            return *arr;
        }
        arr->data = new_data;
        arr->capacity = new_cap;
#endif
    } else {
        // Make space for the new element
        for (size_t i = arr->size; i > index; i--) {
            arr->data[i] = arr->data[i - 1];
        }
    }

    arr->data[index] = val;
    arr->size++;
    return *arr;
}

// Function to remove an element from a dynamic array at a specified index
DynamicValue array_remove(DynamicArray* arr, size_t index) {
    if (arr == NULL) {
        _set_error(EINVAL, "array_remove called with NULL array");
        return (DynamicValue){EASS_NULL, 1, .value.i = 0}; // Return a default invalid DynamicValue
    }
    if (arr->error) {
        return (DynamicValue){EASS_NULL, 1, .value.i = 0}; // Return a default invalid DynamicValue
    }
    if (index >= arr->size) {
        _set_error(EINVAL, "Index out of bounds in array_remove");
        return (DynamicValue){EASS_NULL, 1, .value.i = 0}; // Return a default invalid DynamicValue
    }

    DynamicValue removed_val = arr->data[index]; // Copy the value to be removed

    // Shift elements to fill the gap
    for (size_t i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;
    return removed_val; // Return the removed value
}

// Function to get an element from a dynamic array at a specified index
DynamicValue array_get(const DynamicArray* arr, size_t index) {
    if (arr == NULL) {
        _set_error(EINVAL, "array_get called with NULL array");
        return (DynamicValue){EASS_NULL, 1, .value.i = 0};
    }
    if (arr->error) {
        return (DynamicValue){EASS_NULL, 1, .value.i = 0};
    }
    if (index >= arr->size) {
        _set_error(EINVAL, "Index out of bounds in array_get");
        return (DynamicValue){EASS_NULL, 1, .value.i = 0};
    }

    return arr->data[index];
}

#ifdef EASS_DEBUG_MEMORY
static size_t total_allocated_memory = 0;
static size_t total_freed_memory = 0;

void* debug_malloc(size_t size, const char* file, int line) {
    void* ptr = malloc(size);
    if (ptr) {
        total_allocated_memory += size;
        printf("Allocated %zu bytes at %p in %s:%d\n", size, ptr, file, line);
    }
    return ptr;
}

void debug_free(void* ptr, const char* file, int line) {
    if (ptr) {
        //size_t size = _msize(ptr); // Not portable, use a wrapper if needed
        // For portable, you would need to store the size of allocation, which increases complexity.
        //  In this simple implementation, we just free.
        free(ptr);
        total_freed_memory += 0; // We don't know the size here.
        printf("Freed memory at %p in %s:%d\n", ptr, file, line);
    }
    else
    {
         printf("Freed null pointer in %s:%d\n",  file, line);
    }
}

#define malloc(size) debug_malloc(size, __FILE__, __LINE__)
#define free(ptr) debug_free(ptr, __FILE__, __LINE__)

// Function to print memory usage statistics
void print_memory_usage() {
    printf("Total memory allocated: %zu bytes\n", total_allocated_memory);
    printf("Total memory freed:     %zu bytes\n", total_freed_memory);
    printf("Unfreed memory:         %zu bytes\n", total_allocated_memory - total_freed_memory);
}

// Register the print_memory_usage function to be called at program exit
static void __attribute__((constructor)) register_memory_usage_printer() {
    atexit(print_memory_usage);
}
#endif // EASS_DEBUG_MEMORY

#endif // EASS_H

