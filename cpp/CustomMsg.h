#pragma once

#include <string>
#include <vector>
#include <functional>

using namespace UnityEngine;

namespace SuperNewRoles
{
	class CustomMessage
	{
	private:
		TMPro::TMP_Text *text;
		static std::vector<CustomMessage*> customMessages;

	public:
		virtual ~CustomMessage()
		{
			delete text;
		}

		CustomMessage(const std::wstring &message, float duration);
	};
}
