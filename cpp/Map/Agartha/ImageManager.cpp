#include "ImageManager.h"
#include "../../ModHelpers.h"

using namespace UnityEngine;

namespace SuperNewRoles::Map::Agartha
{

Sprite *ImageManager::m_MiniMap;

	Sprite *ImageManager::getMiniMap()
	{
		if (m_MiniMap != nullptr)
		{
			return m_MiniMap;
		}
		m_MiniMap = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Agartha.MiniMap.png", 115.0f);
		return m_MiniMap;
	}

Sprite *ImageManager::m_ExileBackImage;

	Sprite *ImageManager::getExileBackImage()
	{
		if (m_ExileBackImage != nullptr)
		{
			return m_ExileBackImage;
		}
		m_ExileBackImage = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Agartha.ExileBack.png", 115.0f);
		return m_ExileBackImage;
	}

Sprite *ImageManager::m_Admin_Table;

	Sprite *ImageManager::getAdminTable()
	{
		if (m_Admin_Table != nullptr)
		{
			return m_Admin_Table;
		}
		m_Admin_Table = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Agartha.Admin_Table.png", 115.0f);
		return m_Admin_Table;
	}

Sprite *ImageManager::m_Room_Admin;

	Sprite *ImageManager::getRoomAdmin()
	{
		if (m_Room_Admin != nullptr)
		{
			return m_Room_Admin;
		}
		m_Room_Admin = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Agartha.Room_Admin.png", 115.0f);
		return m_Room_Admin;
	}

Sprite *ImageManager::m_Room_Meeting;

	Sprite *ImageManager::getRoomMeeting()
	{
		if (m_Room_Meeting != nullptr)
		{
			return m_Room_Meeting;
		}
		m_Room_Meeting = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Agartha.Room_Meeting.png", 115.0f);
		return m_Room_Meeting;
	}

Sprite *ImageManager::m_Object_Table1;

	Sprite *ImageManager::getObjectTable1()
	{
		if (m_Object_Table1 != nullptr)
		{
			return m_Object_Table1;
		}
		m_Object_Table1 = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Agartha.Object_Table1.png", 115.0f);
		return m_Object_Table1;
	}

Sprite *ImageManager::m_CustomExilePlayer;

	Sprite *ImageManager::getCustomExilePlayer()
	{
		if (m_CustomExilePlayer != nullptr)
		{
			return m_CustomExilePlayer;
		}
		m_CustomExilePlayer = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Agartha.CustomExilePlayer.png", 115.0f);
		return m_CustomExilePlayer;
	}

Sprite *ImageManager::m_Room_Security;

	Sprite *ImageManager::getRoomSecurity()
	{
		if (m_Room_Security != nullptr)
		{
			return m_Room_Security;
		}
		m_Room_Security = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.Agartha.Room_Security.png", 115.0f);
		return m_Room_Security;
	}
}
