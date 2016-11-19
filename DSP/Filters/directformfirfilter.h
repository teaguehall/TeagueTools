#ifndef DIRECTFORMFIRFILTER_H
#define DIRECTFORMFIRFILTER_H

#include "firfilter.h"

class DirectFormFIRFilter : public FIRFilter
{
    public:
        DirectFormFIRFilter(std::vector<double> impulse_response);
        double update(double input);

    protected:
        void initFilter();

};

#endif // DIRECTFORMFIRFILTER_H
