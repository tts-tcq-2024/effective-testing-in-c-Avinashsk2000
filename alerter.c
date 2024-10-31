#include <stdio.h>
#include <assert.h>
#include <string.h>

// Global variables
int alertFailureCount = 0;

// Function pointer type for networkAlert
typedef int (*networkAlert_ptr)(float);

// Stub function to simulate the network alert
int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Stub always succeeds and returns 200
    return 200;
}

// Function to alert in Celsius
void alertInCelcius(float farenheit, networkAlert_ptr alertFunc) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = alertFunc(celcius);
    if (returnCode != 200) {
        // This code does not count failures correctly!
        alertFailureCount += 0; // The bug is here
    }
}

// Mock function to simulate a failure
int mockNetworkAlert(float celcius) {
    // Simulate a failure response
    return 500; // Non-ok response
}

// Test function to validate behavior
void test_alertInCelcius() {
    // Reset failure count before the test
    alertFailureCount = 0;

    // Call alertInCelcius with the mock function
    alertInCelcius(400.5, mockNetworkAlert);
    alertInCelcius(303.6, mockNetworkAlert);

    // The alertFailureCount should still be 0 due to the bug in the logic
    assert(alertFailureCount == 0); // This will fail if the bug is fixed incorrectly
}

int main() {
    // Run the test
    test_alertInCelcius();

    // Original calls to see the output
    alertInCelcius(400.5, networkAlertStub);
    alertInCelcius(303.6, networkAlertStub);
    printf("%d alerts failed.\n", alertFailureCount);
    return 0;
}
