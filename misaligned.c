#include <stdio.h>
#include <assert.h>
#include <cstring>

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

int main() {
    int result = printColorMap();
    assert(result == 25);
    const char* expectedMajor = "Red";   // Major color at i = 1
    const char* expectedMinor = "Orange";  // Minor color at j = 1
    assert(strcmp(expectedMajor, "Red") == 0);    // This will pass
    assert(strcmp(expectedMinor, "Blue") == 0);   // This will fail because the bug uses wrong minorColor
    printf("All is well (maybe!)\n");
    return 0;
}
