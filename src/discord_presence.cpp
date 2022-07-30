#include "discord_presence.h"

#include "config.h"

#include <iostream>
#include <ctime>

namespace FusterPresence
{



	void Init() noexcept
	{
		Config::Load();
		DiscordEventHandlers handlers{};
		memset(&handlers, 0, sizeof(handlers));
		
		handlers.ready = OnReady;
		handlers.errored = OnError;
		Discord_Initialize(Config::applicationId.c_str(), &handlers, 1, nullptr);
		


		Discord_UpdatePresence(&Config::presence);

	}
	void Shutdown() noexcept
	{
		Discord_Shutdown();
	}

	void OnReady(const DiscordUser* user) noexcept
	{
		std::cout << "Connected to " << user->username << '#' << user->discriminator << '\n';
	}

	void OnError(int errorCode, const char* message) noexcept
	{
		std::cout << "Error code " << errorCode << ": " << message << '\n';
	}


}