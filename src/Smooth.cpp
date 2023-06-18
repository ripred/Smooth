/*
 * Smooth.h
 * 
 * implementation file for Smooth averaging class
 * 
 * version 1.0 - June, 2023 ++trent m. wyatt
 * 
 */
#include "Smooth.h"

Smooth::Smooth(int const window, int const c, double const a) :
        set_size(window),
        count(c),
        avg(a)
    { 
    }

// get the current running average
double Smooth::get_avg() const
{
    return avg; 
}

// get the total sample count
int Smooth::get_count() const
{
    return count;
}

// get the current window size (num samples)
int Smooth::get_window() const
{ 
    return set_size;
}

// set the current window size (num samples)
void   Smooth::set_window(int const size) 
{ 
    set_size = size;
}

// reset the smoothing object
void Smooth::reset(int const window) 
{
    set_size = window;
    count = 0;
    avg = 0.0;
}

// add a sample to the set and return the running average
double Smooth::add(double const val) 
{
    int num = ++count;
    if (num > set_size) {
        num = set_size;
    }

    double run_coef = double(num - 1) / double(num);
    double val_coef = 1.0 / double(num);

    avg = avg * run_coef + val * val_coef;

    return avg;
}

// operator overload for +=
double Smooth::operator += (double const term) {
    return add(term);
}

// operator overload for ()
double Smooth::operator () () {
    return avg;
}
