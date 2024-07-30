#include "handler.h"
#include "register.h"
#include "ds_rpc.h"
#include "natives.hpp"
#include <chrono>
#include "common.hpp"
#pragma comment(lib, "discord-rpc.lib")

using namespace big;

void discordhandler::Init() {
    DiscordEventHandlers handlers;
    std::memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize("1251250463957979166", &handlers, 1, "0");
}

void discordhandler::Tick() {
    static int64_t StartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    DiscordRichPresence discordPresence;
    std::memset(&discordPresence, 0, sizeof(discordPresence));
    if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
        discordPresence.state = "Playing in online";
        discordPresence.partySize = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
        discordPresence.partyMax = 32;
    }
    else {
        discordPresence.state = "Playing in story mode";
    }

    discordPresence.details = "Moding With BigBase By XIFI";

    discordPresence.startTimestamp = StartTime;
    discordPresence.largeImageKey = "compressjpeg_online_512x512_image";
    discordPresence.smallImageKey = "gta";
    discordPresence.smallImageText = "V1.0.2";
    discordPresence.largeImageText = "compressjpeg_online_512x512_image";
    discordPresence.instance = 1;
    Discord_UpdatePresence(&discordPresence);
}

void discordhandler::Shutdown() {
    Discord_ClearPresence();
    Discord_Shutdown();
}