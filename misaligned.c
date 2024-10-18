#include <stdio.h>
#include <assert.h>
#include <string.h>

// Define a function pointer for the formatting function (to allow mocking)
typedef void (*FormatColorMapFunc)(char*, int, const char*, const char*);

// Original formatColorMap function
void realFormatColorMap(char* buffer, int index, const char* majorColor, const char* minorColor) {
    snprintf(buffer, 50, "%d | %s | %s", index, majorColor, minorColor);
}

// Function to generate the color map using a function pointer (can pass mock function for testing)
int generateColorMap(char colorMap[25][50], FormatColorMapFunc formatFunc) {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;

    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            int index = i * 5 + j;
            formatFunc(colorMap[index], index, majorColor[i], minorColor[j]);
        }
    }
    
    return i * j;
}

// Mock function to simulate the behavior of formatColorMap
int mockCallCount = 0;
int lastIndex = -1;
char lastMajorColor[10] = "";
char lastMinorColor[10] = "";

// Mock implementation of formatColorMap to track calls and parameters
void mockFormatColorMap(char* buffer, int index, const char* majorColor, const char* minorColor) {
    mockCallCount++;
    lastIndex = index;
    strcpy(lastMajorColor, majorColor);
    strcpy(lastMinorColor, minorColor);

    // Use the buffer to prevent the unused parameter warning
    buffer[0] = '\0';  // Just a dummy use
}

int main() {
    char colorMap[25][50];  // Array to hold the formatted color map entries

    // Use the mock function to test
    generateColorMap(colorMap, mockFormatColorMap);

    // Assertions to verify that the mock function was called correctly
    assert(mockCallCount == 25);  // Ensure that the mock was called 25 times (once for each combination)
    assert(lastIndex == 24);  // Check the last index passed to the mock function
    assert(strcmp(lastMajorColor, "Violet") == 0);  // Verify the last major color
    assert(strcmp(lastMinorColor, "Slate") == 0);  // Verify the last minor color

    printf("All tests passed! Mock function worked as expected.\n");
    return 0;
}
