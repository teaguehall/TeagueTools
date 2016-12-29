#ifndef POLYPHASEDOWNSAMPLER_H
#define POLYPHASEDOWNSAMPLER_H

#include "../../Filters/firfilter.h"
#include <vector>
#include <memory>

/// PolyphaseDownSampler is a class that implements sample rate conversion and filtering. This class
/// will downsample an input signal by a user specified factor and then apply a low pass filter to
/// prevent aliasing. This downsampler/filter unit is implemented in a polyphase fashion for efficiency.
class PolyphaseDownSampler
{
    public:

        /// Creates a downsampler and filter device implemented in polyphase form.
        /// @param impulse_response Impulse response of the filter
        /// @param downsample_factor Downsample factor
        /// @param p_in Shared pointer that points to input source
        PolyphaseDownSampler(const std::vector<double>& impulse_response, unsigned downsample_factor, std::shared_ptr<double> p_in);

        /// Sets the input reference to the polyphase downsampler
        /// @param p_in Shared pointer that points to an input source
        void setInputReference(std::shared_ptr<double>);

        /// Returns a reference to the polyphase downsampler output.
        /// @return Shared pointer to output
        std::shared_ptr<double> getOutputReference();

        /// Sets the impulse response of the polyphase downsampler FIR filter
        /// @param impulse_response The desired FIR impulse response
        void setImpResponse(const std::vector<double>& impulse_response);

        /// Sets the downsample factor of the polyphase downsampler
        /// @param downsample_factor Desired downsample factor
        void setDownsampleFactor(unsigned downsample_factor);

        /// Returns the downsample factor of the polyphase downsampler
        /// @return downsample factor
        unsigned getDownsampleFactor();

        /// Clears (zeros) the polpyase downsampler filter history
        void clear();

        /// Calling this method will cause the polyphase filter to read the next input. Because
        /// the input rate is greater than the output when downsampling, the filter will read from
        /// its input reference, and then write to its output. Thus, this method neither contains
        /// an input argument or returns a value.
        void update();

    private:
        std::vector<double> m_impulse_response;
        unsigned m_downsample_factor;
        unsigned m_filter_index;
        double m_sum;
        std::vector<std::unique_ptr<FIRFilter>> m_filter_array;
        std::shared_ptr<double> m_p_in;
        std::shared_ptr<double> m_p_out = std::make_shared<double>(0);

        /// Initializes the polyphase downsampler. This method is called during construction
        /// or when one of its parameters changes (e.g. filter impulse response or downsample factor).
        void init();

        /// Calculates the subfilters that constitute the 'polyphase' implementation. Polyphase filters
        /// divide a single filter into subfilters dependent on the exact downsample factor. This method
        /// iterates through and builds each subfilter.
        void calcSubFilters();
};

#endif // POLYPHASEDOWNSAMPLER_H
