#pragma once

#include <string>
#include <vector>
#include <functional>

// Taken from https://github.com/NuclearPowered/Reactor/ , licensed under the LGPLv3

using namespace TMPro;
using namespace UnityEngine;
using namespace UnityEngine::SceneManagement;
//C# TO C++ CONVERTER TODO TASK: C# to C++ Converter could not confirm whether this is a namespace alias or a type alias:
//using Object = UnityEngine::Object;

namespace SuperNewRoles::Patches
{
	class FreeNamePatch
	{
	public:
		static void Initialize();

	private:
		static bool TryMoveObjects();
	};
}
