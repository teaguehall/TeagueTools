#ifndef LINEARPHASETYPE1_H
#define LINEARPHASETYPE1_H

#include "firfilter.h"

class LinearPhaseType1 : public FIRFilter
{
    public:
        LinearPhaseType1(std::vector<double> impulse_response);
        double update(double input);

    private:
        int m_num_relevant_coefs;
        void initFilter();
};

#endif // LINEARPHASETYPE1_H
