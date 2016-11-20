#include "directformfirfilter.h"
#include <iostream>

/**
 * @brief Constructs direct form FIR filter with input specified impulse response
 * @param impulse_response Impulse response
 */

DirectFormFIRFilter::DirectFormFIRFilter(std::vector<double> impulse_response) :
    FIRFilter(impulse_response)
{
}

/**
 * @brief Accepts input and calculates filter output
 *
 * @param input Filter input
 * @return Returns filter output
 */
double DirectFormFIRFilter::update(double input)
{
    double output = 0;
    m_buffer.insert(input);
//    std::cout << "Inserted value: " << input << "\n";
 //   m_buffer.printBuffer();
 //   std::cout << "Summation: ";
    for(int i = 0; i < (m_filter_order + 1); i++)
    {
        output += m_impulse_response[i]*m_buffer[i];
//        std::cout << m_impulse_response[i] << "*" << m_buffer[i] << " + ";
    }
//    std::cout << " = ";
    return output;
}

/****************** Protected ***************/

/**
 * @brief Initializes the filter after a new impulse response has been configured
 */
void DirectFormFIRFilter::initFilter()
{

}
