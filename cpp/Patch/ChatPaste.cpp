#include "ChatPaste.h"
#include "../Helpers/FastDestroyableSingleton.h"

using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

	void ChatPaste::pastepatch::Postfix()
	{
		if (FastDestroyableSingleton<HudManager*>::getInstance().Chat::IsOpen && SaveManager->chatModeType == 1)
		{
			if (Input->GetKey(KeyCode::LeftControl) && Input->GetKeyDown(KeyCode::V))
			{
				FastDestroyableSingleton<HudManager*>::getInstance().Chat::TextArea::SetText(FastDestroyableSingleton<HudManager*>::getInstance().Chat::TextArea::text + GUIUtility::systemCopyBuffer);
				FastDestroyableSingleton<HudManager*>::getInstance().Chat::quickChatMenu::ResetGlyphs();
			}
			if (Input->GetKey(KeyCode::LeftControl) && Input->GetKeyDown(KeyCode::X))
			{
				GUIUtility->systemCopyBuffer = FastDestroyableSingleton<HudManager*>::getInstance().Chat::TextArea::text;
				FastDestroyableSingleton<HudManager*>::getInstance().Chat::TextArea->Clear();
				FastDestroyableSingleton<HudManager*>::getInstance().Chat::quickChatMenu::ResetGlyphs();
			}
			if (Input->GetKey(KeyCode::LeftControl) && Input->GetKeyDown(KeyCode::C))
			{
				GUIUtility->systemCopyBuffer = FastDestroyableSingleton<HudManager*>::getInstance().Chat::TextArea::text;
				FastDestroyableSingleton<HudManager*>::getInstance().Chat::quickChatMenu::ResetGlyphs();
			}
		}
	}
}
