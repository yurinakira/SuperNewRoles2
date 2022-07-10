#pragma once

#include <string>

namespace SuperNewRoles::CustomCosmetics::ShareCosmetics
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [DataContract] public partial class NamePlatesObject
	class NamePlatesObject
	{
	private:
		std::wstring Name;
		std::wstring Author;
		std::wstring Url;

	public:
		std::wstring getName() const;
		void setName(const std::wstring &value);
		std::wstring getAuthor() const;
		void setAuthor(const std::wstring &value);
		std::wstring getUrl() const;
		void setUrl(const std::wstring &value);
	};
}
