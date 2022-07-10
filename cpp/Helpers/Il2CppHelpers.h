#pragma once

#include <vector>
#include <typeinfo>
#include <functional>
#include <cstdint>
#include <type_traits>

using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles
{
	class Il2CppHelpers final
	{
	private:
		template<typename T>
		class CastHelper final
		{
			static_assert(std::is_base_of<Il2CppObjectBase, T>::value, L"T must inherit from Il2CppObjectBase");

		public:
			static std::function<T(std::intptr_t)> Cast;
		private:
			class StaticConstructor
			{
			public:
				StaticConstructor()
				{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
					auto constructor = typeid(T).GetConstructor(std::vector<std::type_info> {typeof(std::intptr_t)});
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
					auto ptr = Expression::Parameter(typeof(std::intptr_t));
	//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
	//ORIGINAL LINE: var create = Expression.New(constructor!, ptr);
					auto create = Expression::New(constructor, ptr);
					auto lambda = Expression::Lambda<std::function<T(std::intptr_t)>*>(create, ptr);
					Cast = lambda->Compile();
				}
			};

		private:
			static CastHelper::StaticConstructor staticConstructor;

		};

	public:
		template<typename T>
		static T CastFast(Il2CppObjectBase *obj)
		{
			static_assert(std::is_base_of<Il2CppObjectBase, T>::value, L"T must inherit from Il2CppObjectBase");

			T casted = dynamic_cast<T>(obj);
			if (casted != nullptr)
			{
				return casted;
			}
			return obj->Pointer.CastFast<T>();
		}

		template<typename T>
		static T CastFast(std::intptr_t ptr)
		{
			static_assert(std::is_base_of<Il2CppObjectBase, T>::value, L"T must inherit from Il2CppObjectBase");

			return CastHelper<T>::Cast(ptr);
		}
	};
}
