#pragma once

using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles
{
//C# TO C++ CONVERTER TODO TASK: C# 'unsafe' code is not converted by C# to C++ Converter:
//	public static unsafe class FastDestroyableSingleton<T> where T : MonoBehaviour
//	{
//		private static readonly IntPtr _fieldPtr;
//		private static readonly Func<IntPtr, T> _createObject;
//		static FastDestroyableSingleton()
//		{
//			_fieldPtr = IL2CPP.GetIl2CppField(Il2CppClassPointerStore<DestroyableSingleton<T>>.NativeClassPtr, nameof(DestroyableSingleton<T>._instance));
//			var constructor = typeof(T).GetConstructor(new[] { typeof(IntPtr) });
//			var ptr = Expression.Parameter(typeof(IntPtr));
////C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
////ORIGINAL LINE: var create = Expression.New(constructor!, ptr);
//			var create = Expression.New(constructor, ptr);
//			var lambda = Expression.Lambda<Func<IntPtr, T>>(create, ptr);
//			_createObject = lambda.Compile();
//		}
//
//		public static T Instance
//		{
//			get
//			{
//				IntPtr objectPointer;
//				IL2CPP.il2cpp_field_static_get_value(_fieldPtr, & objectPointer);
//				if (objectPointer == IntPtr.Zero)
//					return DestroyableSingleton<T>.Instance;
//				return _createObject(objectPointer);
//			}
//		}
//	}
}
