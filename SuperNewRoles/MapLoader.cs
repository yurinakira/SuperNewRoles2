using BepInEx.IL2CPP.Utils;
using HarmonyLib;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;

namespace SuperNewRoles
{
	public static class MapLoader
	{
		private static ShipStatus skeld;
		public static ShipStatus Skeld { get {
				if (SubmergedCompatibility.Loaded)
				{
					return SubmergedCompatibility.GetSkeld();
				}
				else
				{
					return skeld;
				}
			} }

		private static ShipStatus airship;
		public static ShipStatus Airship
		{
			get
			{
				if (SubmergedCompatibility.Loaded)
				{
					return SubmergedCompatibility.GetAirship();
				}
				else
				{
					return airship;
				}
			}
		}

		public static ShipStatus Polus;

		public static GameObject SkeldObject => Skeld.gameObject;

		public static GameObject AirshipObject => Airship.gameObject;

		public static GameObject PolusObject => Polus.gameObject;

		public static IEnumerator LoadPolus()
		{
			while ((Object)(object)AmongUsClient.Instance == null)
			{
				yield return null;
			}
			AsyncOperationHandle<GameObject> polusAsset = AmongUsClient.Instance.ShipPrefabs.ToArray()[2].LoadAsset<GameObject>();
			while (!polusAsset.IsDone)
			{
				yield return null;
			}
			Polus = polusAsset.Result.GetComponent<ShipStatus>();
		}
		public static IEnumerator LoadMaps()
		{
			while ((Object)(object)AmongUsClient.Instance == null)
			{
				yield return null;
			}
			AsyncOperationHandle<GameObject> skeldAsset = AmongUsClient.Instance.ShipPrefabs.ToArray()[0].LoadAsset<GameObject>();
			while (!skeldAsset.IsDone)
			{
				yield return null;
			};
			skeld= skeldAsset.Result.GetComponent<ShipStatus>();
			AsyncOperationHandle<GameObject> airshipAsset = AmongUsClient.Instance.ShipPrefabs.ToArray()[4].LoadAsset<GameObject>();
			while (!airshipAsset.IsDone)
			{
				yield return null;
			}
			airship = airshipAsset.Result.GetComponent<ShipStatus>();
			AsyncOperationHandle<GameObject> polusAsset = AmongUsClient.Instance.ShipPrefabs.ToArray()[2].LoadAsset<GameObject>();
			while (!polusAsset.IsDone)
			{
				yield return null;
			}
			Polus = polusAsset.Result.GetComponent<ShipStatus>();
		}
	}


	[HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.Awake))]
	public static class AmongUsClient_Awake_Patch
	{
		[HarmonyPrefix]
		[HarmonyPriority(900)]
		public static void Prefix(AmongUsClient __instance)
		{
			if (!SubmergedCompatibility.Loaded)
			{
				((MonoBehaviour)(object)__instance).StartCoroutine(MapLoader.LoadMaps());
			}
			else
			{
				((MonoBehaviour)(object)__instance).StartCoroutine(MapLoader.LoadPolus());
			}
		}
	}
}