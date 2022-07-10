//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "CustomHats.h"
#include "../ModHelpers.h"
#include "../Helpers/CachedPlayer.h"
#include "../TranslateDate.h"
#include "../Main.h"
#include "../Config.h"

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

Material *CustomHats::hatShader;
std::unordered_map<std::wstring, HatExtension*> CustomHats::CustomHatRegistry;
CustomHats::HatExtension *CustomHats::TestExt = nullptr;
bool CustomHats::IsEnd = false;

	std::wstring CustomHats::HatExtension::getAuthor() const
	{
		return author;
	}

	void CustomHats::HatExtension::setAuthor(const std::wstring &value)
	{
		author = value;
	}

	std::wstring CustomHats::HatExtension::getPackage() const
	{
		return package;
	}

	void CustomHats::HatExtension::setPackage(const std::wstring &value)
	{
		package = value;
	}

	std::wstring CustomHats::HatExtension::getCondition() const
	{
		return condition;
	}

	void CustomHats::HatExtension::setCondition(const std::wstring &value)
	{
		condition = value;
	}

	Sprite *CustomHats::HatExtension::getFlipImage() const
	{
		return FlipImage;
	}

	void CustomHats::HatExtension::setFlipImage(Sprite *value)
	{
		FlipImage = value;
	}

	Sprite *CustomHats::HatExtension::getBackFlipImage() const
	{
		return BackFlipImage;
	}

	void CustomHats::HatExtension::setBackFlipImage(Sprite *value)
	{
		BackFlipImage = value;
	}

	std::wstring CustomHats::CustomHat::getAuthor() const
	{
		return author;
	}

	void CustomHats::CustomHat::setAuthor(const std::wstring &value)
	{
		author = value;
	}

	std::wstring CustomHats::CustomHat::getPackage() const
	{
		return package;
	}

	void CustomHats::CustomHat::setPackage(const std::wstring &value)
	{
		package = value;
	}

	std::wstring CustomHats::CustomHat::getCondition() const
	{
		return condition;
	}

	void CustomHats::CustomHat::setCondition(const std::wstring &value)
	{
		condition = value;
	}

	std::wstring CustomHats::CustomHat::getName() const
	{
		return name;
	}

	void CustomHats::CustomHat::setName(const std::wstring &value)
	{
		name = value;
	}

	std::wstring CustomHats::CustomHat::getResource() const
	{
		return resource;
	}

	void CustomHats::CustomHat::setResource(const std::wstring &value)
	{
		resource = value;
	}

	std::wstring CustomHats::CustomHat::getFlipresource() const
	{
		return flipresource;
	}

	void CustomHats::CustomHat::setFlipresource(const std::wstring &value)
	{
		flipresource = value;
	}

	std::wstring CustomHats::CustomHat::getBackflipresource() const
	{
		return backflipresource;
	}

	void CustomHats::CustomHat::setBackflipresource(const std::wstring &value)
	{
		backflipresource = value;
	}

	std::wstring CustomHats::CustomHat::getBackresource() const
	{
		return backresource;
	}

	void CustomHats::CustomHat::setBackresource(const std::wstring &value)
	{
		backresource = value;
	}

	std::wstring CustomHats::CustomHat::getClimbresource() const
	{
		return climbresource;
	}

	void CustomHats::CustomHat::setClimbresource(const std::wstring &value)
	{
		climbresource = value;
	}

	bool CustomHats::CustomHat::getBounce() const
	{
		return bounce;
	}

	void CustomHats::CustomHat::setBounce(bool value)
	{
		bounce = value;
	}

	bool CustomHats::CustomHat::getAdaptive() const
	{
		return adaptive;
	}

	void CustomHats::CustomHat::setAdaptive(bool value)
	{
		adaptive = value;
	}

	bool CustomHats::CustomHat::getBehind() const
	{
		return behind;
	}

	void CustomHats::CustomHat::setBehind(bool value)
	{
		behind = value;
	}

	std::vector<CustomHat*> CustomHats::createCustomHatDetails(std::vector<std::wstring> &hats, bool fromDisk)
	{
		std::unordered_map<std::wstring, CustomHat*> fronts;
		std::unordered_map<std::wstring, std::wstring> backs;
		std::unordered_map<std::wstring, std::wstring> flips;
		std::unordered_map<std::wstring, std::wstring> backflips;
		std::unordered_map<std::wstring, std::wstring> climbs;

		for (int i = 0; i < hats.size(); i++)
		{
			std::wstring s = fromDisk ? hats[i][((int)hats[i].rfind(L"\\") + 1)..].Split(L'.')[0] : StringHelper::split(hats[i], L'.')[3];
			std::vector<std::wstring> p = StringHelper::split(s, L'_');

			std::unordered_set<std::wstring> options;
			for (int j = 1; j < p.size(); j++)
			{
				options.insert(p[j]);
			}

			if (std::find(options.begin(), options.end(), L"back") != options.end() && options.Contains(L"flip"))
			{
				backflips.emplace(p[0], hats[i]);
			}
			else if (std::find(options.begin(), options.end(), L"climb") != options.end())
			{
				climbs.emplace(p[0], hats[i]);
			}
			else if (std::find(options.begin(), options.end(), L"back") != options.end())
			{
				backs.emplace(p[0], hats[i]);
			}

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
