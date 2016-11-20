#ifndef LINEARPHASETYPE4_H
#define LINEARPHASETYPE4_H

#include "firfilter.h"

class LinearPhaseType4 : public FIRFilter
{
    public:
        LinearPhaseType4(std::vector<double> impulse_response);
        double update(double input);

    private:
        int m_num_relevant_coefs;
        void initFilter();
};

#endif // LINEARPHASETYPE4_H
