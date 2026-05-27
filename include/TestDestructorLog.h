#pragma once

#include <string>
#include <vector>

class TestDestructorLog
{
public:
    static void log(const std::string& name)
    {
#ifdef UNIT_TESTING
        getLog().push_back(name);
#endif
    }

    static void clear()
    {
#ifdef UNIT_TESTING
        getLog().clear();
#endif
    }

    static const std::vector<std::string>& get()
    {
        return getLog();
    }

private:
    static std::vector<std::string>& getLog()
    {
        static std::vector<std::string> logData;
        return logData;
    }
};