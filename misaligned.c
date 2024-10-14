#include <stdio.h>
#include <assert.h>
#include <cstring>

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {

            for(j = 0; j < 5; j++) {
            // Add an assertion to check if the correct minor color is used
            assert(minorColor[j] != NULL);  // Ensure j indexes into minorColor properly
            
            // Check if major and minor colors form the correct pairs
            if (i == 1 && j == 1) {  // Expect Red and Orange at index 6
                assert(strcmp(majorColor[i], "Red") == 0);
                assert(strcmp(minorColor[j], "Orange") == 0);  // This will fail due to the bug
            }
                        
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]);
        }
    }
    return i * j;
}

int main() {
    int result = printColorMap();
    assert(result == 25);
    printf("All is well (maybe!)\n");
    return 0;
}
