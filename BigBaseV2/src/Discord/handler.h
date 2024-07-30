#pragma once
#include "register.h"
#include "ds_rpc.h"

namespace big {
    class discordhandler {
    public:
        void Init();
        void Tick();
        void Shutdown();
    };

    inline std::unique_ptr<discordhandler> g_Discord;
}