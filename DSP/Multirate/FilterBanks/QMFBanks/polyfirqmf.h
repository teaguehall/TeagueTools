#ifndef POLYFIRQMF_H
#define POLYFIRQMF_H

#include "qmfbank.h"
#include "../../Filters/polyphasedownsample.h"
#include <memory>

/// PolyFIRQMF class is a quadrature mirror filter bank (QMF bank) implemented using polyphase
/// FIR filters. The lowband and highband are both critically sampled (thus the highband signal
/// is 'flipped' due to subsampling.
class PolyFIRQMF : public QMFBank
{
    public:
        /// Creates a quadrature mirror filter bank implemented with polyphase FIR filters.
        /// Provide this constructor with the QMF bank's low pass FIR filter and the corresponding high pass filter
        /// will automatically be calculated
        /// @param lowpass_imp_response The impulse response of the low pass filter
        /// @param p_in  A shared pointer to the filter banks input source
        PolyFIRQMF(const std::vector<double>& imp_response_lowpass, std::shared_ptr<double> p_in);

        void setInputReference(std::shared_ptr<double>);

        /// Sets the low pass FIR filter of the QMF bank. Setting a new lowpass impulse response
        /// will automatically trigger a recalculation of the corresponding highpass impulse response.
        /// @param lowpass_imp_response The impulse response of the lowpass FIR filter
        void setLowPassImpResponse(const std::vector<double>& lowpass_imp_response);

        std::shared_ptr<double> getLowBandReference();

        std::shared_ptr<double> getHighBandReference();

        /// Returns the lowpass filter impulse response of the QMF bank.
        std::vector<double> getLowpassImpResponse();

        /// Returns the highpass filter impulse response of the QMF bank
        std::vector<double> getHighpassImpResponse();

        void clear();

        void update();

    private:
        PolyphaseDownSample m_polyfilter_lowband;
        PolyphaseDownSample m_polyfilter_highband;
        std::vector<double> m_imp_response_lowpass;
        std::vector<double> m_imp_response_highpass;

        /// Initializes the filter bank when the impulse response changes
        void init();

        /// Calculates a new highpass impulse response when a new lowpass impulse response is specified.
        void calcHighpassImpResponse();
};

#endif // POLYFIRQMF_H
