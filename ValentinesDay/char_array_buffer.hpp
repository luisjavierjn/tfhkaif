
#ifndef _CHAR_ARRAY_BUFFER_HPP_
#define _CHAR_ARRAY_BUFFER_HPP_

#include <streambuf>

class char_array_buffer : public std::streambuf
{
    public:
        char_array_buffer(const char *begin, const char *end);
        explicit char_array_buffer(const char *str);

    private:
        int_type uflow();
        int_type underflow();
        int_type pbackfail(int_type ch);
        std::streamsize showmanyc();
        
        // copy ctor and assignment not implemented;
		// copying not allowed
		char_array_buffer(const char_array_buffer &);
		char_array_buffer &operator= (const char_array_buffer &);

    private:
        const char * const begin_;
        const char * const end_;
        const char * current_;
};

#endif

