#ifndef FIRFILTER_H
#define FIRFILTER_H

#include "digitalfilter.h"
#include "../../DataStructures/circularbuffer.h"
#include <vector>

/// FIRFilter is an abstract class used for implementing FIR filters. This class provides common
/// methods that FIR filters will use.
class FIRFilter : public DigitalFilter
{
    public:
        /// Constructs an FIR filter using the specified impulse response
        FIRFilter(std::vector<double> impulse_response ={1});

        virtual ~FIRFilter(){};

        /// Sets the impulse response of the FIR filter
        /// @param impulse_response Impulse response
        virtual void setImpulseResponse(std::vector<double> impulse_response);

        /// Returns the impulse response of the filter
        /// @return Impulse response
        std::vector<double> getImpulseResponse();

        /// Enumerated class FIRType. This enum type contains a set of possible FIR filter types.
        enum class FIRType {
            directform,         ///< FIR type 'direct form' (indicates FIR filter is implemented using direct calculation)
            linearphasetype1,   ///< FIR type 'linear phase type 1'
            linearphasetype2,   ///< FIR type 'linear phase type 2'
            linearphasetype3,   ///< FIR type 'linear phase type 3'
            linearphasetype4,   ///< FIR type 'linear phase type 4'
            movingaverage,      ///< FIR type 'moving average'
            summer              ///< FIR type 'summer'
        };

        /// Returns the FIR type of the filter instance (e.g. linear phase type 1, 2, 3, 4, direct form, etc.).
        /// This is a useful method for determining the filter type when dealing with base pointers to the
        /// abstract 'FIRFilter' class.
        /// @return Returns the enumerated FIR type
        FIRType getFIRType();

        virtual double update(double input) = 0;
        void clear();

    protected:
        std::vector<double> m_impulse_response;
        CircularBuffer m_buffer;
        FIRType m_fir_type;

        /// Function to be called when the filter needs to be initialized (e.g. after the
        /// filter's impulse response has been modified). This function will be specific to classes
        /// that derive from the 'FIRFilter' base class.
        virtual void init(){};

    private:
        /// This function will be called to initialize the filter when the impulse response has
        /// been modified. Note that this function contains initialization code that will be common for
        /// all classes that derive from the 'FIRFilter' class, unlike 'init()' which must be defined
        /// by derived classes.
        void commonInit();
};

#endif // FIRFILTER_H
