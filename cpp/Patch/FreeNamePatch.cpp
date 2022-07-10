#include "FreeNamePatch.h"

using namespace TMPro;
using namespace UnityEngine;
using namespace UnityEngine::SceneManagement;

namespace SuperNewRoles::Patches
{

	void FreeNamePatch::Initialize()
	{
		SceneManager::add_sceneLoaded(static_cast<std::function<void(Scene*, LoadSceneMode*)>*>([&] (scene, _)
		{
			if (!scene::name->Equals(L"MMOnline"))
			{
				return;
			}
			if (!TryMoveObjects())
			{
				return;
			}
			auto editName = AccountManager::Instance->accountTab.editNameScreen;
			auto nameText = UnityEngine::Object::Instantiate(editName->nameText.gameObject);
			nameText->transform.localPosition += Vector3::up * 2.2f;
			auto textBox = nameText->GetComponent<TextBoxTMP*>();
			textBox->outputText->alignment = TextAlignmentOptions::CenterGeoAligned;
			textBox->outputText.transform->position = nameText->transform.position;
			textBox->outputText->fontSize = 4.0f;
			textBox->OnChange.AddListener(static_cast<std::function<void()>>([&] ()
			{
					SaveManager->PlayerName = textBox->text;
			}));
			textBox->OnEnter = textBox->OnFocusLost = textBox->OnChange;
			textBox->Pipe->GetComponent<TextMeshPro*>()->fontSize = 4.0f;
		}));
	}

	bool FreeNamePatch::TryMoveObjects()
	{
		auto toMove = std::vector<std::wstring> {L"HostGameButton", L"FindGameButton", L"JoinGameButton"};
		auto yStart = Vector3::up;
		auto yOffset = Vector3::down * 1.5f;
		auto gameObjects = toMove.Select([&] (std::any x)
		{
			GameObject::Find(L"NormalMenu/" + x);
		})->ToList();
		if (gameObjects.Any([&] (std::any x)
		{
			return x == nullptr;
		}))
		{
			return false;
		}
		for (auto i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i].transform->position = yStart + (yOffset * i);
		}
		return true;
	}
}
