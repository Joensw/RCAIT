#ifndef MAPADAPT_H
#define MAPADAPT_H

/**
 * @brief Utility class to use Key-Value Pair iterators with <code>QMap</code>s.
 * With this, all features of a <code>std::map</code> can be applied here
 * @usage C++ 17 structured bindings are fully supported \n\n
 * <code>for (const auto &[key, value]: MapAdapt(m_data)) {</code>
 * @tparam Container container type like QMap
 */
template<class Container>
class MapAdapt {
public:

    /**
     * @brief Adapts a given container
     * @param container input container to be adapted
     */
    explicit MapAdapt(const Container &container) : c(container) {}

    /**
     * @brief Gets the Key-Value Pair iterator beginning
     * @return begin of the key-value pair iterator
     */
    typename Container::const_key_value_iterator begin() const { return c.keyValueBegin(); }

    /**
     * @brief Gets the Key-Value Pair iterator ending
     * @return end of the key-value pair iterator
     */
    typename Container::const_key_value_iterator end() const { return c.keyValueEnd(); }

private:
    const Container &c;
};

#endif // MAPADAPT_H
