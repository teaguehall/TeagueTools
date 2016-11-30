#ifndef IIRTRANSDIRECTFORM2_H
#define IIRTRANSDIRECTFORM2_H

#include "iirfilter.h"
#include <vector>

class IIRTransDirectForm2 : public IIRFilter
{
    public:
        IIRTransDirectForm2(std::vector<double> b_coefs = {1}, std::vector<double> a_coefs = {1});
        double update(double input);
        void clearFilter();
        std::vector<double> getNormalizedACoefs();
        std::vector<double> getNormalizedBCoefs();

    protected:
        std::vector<double> m_norm_a_coefs;
        std::vector<double> m_norm_b_coefs;
        std::vector<double> m_buffer;

    private:
        void sizeBuffer();
        void calcNormalizedCoefs();
        void initFilter();
};

#endif // IIRTRANSDIRECTFORM2_H
