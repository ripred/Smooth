
[![Arduino CI](https://github.com/ripred/Smooth/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/ripred/Smooth/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/ripred/Smooth/actions/workflows/arduino-lint.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/ripred/Smooth/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/ripred/Smooth.svg?maxAge=3600)](https://github.com/ripred/Smooth/releases)


# Smooth Arduino Library


Keep smooth running averages without using arrays! No arrays. No Looping. Fast and Constant Time regardless of the sample window size!

The sample size is adjustable at runtime. The average is available and accurate even before N samples have been received. The `Smooth` object uses 8 bytes of memory. That's it. No matter how large the window size. Perfect for smoothing and filtering signals from noisy devices **like accelerometers**!

update: added support for change, upper and lower bounds callbacks!


### Example

```cpp
#include <Arduino.h>
#include <Smooth.h>

#define  SMOOTHED_SAMPLE_SIZE  10

// Smoothing average object
Smooth  average(SMOOTHED_SAMPLE_SIZE);

// Simulated wandering sample value
int sample = 0;

void setup() {
    Serial.begin(115200);
}

void loop() {
    // get a random -1, 0, or +1 value
    int const updown = random(0, 3) - 1;

    // move our simulated wandering sample up or down
    sample += updown;

    // add it to the running average
    average += sample;                      // or call average.add(sample)

    // display the results:
    char scratch[64] = "";
    snprintf(scratch, sizeof(scratch), "count: %4d, sample: %3d, average: %3d\n",
        average.get_count(),
        updown,
        (int) average());                   // or call average.get_avg()

    Serial.print(scratch);
}
```

example output:
```
count:    1, sample:   0, average:   0
count:    2, sample:   0, average:   0
count:    3, sample:   1, average:   0
count:    4, sample:   2, average:   0
count:    5, sample:   2, average:   1
count:    6, sample:   3, average:   1
count:    7, sample:   2, average:   1
count:    8, sample:   3, average:   1
count:    9, sample:   4, average:   1
count:   10, sample:   4, average:   2
count:   11, sample:   3, average:   2
count:   12, sample:   4, average:   2
count:   13, sample:   3, average:   2
count:   14, sample:   4, average:   2
count:   15, sample:   3, average:   2
count:   16, sample:   4, average:   2
count:   17, sample:   4, average:   2
count:   18, sample:   4, average:   3
count:   19, sample:   4, average:   3
count:   20, sample:   4, average:   3
count:   21, sample:   3, average:   3
count:   22, sample:   3, average:   3
count:   23, sample:   2, average:   3
count:   24, sample:   3, average:   3
count:   25, sample:   3, average:   3
count:   26, sample:   2, average:   2
count:   27, sample:   1, average:   2
count:   28, sample:   0, average:   2
count:   29, sample:   1, average:   2
count:   30, sample:   1, average:   2
count:   31, sample:   1, average:   2
count:   32, sample:   2, average:   2
count:   33, sample:   3, average:   2
count:   34, sample:   3, average:   2
count:   35, sample:   4, average:   2
count:   36, sample:   3, average:   2
count:   37, sample:   3, average:   2
count:   38, sample:   3, average:   2
count:   39, sample:   2, average:   2
```

