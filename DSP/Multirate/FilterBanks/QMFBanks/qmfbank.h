#ifndef QMFBANK_H
#define QMFBANK_H

#include <memory>

/// QMFBank is an abstract class for designing a 'quadrature mirror filter bank'.
/// This class provides the interface for a filter bank that splits
/// a signal into a high and low frequency subband. These subbands should be split at Fs/4
class QMFBank
{
    public:
        virtual ~QMFBank(){};

        /// Sets the input reference to the filter bank.
        /// @param p_in Shared pointer that points to filter bank input source
        virtual void setInputReference(std::shared_ptr<double> p_in) = 0;

        /// Returns a shared pointer to the lowband signal
        virtual std::shared_ptr<double> getLowBandReference() = 0;

        /// Returns a shared pointer to the highband signal
        virtual std::shared_ptr<double> getHighBandReference() = 0;

        /// Clears (zeros) the filter bank history
        virtual void clear() = 0;

        /// Filter bank will input the next value and update its subband signal outputs
        virtual void update() = 0;
};

#endif // QMFBANK_H
