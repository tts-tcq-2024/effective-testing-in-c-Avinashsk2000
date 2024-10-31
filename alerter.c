#include <stdio.h>
#include <assert.h>

// Global variable to count alert failures
int alertFailureCount = 0;

// Declare a function pointer type for network alert
typedef int (*NetworkAlertFunc)(float);

// Stub function for testing
int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Stub always returns 500 for failure (simulate alert failure)
    return 500;
}

// Real function for production (for demonstration purposes)
int realNetworkAlert(float celcius) {
    printf("Sending real alert for temperature: %.1f celcius.\n", celcius);
    // Return 200 for ok and 500 for failure
    return (celcius > 200.0) ? 500 : 200;
}

// Function to alert based on temperature, with injected network alert function
void alertInCelcius(float farenheit, NetworkAlertFunc networkAlert) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlert(celcius);
    if (returnCode != 200) {
        // Increment failure count on failure
        alertFailureCount += 1; // This is where the bug is
    }
}

int main() {
    // Test environment using the stub
    alertInCelcius(400.5, networkAlertStub);  // This should fail
    alertInCelcius(303.6, networkAlertStub);  // This should fail

    assert(alertFailureCount == 2); // Check that we correctly count failures

    alertInCelcius(150.0, realNetworkAlert);  // This should pass
    alertInCelcius(400.5, realNetworkAlert);  // This should fail

    assert(alertFailureCount == 3); // Validate the final count
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
