/*
 * Smooth.cpp
 * 
 * implementation file for Smooth averaging class
 * 
 * version 1.6 - June, 2023 ++trent m. wyatt
 * 
 */
#include "Smooth.h"

Smooth::Smooth(int const window, int const c, double const a) :
        set_size(window),
        count(c),
        avg(a)
    { 
        last = avg;
        upper = 0.0;
        lower = 0.0;
        cbupper = nullptr;
        cblower = nullptr;
    }


// register optional callbacks for change, and upper and lower bounds
void Smooth::set_change(FNcallback const cb)
{
    cbchange = cb;
}

void Smooth::set_lower(FNcallback const cb, double const value)
{
    cblower = cb;
    lower = value;
}

void Smooth::set_upper(FNcallback const cb, double const value)
{
    cbupper = cb;
    upper = value;
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
    last = 0.0;
    lower = 0.0;
    upper = 0.0;
    cbchange = nullptr;
    cblower = nullptr;
    cbupper = nullptr;
}


// add a sample to the set and return the running average
double Smooth::add(double const val) 
{
    double run_coef = 0;
    double val_coef = 0;

    int num = ++count;
    //  do we need to calculate new coefficients?
    if (num > set_size) 
    {
        num = set_size;
        val_coef = 1.0 / double(num);
        //   multiply is faster than divide, so reuse math
        run_coef = double(num - 1) * val_coef; 
    }

    avg = avg * run_coef + val * val_coef;

    if (last != avg) {
        last = avg;

        if (nullptr != cbchange) {
            cbchange(avg);
        }

        // testing nullptr is faster than comparing floats
        // so lets do that first.
        if (nullptr != cblower) {
            if (avg < lower) {
                cblower(avg);
            }
        }

        if (nullptr != cbupper) {
            if (avg >= upper) {
                cbupper(avg);
            }
        }
    }

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
