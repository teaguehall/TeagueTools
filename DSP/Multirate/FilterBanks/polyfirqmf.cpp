#include "polyfirqmf.h"

/**
 * @brief Creates a quadrature mirror filter bank implementing polyphase FIR filters
 * Provide this constructor with the QMF bank's low pass FIR filter and the corresponding high pass filter
 * will be automatically calculated
 *
 * @param lowpass_imp_response The impulse response of the low pass filter
 * @param p_in  A reference to the input source
 */
PolyFIRQMF::PolyFIRQMF(const std::vector<double> &imp_response_lowpass, std::shared_ptr<double> p_in) :
    QMFBank(p_in),
    m_polyfilter_lowband({1}, 2, p_in),
    m_polyfilter_highband({1}, 2, p_in),
    m_imp_response_lowpass(imp_response_lowpass)
{
    m_p_out_lowband = m_polyfilter_lowband.getOutputReference();
    m_p_out_highband = m_polyfilter_highband.getOutputReference();
    init();
}

/**
 * @brief Sets the data source reference
 * @param p_in Shared pointer to a data source
 */
void PolyFIRQMF::setInputReference(std::shared_ptr<double> p_in)
{
    m_p_in = p_in;
    m_polyfilter_lowband.setInputReference(m_p_in);     // see note
    m_polyfilter_highband.setInputReference(m_p_in);

    /* note: it is necessary to explicity reset the polyphase filter input references
     * when the QMF input reference changes. Otherwise, the polyphase filters would hold
     * onto the original shared pointers provided to them. */
}

/**
 * @brief Sets the low pass FIR filter of the QMF bank.
 * Setting the low pass filters will automatically calculate a corresponding high pass filter
 *
 * @param lowpass_imp_response The impulse response of the lowpass FIR filter
 */
void PolyFIRQMF::setLowPassImpResponse(const std::vector<double>& imp_response_lowpass)
{
    m_imp_response_lowpass = imp_response_lowpass;
    init();
}

/**
 * @brief Returns the lowpass filter impulse response of the QMF bank
 * @return
 */
std::vector<double> PolyFIRQMF::getLowpassImpResponse()
{
    return m_imp_response_lowpass;
}

/**
 * @brief Returns the highpass filter impulse response of the QMF bank
 * @return
 */
std::vector<double> PolyFIRQMF::getHighpassImpResponse()
{
    return m_imp_response_highpass;
}

/**
 * @brief Clears (zeros) the QMF bank.
 */
void PolyFIRQMF::clearFilter()
{
    m_polyfilter_lowband.clearFilter();
    m_polyfilter_highband.clearFilter();
}

void PolyFIRQMF::update()
{
    m_polyfilter_lowband.update();
    m_polyfilter_highband.update();
}

/***************************
 * Private Functions
 * *************************/

/**
 * @brief Initialize the QMF bank after a change has been made to the lowpass filter
 */
void PolyFIRQMF::init()
{
    calcHighpassImpResponse();
    m_polyfilter_lowband.setImpulse(m_imp_response_lowpass);
    m_polyfilter_highband.setImpulse(m_imp_response_highpass);
}

/**
 * @brief Calculates the highpass filter corresponding to the lowpass filter (H1[z] = H0[-z])
 *
 */
void PolyFIRQMF::calcHighpassImpResponse()
{
    // we assume the impulse response are causal (i.e. z^n where n <= 0)
    m_imp_response_highpass = m_imp_response_lowpass;
    for(unsigned i = 0; i < m_imp_response_highpass.size(); i++)
    {
        if(i%2) // negative ever odd coefficient
            m_imp_response_highpass[i] = -m_imp_response_lowpass[i];
    }
}

