/*
 * Smooth_Callbacks.ino
 * 
 * Example using callbacks with the Smooth Arduino library
 * 
 * version 1.0 2023 ++trent m. wyatt
 * 
 */
#include <Smooth.h>

// Define an alias for the number of samples we want to average together
#define  SMOOTHED_SAMPLE_SIZE  10

// Smoothing average object
Smooth  average(SMOOTHED_SAMPLE_SIZE);

// Simulated moving sample for this example
int sample = 0;
int last = 0;

// function to display the sample count the current
// sample, and the current moving average
void display() {
    char scratch[64] = "";
    snprintf(scratch, sizeof(scratch), "count: %4d, sample: %4d, average: %3d\n",
        average.get_count(),
        sample,
        (int) average());

    Serial.print(scratch);
}

// This function is our callback function for any changes to
// the running average. This gets registered with the library
// and then automatically called as needed.
void on_change(double const new_value) {
    if (last != (int) new_value) {
        last = (int) new_value;
        Serial.print("on_change(...): ");
        display();
    }
}

// This function is our callback function for changes to the
// running average that go above the upper limit we set when
// we registered this callback. This gets registered with the
// library and then automatically called as needed.
void on_upper(double const new_value) {
    if (last != (int) new_value) {
        last = (int) new_value;
        Serial.print("on_upper(...): ");
        display();
    }
}


// This function is our callback function for changes to the
// running average that go below the lower limit we set when
// we registered this callback. This gets registered with the
// library and then automatically called as needed.
void on_lower(double const new_value) {
    if (last != (int) new_value) {
        last = (int) new_value;
        Serial.print("on_lower(...): ");
        display();
    }
}

void setup() {
    Serial.begin(115200);

    // register our callback functions
    average.set_change(on_change);
//  average.set_upper(on_upper, 3);     // register callbacks when the average is >= 3
//  average.set_lower(on_lower, 1);     // register callbacks when the average is <  1
}

void loop() {
    // create a random -1, 0, or +1 value
    int const updown = random(0, 3) - 1;

    // move the simulated sample value up or down
    sample += updown;

    // add the sample to the running average.
    // Note Below: It is during this update
    // that our callbacks might be called:
    average += sample;
}
