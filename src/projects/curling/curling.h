#include <string>

namespace Curling
{
    bool get(const char* url, long* response_code, std::string* response_message);
    std::string escape(const char *string);
    void init();
}