#ifndef DISCORD_PRESENCE_H_TERFUSTI
#define DISCORD_PRESENCE_H_TERFUSTI

#include <discord_rpc.h>

namespace FusterPresence
{
	inline volatile bool interrupted{ false };


	void Init() noexcept;

	void Shutdown() noexcept;

	void OnReady(const DiscordUser* user) noexcept;

	void OnError(int errorCode, const char* message) noexcept;




}

#endif // !DISCORD_PRESENCE_H_TERFUSTI
