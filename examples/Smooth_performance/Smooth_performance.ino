/*
 * Smooth_performance.ino
 * 
 * performance measurement of the Smooth object to  average a group of sample values
* measures only add() function as that is where  work is done
 * 
 * added to version 1.6.0 june 2023 ++ robtillaart
 * 
 */
#include <Smooth.h>

#define  SMOOTHED_SAMPLE_SIZE  10

// Smoothing average object
Smooth  average(SMOOTHED_SAMPLE_SIZE);

// Simulated moving sample
int sample = 0;

// for time measurement
uint32_t start, stop;

void setup() {
    Serial.begin(115200);
}

void loop() {
    // get a random -1, 0, or +1
    int const updown = random(0, 3) - 1;

    sample += updown;

    //  some time to flush all Serial
    delay(10);
    start = micros();
    average += sample;
    stop = micros();

    char scratch[64] = "";
    snprintf(scratch, sizeof(scratch), "count: %4d, sample: %3d, average: %3d, time %3ld\n",
        average.get_count(),
        sample,
        (int) average(),
        (stop - start)
        );

    Serial.print(scratch);
}