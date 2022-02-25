#include "pch.h"
#include "include/FlashRuntimeExtensions.h"
#include <string>
#include <assert.h>
#include <sstream>
#include "include/discord_rpc.h"

#define _ITERATOR_DEBUG_LEVEL = 0;

static const char* APPLICATION_ID = "463369595441643530";

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


FREObject ASChangePresence(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
{
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));

	uint32_t strLength = 0;
	const uint8_t* state = NULL;
	FREGetObjectAsUTF8(argv[0], &strLength, &state);
	discordPresence.state = (const char*)state;

	const uint8_t* details = NULL;
	FREGetObjectAsUTF8(argv[1], &strLength, &details);
	discordPresence.details = (const char*)details;

	const uint8_t* largeImageKey = NULL;
	FREGetObjectAsUTF8(argv[2], &strLength, &largeImageKey);
	discordPresence.largeImageKey = (const char*)largeImageKey;

	const uint8_t* smallImageKey = NULL;
	FREGetObjectAsUTF8(argv[3], &strLength, &smallImageKey);
	discordPresence.smallImageKey = (const char*)smallImageKey;

	Discord_UpdatePresence(&discordPresence);

	FREObject retObj = NULL;
	FRENewObjectFromUTF8(sizeof(state), state, &retObj);

	return retObj;
}



void contextInitializer(
		void* extData,
		const uint8_t* ctxType,
		FREContext				   ctx,
		uint32_t* numFunctionsToSet,
		const FRENamedFunction** functionsToSet)
	{

	Discord_Initialize(APPLICATION_ID, NULL, 1, NULL);

	static FRENamedFunction extensionFunctions[] =
	{
		{ (const uint8_t*)"as_sendPresence",        NULL, &ASChangePresence }
	};

	*numFunctionsToSet = sizeof(extensionFunctions) / sizeof(FRENamedFunction);

	*functionsToSet = extensionFunctions;
}


void contextFinalizer(FREContext ctx)
{
	Discord_Shutdown();
	return;
}


extern "C"
{	
	__declspec(dllexport) void ExtensionInitializer(void** extData, FREContextInitializer* ctxInitializer, FREContextFinalizer* ctxFinalizer)
	{
		*ctxInitializer = &contextInitializer; // The name of function that will intialize the extension context
		*ctxFinalizer = &contextFinalizer; // The name of function that will finalize the extension context
	}

	__declspec(dllexport) void ExtensionFinalizer(void* extData)
	{
		return;		
	}
}
