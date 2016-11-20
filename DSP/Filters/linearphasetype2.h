#ifndef LINEARPHASETYPE2_H
#define LINEARPHASETYPE2_H

#include "firfilter.h"

class LinearPhaseType2 : public FIRFilter
{
    public:
        LinearPhaseType2(std::vector<double> impulse_response);
        double update(double input);

    private:
        int m_num_relevant_coefs;
        void initFilter();
};

#endif // LINEARPHASETYPE2_H
