#include "firfilter.h"

/**
 * @brief Constructs an FIRFilter with user specified impulse response
 * @param impulse_response Impulse response
 */
FIRFilter::FIRFilter(std::vector<double> impulse_response) :
    m_impulse_response(impulse_response)
{
    commonInitFilter();
}

/**
 * @brief Clears (zeros) the filter history
 */
void FIRFilter::clearFilter()
{
    m_buffer.clear();
}

/**
 * @brief Sets the transfer function of the FIR filter
 * @param impulse_response Impulse response
 */
void FIRFilter::setImpulseResponse(std::vector<double> impulse_response)
{
    m_impulse_response = impulse_response;
    commonInitFilter();
    initFilter();
}

/**
 * @brief Returns the impulse response of the filter
 * @return Returns impulse response
 */
std::vector<double> FIRFilter::getImpulseResponse()
{
    return m_impulse_response;
}

/******************* Protected *****************/

/**
 * @brief Function to be called when the filter needs to be initialized (e.g. after the
 * filter's impulse response has been modified). This function will be specific to classes
 * that derive from this class.
 */
void FIRFilter::initFilter()
{

}

/******************* Private *****************/
/**
 * @brief This function will be called to initialize the filter after the impulse response has
 * been modified. Note that this function contains initialization code that will be common for
 * all classes that derive from the FIRFilter class.
 */
void FIRFilter::commonInitFilter()
{
    m_filter_order = m_impulse_response.size() - 1;
    m_buffer.setBufferSize(m_impulse_response.size());
}
