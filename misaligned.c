#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef int (*printf_ptr)(const char *format, ...);

int mock_printf(const char *format, ...) {
    // Capture the output for testing purposes
    static char output[1024]; // Buffer for output
    va_list args;
    va_start(args, format);
    vsnprintf(output, sizeof(output), format, args);
    va_end(args);
    
    // Here, we could perform checks on `output`
    // For now, we'll just print it
    printf("%s", output);
    
    return strlen(output); // Returning the length of printed output
}

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[j]); // Fixed minorColor[i] to minorColor[j]
        }
    }
    return i * j;
}

void test_printColorMap(printf_ptr custom_printf) {
    int original_printf = printf;
    printf = custom_printf; // Use mock printf

    // Call the function we want to test
    int result = printColorMap();

    // Assert that the result is what we expect
    assert(result == 25);
    
    // Restore the original printf
    printf = original_printf;
}

int main() {
    test_printColorMap(mock_printf);
    return 0;
}
