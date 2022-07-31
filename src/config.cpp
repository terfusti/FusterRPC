#include "config.h"

#include <rapidjson/allocators.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

#include <cstdio>
#include <iostream>
#include <fstream>
#include <ostream>
#include <thread>

namespace Config
{
	void Load() noexcept
	{
		std::ifstream file{ "config.json" };

		if (file.is_open())
		{
			IStreamWrapper isw{ file };
			config.ParseStream(isw);
			if (config.HasMember("application_id"))
				applicationId = config["application_id"].GetString();

			if (config.HasMember("state"))
				presence.state = config["state"].GetString();

			if (config.HasMember("details"))
				presence.details = config["details"].GetString();

			if (config.HasMember("largeImageKey"))
				presence.largeImageKey = config["largeImageKey"].GetString();

			if (config.HasMember("largeImageText"))
				presence.largeImageText = config["largeImageText"].GetString();

			if (config.HasMember("smallImageKey"))
				presence.smallImageKey = config["smallImageKey"].GetString();

			if (config.HasMember("smallImageText"))
				presence.smallImageText = config["smallImageText"].GetString();

			if (config.HasMember("buttons"))
			{
				auto buttons{ config["buttons"].GetArray() };
				int index{ 0 };
				for (const auto& button : buttons)
				{
					if (button.IsObject())
					{
						if (button.HasMember("label"))
							presence.buttons[index].label = button["label"].GetString();
						if (button.HasMember("url"))
							presence.buttons[index].url = button["url"].GetString();
						++index;
					}
				}
			}

			presence.startTimestamp = std::time(nullptr);
			file.close();
		}
		else
		{
			std::cout << "Please fill in config!\n";

			std::ofstream outFile{ "config.json" };
			if (outFile.is_open())
			{
				OStreamWrapper osw{ outFile };
				PrettyWriter<OStreamWrapper> writer{ osw };

				writer.StartObject();
				writer.Key("application_id");
				writer.String("Go to https://discord.com/developers/applications, create application, and put application id here");
				writer.Key("state");
				writer.String("this goes under details in profile");
				writer.Key("details");
				writer.String("this goes above state in profile");
				writer.Key("largeImageKey");
				writer.String("From dev portal, go to Rich Presence, then add asset and put name here");
				writer.Key("largeImageText");
				writer.String("Text for when hovered over image");
				writer.Key("smallImageKey");
				writer.String("LOOK ABOVE");
				writer.Key("smallImageText");
				writer.String("LOOK ABOVE");

				writer.Key("buttons");
				writer.StartArray();

				writer.Key("button 1");
				writer.StartObject();
				writer.Key("label");
				writer.String("The text on the button");
				writer.Key("url");
				writer.String("The URL it directs you to (MUST HAVE BOTH TO WORK)");
				writer.EndObject();

				writer.Key("button 2");
				writer.StartObject();
				writer.Key("label");
				writer.String("Same as first button");
				writer.Key("url");
				writer.String("Please set both ;(");
				writer.EndObject();


				writer.EndArray();
				writer.EndObject();

				outFile.close();
			}
			else
			{
				std::cout << "Error creating config.json!\n";
			}

			std::ofstream tutFile{ "READ_ME_FIRST.txt" };
			if (tutFile.is_open())
			{
				tutFile << "Welcome to FusterRPC. This will set your rich presence and all that jazz. To start, replace all the descriptions in the config.json. LEAVE THE ONES YOU DONT WANT BLANK. You firstly need to create a discord developer application, from there you can add assets and get the application id. For any questions / concerns feel free to message me on discord.\nTerfusti#5865";
				tutFile.close();
			}
			else
			{
				std::cout << "Error creating tutorial file!\n";
			}

			std::this_thread::sleep_for(std::chrono::seconds{ 3 });
			std::exit(-1);
		}
	}

}