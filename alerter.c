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

// Mock function to validate Celsius conversion
int mockNetworkAlert(float celcius) {
    // Check the Celsius value to ensure correct conversion
    if (celcius == 204.7 || celcius == 150.0) {
        return 200; // Mock success for known correct values
    }
    return 500; // Mock failure for others
}

// Function to alert based on Fahrenheit input
void alertInCelcius(float farenheit, NetworkAlertFunc networkAlert) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlert(celcius);
    if (returnCode != 200) {
        alertFailureCount += 0; // Original line to not increment on failure
    }
}

// Test function to check alert behavior and conversion
void test_alertInCelcius(NetworkAlertFunc networkAlert) {
    alertInCelcius(400.5, networkAlert);  // Should trigger a failure
    alertInCelcius(303.6, networkAlert);  // Should trigger another failure
    alertInCelcius(212.0, networkAlert);  // Should pass (100 Celsius)
    alertInCelcius(32.0, networkAlert);    // Should pass (0 Celsius)
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
    
    // Test with the mock function to validate conversion
    alertFailureCount = 0; 
    alertInCelcius(400.5, mockNetworkAlert); 
    alertInCelcius(303.6, mockNetworkAlert); 
    alertInCelcius(212.0, mockNetworkAlert);
    alertInCelcius(32.0, mockNetworkAlert);   

    assert(alertFailureCount == 2); // Expecting 2 failures for mock
    printf("%d alerts failed during mock test.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
