#include "CustomMsg.h"
#include "Helpers/FastDestroyableSingleton.h"

using namespace UnityEngine;

namespace SuperNewRoles
{

std::vector<CustomMessage*> CustomMessage::customMessages;

	CustomMessage::CustomMessage(const std::wstring &message, float duration)
	{
		RoomTracker *roomTracker = FastDestroyableSingleton<HudManager*>::getInstance() == nullptr ? nullptr : FastDestroyableSingleton<HudManager*>::getInstance().roomTracker;
		if (roomTracker != nullptr)
		{
			GameObject *gameObject = UnityEngine::Object::Instantiate(roomTracker->gameObject);

			gameObject->transform.SetParent(FastDestroyableSingleton<HudManager*>::getInstance().transform);
			UnityEngine::Object::DestroyImmediate(gameObject->GetComponent<RoomTracker*>());
			text = gameObject->GetComponent<TMPro::TMP_Text*>();
			text->text = message;

			// Use local position to place it in the player's view instead of the world location
			gameObject->transform->localPosition = new Vector3(0, -1.8f, gameObject->transform.localPosition.z);
			customMessages.push_back(this);

			std::function<void(float)> tempVar([&] (p)
			{
				bool even = (static_cast<int>(p * duration / 0.25f)) % 2 == 0; // Bool flips every 0.25 seconds
				std::wstring prefix = even ? L"<color=#FCBA03FF>" : L"<color=#FF0000FF>";
				text->text = prefix + message + L"</color>";
				if (text != nullptr)
				{
					text->color = even ? Color::yellow : Color::red;
				}
				if (p == 1.0f && text != nullptr && text->gameObject != nullptr)
				{
					UnityEngine::Object::Destroy(text->gameObject);
					customMessages.Remove(this);
				}
			});
			FastDestroyableSingleton<HudManager*>::getInstance().StartCoroutine(Effects::Lerp(duration, &tempVar));
		}
	}
}
