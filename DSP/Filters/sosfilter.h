#ifndef SOSFILTER_H
#define SOSFILTER_H

#include "biquadfilter.h"
#include <vector>

/// SOSFilter is a class that implements a cascaded series of second order IIR filters (biquad
/// filters). This class is often useful for realizing higher order IIR filters that are typically
/// sensitive to coefficient quantization.
class SOSFilter : public DigitalFilter
{
    public:
        /// Constructs a 'second order sections' filter (cascaded biquad filter)
        /// @param biquad_stages Vector of biquad stages that specify the filter
        SOSFilter(std::vector<BiquadFilter> biquad_stages);

        /// Method used to retrieve a single biquad stage within the filter
        /// @param i Index of stage that is request
        /// @return Returns requested biquad stage. Returns {0,0,0}/{0,0,0} stage if invalid index was specified
        BiquadFilter getBiquadStage(unsigned i);

        /// Sets a single biquad filter stage
        /// @param i Index that specifies which biquad stage to set
        /// @param stage The biquad stage that will be inserted into the SOS filter
        void setBiquadStage(unsigned i, BiquadFilter stage);

        /// Replaces every biquad stage of the SOS filter
        /// @param biquad_stages Vector of biquad stages that will be used to define the SOS filter
        void setBiquads(std::vector<BiquadFilter> biquad_stages);

        double update(double input);
        void clear();

    protected:
        std::vector<BiquadFilter> m_biquad_stages;
};

#endif // SOSFILTER_H
