#include "circularbuffer.h"
#include <vector>

/** Constructs buffer of user specified size
 *
 *  Constructs a circular buffer with a user specified size. If no size is specified
 *  by the user, it will default to size 8.
 */
CircularBuffer::CircularBuffer(unsigned size)
{
	setBufferSize(size);
}

/** Clears (zeros) the contents of the buffer
 *
 */
void CircularBuffer::clear()
{
	std::fill(m_buffer.begin(), m_buffer.end(), 0);
}

/** Sets the buffer size
 *
 * This method sets the size of the buffer. Note that the size will actually be set
 * to a base 2 integer (2^n). Example: size = 7 -> size = 8
 * @param size The desired buffer size
 */
void CircularBuffer::setBufferSize(unsigned size)
{
	m_buffer.resize(calcBufferSize(size));
    m_buffer_mask = calcBufferMask();
}

/** Returns the size of the buffer
 *
 * @return Returns the buffer size
 */
unsigned CircularBuffer::getBufferSize()
{
	return m_buffer.size();
}

/** Inserts new value into the buffer
 *
 *
 * @param val Value to insert into buffer
 */
void CircularBuffer::insert(double val)
{
    m_index_write = (m_index_write + 1) & m_buffer_mask;
    m_buffer[m_index_write] = val;
}

/** [] operator returns previous buffer inputs
 *
 * The [] operator is used to return previous inputs into the buffer. An index value of zero
 * (buffer[0]) will return the most recently inserted value. An index value of one (buffer[1])
 * will return the value inserted prior to the most recent insert. This trend continues.
 * Indexes greater than the buffer size will rollover, thus there is no concern about
 * accessing out of bounds values.
 *
 * @param index Index used to access previous buffer inputs
 * @return Returns buffer value associated with index
 */
double& CircularBuffer::operator[] (unsigned index)
{
    return m_buffer[(m_index_write - index) & m_buffer_mask];
}

/************************* Private ****************************/

/** Calculates base 2 (2^n) buffer size
 *
 *  Due to the efficiencies and simplifications gained by having a buffer size
 *  of 2^n, where n is an integer, the user input buffer size will be modified to
 *  to be of base 2.
 *
 * @param val Value to insert into buffer
 */
unsigned CircularBuffer::calcBufferSize(unsigned size)
{
    double temp;
    temp = std::log2(size);
    temp = std::ceil(temp);
    temp = std::pow(2, temp);
    return (unsigned) temp;
}

/** Calculates buffer mask (which is dependent on buffer size) */
unsigned CircularBuffer::calcBufferMask()
{
    return (m_buffer.size() - 1);
}

#ifdef _DEBUG_CIRCULAR_BUFFER
#include <iostream>
/** Prints contents of buffer */
void CircularBuffer::printBuffer()
{
    std::cout << "Buffer = ";
    for(unsigned i = 0; i < m_buffer.size(); i++)
    {
        std::cout << m_buffer[i] << " ";
    }
    std::cout << "\n";
}
/** Prints previous X elements of buffer */
void CircularBuffer::printPrevX(unsigned x)
{
    std::cout << "Previous " << x << " elements: ";
    for(unsigned i = 0; i < x; i++)
    {
        std::cout << (*this)[i] << " ";
    }
    std::cout << "\n";
}
#endif


