/** Circular buffer data structure for data type 'double'
 *
 * This is a circular buffer data strucutre used for storing
 * and retrieving data of type 'double'. This data structure is efficient for FIFO
 * buffering.
 */

#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#define _DEBUG_CIRCULAR_BUFFER

#include <vector>

class CircularBuffer
{
    public:
        CircularBuffer(unsigned size = 8);
        void insert(double val);
        void clear();
        void setBufferSize(unsigned size);
		unsigned getBufferSize();
        double& operator[](unsigned i);

        #ifdef _DEBUG_CIRCULAR_BUFFER
            void printBuffer();
            void printPrevX(unsigned x);
        #endif
		
	private:
		std::vector<double> m_buffer;
		unsigned m_buffer_mask;
		unsigned m_index_write;
		unsigned m_index_read;
		
        unsigned calcBufferSize(unsigned input_size);
        unsigned calcBufferMask();
};

#endif // CIRCULARBUFFER_H
