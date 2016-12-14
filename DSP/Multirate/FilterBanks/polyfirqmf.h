#ifndef POLYFIRQMF_H
#define POLYFIRQMF_H

#include "qmfbank.h"
#include "../Filters/polyphasedownsample.h"
#include <memory>

class PolyFIRQMF : public QMFBank
{
    public:
        PolyFIRQMF(const std::vector<double>& imp_response_lowpass, std::shared_ptr<double> p_in);
        void setLowPassImpResponse(const std::vector<double>& lowpass_imp_response);
        std::vector<double> getLowpassImpResponse();
        std::vector<double> getHighpassImpResponse();
        void setInputReference(std::shared_ptr<double> p_in);
        void clearFilter();
        void update();

    private:
        PolyphaseDownSample m_polyfilter_lowband;
        PolyphaseDownSample m_polyfilter_highband;
        std::vector<double> m_imp_response_lowpass;
        std::vector<double> m_imp_response_highpass;

        void init();
        void calcHighpassImpResponse();
};

#endif // POLYFIRQMF_H
