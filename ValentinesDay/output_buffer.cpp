
#include "output_buffer.hpp"

#include <cctype>
#include <ostream>
#include <functional>
#include <cassert>

output_buffer::output_buffer(std::ostream &sink, ::size_t buff_sz) :
    cap_next_(true),
    sink_(sink),
    buffer_(buff_sz + 1)
{
    sink_.clear();
    char *base = &buffer_.front();
    setp(base, base + buffer_.size() - 1);
}

output_buffer::int_type output_buffer::overflow(int_type ch)
{
    if (sink_ && ch != traits_type::eof())
    {
        assert(std::less_equal<char *>()(pptr(), epptr()));
        *pptr() = char(ch);
        pbump(1);
        if (do_caps_and_flush())
            return ch;
    }

    return traits_type::eof();
}

int output_buffer::sync()
{
    return do_caps_and_flush() ? 0 : -1;
}

bool output_buffer::do_caps_and_flush()
{
    for (char *p = pbase(), *e = pptr(); p != e; ++p)
    {
        if (*p == '.')
            cap_next_ = true;
        else if (::isalpha(*p))
        {
            if (cap_next_)
                *p = char(::toupper(*p));

            cap_next_ = false;
        }
    }
    ::ptrdiff_t n = pptr() - pbase();
    pbump(-n);

    return sink_.write(pbase(), n) == NULL ? false : true;
}

std::vector<char> output_buffer::getbuffer()
{
	return buffer_;
}
