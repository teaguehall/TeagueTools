#include "iirfilter.h"

IIRFilter::IIRFilter(const std::vector<double>& b_coefs, const std::vector<double>& a_coefs) :
    m_a_coefs(a_coefs),
    m_b_coefs(b_coefs)
{
    commonInit();
}

double IIRFilter::update(double input)
{
    return input; // this method will be overwritten, so output whatever
}

void IIRFilter::setCoefs(const std::vector<double>& b_coefs, const std::vector<double>& a_coefs)
{
    m_a_coefs = a_coefs;
    m_b_coefs = b_coefs;
    commonInit();
    init();
}

void IIRFilter::setACoefs(const std::vector<double>& a_coefs)
{
    m_a_coefs = a_coefs;
    commonInit();
    init();
}

void IIRFilter::setBCoefs(const std::vector<double>& b_coefs)
{
    m_b_coefs = b_coefs;
    commonInit();
    init();
}

std::vector<double> IIRFilter::getACoefs()
{
    return m_a_coefs;
}

std::vector<double> IIRFilter::getBCoefs()
{
    return m_b_coefs;
}

/********************
 * Private Functions
 ********************/

void IIRFilter::commonInit()
{
    m_filter_order = m_a_coefs.size() - 1;
}

