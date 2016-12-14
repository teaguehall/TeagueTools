#ifndef QMFBANK_H
#define QMFBANK_H

#include <memory>

class QMFBank
{
    public:
        QMFBank(std::shared_ptr<double> p_in);
        void setInputReference(std::shared_ptr<double>);
		std::shared_ptr<double> getLowBandReference();
        std::shared_ptr<double> getHighBandReference();
        virtual void clearFilter() = 0;
        virtual void update() = 0;

    protected:
        std::shared_ptr<double> m_p_in;
        std::shared_ptr<double> m_p_out_lowband = std::make_shared<double>(0);
        std::shared_ptr<double> m_p_out_highband = std::make_shared<double>(0);		
};

#endif // QMFBANK_H
