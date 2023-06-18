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

class Smooth {
    private:
    int set_size;
    int count;
    double avg;

    public:
    Smooth(int const window = 1, int const c = 0, double const a = 0.0);

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
