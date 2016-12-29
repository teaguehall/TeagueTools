#ifndef DYADICPOLY_H
#define DYADICPOLY_H

#include "dyadicbank.h"
#include "../QMFBanks/polyfirqmf.h"
#include <memory>
#include <vector>
#include <stdint.h>

/// A dyadic filter bank implemented using quadrature mirror filterbank (QMFbank) polyphase FIR
/// stages. Each subband output of the dyadic filter bank is critically sampled (i.e. sample rate
/// changed).
class DyadicPoly : public DyadicBank
{
    public:
        /// Constructs a dyadic filter bank implemented with polyphase QMFbank stages
        /// @param num_of_subbands Desired number of subband outputs
        /// @param fir_imp_response Low pass filter impulse response
        /// @param p_in Reference to dyadic filter bank input source
        DyadicPoly(unsigned num_of_subbands, const std::vector<double>& fir_imp_response, std::shared_ptr<double> p_in);

        void setInputReference(std::shared_ptr<double> p_in);

        /// Sets the impulse response of the FIR low pass filters used in the dyadic filter bank.
        /// This impulse response is used for each QMF stages within the dyadic bank. The high pass filter
        /// impulse response is calculated to mirror that of the low pass filter
        /// @param fir_imp_response Low pass filter impulse response
        void setFIRImpResponse(const std::vector<double>& fir_imp_response);

        void clear();

        /// This method tells the filter bank to read the current input and calculate the new outputs.
        void update();

    protected:
        uint32_t m_count = 0;
        std::vector<double> m_fir_imp_response;
        std::vector<PolyFIRQMF> m_qmf_banks;

        /// Initializes the dyadic filter bank when needed. When the dyadic bank is constructed or
        /// a parameter changes (e.g. FIR low pass impulse response of the QMFbank stages), the
        /// dyadic bank will need to be initialized. This function acts as a central entrance to
        /// all necessary initialization
        void init();

        /// Constructs the QMFbank stages
        void createQMFBanks();

        /// Maps the QMFbank stage outputs to the appropriate dydiac filter bank outputs
        void mapDyadicBankOutputs();

        /// Assigns the impulse response to each QMFbank stage
        void assignImpReponses();

};

#endif // DYADICPOLY_H
