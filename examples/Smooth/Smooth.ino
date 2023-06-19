/*
 * Smooth.ino
 * 
 * Example of basic use of the Smooth object to  average a group of sample values
 * 
 * version 1.0 2023 ++trent m. wyatt
 * 
 */
#include <Smooth.h>

#define  SMOOTHED_SAMPLE_SIZE  10

// Smoothing average object
Smooth  average(SMOOTHED_SAMPLE_SIZE);

// Simulated moving sample
int sample = 0;

void setup() {
    Serial.begin(115200);
}

void loop() {
    // get a random -1, 0, or +1
    int const updown = random(0, 3) - 1;

    sample += updown;

    average += sample;

    char scratch[64] = "";
    snprintf(scratch, sizeof(scratch), "count: %4d, sample: %3d, average: %3d\n",
        average.get_count(),
        sample,
        (int) average());

    Serial.print(scratch);
}
