#ifndef IIRDIRECTFORM1_H
#define IIRDIRECTFORM1_H

#include "iirfilter.h"
#include "../../DataStructures/circularbuffer.h"
#include <vector>

class IIRDirectForm1 : public IIRFilter
{
    public:
        IIRDirectForm1(std::vector<double> b_coefs = {1}, std::vector<double> a_coefs = {1});
        double update(double input);
        void clearFilter();

        std::vector<double> getNormalizedACoefs();
        std::vector<double> getNormalizedBCoefs();

    protected:
        CircularBuffer m_buffer_x;
        CircularBuffer m_buffer_y;
        std::vector<double> m_norm_a_coefs;
        std::vector<double> m_norm_b_coefs;

        void initFilter();
        void calcNormalizedCoefs();
};

#endif // IIRDIRECTFORM1_H
