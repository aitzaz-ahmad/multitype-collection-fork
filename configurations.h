#pragma once

#include <any>
#include <string>
#include <optional>
#include <type_traits>
#include <unordered_map>


class property 
{
public:
    property(const std::string& section,
             const std::string& key,
             const std::any& val):  m_section(section),
                                    m_key(key),
                                    m_value(val) {
    }

    property() = default;
    ~property() = default;
    property(const property&) = default;
    property& operator=(const property&) = default;
    property(property&&) = default;
    property& operator=(property&&) = default;

    inline std::string hash_key() const {

        return m_section + "_" + m_key;
    }

    template<class T>
    std::optional<T> get_as() const 
    {

        if (!m_value.has_value())
            return std::optional<T>{};

        if(m_value.type() != typeid(T))
            return std::optional<T>{};
        
        return std::optional{ std::any_cast<T>(m_value) };
    }

private:

    std::string m_section;
    std::string m_key;
    std::any    m_value;
};

using server_configs = std::unordered_map<std::string, property>;

class configurations {
public:

    void insert(const property& config);
    void insert(const property&& config);

    void remove(const property& config);

    bool exists(const property& config);
    bool exists(const std::string& section, const std::string& key) const;
    
    template<class U>
    std::optional<U> get_value(const std::string& section,
                               const std::string& key) const
    {
        if (!exists(section, key)) {

            return std::optional<U>{};
        }

        const auto& config = m_config_properties.at(section + "_" + key);
        return std::optional{ config.get_as<U>() };
    }

    template<typename U>
    U get_value_or(const std::string& section,
                   const std::string& key,
                   const U default_value) const
    {
        const auto result = get_value<U>(section, key);
        return result.value_or(default_value);
    }

    /**
    * <-------  TODO  ------->
    * 
    * @author:  Aitzaz Ahmad
    * @date:    25.07.2022
    * 
    * @remark:  Consider adding an overload for the get_value function template
    *           which accepts a 'const property&' as an input.
    */

private:
    server_configs m_config_properties;
};
