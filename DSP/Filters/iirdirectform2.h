#ifndef IIRDIRECTFORM2_H
#define IIRDIRECTFORM2_H

#include "iirfilter.h"
#include "../../DataStructures/circularbuffer.h"
#include <vector>

class IIRDirectForm2 : public IIRFilter
{
    public:
        IIRDirectForm2(std::vector<double> b_coefs = {1}, std::vector<double> a_coefs = {1});
        double update(double input);
        void clearFilter();
        std::vector<double> getNormalizedACoefs();
        std::vector<double> getNormalizedBCoefs();

    protected:
        std::vector<double> m_norm_a_coefs;
        std::vector<double> m_norm_b_coefs;
        CircularBuffer m_buffer;

    private:
        void calcNormalizedCoefs();
        void initFilter();

};

#endif // IIRDIRECTFORM2_H
