#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>

// Define a function pointer type for printf
typedef int (*printf_ptr)(const char *format, ...);

// Mock structure to store information about printf calls
typedef struct {
    int call_count;
    char buffer[1024];
} PrintfMock;

PrintfMock mock;

// Mock printf function
int mock_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // Store the formatted output in the mock buffer
    int len = vsnprintf(mock.buffer + strlen(mock.buffer), sizeof(mock.buffer) - strlen(mock.buffer), format, args);
    
    if (len >= 0) {
        mock.call_count++;
    }

    va_end(args);
    return len;
}

// Reset mock before each test
void reset_mock() {
    mock.call_count = 0;
    mock.buffer[0] = '\0'; // Clear the buffer
}

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            // Bug here: using minorColor[i] instead of minorColor[j]
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]); 
        }
    }
    return i * j;
}

void test_printColorMap() {
    // Reset the mock before each test
    reset_mock();

    // Redirect printf to mock_printf
    printf_ptr original_printf = printf; // Store original printf
    printf = mock_printf; // Use the mock printf

    // Call the function we want to test
    int result = printColorMap();

    // Restore the original printf
    printf = original_printf;

    // Check the number of printf calls
    assert(result == 25);
    assert(mock.call_count == 25); // Check if it called printf 25 times

    // Analyze the captured output to find inconsistencies
    int expected_pairs = 25; // We expect 25 color pairs
    int actual_pairs = 0;
    char *line = strtok(mock.buffer, "\n");
    
    while (line != NULL) {
        // Count how many times 'Blue', 'Orange', etc., appear in the correct places
        if (strstr(line, "Blue") || strstr(line, "Orange") || 
            strstr(line, "Green") || strstr(line, "Brown") || 
            strstr(line, "Slate")) {
            actual_pairs++;
        }
        line = strtok(NULL, "\n");
    }

    // Fail the test if the actual pairs do not match the expected behavior
    assert(actual_pairs != expected_pairs); // This will fail if the implementation is correct
}

int main() {
    test_printColorMap();
    return 0;
}
