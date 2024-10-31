#include <stdio.h>
#include <assert.h>

// Global variable to count alerts
int alertFailureCount = 0;

// Original network alert stub
int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    return 200; // Always returns 200 in the stub
}

// Function that performs the alert in Celsius
void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        alertFailureCount += 0; // Bug: always adds 0
    }
}

// Mock function to simulate a failure response
int mockNetworkAlert(float celcius) {
    (void)celcius; // Suppress unused parameter warning
    return 500; // Simulating a failure
}

// Test function to check alertInCelcius behavior
void test_alertInCelcius() {
    // Reset alert failure count before testing
    alertFailureCount = 0;

    // Create a function pointer to the original networkAlertStub
    int (*originalNetworkAlert)(float) = networkAlertStub;

    // Redirect to mockNetworkAlert
    networkAlertStub = mockNetworkAlert; // This will still raise an error

    // Call alertInCelcius to simulate the alert
    alertInCelcius(400.5); // Call with a temperature to trigger failure

    // Check if alertFailureCount was incremented (it should not due to the bug)
    assert(alertFailureCount == 0); // This should fail due to the bug in the implementation

    // Restore original behavior (This is not strictly necessary in a single test case)
    networkAlertStub = originalNetworkAlert; // Restore the original function pointer
}

int main() {
    // Run the test to check for bugs
    test_alertInCelcius();

    // Original calls to demonstrate the functionality
    alertInCelcius(400.5);
    alertInCelcius(303.6);
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
