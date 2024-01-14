//
// Created by kane on 14/01/24.
//

#include <rtype/IAudioModule.hh>

rtype::AudioModuleException::AudioModuleException(std::string &&perror_msg)
{
    m_error_msg = perror_msg;
}

const char *rtype::AudioModuleException::what() const noexcept
{
    return m_error_msg.c_str();
}
