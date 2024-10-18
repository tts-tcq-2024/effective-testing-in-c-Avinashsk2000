#include <stdio.h>
#include <assert.h>
#include <string.h>

// Function to format the color map entry
void formatColorMap(char* buffer, int index, const char* majorColor, const char* minorColor) {
    snprintf(buffer, 50, "%d | %s | %s", index, majorColor, minorColor);
}

int generateColorMap(char colorMap[25][50]) {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    
    // Generating the color map without printing
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            int index = i * 5 + j;
            formatColorMap(colorMap[index], index, majorColor[i], minorColor[i]);
        }
    }
    
    return i * j;
}

int main() {
    char colorMap[25][50];  // Array to hold the formatted color map entries
    int result = generateColorMap(colorMap);

    // Print the color map in the main function, if needed
    for (int i = 0; i < 25; i++) {
        printf("%s\n", colorMap[i]);  // Now the formatted strings are printed here
    }

    // Assert that the function returns the expected value
    assert(result == 25);

    printf("All is well (maybe!)\n");
    return 0;
}
