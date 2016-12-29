#ifndef IIRFILTER_H
#define IIRFILTER_H

#include "digitalfilter.h"
#include <vector>

/// IIRFilter is an abstract class that provides partial implementation of an IIR filter. This class
/// provides methods for getting/setting filter coefficients, but does not provide the actual filter
/// 'update' method. This is left for derived classes (refer to direct form 1, 2, transposed forms).
class IIRFilter : public DigitalFilter
{
    public:
        /// Constructs an IIR filter
        /// @param a_coefs Denominator coefficients
        /// @param b_coefs Numerator coefficients
        IIRFilter(const std::vector<double>& b_coefs = {1}, const std::vector<double>& a_coefs = {1});

        virtual ~IIRFilter(){};

        /// Sets the coefficients of the IIR filter
        /// @param a_coefs Denominator coefficients
        /// @param b_coefs Numerator coefficients
        void setCoefs(const std::vector<double>& b_coefs, const std::vector<double>& a_coefs);

        /// Sets the denominator coefficients of the IIR filter
        /// @param a_coefs Denominator coefficients
        void setACoefs(const std::vector<double>& a_coefs);

        /// Sets the numerator coefficients of the IIR filter
        /// @param b_coefs Denominator coefficients
        void setBCoefs(const std::vector<double>& b_coefs);
		
        /// Returns the denominator coefficients
        /// @return Denominator coefficients
        std::vector<double> getACoefs();

        /// Returns the numerator coefficients
        /// @return Numerator coefficients
        std::vector<double> getBCoefs();

        virtual double update(double input) = 0;
        virtual void clear() = 0;

    protected:
        std::vector<double> m_a_coefs;
        std::vector<double> m_b_coefs;

        /// Initializes the filter. This method is called during object construction or when one of
        /// the filter parameters is modified (e.g. filter coefficients). This method is virtual
        /// and will specific to derived classes.
        virtual void init() = 0;

    private:
        /// This function will be called to initialize the filter when the impulse response has
        /// been modified. Note that this function contains initialization code that will be common for
        /// all classes that derive from the IIRFilter class, unlike 'init()' which must be defined
        /// by derived classes.
        void commonInit();
};

#endif // IIRFILTER_H
