#ifndef DYADICBANK_H
#define DYADICBANK_H

#include <memory>
#include <vector>

/// DyadicBank is an abstract class for designing dyadic filter banks. A dyadic filter bank
/// is any filter bank that produces subbands split at octave frequencies.
class DyadicBank
{
    public:
        /// Constructs a dyadic filter bank
        /// @param num_of_subbands Number of subbands that the filter bank will output
        DyadicBank(unsigned num_of_subbands);

        /// Returns a vector of shared pointers pointing to each subband output of the filter bank
        /// @return Vectors of shared pointers pointing to each output of the filter bank
        std::vector<std::shared_ptr<double>> getSubbandReferences();

        /// Returns a shared pointer to one of the filter banks subband outputs.
        /// @param index The desired subband (index is zero based, i.e. index = 0 returns first output)
        /// @return Shared pointer pointing to the subband output specified by the 'index' argument
        std::shared_ptr<double> getSubbandReference(unsigned index);

        /// Returns the number of subbands the filter bank has been configured to output.
        /// @return The number of subbands the filter bank has been configured to output.
        unsigned getNumSubbands();

        /// Sets the filter bank input source.
        /// @param p_in Shared pointer to an input source
        virtual void setInputReference(std::shared_ptr<double> p_in) = 0;

        /// Clears (zeros) the filter bank history.
        virtual void clear() = 0;

        /// Filter bank will input the next value and update its subband signal outputs.
        virtual void update() = 0;

    protected:
        unsigned m_num_of_subbands;
        std::vector<std::shared_ptr<double>> m_p_subbands;

        /// Sets the number of outputs of the dyadic filter bank
        /// @param num_of_outputs Desired number of subbands in which the inputted signal will be decomposed
        void setNumSubbands(unsigned num_of_subbands);
};

#endif // DYADICBANK_H
