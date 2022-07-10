//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "SetPosition.h"
#include "main.h"
#include "Agartha/ImageManager.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Map
{

	void SetPosition::ShipStatusAwakePatch::Postfix(ShipStatus *__instance)
	{
		ApplyChanges(__instance);
	}

	void SetPosition::ApplyChanges(ShipStatus *__instance)
	{
		if (Data::IsMap(CustomMapNames::Agartha))
		{
			if (__instance->Type == ShipStatus::MapType::Hq)
			{
				Transform *MiraShip = GameObject::Find(L"MiraShip(Clone)")->transform;

				Transform *Wall = MiraShip->FindChild(L"Walls");

				Wall->gameObject.AddComponent<EdgeCollider2D*>()->points = std::vector<Vector2*>
				{
					new Vector2(-6.25f, 3.0f),
					new Vector2(10.0f, 3.0f),
					new Vector2(10.0f, 5.6f),
					new Vector2(12.0f, 5.6f),
					new Vector2(12.0f, 23.6f),
					new Vector2(11.0f, 23.6f),
					new Vector2(11.0f, 27.4f),
					new Vector2(-6.25f, 27.4f),
					new Vector2(-6.25f, 22.0f),
					new Vector2(-12.25f, 22.0f),
					new Vector2(-12.5f, 24.0f),
					new Vector2(-10.5f, 24.0f),
					new Vector2(-10.5f, 26.7f),
					new Vector2(-15.5f, 26.7f),
					new Vector2(-15.5f, 24.0f),
					new Vector2(-13.5f, 24.0f),
					new Vector2(-13.5f, 22.0f),
					new Vector2(-19.0f, 22.0f),
					new Vector2(-19.0f, 26.7f),
					new Vector2(-25.3f, 26.7f),
					new Vector2(-25.3f, 15.5f),
					new Vector2(-23.0f,15.5f),
					new Vector2(-23.0f, 13.0f),
					new Vector2(-25.3f, 13.0f),
					new Vector2(-25.3f, 2.5f),
					new Vector2(-19.0f, 2.5f),
					new Vector2(-19.0f, 6.8f),
					new Vector2(-14.0f, 6.8f),
					new Vector2(-14.0f, 4.8f),
					new Vector2(-16.0f, 4.8f),
					new Vector2(-16.0f, 2.3f),
					new Vector2(-9.7f, 2.3f),
					new Vector2(-9.7f, 5.3f),
					new Vector2(-11.7f, 5.3f),
					new Vector2(-11.7f, 6.8f),
					new Vector2(-6.25f, 6.8f),
					new Vector2(-6.25f, 3.0f)
				};
				Wall->gameObject.AddComponent<EdgeCollider2D*>()->points = std::vector<Vector2*>
				{
					new Vector2(-5.25f, 4.0f),
					new Vector2(9.0f, 4.0f),
					new Vector2(9.0f, 6.0f),
					new Vector2(6.8f, 6.0f),
					new Vector2(6.8f, 8.0f),
					new Vector2(5.3f, 8.0f),
					new Vector2(5.3f, 7.0f),
					new Vector2(2.3f, 7.0f),
					new Vector2(2.3f, 11.0f),
					new Vector2(4.5f, 11.0f),
					new Vector2(5.3f, 10.0f),
					new Vector2(5.3f, 9.25f),
					new Vector2(6.8f, 9.25f),
					new Vector2(6.8f, 12.5f),
					new Vector2(10.8f, 12.5f),
					new Vector2(10.8f, 14.5f),
					new Vector2(5.8f, 14.5f),
					new Vector2(5.8f, 19.5f),
					new Vector2(4.0f, 19.5f),
					new Vector2(4.0f, 14.3f),
					new Vector2(-2.8f, 14.3f),
					new Vector2(-2.8f, 17.8f),
					new Vector2(-5.0f, 17.8f),
					new Vector2(-5.0f, 9.2f),
					new Vector2(-3.0f, 9.2f),
					new Vector2(-3.0f, 10.2f),
					new Vector2(-2.5f, 11.0f),
					new Vector2(0.0f, 11.0f),
					new Vector2(0.0f, 7.0f),
					new Vector2(-3.0f, 7.0f),
					new Vector2(-3.0f, 8.0f),
					new Vector2(-5.25f, 8.0f),
					new Vector2(-5.25f, 4.0f)
				};
				//会議室左上
				Wall->gameObject.AddComponent<EdgeCollider2D*>()->points = std::vector<Vector2*>
				{
					new Vector2(-5.0f, 19.3f),
					new Vector2(-5.0f, 25.5f),
					new Vector2(0.0f, 25.5f),
					new Vector2(0.0f, 23.7f),
					new Vector2(0.0f, 23.7f),
					new Vector2(-2.8f, 21.4f),
					new Vector2(-2.8f, 19.3f),
					new Vector2(-5.0f, 19.3f)
				};
				//会議室右上
				Wall->gameObject.AddComponent<EdgeCollider2D*>()->points = std::vector<Vector2*>
				{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
