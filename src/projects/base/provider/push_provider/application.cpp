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
#include <curling/curling.h>

namespace pvd
{
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
		logti("Authentication url %s", authenticationUrl.CStr());
		if (authenticationUrl.GetLength() > 0) {
			logti("Authentication middleware %s", stream->GetName().CStr());

			std::string newStreamName;
			long response_code;

			
			std::string escaped_streamname = Curling::escape(stream->GetName().CStr());
			std::string get_url = ov::String::FormatString("%s/%s", authenticationUrl.CStr(), escaped_streamname.c_str()).CStr();

			logti("Authentication full url %s (%s / %s)", get_url.c_str(), authenticationUrl.CStr(), escaped_streamname.c_str());

			if (!Curling::get(get_url.c_str(), &response_code, &newStreamName)) {
				return false;
			}

			logti("Query successful! %u %s", response_code, newStreamName.c_str());
			if (response_code != 200) {
				return false;
			}

			// update stream name
			stream->SetName(ov::String(newStreamName.c_str()));
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