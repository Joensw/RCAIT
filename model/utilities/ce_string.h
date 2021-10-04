#ifndef CE_STRING_H
#define CE_STRING_H

/**
 * @brief Special version of a QLatin1String which is compliant to <code>constexpr</code>
 * Useful, because it supports methods of Qt's and otherwise,
 * one would have to use <code>std</code> C strings which are just char arrays
 */
struct CE_String final : public QLatin1String {
    /**
     * @brief Constructs a CE_String with implicit conversion from standard C string
     * @param s C string to construct from
     */
    /* implicit */ constexpr CE_String(const char *const s) : // NOLINT(google-explicit-constructor)
            QLatin1String(s, static_cast<int>(std::char_traits<char>::length(s))) {}
};

#endif //CE_STRING_H
