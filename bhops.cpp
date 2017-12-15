#include "sdk.h"
#include <memory>
#include "vmthook.h"
using namespace std;

unique_ptr<VMTHook> = clientmode;
IBaseClientDLL* clientDLL = nullptr;
IVEngineClient* engine = nullptr;
IClientEntityList* entityList = nullptr;

typedef void* (*GetClientModeFn)();

bool CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd) {
    if (cmd && cmd->command_number) {
        C_BaseEntity* player = reinterpret_cast<C_BaseEntity*>(entityList->GetClientEntity());
    }   
}

int __attribute__((constructor)) init() {
    clientDLL = GetInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", CLIENT_DLL_INTERFACE_VERSION);
    engine = GetInterface<IVEngineClient>("./csgo/bin/linux64/engine_client.so", VENGINE_CLIENT_INTERFACE_VERSION);
    entityList = GetInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", VCLIENTENTITYLIST_INTERFACE_VERSION);

    const uintptr_t HUDProcessInput = reinterpret_cast<uintptr_t>(GetVirtualTable(clientDLL)[10]);
    GetClientModeFn GetClientMode = reinterpret_cast<GetClientModeFn>(GetAbsoluteAddress(HUDProcessInput + 11, 1, 5));
    
    clientmode = make_unique<VMTHook>(GetClientMode());
    clientmode->HookFunction(reinterpret_cast<void*>(CreateMove), 5);
}
