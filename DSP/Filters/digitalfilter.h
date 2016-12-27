#ifndef DIGITALFILTER_H
#define DIGITALFILTER_H

class DigitalFilter
{
    public:
        DigitalFilter();
		virtual double update(double input) = 0;
        virtual void clear() = 0;
		int getFilterOrder();
		
	protected:
		int m_filter_order;

};

#endif // DIGITALFILTER_H
