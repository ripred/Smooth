#include <Smooth.h>

#define  SMOOTHED_SAMPLE_SIZE  10

// Smoothing average object
Smooth  average(SMOOTHED_SAMPLE_SIZE);

// Simulated moving sample
int sample = 0;


void on_change(double const new_value) {
    Serial.print("on_change(");
    Serial.print((int) new_value, DEC);
    Serial.print(")\n");
}

void on_upper(double const new_value) {
    Serial.print("on_lower(");
    Serial.print((int) new_value, DEC);
    Serial.print(")\n");
}

void on_lower(double const new_value) {
    Serial.print("on_upper(");
    Serial.print((int) new_value, DEC);
    Serial.print(")\n");
}

void setup() {
    Serial.begin(115200);
    average.set_change(on_change);
    average.set_upper(on_lower, 256);
    average.set_upper(on_upper, 768);
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
