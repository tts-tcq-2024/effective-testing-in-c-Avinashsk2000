#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

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
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]); 
        }
    }
    return i * j;
}

void test_printColorMap(printf_ptr custom_printf) {
    // Use the mock printf function
    printf = custom_printf;

    // Reset output before each test
    reset_output();
    
    // Call the function we want to test
    int result = printColorMap();

    // Check the result
    assert(result == 25);

    // Output the captured output for inspection
    printf("%s", output);
}

int main() {
    test_printColorMap(mock_printf);
    printf("All is well (maybe!)\n");
    return 0;
}
