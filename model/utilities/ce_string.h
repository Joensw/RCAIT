#ifndef CE_STRING_H
#define CE_STRING_H

/**
 * @brief Special version of a QLatin1String which is compliant to <code>constexpr</code>
 * Useful, because it supports methods of Qt's and otherwise,
 * one would have to use <code>std</code> C strings which are just char arrays
 */
struct CE_String : public QLatin1String {
    /**
     * @brief Constructs a CE_String
     * @param s C string to construct from
     */
    constexpr CE_String(const char *const s) :
            QLatin1String(s, static_cast<int>(std::char_traits<char>::length(s))) {}
};

#endif //CE_STRING_H
