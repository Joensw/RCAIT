#ifndef CE_STRING_H
#define CE_STRING_H

struct CE_String : public QLatin1String
{
    constexpr CE_String(const char* const s) :
            QLatin1String(s, static_cast<int>(std::char_traits<char>::length(s))) {}
};

#endif //CE_STRING_H
