#include "PolyphaseDownSampler.h"
#include "../../Filters/firfactory.h"

PolyphaseDownSampler::PolyphaseDownSampler(const std::vector<double>& impulse_response, unsigned downsample_factor, std::shared_ptr<double> p_in) :
    m_p_in(p_in),
    m_impulse_response(impulse_response),
    m_downsample_factor(downsample_factor)
{
    init();
}

void PolyphaseDownSampler::setInputReference(std::shared_ptr<double> p_in)
{
    m_p_in = p_in;
}

std::shared_ptr<double> PolyphaseDownSampler::getOutputReference()
{
    return m_p_out;
}

void PolyphaseDownSampler::setImpResponse(const std::vector<double>& impulse_response)
{
    m_impulse_response = impulse_response;
    init();
}

void PolyphaseDownSampler::setDownsampleFactor(unsigned downsample_factor)
{
    m_downsample_factor = downsample_factor;
    init();
}

unsigned PolyphaseDownSampler::getDownsampleFactor()
{
    return m_downsample_factor;
}

void PolyphaseDownSampler::clear()
{
    for(unsigned i = 0; i < m_filter_array.size(); i++)
    {
        m_filter_array[i]->clear();
    }
}

void PolyphaseDownSampler::update()
{
    // filter index counts down (commutation direction of polyphase is important)
    m_filter_index--;
    m_sum += m_filter_array[m_filter_index]->update(*m_p_in);

    if(m_filter_index == 0)
    {
        *m_p_out = m_sum;
         m_sum = 0;
         m_filter_index = m_downsample_factor;
    }
}

/********************
 * Private Functions
 ********************/

void PolyphaseDownSampler::init()
{
    m_filter_index = m_downsample_factor;
    m_sum = 0;
    m_filter_array.resize(m_downsample_factor);
    calcSubFilters();
}

void PolyphaseDownSampler::calcSubFilters()
{
    unsigned index;
    unsigned sub_filter_size = (int)std::ceil(m_impulse_response.size()/(double)m_downsample_factor);
    std::vector<double> sub_impulse_response(sub_filter_size);

    for(unsigned i = 0; i < m_downsample_factor; i++)   // number of subfilter= downsample factor
    {
        // create subfilter impulse response
        std::fill(sub_impulse_response.begin(), sub_impulse_response.end(), 0);
        for(unsigned j = 0; j < sub_impulse_response.size(); j++)
        {
            index = i + j*m_downsample_factor;
            if(index < m_impulse_response.size())
                sub_impulse_response[j] = m_impulse_response[index];
        }
        m_filter_array[i] = FIRFactory::getFilter(sub_impulse_response);
    }
}

