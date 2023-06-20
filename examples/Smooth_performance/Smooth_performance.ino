/*
   Smooth_performance.ino

   performance measurement of the Smooth object to  average a group of sample values
  measures only add() function as that is where  work is done

   added to version 1.6.0 june 2023 ++ robtillaart

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
  int updown = random(0, 3) - 1;

  sample += updown;

  //  some time to flush all Serial
  delay(10);
  start = micros();
  average += sample;
  stop = micros();

  Serial.print("count: ");
  Serial.print(average.get_count());
  Serial.print(", sample: ");
  Serial.print(sample);
  Serial.print(", average: ");
  Serial.print((int) average());
  Serial.print(", time: ");
  Serial.println(stop - start);

  delay(100);

  // test effect window size
  if (average.get_count() % 15 == 0)  {
    average.set_window(average.get_window() + 2);
  }
}
