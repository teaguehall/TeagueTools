#include "firdirectform.h"

FIRDirectForm::FIRDirectForm(std::vector<double> impulse_response) :
    FIRFilter(impulse_response)
{
    m_fir_type = FIRType::directform;
    init();
}

double FIRDirectForm::update(double input)
{
    double output = 0;
    m_buffer.insert(input);

    for(int i = 0; i < (m_filter_order + 1); i++)
    {
        output += m_impulse_response[i]*m_buffer[i];
    }
    return output;
}
