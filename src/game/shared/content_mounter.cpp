#include "cbase.h"
#include "SteamCommon.h"
#ifdef CLIENT_DLL
#include "clientsteamcontext.h"
#endif
#include "filesystem.h"
#include "fmtstr.h"

#include "content_mounter.h"

void MountExtraContent()
{
	KeyValuesAD gameinfo("GameInfo");
	gameinfo->LoadFromFile(filesystem, "gameinfo.txt");

	if (gameinfo->GetBool("extracontent"))
	{
		if (steamapicontext->SteamApps()->BIsAppInstalled(420))
		{
			char ep2Path[MAX_PATH];
			steamapicontext->SteamApps()->GetAppInstallDir(420, ep2Path, sizeof(ep2Path));
			filesystem->AddSearchPath(CFmtStr("%s/ep2", ep2Path), "GAME");
		}

		if (steamapicontext->SteamApps()->BIsAppInstalled(380))
		{
			char ep1Path[MAX_PATH];
			steamapicontext->SteamApps()->GetAppInstallDir(380, ep1Path, sizeof(ep1Path));
			filesystem->AddSearchPath(CFmtStr("%s/episodic", ep1Path), "GAME");
		}

		if (steamapicontext->SteamApps()->BIsAppInstalled(220))
		{
			char hl2Path[MAX_PATH];
			steamapicontext->SteamApps()->GetAppInstallDir(420, hl2Path, sizeof(hl2Path));
			filesystem->AddSearchPath(CFmtStr("%s/hl2", hl2Path), "GAME");
		}

		if (steamapicontext->SteamApps()->BIsAppInstalled(243730))
		{
			char sdk2013SPPath[MAX_PATH];
			steamapicontext->SteamApps()->GetAppInstallDir(243730, sdk2013SPPath, sizeof(sdk2013SPPath));

			filesystem->AddSearchPath(CFmtStr("%s/ep2", sdk2013SPPath), "GAME");
			filesystem->AddSearchPath(CFmtStr("%s/episodic", sdk2013SPPath), "GAME");
			filesystem->AddSearchPath(CFmtStr("%s/hl2", sdk2013SPPath), "GAME");
		}
	}
}