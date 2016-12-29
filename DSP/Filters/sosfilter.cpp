#include "sosfilter.h"

SOSFilter::SOSFilter(std::vector<BiquadFilter> biquad_stages) :
    m_biquad_stages(biquad_stages)
{
}

BiquadFilter SOSFilter::getBiquadStage(unsigned i)
{
    if(i < m_biquad_stages.size())
        return m_biquad_stages[i];
    else
        return BiquadFilter({0,0,0},{0,0,0});
}

void SOSFilter::setBiquadStage(unsigned i, BiquadFilter stage)
{
    if(i < m_biquad_stages.size())
        m_biquad_stages[i] = stage;
}

void SOSFilter::setBiquads(std::vector<BiquadFilter> biquad_stages)
{
    m_biquad_stages = biquad_stages;
}

double SOSFilter::update(double input)
{
    double val = input;
    for(unsigned i = 0; i < m_biquad_stages.size(); i++)
    {
        val = m_biquad_stages[i].update(val);
    }
    return val;
}

void SOSFilter::clear()
{
    for(BiquadFilter stage : m_biquad_stages)
    {
        stage.clear();
    }
}

