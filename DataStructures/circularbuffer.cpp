#include "circularbuffer.h"
#include <vector>

CircularBuffer::CircularBuffer(unsigned size)
{
	setBufferSize(size);
}

void CircularBuffer::insert(double val)
{
    m_index_write = (m_index_write + 1) & m_buffer_mask;
    m_buffer[m_index_write] = val;
}

void CircularBuffer::clear()
{
	std::fill(m_buffer.begin(), m_buffer.end(), 0);
}

void CircularBuffer::setBufferSize(unsigned size)
{
	m_buffer.resize(calcBufferSize(size));
    m_buffer_mask = (m_buffer.size() - 1);
}

unsigned CircularBuffer::getBufferSize()
{
	return m_buffer.size();
}


double& CircularBuffer::operator[] (unsigned index)
{
    return m_buffer[(m_index_write - index) & m_buffer_mask];

    /* Note that the write index is incremented right before a 'insert' call. Thus, the write index within
     this method corresponds to the most recently inserted value (i.e. not one ahead) */
}

/********************
 * Private Functions
 ********************/

unsigned CircularBuffer::calcBufferSize(unsigned size)
{
    double temp;
    temp = std::log2(size);
    temp = std::ceil(temp);
    temp = std::pow(2, temp);
    return (unsigned) temp;
}



