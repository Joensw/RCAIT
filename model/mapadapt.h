#ifndef MAPADAPT_H
#define MAPADAPT_H

template<class Container> class MapAdapt
{
public:
    MapAdapt(const Container& container) : c(container) {}
    typename Container::const_key_value_iterator begin() const { return c.keyValueBegin(); }
    typename Container::const_key_value_iterator end() const { return c.keyValueEnd(); }
private:
    const Container& c;
};

#endif // MAPADAPT_H
