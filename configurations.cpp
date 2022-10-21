#include "configurations.h"

void configurations::insert(const property& config) 
{
    if (!exists(config)) {

        //insert unique properties only
        m_config_properties[config.hash_key()] = config;
    }
}

void configurations::insert(const property&& config)
{
    if (!exists(config)) {

        //insert unique properties only
        m_config_properties[config.hash_key()] = config;
    }
}

void configurations::remove(const property& config)
{
    if (exists(config)) {

        m_config_properties.erase(config.hash_key());
    }
}

bool configurations::exists(const property& config)
{
    const auto search = m_config_properties.find(config.hash_key());
    return search != m_config_properties.cend();
}

bool configurations::exists(const std::string& section, const std::string& key) const
{
    const auto search = m_config_properties.find(section + "_" + key);
    return search != m_config_properties.cend();
}
