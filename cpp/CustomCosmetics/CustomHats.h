#pragma once

//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include "../stringhelper.h"
#include "../tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace SuperNewRoles::CustomCosmetics { class HatExtension; }
namespace SuperNewRoles::CustomCosmetics { class CustomHatLoader; }
namespace SuperNewRoles::CustomCosmetics { class CustomHatOnline; }

using namespace BepInEx;
using namespace BepInEx::Configuration;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace Il2CppSystem;
using namespace Newtonsoft::Json;
using namespace Newtonsoft::Json::Linq;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public class CustomHats
	class CustomHats
	{
	public:
		static Material *hatShader;

		static std::unordered_map<std::wstring, HatExtension*> CustomHatRegistry;
		static HatExtension *TestExt;
		static bool IsEnd;

	public:
		class HatExtension
		{
		private:
			std::wstring author;
			std::wstring package;
			std::wstring condition;
			Sprite *FlipImage;
			Sprite *BackFlipImage;

		public:
			std::wstring getAuthor() const;
			void setAuthor(const std::wstring &value);
			std::wstring getPackage() const;
			void setPackage(const std::wstring &value);
			std::wstring getCondition() const;
			void setCondition(const std::wstring &value);
			Sprite *getFlipImage() const;
			void setFlipImage(Sprite *value);
			Sprite *getBackFlipImage() const;
			void setBackFlipImage(Sprite *value);
		};

	public:
		class CustomHat
		{
		private:
			std::wstring author;
			std::wstring package;
			std::wstring condition;
			std::wstring name;
			std::wstring resource;
			std::wstring flipresource;
			std::wstring backflipresource;
			std::wstring backresource;
			std::wstring climbresource;
			bool bounce = false;
			bool adaptive = false;
			bool behind = false;

		public:
			std::wstring getAuthor() const;
			void setAuthor(const std::wstring &value);
			std::wstring getPackage() const;
			void setPackage(const std::wstring &value);
			std::wstring getCondition() const;
			void setCondition(const std::wstring &value);
			std::wstring getName() const;
			void setName(const std::wstring &value);
			std::wstring getResource() const;
			void setResource(const std::wstring &value);
			std::wstring getFlipresource() const;
			void setFlipresource(const std::wstring &value);
			std::wstring getBackflipresource() const;
			void setBackflipresource(const std::wstring &value);
			std::wstring getBackresource() const;
			void setBackresource(const std::wstring &value);
			std::wstring getClimbresource() const;
			void setClimbresource(const std::wstring &value);
			bool getBounce() const;
			void setBounce(bool value);
			bool getAdaptive() const;
			void setAdaptive(bool value);
			bool getBehind() const;
			void setBehind(bool value);
		};

	private:
		static std::vector<CustomHat*> createCustomHatDetails(std::vector<std::wstring> &hats, bool fromDisk = false);

		static Sprite *CreateHatSprite(const std::wstring &path, bool fromDisk = false);


//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
