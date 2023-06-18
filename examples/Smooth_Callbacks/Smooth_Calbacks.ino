#include <Smooth.h>

#define  SMOOTHED_SAMPLE_SIZE  10

// Smoothing average object
Smooth  average(SMOOTHED_SAMPLE_SIZE);

// Simulated moving sample
int sample = 0;

void display() {
    char scratch[32] = "";
    snprintf(scratch, sizeof(scratch), "count: %4d, average: %3d\n",
        average.get_count(),
        (int) average());

    Serial.print(scratch);
}

void on_change(double const new_value) {
    static int last = average();
    if (last != (int) new_value) {
        last = (int) new_value;
        Serial.print("on_change(...): ");
        display();
    }
}

void on_upper(double const new_value) {
    static int last = average();
    if (last != (int) new_value) {
        last = (int) new_value;
        Serial.print("on_upper(...): ");
    }
}

void on_lower(double const new_value) {
    static int last = average();
    if (last != (int) new_value) {
        last = (int) new_value;
        Serial.print("on_lower(...): ");
    }
}

void setup() {
    Serial.begin(115200);
    average.set_change(on_change);
    average.set_upper(on_upper, 3);
    average.set_lower(on_lower, 1);
}

void loop() {
    // get a random -1, 0, or +1
    int const updown = random(0, 3) - 1;

    sample += updown;

    average += sample;
}
