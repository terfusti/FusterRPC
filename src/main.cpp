
#include "discord_presence.h"
#include <rapidjson/rapidjson.h>
#include <serialization.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <cassert>


int main()
{

	FusterPresence::Init();
	std::signal(SIGINT, [](int)
		{
			FusterPresence::interrupted = true;
		});

	do
	{
		
		Discord_RunCallbacks();
		std::this_thread::sleep_for(std::chrono::milliseconds{ 16 });

	} while (!FusterPresence::interrupted);

	FusterPresence::Shutdown();


	return 0;
}