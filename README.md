# Smooth
Keep smooth running averages without using arrays! The sample size is adjustable at runtime. Additionally the average is available and accurate even before N samples have been received.

```
#include <Arduino.h>
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
    // get a random -1, 0, or +1 value
    int const updown = random(0, 3) - 1;

    // move our sample
    sample += updown;

    // add it to the running average
    average += sample;

    // display the results:
    char scratch[64] = "";
    snprintf(scratch, sizeof(scratch), "count: %4d, sample: %3d, average: %3d\n",
        average.get_count(),
        updown,
        (int) average());

    Serial.print(scratch);
}
```
