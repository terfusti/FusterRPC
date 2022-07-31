#ifndef CONFIG_H_TERFUSTI
#define CONFIG_H_TERFUSTI

#include <rapidjson/document.h>
#include <discord_rpc.h>

#include <string>

namespace Config
{
	using namespace rapidjson;
	inline Document config{};

	inline std::string applicationId{};
	inline DiscordRichPresence presence{};

	void Load() noexcept;
}

#endif // !CONFIG_H_TERFUSTI
