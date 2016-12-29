#ifndef DIGITALFILTER_H
#define DIGITALFILTER_H

/// DigitalFilter is an abstract class that should be used to implement digital filters.
class DigitalFilter
{
    public:
        virtual ~DigitalFilter(){};

        /// Clears (zeros) the filter history
        virtual void clear() = 0;

        /// Methods calculates new filter output given an input
        /// @param input Filter input
        /// @return Filter output
		virtual double update(double input) = 0;

        /// Returns the filter order
        /// @return Filter order
        int getFilterOrder(){return m_filter_order;};
		
	protected:
		int m_filter_order;
};

#endif // DIGITALFILTER_H
