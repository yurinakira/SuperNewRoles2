#pragma once

#include <vector>
#include <type_traits>

using namespace Il2CppSystem::Collections::Generic;

namespace SuperNewRoles
{

	class EnumerationHelpers final
	{
	public:
		template<typename T>
		static std::vector<T> GetFastEnumerator(std::vector<T> &list)
		{
			static_assert(std::is_base_of<Il2CppSystem.Object, T>::value, L"T must inherit from Il2CppSystem.Object");

			return new Il2CppListEnumerable<T>(list);
		}
	};

//C# TO C++ CONVERTER TODO TASK: C# 'unsafe' code is not converted by C# to C++ Converter:
//	public unsafe class Il2CppListEnumerable<T> : System.Collections.Generic.IEnumerable<T>, System.Collections.Generic.IEnumerator<T> where T : Il2CppSystem.Object
//	{
//		private struct Il2CppListStruct
//		{
////C# TO C++ CONVERTER TODO TASK: C++ #pragma warning numbers are different from C# #pragma warning numbers:
//#pragma warning( disable: CS0169 )
//			private IntPtr _unusedPtr1;
//			private IntPtr _unusedPtr2;
////C# TO C++ CONVERTER TODO TASK: C++ #pragma warning numbers are different from C# #pragma warning numbers:
//#pragma warning( default: CS0169 )
//
////C# TO C++ CONVERTER TODO TASK: C++ #pragma warning numbers are different from C# #pragma warning numbers:
//#pragma warning( disable: CS0649 )
//			public IntPtr _items;
//			public int _size;
////C# TO C++ CONVERTER TODO TASK: C++ #pragma warning numbers are different from C# #pragma warning numbers:
//#pragma warning( default: CS0649 )
//		}
//
//		private static readonly int _elemSize;
//		private static readonly int _offset;
//		private static Func<IntPtr, T> _objFactory;
//
//		static Il2CppListEnumerable()
//		{
//			_elemSize = IntPtr.Size;
//			_offset = 4 * IntPtr.Size;
//
//			var constructor = typeof(T).GetConstructor(new[] { typeof(IntPtr) });
//			var ptr = Expression.Parameter(typeof(IntPtr));
////C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
////ORIGINAL LINE: var create = Expression.New(constructor!, ptr);
//			var create = Expression.New(constructor, ptr);
//			var lambda = Expression.Lambda<Func<IntPtr, T>>(create, ptr);
//			_objFactory = lambda.Compile();
//		}
//
//		private readonly IntPtr _arrayPointer;
//		private readonly int _count;
//		private int _index = -1;
//
//		public Il2CppListEnumerable(List<T> list)
//		{
//			var listStruct = (Il2CppListStruct * )list.Pointer;
//			_count = listStruct-> _size;
//			_arrayPointer = listStruct-> _items;
//		}
//
//		Object IEnumerator.Current => Current;
//		public T Current
//		{
//			get;
//			private set;
//		}
//
//		public bool MoveNext()
//		{
//			if (++_index >= _count)
//				return false;
//			var refPtr = * (IntPtr * )IntPtr.Add(IntPtr.Add(_arrayPointer, _offset), _index * _elemSize);
//			Current = _objFactory(refPtr);
//			return true;
//		}
//
//		public void Reset()
//		{
//			_index = -1;
//		}
//
//		public System.Collections.Generic.IEnumerator<T> GetEnumerator()
//		{
//			return this;
//		}
//
//		System.Collections.IEnumerator IEnumerable.GetEnumerator()
//		{
//			return this;
//		}
//
//		public void Dispose()
//		{
//		}
//	}
}
