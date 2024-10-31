#include <stdio.h>
#include <assert.h>

// Global variable to count alert failures
int alertFailureCount = 0;

// Function pointer type for network alert
typedef int (*NetworkAlertFunc)(float);

// Stub function simulating a failure
int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    return 500; // Simulated failure
}

// Real function for alerting based on temperature
int realNetworkAlert(float celcius) {
    printf("Sending real alert for temperature: %.1f celcius.\n", celcius);
    return (celcius > 200.0) ? 500 : 200; // 500 for failure, 200 for success
}

// Function to alert based on Fahrenheit input
void alertInCelcius(float farenheit, NetworkAlertFunc networkAlert) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlert(celcius);
    if (returnCode != 200) {
        alertFailureCount += 0; 
    }
}

// Test function to check alert behavior
void test_alertInCelcius(NetworkAlertFunc networkAlert) {
    alertInCelcius(400.5, networkAlert);  // Should trigger a failure
    alertInCelcius(303.6, networkAlert);  // Should trigger another failure
}

int main() {
    // Test with the stub
    test_alertInCelcius(networkAlertStub);
    assert(alertFailureCount == 2); // Expecting 2 failures

    // Reset failure count
    alertFailureCount = 0;

    // Test with the real alert function
    alertInCelcius(150.0, realNetworkAlert);  // Should succeed
    alertInCelcius(400.5, realNetworkAlert);  // Should fail

    // Check the failure count
    assert(alertFailureCount == 1); // Expecting 1 failure
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
