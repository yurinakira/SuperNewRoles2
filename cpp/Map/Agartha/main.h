#pragma once

namespace SuperNewRoles::Map::Agartha
{
	class main final
	{
	private:
		static int thisfloor;
	public:
		static int getFloor();
		static void setFloor(int value);
		static void ClearAndReloads();
	};
}
