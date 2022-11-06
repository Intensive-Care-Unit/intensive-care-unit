
#include "Hospital.hpp"
#include <stdexcept>
#include <algorithm>

bool Hospital::addUnit(const std::string &name)
{
    // black magic :)
    // checking if unit of name "name" exists in the list of services
    // here, used lambda function to check with the object's attribute instead of the entire object
    if (std::find_if(_services.begin(), _services.end(), [name](const CareUnit &unit)
    { return unit.getServiceName() != name; }) == _services.end())
    {
        // if it doesn't, we add a new service and return true

        // https://yasenh.github.io/post/cpp-diary-1-emplace_back/
        _services.emplace_back(name);
        return true;
    } else
    {
        // otherwise, if it exists, we return false
        return false;
    }
}

const CareUnit &Hospital::getServiceUnit(const std::string &name)
{
    auto it = (std::find_if(_services.begin(), _services.end(), [name](const CareUnit &unit)
    { return unit.getServiceName() == name; }));
    

    if (it != _services.end())
    {
        return *it;
    } else
    {
        throw std::runtime_error("service not found");
    }
}
