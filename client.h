#pragma once
#include "Includes.hpp"
#include <filesystem>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

json m_resources;

#include <ctime>
#include <iostream>
#include <vector>

std::string gen_random(const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	std::string tmp_s;
	tmp_s.reserve(len);

	for (int i = 0; i < len; ++i) {
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return tmp_s;
}


auto m_manager = ManageResources;

class Client
{
public:

	void Execute(std::string script)
	{
		int numofresource = 0;

		std::string fileName = "client";
		std::string buffer;

		if (!API::filesystem::exists("C:\\MND1337\\exec\\"))
			API::filesystem::create_directories("C:\\MND1337\\exec\\");


		buffer += ("Citizen.CreateThread(function()\n");
		buffer += script;
		buffer += ("\nend)");

		std::string path;
		path += ("C:\\MND1337\\exec\\");
		path += fileName;
		path += (".lua");

		std::ofstream Loadscript;
		Loadscript.open(path);
		Loadscript << buffer;
		Loadscript.close();

		std::ofstream metadata;
		metadata.open(("C:\\MND1337\\exec\\fxmanifest.lua"));
		metadata << ("game 'gta5'\n");
		metadata << ("client_script '");
		metadata << fileName;
		metadata << (".lua'\n");
		metadata << ("fx_version 'cerulean'");
		metadata.close();
		//now we create an random resource name

		try
		{
			auto Scrpting = ManageResources->CreateResource(gen_random(8), nullptr);
			Scrpting->SetComponent(new ResourceCacheEntryList{});
			Scrpting->LoadFrom("C:\\MND1337\\exec\\");
			Scrpting->Start();
		}
		catch (...)
		{

		}


	}

	void ToggelResource(std::string resourceName)
	{
		if (resourceName == "_cfx_internal" || resourceName == "")
			return;

		if (ManageResources->GetResource(resourceName)->GetState() == fx::ResourceState::Started)
		{
			ManageResources->GetResource(resourceName)->Stop();

		}
		else if (ManageResources->GetResource(resourceName)->GetState() == fx::ResourceState::Stopped)
		{
			ManageResources->GetResource(resourceName)->Start();

		}
	}
	std::string ResourceNameState(std::string name)
	{
		if (ManageResources->GetResource(name.c_str())->GetState() == fx::ResourceState::Started)
			return "Started";
		else if (ManageResources->GetResource(name.c_str())->GetState() == fx::ResourceState::Stopped)
			return "Freezed"; //Stopped/Freezed
		else if (ManageResources->GetResource(name.c_str())->GetState() == fx::ResourceState::Starting)
			return "Starting";
		else if (ManageResources->GetResource(name.c_str())->GetState() == fx::ResourceState::Stopping)
			return "Stopping";
		else if (ManageResources->GetResource(name.c_str())->GetState() == fx::ResourceState::Uninitialized)
			return "Uninitialized";
	}
	void DumpFiles() {

	}
	void DumpResourceFile(std::string resourcePath)
	{

	}

};