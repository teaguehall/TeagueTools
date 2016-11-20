#ifndef LINEARPHASETYPE3_H
#define LINEARPHASETYPE3_H

#include "firfilter.h"

class LinearPhaseType3 : public FIRFilter
{
    public:
        LinearPhaseType3(std::vector<double> impulse_response);
        double update(double input);

    private:
        int m_num_relevant_coefs;
        void initFilter();
};

#endif // LINEARPHASETYPE3_H
