#include <stdio.h>
#include <assert.h>

// Global variable to count alert failures
int alertFailureCount = 0;

// Declare a function pointer type for network alert
typedef int (*NetworkAlertFunc)(float);

// Stub function for testing
int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Stub simulates failure by returning 500
    return 500; // Simulate failure
}

// Real function for production (for demonstration purposes)
int realNetworkAlert(float celcius) {
    printf("Sending real alert for temperature: %.1f celcius.\n", celcius);
    // Return 200 for ok, return 500 for failure if the temperature exceeds 200.0
    return (celcius > 200.0) ? 500 : 200;
}

// Function to alert based on temperature, with injected network alert function
void alertInCelcius(float farenheit, NetworkAlertFunc networkAlert) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlert(celcius);
    if (returnCode != 200) {
        // Increment failure count on failure
        alertFailureCount += 1; // This is the bug in the original implementation
    }
}

void test_alertInCelcius(NetworkAlertFunc networkAlert) {
    alertInCelcius(400.5, networkAlert);  // This should trigger a failure
    alertInCelcius(303.6, networkAlert);  // This should also trigger a failure
}

int main() {
    // Test environment using the stub
    test_alertInCelcius(networkAlertStub);  // Use stub that always fails

    assert(alertFailureCount == 2); // Check the failure count for the stub

    // Reset the failure count for the next tests
    alertFailureCount = 0;

    // Test environment using the real network alert
    alertInCelcius(150.0, realNetworkAlert);  // This should pass
    alertInCelcius(400.5, realNetworkAlert);  // This should fail

    // Check that the failure count reflects the real network alert logic
    assert(alertFailureCount == 1); // Expecting 1 failure for the temperature over 200.0
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}

