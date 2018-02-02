
#ifndef _OUTPUT_BUFFER_HPP_
#define _OUTPUT_BUFFER_HPP_

#include <streambuf>
#include <iosfwd>
#include <cstdlib>
#include <vector>

class output_buffer : public std::streambuf
{
    public:
        explicit output_buffer(std::ostream &sink, ::size_t buff_sz = 256);
		std::vector<char> getbuffer();

    protected:
        bool do_caps_and_flush();		

    private:
        int_type overflow(int_type ch);
        int sync();

        // copy ctor and assignment not implemented;
        // copying not allowed
        output_buffer(const output_buffer &);
        output_buffer &operator= (const output_buffer &);

    private:
        bool cap_next_;
        std::ostream &sink_;
        std::vector<char> buffer_;
};

#endif
