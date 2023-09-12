/*
 * Smooth.h
 * 
 * header file for Smooth averaging class
 * 
 * version 1.8.0 - August, 2023 ++trent m. wyatt
 * 
 */
#ifndef   SMOOTH_H_INCL
#define   SMOOTH_H_INCL

#include <inttypes.h>

typedef void (*FNcallback)(double const /* new_value */);

class Smooth {
    private:
    uint16_t set_size;
    uint32_t count;

    FNcallback cbchange;
    FNcallback cblower;
    FNcallback cbupper;

    double avg;
    double last;
    double upper;
    double lower;

    public:
    Smooth(int const window = 1, int const counter = 0, double const a = 0.0);

    // callback registration:
    void set_change(FNcallback const cb);
    void set_lower(FNcallback const cb, double const value);
    void set_upper(FNcallback const cb, double const value);

    // get/set the current running average
    double get_avg() const;
    void set_avg(double const average);

    // get the total sample count
    uint32_t get_count() const;

    // get/set the current window size (num samples)
    uint16_t get_window() const;
    void set_window(int const size);

    // reset the smoothing object
    void reset(int const window, int const counter = 0, double const average = 0.0);

    // add a sample to the set and return the running average
    double add(double const val);

    // operator overload for +=
    double operator += (double const term);

    // operator overload for ()
    double operator () ();

}; // class Smooth

#endif //  #ifndef SMOOTH_H_INCL
