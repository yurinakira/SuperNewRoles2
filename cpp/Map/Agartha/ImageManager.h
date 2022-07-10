#pragma once

using namespace UnityEngine;

namespace SuperNewRoles::Map::Agartha
{
	class ImageManager final
	{
	private:
		static Sprite *m_MiniMap;
	public:
		static Sprite *getMiniMap();
	private:
		static Sprite *m_ExileBackImage;
	public:
		static Sprite *getExileBackImage();
	private:
		static Sprite *m_Admin_Table;
	public:
		static Sprite *getAdminTable();
	private:
		static Sprite *m_Room_Admin;
	public:
		static Sprite *getRoomAdmin();
	private:
		static Sprite *m_Room_Meeting;
	public:
		static Sprite *getRoomMeeting();
	private:
		static Sprite *m_Object_Table1;
	public:
		static Sprite *getObjectTable1();
	private:
		static Sprite *m_CustomExilePlayer;
	public:
		static Sprite *getCustomExilePlayer();
	private:
		static Sprite *m_Room_Security;
	public:
		static Sprite *getRoomSecurity();
	};
}
