#include "SuperNewRoles.CustomCosmetics.ShareCosmetics.NamePlatesObject.h"

namespace SuperNewRoles::CustomCosmetics::ShareCosmetics
{

	std::wstring NamePlatesObject::getName() const
	{
		return Name;
	}

	void NamePlatesObject::setName(const std::wstring &value)
	{
		Name = value;
	}

	std::wstring NamePlatesObject::getAuthor() const
	{
		return Author;
	}

	void NamePlatesObject::setAuthor(const std::wstring &value)
	{
		Author = value;
	}

	std::wstring NamePlatesObject::getUrl() const
	{
		return Url;
	}

	void NamePlatesObject::setUrl(const std::wstring &value)
	{
		Url = value;
	}
}
