#ifndef IIRTRANSDIRECTFORM1_H
#define IIRTRANSDIRECTFORM1_H

#include "iirfilter.h"
#include "../../DataStructures/circularbuffer.h"
#include <vector>

class IIRTransDirectForm1 : public IIRFilter
{
    public:
        IIRTransDirectForm1(std::vector<double> b_coefs = {1}, std::vector<double> a_coefs = {1});
        double update(double input);
        void clear();
        std::vector<double> getNormalizedACoefs();
        std::vector<double> getNormalizedBCoefs();

    protected:
        std::vector<double> m_norm_a_coefs;
        std::vector<double> m_norm_b_coefs;
        std::vector<double> m_buffer_1; // corresponds to input side
        std::vector<double> m_buffer_2; // corresponds to output side

    private:
        void calcNormalizedCoefs();
        void initFilter();
};

#endif // IIRTRANSDIRECTFORM1_H
