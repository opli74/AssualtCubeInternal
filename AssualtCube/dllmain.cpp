// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include <string>
#include "entities.h"

void LoopPlayers( Entities* entities )
{
    std::cout << "Local player name: " << entities->GetLocalPlayer()->GetName() << "\n";
    for ( Player* player : entities->GetEntities( ) )
    {
        std::cout << "Players' name: " << player->GetName() << "\n";
    }
}

void WINAPI main(HMODULE hModule)
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    // base address of process we have injected to
    UINT32 base = (UINT32)GetModuleHandle(L"ac_client.exe");
    std::cout << "Attached image base -> [0x" << std::uppercase << std::hex << base << "]\n";

    // get entities from game!!
    Entities* g_entities = ( Entities* )( base + 0x18AC00 );

   while ( 1 )
   {
       //press delete to exit process!!
        if( GetAsyncKeyState( VK_DELETE ) & 1) 
            break;

        //press control key to display player names
        if (GetAsyncKeyState( VK_CONTROL ) & 1)
            LoopPlayers( g_entities );
   }

    system("pause");

    FreeConsole();
    FreeLibraryAndExitThread(hModule, S_OK);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);
        CloseHandle(CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)main, hModule, NULL, NULL ));
    }
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

