#ifndef SOSFILTER_H
#define SOSFILTER_H

#include "biquadfilter.h"
#include <vector>

class SOSFilter : public DigitalFilter
{
    public:
        SOSFilter(std::vector<BiquadFilter> biquad_stages);
        double update(double input);
        void clearFilter();
        BiquadFilter getBiquadStage(unsigned i);
        void setBiquadStage(unsigned i, BiquadFilter stage);
        void setBiquads(std::vector<BiquadFilter> biquad_stages);

    protected:
        std::vector<BiquadFilter> m_biquad_stages;

    private:

};

#endif // SOSFILTER_H
