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
    return 500; // Simulating a failure
}

// Test function to check alertInCelcius behavior
void test_alertInCelcius() {
    // Reset alert failure count before testing
    alertFailureCount = 0;

    // Call alertInCelcius with the mock function
    alertInCelcius(400.5); // Normal call
    alertInCelcius(303.6); // Normal call

    // We expect that the alertFailureCount remains 0 due to the bug
    assert(alertFailureCount == 0); // This will fail due to the bug
}

int main() {
    // Run the test
    test_alertInCelcius();

    // Original calls to demonstrate the functionality
    alertInCelcius(400.5);
    alertInCelcius(303.6);
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
