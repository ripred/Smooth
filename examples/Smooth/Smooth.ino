#include "Smooth.h"

#define  SMOOTHED_SAMPLE_SIZE  10

// Smoothing average object
Smooth  average(SMOOTHED_SAMPLE_SIZE);

// Simulated moving sample
int sample = 0;

void setup() {
    Serial.begin(115200);
}

void loop() {
    // get a random -10, 0, or +10
    int const updown = 10 * (random(0, 3) - 1);

    sample += updown;

    average += sample;

    char scratch[64] = "";
    snprintf(scratch, sizeof(scratch), "count: %4d, sample: %3d, average: %3d\n",
        average.get_count(),
        updown,
        (int) average());

    Serial.print(scratch);
}
