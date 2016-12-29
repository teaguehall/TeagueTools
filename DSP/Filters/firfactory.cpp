#include "firfactory.h"
#include "firtype1.h"
#include "firtype2.h"
#include "firtype3.h"
#include "firtype4.h"
#include "firdirectform.h"

std::unique_ptr<FIRFilter> FIRFactory::getFilter(std::vector<double> impulse_response)
{
    if(isLinearPhaseType1(impulse_response))
        return std::unique_ptr<FIRType1>{new FIRType1(impulse_response)};
    if(isLinearPhaseType2(impulse_response))
        return std::unique_ptr<FIRType2>{new FIRType2(impulse_response)};
    if(isLinearPhaseType3(impulse_response))
        return std::unique_ptr<FIRType3>{new FIRType3(impulse_response)};
    if(isLinearPhaseType4(impulse_response))
        return std::unique_ptr<FIRType4>{new FIRType4(impulse_response)};
    else
        return std::unique_ptr<FIRDirectForm>{new FIRDirectForm(impulse_response)};
}

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

