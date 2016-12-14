#include "polyphasedownsample.h"
#include "../../Filters/firfactory.h"

/**
 * @brief Creates a polyphase downsample filter.
 *
 * The polyphase downsample filter is a input-output device that simulataneous applies a filter and downsamples
 * incoming data.
 *
 * @param impulse_response The impulse response of the filter
 * @param downsample_factor Sets the downsample factor of the filter
 * @param p_in Shared pointer to a data source
 */
PolyphaseDownSample::PolyphaseDownSample(const std::vector<double>& impulse_response, unsigned downsample_factor, std::shared_ptr<double> p_in) :
    m_p_in(p_in),
    m_impulse_response(impulse_response),
    m_downsample_factor(downsample_factor)
{
    initFilter();
}

/**
 * @brief Sets the data source reference
 * @param p_in Shared pointer to a data source
 */
void PolyphaseDownSample::setInputReference(std::shared_ptr<double> p_in)
{
    m_p_in = p_in;
}

/**
 * @brief Returns a shared pointer reference to the filter's output. This allows other devices to listen
 * to the filter output.
 *
 * @return Shared pointer to filter output
 */
std::shared_ptr<double> PolyphaseDownSample::getOutputReference()
{
    return m_p_out;
}

/**
 * @brief Sets the impulse response of the polyphase filter
 * @param impulse_response The specified impulse response
 */
void PolyphaseDownSample::setImpulse(const std::vector<double>& impulse_response)
{
    m_impulse_response = impulse_response;
    initFilter();
}

/**
 * @brief Sets the downsample factor of the polyphase filter
 * @param downsample_factor The downsample factor
 */
void PolyphaseDownSample::setDownsampleFactor(unsigned downsample_factor)
{
    m_downsample_factor = downsample_factor;
    initFilter();
}

/**
 * @brief Clears (zeros) the filter history
 */
void PolyphaseDownSample::clearFilter()
{
    for(unsigned i = 0; i < m_filter_array.size(); i++)
    {
        m_filter_array[i]->clearFilter();
    }
}

/**
 * @brief Updates the polyphase filter.
 *
 * Calling this method will cause the polyphase filter to read the next input.
 */
void PolyphaseDownSample::update()
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

/*********************************************
 * Private Methods
 *********************************************/

/**
 * @brief PolyphaseDownSample::initFilter
 */
void PolyphaseDownSample::initFilter()
{
    m_filter_index = m_downsample_factor;
    m_sum = 0;
    m_filter_array.resize(m_downsample_factor);
    calcSubFilters();
}

/**
 * @brief Given the filters impulse response and downsample factor, a certain number of
 * subfilters will exist. This method will generate those subfilters.
 */
void PolyphaseDownSample::calcSubFilters()
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

