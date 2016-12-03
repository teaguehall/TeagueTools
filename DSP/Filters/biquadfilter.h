#ifndef BIQUADFILTER_H
#define BIQUADFILTER_H

#include "iirfilter.h"
#include <vector>

class BiquadFilter : public IIRFilter
{
    public:
        BiquadFilter(std::vector<double> b_coefs = {1, 1, 1}, std::vector<double> a_coefs = {1, 1, 1});
        double update(double input);
        void clearFilter();
        std::vector<double> getNormalizedACoefs();
        std::vector<double> getNormalizedBCoefs();

    protected:
        std::vector<double> m_norm_a_coefs;
        std::vector<double> m_norm_b_coefs;
        std::vector<double> m_buffer;

    private:
        void calcNormalizedCoefs();
        void initFilter();
};

#endif // BIQUADFILTER_H
