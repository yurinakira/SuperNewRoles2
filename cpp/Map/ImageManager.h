#pragma once

using namespace UnityEngine;

namespace SuperNewRoles::Map
{
	class ImageManager final
	{
	private:
		static Sprite *AgarthaAdminButton;
	public:
		static Sprite *GetAgarthaAdminButton();
	};
}
