#ifndef IIRFILTER_H
#define IIRFILTER_H

#include "digitalfilter.h"
#include "../../DataStructures/circularbuffer.h"
#include <vector>

class IIRFilter : public DigitalFilter
{
    public:
        IIRFilter(std::vector<double> tf_num = {1}, std::vector<double> tf_denom = {1});
        double update(double input);
        void clearFilter();

        void setTransferFunction(std::vector<double> tf_num, std::vector<double> tf_denom);
        void setTransferFunctionNum(std::vector<double> tf_num);
        void setTransferFunctionDenom(std::vector<double> tf_denom);
		
        std::vector<double> getTransferFunctionNum();
        std::vector<double> getTransferFunctionDenom();

    private:
        std::vector<double> m_tf_num;
        std::vector<double> m_tf_denom;
        CircularBuffer m_buffer_input;
        CircularBuffer m_buffer_output;
};

#endif // IIRFILTER_H
