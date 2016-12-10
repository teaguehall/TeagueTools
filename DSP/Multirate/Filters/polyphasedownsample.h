#ifndef POLYPHASEDOWNSAMPLE_H
#define POLYPHASEDOWNSAMPLE_H

#include "../../Filters/firfilter.h"
#include <vector>
#include <memory>

class PolyphaseDownSample
{
    public:
        PolyphaseDownSample(std::vector<double> impulse_response, unsigned downsample_factor, std::shared_ptr<double> p_in);
        void setInputReference(std::shared_ptr<double>);
        std::shared_ptr<double> getOutputReference();
        void setImpulse(std::vector<double> impulse_response);
        void setDownsampleFactor(unsigned downsample_factor);
        void clearFilter();
        void update();

    private:
        std::vector<double> m_impulse_response;
        unsigned m_downsample_factor;
        unsigned m_filter_index;
        double m_sum;
        std::vector<std::unique_ptr<FIRFilter>> m_filter_array;
        std::shared_ptr<double> m_p_in;
        std::shared_ptr<double> m_p_out = std::make_shared<double>(0);

        void initFilter();
        void calcSubFilters();
};

#endif // POLYPHASEDOWNSAMPLE_H
