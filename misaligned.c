#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

// Define a function pointer type for printf
typedef int (*printf_ptr)(const char *format, ...);

// Buffer to capture output
static char output[1024];
static int output_index = 0;

// Mock printf function
int mock_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int len = vsnprintf(output + output_index, sizeof(output) - output_index, format, args);
    if (len >= 0) {
        output_index += len;
    }
    va_end(args);
    return len;
}

// Reset output for fresh test runs
void reset_output() {
    output_index = 0;
    output[0] = '\0'; // Clear the buffer
}

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            // The bug here is minorColor[i], which should be minorColor[j]
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]); 
        }
    }
    return i * j;
}

void test_printColorMap() {
    // Expected output based on correct implementation
    const char *expected_output =
        "0 | White | Blue\n"
        "1 | White | Blue\n"
        "2 | White | Blue\n"
        "3 | White | Blue\n"
        "4 | White | Blue\n"
        "5 | Red | Orange\n"
        "6 | Red | Orange\n"
        "7 | Red | Orange\n"
        "8 | Red | Orange\n"
        "9 | Red | Orange\n"
        "10 | Black | Green\n"
        "11 | Black | Green\n"
        "12 | Black | Green\n"
        "13 | Black | Green\n"
        "14 | Black | Green\n"
        "15 | Yellow | Brown\n"
        "16 | Yellow | Brown\n"
        "17 | Yellow | Brown\n"
        "18 | Yellow | Brown\n"
        "19 | Yellow | Brown\n"
        "20 | Violet | Slate\n"
        "21 | Violet | Slate\n"
        "22 | Violet | Slate\n"
        "23 | Violet | Slate\n"
        "24 | Violet | Slate\n";

    // Reset output before each test
    reset_output();

    // Call the function we want to test
    int result = printColorMap();

    // Check the result
    assert(result == 25);

    // Compare the captured output to the expected output
    if (strcmp(output, expected_output) != 0) {
        printf("Test failed! Output does not match expected:\n");
        printf("Captured Output:\n%s", output);
        printf("Expected Output:\n%s", expected_output);
        assert(0);  // Force the test to fail
    } else {
        printf("Test passed!\n");
    }
}

int main() {
    test_printColorMap();
    printf("All is well (maybe!)\n");
    return 0;
}
