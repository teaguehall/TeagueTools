#include "dyadicbank.h"

DyadicBank::DyadicBank(unsigned num_of_subbands)
{
    setNumSubbands(num_of_subbands);
}

std::shared_ptr<double> DyadicBank::getSubbandReference(unsigned index)
{
    if(index > m_p_subbands.size()) // return last output if index is too big
        return m_p_subbands.back();

    return m_p_subbands[index];
}

std::vector<std::shared_ptr<double>> DyadicBank::getSubbandReferences()
{
    return m_p_subbands;
}

unsigned DyadicBank::getNumSubbands()
{
    return m_num_of_subbands;
}

/********************
 * Private Functions
 ********************/

void DyadicBank::setNumSubbands(unsigned num_of_subbands)
{
    if(num_of_subbands < 2) // 2 subbands is the minimum allowed
        m_num_of_subbands  = 2;
    else if(num_of_subbands > 64) // 64 subbands is maximum due to how update is implemented
        m_num_of_subbands = 64;
    else
        m_num_of_subbands = num_of_subbands;

    m_p_subbands.resize(m_num_of_subbands);
}







