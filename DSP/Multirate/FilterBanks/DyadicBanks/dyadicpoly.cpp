#include "dyadicpoly.h"

DyadicPoly::DyadicPoly(unsigned num_of_subbands, const std::vector<double>& fir_imp_response, std::shared_ptr<double> p_in) :
    DyadicBank(num_of_subbands),
    m_fir_imp_response(fir_imp_response)
{
    init();
    setInputReference(p_in);
}

void DyadicPoly::setInputReference(std::shared_ptr<double> p_in)
{
    m_qmf_banks[0].setInputReference(p_in);
}

void DyadicPoly::setFIRImpResponse(const std::vector<double>& fir_imp_response)
{
    m_fir_imp_response = fir_imp_response;
    assignImpReponses();
}

void DyadicPoly::clear()
{
    for(unsigned i = 0; i < m_qmf_banks.size(); i++)
    {
        m_qmf_banks[i].clear();
    }
}

/* This method takes advantage of the fact that the QMF stages will be updated at a rate of
 *  1/2^n of the input sample rate. Because this occurs as a power of 2, masking is used to
 *  determine when to update the filter stages. */
void DyadicPoly::update()
{
    m_count++;

    /* update QMF banks as needed */
    m_qmf_banks[0].update();

    for(unsigned i = 0; i < m_qmf_banks.size() - 1; i++)
    {

        if((m_count >> i) & 1)
            m_qmf_banks[i+1].update();
        else
            return;
    }
    /* note: this update routine can be thought of updating a consectutive series of '1's when viewing
     * m_count in binary form. For example, when m_count = 0b0111, this would suggest that stage 0 would
     * get updated (as it does every iteration) along with stage 1, 2, 3. when m_count is incremented
     * to 0b1000, stage 0 would get updated, however, no other stage would update seeing as how the next
     * value in the binary representation is zero. Incrementing one more time yields 0b1001. In this
     * case, stage 0 is updated along with stage 1 (since the next bit = 1). The next bit is zero
     * and the updates stop. Incrementing two more times to 0b1011 would then update stages 0, 1, and 2*/
}

void DyadicPoly::init()
{
    createQMFBanks();
    mapDyadicBankOutputs();
    assignImpReponses();
}

void DyadicPoly::createQMFBanks()
{
    // prepare QMF bank vector
    m_qmf_banks.clear();
    m_qmf_banks.reserve(m_num_of_subbands-1);

    // create QMF banks
    m_qmf_banks.push_back(PolyFIRQMF({1}, nullptr)); // imp response as '1' and nullptr will be overwritten later
    for(unsigned i = 1; i < m_num_of_subbands-1; i++)
    {
        std::shared_ptr<double> p_lowband(m_qmf_banks[i-1].getLowBandReference());
        m_qmf_banks.push_back(PolyFIRQMF({1}, p_lowband));
    }
}

void DyadicPoly::mapDyadicBankOutputs()
{
    for(unsigned i = 0; i < m_p_subbands.size() - 1; i++)
    {
        m_p_subbands[i] = m_qmf_banks[i].getHighBandReference();
    }
    m_p_subbands[m_p_subbands.size()-1] = m_qmf_banks[m_qmf_banks.size()-1].getLowBandReference();
}

void DyadicPoly::assignImpReponses()
{
    for(unsigned i = 0; i < m_qmf_banks.size(); i++)
    {
        m_qmf_banks[i].setLowPassImpResponse(m_fir_imp_response);
    }
}
