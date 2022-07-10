#pragma once

#include "SuperNewRoles.CustomCosmetics.ShareCosmetics.NamePlatesObject.h"
#include <string>
#include <vector>

namespace SuperNewRoles::CustomCosmetics::ShareCosmetics
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [DataContract] public partial class CosmeticsObject
	class CosmeticsObject
	{
	private:
		std::wstring GUID;
		std::vector<NamePlatesObject*> AllNamePlates;

	public:
		std::wstring getGUID() const;
		void setGUID(const std::wstring &value);
		std::vector<NamePlatesObject*> getAllNamePlates() const;
		void setAllNamePlates(const std::vector<NamePlatesObject*> &value);
	};
}
