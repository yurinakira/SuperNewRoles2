#include "Fastboot.h"
#include "../Config.h"

using namespace HarmonyLib;

namespace SuperNewRoles::Patch
{

	void SplashLogoAnimatorPatch::Prefix(SplashManager *__instance)
	{
		if (ConfigRoles::getDebugMode()->Value)
		{
			__instance->sceneChanger.AllowFinishLoadingScene();
			__instance->startedSceneLoad = true;
		}
	}
}
