#include "SuperNewRoles.CustomCosmetics.ShareCosmetics.CosmeticsObject.h"

namespace SuperNewRoles::CustomCosmetics::ShareCosmetics
{

	std::wstring CosmeticsObject::getGUID() const
	{
		return GUID;
	}

	void CosmeticsObject::setGUID(const std::wstring &value)
	{
		GUID = value;
	}

	std::vector<NamePlatesObject*> CosmeticsObject::getAllNamePlates() const
	{
		return AllNamePlates;
	}

	void CosmeticsObject::setAllNamePlates(const std::vector<NamePlatesObject*> &value)
	{
		AllNamePlates = value;
	}
}
