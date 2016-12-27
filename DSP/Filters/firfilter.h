#ifndef FIRFILTER_H
#define FIRFILTER_H

#include "digitalfilter.h"
#include "../../DataStructures/circularbuffer.h"
#include <vector>

class FIRFilter : public DigitalFilter
{
    public:
        FIRFilter(std::vector<double> impulse_response ={1});
        virtual double update(double input) = 0;
        void clear();
        void setImpulseResponse(std::vector<double> impulse_response);
        std::vector<double> getImpulseResponse();
        enum FIRType {directform, linearphasetype1, linearphasetype2, linearphasetype3, linearphasetype4};
        FIRType getFIRType();

    protected:
        virtual void initFilter() = 0;
        std::vector<double> m_impulse_response;
        CircularBuffer m_buffer;
        FIRType m_fir_type;

    private:
        void commonInitFilter();
};

#endif // FIRFILTER_H
