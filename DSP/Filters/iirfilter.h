#ifndef IIRFILTER_H
#define IIRFILTER_H

#include "digitalfilter.h"
#include <vector>

class IIRFilter : public DigitalFilter
{
    public:
        IIRFilter(std::vector<double> b_coefs = {1}, std::vector<double> a_coefs = {1});
        virtual double update(double input) = 0;
        virtual void clearFilter() = 0;

        void setCoefs(std::vector<double> b_coefs, std::vector<double> a_coefs);
        void setACoefs(std::vector<double> a_coefs);
        void setBCoefs(std::vector<double> b_coefs);
		
        std::vector<double> getACoefs();
        std::vector<double> getBCoefs();

    protected:
        std::vector<double> m_a_coefs;
        std::vector<double> m_b_coefs;

        virtual void initFilter() = 0;

    private:
        void commonInitFilter();

};

#endif // IIRFILTER_H
