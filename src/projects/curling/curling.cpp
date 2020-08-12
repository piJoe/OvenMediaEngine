#include <string>
#include <curl/curl.h>

namespace Curling
{
    size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
    {
        size_t newLength = size*nmemb;
        try
        {
            s->append((char*)contents, newLength);
        }
        catch(std::bad_alloc &e)
        {
            //handle memory problem
            return 0;
        }
        return newLength;
    }

    bool get(const char* url, long *response_code, std::string *response_message)
    {
        CURL *curl;
        CURLcode res;

        curl = curl_easy_init();
        if (!curl) {
            return false;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_message);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            curl_easy_cleanup(curl);
            return false;
        }

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, response_code);
        curl_easy_cleanup(curl);

        return true;
    }

    std::string escape(const char *unescaped_string)
    {
        CURL *curl = curl_easy_init();
        if(!curl) {
            return nullptr;
        }

        char *output = curl_easy_escape(curl, unescaped_string, 0);
        if(!output) {
            return nullptr;
        }
        std::string escaped_string = output;

        curl_free(output);
        curl_easy_cleanup(curl);

        return escaped_string;
    }

    void init()
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }
}