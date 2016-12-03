#include "sosfilter.h"

/**
 * @brief Constructs a 'second order sections' filter (cascaded biquad filter)
 * @param biquad_stages Vector of biquad stages that specify the filter
 */
SOSFilter::SOSFilter(std::vector<BiquadFilter> biquad_stages) :
    m_biquad_stages(biquad_stages)
{
}

/**
 * @brief Takes input and produces filter output
 * @param input Filter input
 * @return Returns filter output
 */
double SOSFilter::update(double input)
{
    double val = input;
    for(unsigned i = 0; i < m_biquad_stages.size(); i++)
    {
        val = m_biquad_stages[i].update(val);
    }
    return val;
}

/**
 * @brief Clears (zeros) the filter history
 */
void SOSFilter::clearFilter()
{
    for(BiquadFilter stage : m_biquad_stages)
    {
        stage.clearFilter();
    }
}

/**
 * @brief Method used to retrieve a single biquad stage within the filter
 * @param Index of stage that is request
 * @return Returns requested biquad stage. Return {0,0,0}/{0,0,0} stage if invalid index was specified
 */
BiquadFilter SOSFilter::getBiquadStage(unsigned i)
{
    if(i < m_biquad_stages.size())
        return m_biquad_stages[i];
    else
        return BiquadFilter({0,0,0},{0,0,0});
}

/**
 * @brief Sets a single biquad filter stage
 * @param i Index that specifies which biquad stage to set
 * @param stage The biquad stage that will be inserted into the SOS filter
 */
void SOSFilter::setBiquadStage(unsigned i, BiquadFilter stage)
{
    if(i < m_biquad_stages.size())
        m_biquad_stages[i] = stage;
}

/**
 * @brief Replaces every biquad stage of the SOS filter
 * @param biquad_stages Vector of biquad stages that will be used to define the SOS filter
 */
void SOSFilter::setBiquads(std::vector<BiquadFilter> biquad_stages)
{
    m_biquad_stages = biquad_stages;
}
