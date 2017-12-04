#include "cbase.h"
#include "SteamCommon.h"
#ifdef CLIENT_DLL
#include "clientsteamcontext.h"
#endif
#include "filesystem.h"
#include "fmtstr.h"

#include "content_mounter.h"

#include "ienginevgui.h"
#include <vgui/ISurface.h>
#include <vgui/IVGui.h>
#include <vgui/ILocalize.h>
#include "tier3/tier3.h"

void AddEP2(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/ep2", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/ep2/ep2_sound_vo_english.vpk", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/ep2/ep2_pak.vpk", path), "GAME");
	g_pVGuiLocalize->AddFile("resource/ep2_%language%.txt");
}

void AddEP1(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/episodic", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/episodic/ep1_sound_vo_english.vpk", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/episodic/ep1_pak.vpk", path), "GAME");
	g_pVGuiLocalize->AddFile("resource/episodic_%language%.txt");
}

void AddHL2(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/hl2", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/hl2/hl2_sound_vo_english.vpk", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/hl2/hl2_pak.vpk", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/hl2/hl2_textures.vpk", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/hl2/hl2_sound_misc.vpk", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/hl2/hl2_misc.vpk", path), "GAME");
	g_pVGuiLocalize->AddFile("resource/hl2_%language%.txt");
}

void AddHL2MP(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/hl2mp", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/hl2mp/hl2mp_english.vpk", path), "GAME");
	filesystem->AddPackFile(CFmtStr("%s/hl2mp/hl2mp_pak.vpk", path), "GAME");
	g_pVGuiLocalize->AddFile("resource/hl2mp_%language%.txt");
}

void MountExtraContent()
{
	KeyValuesAD gameinfo("GameInfo");
	gameinfo->LoadFromFile(filesystem, "gameinfo.txt");

	if (steamapicontext->SteamApps()->BIsAppInstalled(420) && gameinfo->GetBool("ep2content"))
	{
		char ep2Path[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(420, ep2Path, sizeof(ep2Path));
		AddEP2(ep2Path);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(380) && (gameinfo->GetBool("ep1content") || gameinfo->GetBool("ep2content")))
	{
		char ep1Path[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(380, ep1Path, sizeof(ep1Path));
		AddEP1(ep1Path);
	}
	
	if (steamapicontext->SteamApps()->BIsAppInstalled(320) && gameinfo->GetBool("hl2mpcontent"))
	{
		char hl2mpPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(320, hl2mpPath, sizeof(hl2mpPath));
		AddHL2MP(hl2mpPath);
		AddHL2(hl2mpPath);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(220) && (gameinfo->GetBool("hl2content") || gameinfo->GetBool("ep1content") || gameinfo->GetBool("ep2content")))
	{
		char hl2Path[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(420, hl2Path, sizeof(hl2Path));
		AddHL2(hl2Path);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(243750) && gameinfo->GetBool("hl2mpcontent"))
	{
		char sdk2013MPPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(243750, sdk2013MPPath, sizeof(sdk2013MPPath));
		AddHL2MP(sdk2013MPPath);
		AddHL2(sdk2013MPPath);
	}
	
	if (steamapicontext->SteamApps()->BIsAppInstalled(243730))
	{
		char sdk2013SPPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(243730, sdk2013SPPath, sizeof(sdk2013SPPath));

		if (gameinfo->GetBool("ep2content"))
			AddEP2(sdk2013SPPath);
		
		if (gameinfo->GetBool("ep2content") || gameinfo->GetBool("ep1content"))
			AddEP1(sdk2013SPPath);
		
		if (gameinfo->GetBool("hl2content") || gameinfo->GetBool("ep1content") || gameinfo->GetBool("ep2content"))
			AddHL2(sdk2013SPPath);
	}
}