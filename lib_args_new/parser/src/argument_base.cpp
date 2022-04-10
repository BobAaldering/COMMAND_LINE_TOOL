#include <argument_base.h>

// The constructor. The long flag is used as an identification.
arguments::argument_base::argument_base(std::string flag_identification) :
    m_long_flag{std::move(flag_identification)}
{}

// Get the identification, so your long flag.
const std::string &arguments::argument_base::get_identification() const {
    return m_long_flag; // Return the long flag.
}