//==============================================================================
//
//  PushProviderApplication 
//
//  Created by Getroot
//  Copyright (c) 2020 AirenSoft. All rights reserved.
//
//==============================================================================


#include "application.h"
#include "provider.h"
#include "provider_private.h"
// #include <cpr/cpr.h>
#include <curl/curl.h>

namespace pvd
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

	PushApplication::PushApplication(const std::shared_ptr<PushProvider> &provider, const info::Application &application_info)
		: Application(provider, application_info)
	{
	}

	bool PushApplication::JoinStream(const std::shared_ptr<PushStream> &stream)
	{
		logti("JOINED STREAM %s %s", GetName().CStr(), stream->GetName().CStr());		

		stream->SetApplication(GetSharedPtrAs<Application>());
		stream->SetApplicationInfo(GetSharedPtrAs<Application>());

		// authentication layer (middleware via external server)
		ov::String authenticationUrl = stream->GetApplication()->GetConfig().GetAuthentication();
		logti("Authentication url %s", authenticationUrl);
		if (authenticationUrl.GetLength() > 0) {
			CURL *curl;
			CURLcode res;

			curl_global_init(CURL_GLOBAL_DEFAULT);

			logti("Authentication middleware %s", stream->GetName().CStr());

			std::string newStreamName;
			curl = curl_easy_init();
			if (curl) {
				
				curl_easy_setopt(curl, CURLOPT_URL, ov::String::FormatString("%s/%s", authenticationUrl.CStr(), stream->GetName().CStr()).CStr());

				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, &newStreamName);

				res = curl_easy_perform(curl);

				if (res != CURLE_OK) {
					curl_easy_cleanup(curl);
					return false;
				}

				long response_code;
				curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

				logti("Query successful! %u %s", response_code, newStreamName.c_str());

				if (response_code != 200) {
					curl_easy_cleanup(curl);
					return false;
				}

				// update stream name
				stream->SetName(ov::String(newStreamName.c_str()));
				
				curl_easy_cleanup(curl);
			}
		}
		
		if(GetStreamByName(stream->GetName()) != nullptr)
		{
			logti("Reject %s/%s stream it is a stream with a duplicate name.", GetName().CStr(), stream->GetName().CStr());		
			return false;
		}
	
		if(stream->IsReadyToReceiveStreamData() == false)
		{
			logte("The stream(%s/%s) is not yet ready to be published.", GetName().CStr(), stream->GetName().CStr());
			return false;
		}

		std::unique_lock<std::shared_mutex> streams_lock(_streams_guard);
		_streams[stream->GetId()] = stream;
		streams_lock.unlock();

		NotifyStreamCreated(stream);

		return true;
	}

	bool PushApplication::DeleteAllStreams()
	{
		return Application::DeleteAllStreams();
	}
}