#include "firfactory.h"
#include "linearphasetype1.h"
#include "linearphasetype2.h"
#include "linearphasetype3.h"
#include "linearphasetype4.h"
#include "directformfirfilter.h"

/**
 * @brief Identifies the FIR filter type (type 1, 2, 3, 4) and returns the appropraite FIR object pointer
 * @param Impulse response of FIR filter
 * @return Returns a unique (smart) pointer to an appropriate FIR filter type object
 */
std::unique_ptr<FIRFilter> FIRFactory::getFilter(std::vector<double> impulse_response)
{
    if(isLinearPhaseType1(impulse_response))
        return std::unique_ptr<LinearPhaseType1>{new LinearPhaseType1(impulse_response)};
    if(isLinearPhaseType2(impulse_response))
        return std::unique_ptr<LinearPhaseType2>{new LinearPhaseType2(impulse_response)};
    if(isLinearPhaseType3(impulse_response))
        return std::unique_ptr<LinearPhaseType3>{new LinearPhaseType3(impulse_response)};
    if(isLinearPhaseType4(impulse_response))
        return std::unique_ptr<LinearPhaseType4>{new LinearPhaseType4(impulse_response)};
    else
        return std::unique_ptr<DirectFormFIRFilter>{new DirectFormFIRFilter(impulse_response)};
}

/**
 * @brief Checks to see if the impulse response is FIR Type 1
 * @param impulse_response Impulse response of FIR filter
 * @return Returns 'TRUE' if FIR is Type 1, returns false otherwise
 */
bool FIRFactory::isLinearPhaseType1(std::vector<double> impulse_response)
{
    if(!(impulse_response.size()%2)) // check for odd number of coefficients
        return false;

    for(unsigned i = 0; i < impulse_response.size()/2; i++)
    {
        if(impulse_response[i] != impulse_response[impulse_response.size()-1-i])
            return false;
    }

    return true;
}

/**
 * @brief Checks to see if the impulse response is FIR Type 2
 * @param impulse_response Impulse response of FIR filter
 * @return Returns 'TRUE' if FIR is Type 2, returns false otherwise
 */
bool FIRFactory::isLinearPhaseType2(std::vector<double> impulse_response)
{
    if(impulse_response.size()%2) // check for even number of coefficients
        return false;

    for(unsigned i = 0; i < impulse_response.size()/2; i++)
    {
        if(impulse_response[i] != impulse_response[impulse_response.size()-1-i])
            return false;
    }

    return true;
}

/**
 * @brief Checks to see if the impulse response is FIR Type 3
 * @param impulse_response Impulse response of FIR filter
 * @return Returns 'TRUE' if FIR is Type 3, returns false otherwise
 */
bool FIRFactory::isLinearPhaseType3(std::vector<double> impulse_response)
{
    if(!(impulse_response.size()%2)) // check for odd number of coefficients
        return false;

    for(unsigned i = 0; i < impulse_response.size()/2; i++)
    {
        if(impulse_response[i] != -1*impulse_response[impulse_response.size()-1-i])
            return false;
    }

    return true;
}

/**
 * @brief Checks to see if the impulse response is FIR Type 4
 * @param impulse_response Impulse response of FIR filter
 * @return Returns 'TRUE' if FIR is Type 4, returns false otherwise
 */
bool FIRFactory::isLinearPhaseType4(std::vector<double> impulse_response)
{
    if(impulse_response.size()%2) // check for even number of coefficients
        return false;

    for(unsigned i = 0; i < impulse_response.size()/2; i++)
    {
        if(impulse_response[i] != -1*impulse_response[impulse_response.size()-1-i])
            return false;
    }

    return true;
}

