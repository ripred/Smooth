/*
 * Smooth.h
 * 
 * header file for Smooth averaging class
 * 
 * version 1.0 - June, 2023 ++trent m. wyatt
 * 
 */
#ifndef   SMOOTH_H_INCL
#define   SMOOTH_H_INCL

#include <inttypes.h>

typedef void (*FNcallback)(double const /* new_value */);

class Smooth {
    private:
    int set_size;
    int count;
    FNcallback cbchange;
    FNcallback cblower;
    FNcallback cbupper;

    double avg;
    double last;
    double upper;
    double lower;

    public:
    Smooth(int const window = 1, int const c = 0, double const a = 0.0);

    void tick();

    void set_change(FNcallback const cb);
    void set_lower(FNcallback const cb, double const value);
    void set_upper(FNcallback const cb, double const value);

    // get the current running average
    double get_avg() const;

    // get the total sample count
    int get_count() const;

    // get the current window size (num samples)
    int get_window() const;
    
    // set the current window size (num samples)
    void   set_window(int const size);

    // reset the smoothing object
    void reset(int const window);

    // add a sample to the set and return the running average
    double add(double const val);

    // operator overload for +=
    double operator += (double const term);

    // operator overload for ()
    double operator () ();

}; // class Smooth

#endif //  #ifndef SMOOTH_H_INCL
