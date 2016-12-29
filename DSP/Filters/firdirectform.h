#ifndef FIRDIRECTFORM_H
#define FIRDIRECTFORM_H

#include "firfilter.h"

/// FIRDirectForm is a class that implements an FIRFilter using direct form calculations.
class FIRDirectForm : public FIRFilter
{
    public:
        /// Constructs a direct form FIR filter using a specified impulse response
        /// @param impulse_response Impulse response
        FIRDirectForm(std::vector<double> impulse_response);

        double update(double input);

    protected:
        void init();
};

#endif // FIRDIRECTFORM_H
