#include "polyfirqmf.h"

PolyFIRQMF::PolyFIRQMF(const std::vector<double> &imp_response_lowpass, std::shared_ptr<double> p_in) :
    m_polyfilter_lowband({1}, 2, p_in),
    m_polyfilter_highband({1}, 2, p_in),
    m_imp_response_lowpass(imp_response_lowpass)
{
    init();
}

void PolyFIRQMF::setInputReference(std::shared_ptr<double> p_in)
{
    m_polyfilter_lowband.setInputReference(p_in);
    m_polyfilter_highband.setInputReference(p_in);
}

void PolyFIRQMF::setLowPassImpResponse(const std::vector<double>& imp_response_lowpass)
{
    m_imp_response_lowpass = imp_response_lowpass;
    init();
}

std::shared_ptr<double> PolyFIRQMF::getLowBandReference()
{
    return m_polyfilter_lowband.getOutputReference();
}

std::shared_ptr<double> PolyFIRQMF::getHighBandReference()
{
    return m_polyfilter_highband.getOutputReference();
}

std::vector<double> PolyFIRQMF::getLowpassImpResponse()
{
    return m_imp_response_lowpass;
}

std::vector<double> PolyFIRQMF::getHighpassImpResponse()
{
    return m_imp_response_highpass;
}

void PolyFIRQMF::clear()
{
    m_polyfilter_lowband.clear();
    m_polyfilter_highband.clear();
}

void PolyFIRQMF::update()
{
    m_polyfilter_lowband.update();
    m_polyfilter_highband.update();
}

/********************
 * Private Functions
 ********************/
void PolyFIRQMF::init()
{
    calcHighpassImpResponse();
    m_polyfilter_lowband.setImpResponse(m_imp_response_lowpass);
    m_polyfilter_highband.setImpResponse(m_imp_response_highpass);
}

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

