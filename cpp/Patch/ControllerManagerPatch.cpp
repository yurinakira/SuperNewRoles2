#include "ControllerManagerPatch.h"

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

int ControllerManagerUpdatePatch::resolutionIndex = 0;

	void ControllerManagerUpdatePatch::Postfix(ControllerManager *__instance)
	{
		//解像度変更
		if (Input->GetKeyDown(KeyCode::F9))
		{
			resolutionIndex++;
			if (resolutionIndex >= resolutions->Length)
			{
				resolutionIndex = 0;
			}
			ResolutionManager::SetResolution(resolutions[resolutionIndex].Item1, resolutions[resolutionIndex].Item2, false);
		}
	}
}
