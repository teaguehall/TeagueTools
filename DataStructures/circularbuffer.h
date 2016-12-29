#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <vector>

/// Circular buffer data structure for data type 'double'. This data struture is efficient
/// for FIFO buffering.
class CircularBuffer
{
    public:
        /// Constructs a circular buffer of specified size. If no size is specified,
        /// construction will default to size 8.
        CircularBuffer(unsigned size = 8);

        ///  Inserts new value into the buffer.
        /// @param val Value to insert into buffer
        void insert(double val);

        /// Clears (zeros) the contents of the buffer.
        void clear();

        ///  Sets the buffer size. This method sets the size of the buffer.
        /// Note that the size will actually be set to a base 2 integer (2^n).
        /// Example: size = 7 -> size = 8
        /// @param size The desired buffer size
        void setBufferSize(unsigned size);

        /// Returns the size of the buffer
        ///@return Buffer size
		unsigned getBufferSize();


        /// [] operator returns previous buffer inputs.
        /// The [] operator is used to return previous inputs into the buffer. An index value of zero
        /// (buffer[0]) will return the most recently inserted value. An index value of one (buffer[1])
        /// will return the value inserted prior to the most recent insert. This trend continues.
        /// Indexes greater than the buffer size will rollover, thus there is no concern about
        /// accessing out of bounds values.
        /// @param i Index used to access previous buffer inputs
        /// @return Returns buffer value associated with index
        double& operator[](unsigned i);
		
	private:
		std::vector<double> m_buffer;
		unsigned m_buffer_mask;
		unsigned m_index_write;
		unsigned m_index_read;

        /// Calculates base 2 (2^n) buffer size.
        /// Due to the efficiencies and simplifications gained by having a buffer size
        /// of 2^n, where n is an integer, the user input buffer size will be modified to
        /// to be of base 2.
        /// @param input_size Requested buffer size
        unsigned calcBufferSize(unsigned input_size);
};

#endif // CIRCULARBUFFER_H
