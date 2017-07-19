//
//  String.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/19.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef String_hpp
#define String_hpp

#include "List.hpp"
#include "Allocation.hpp"

namespace st {
	namespace utf8 {
		typedef unsigned int uchar;
		typedef unsigned char byte;
	}

	template <class E /*Element*/, class MA /*Memry Allocation*/ = Mallocation>
	class String :
		public List<E, MA> {
	public:
		size_t length() const;				//character count expect null character

		bool Append(const E* elements, size_t size);

		bool Append(const E element);

		String();

		String(const E* t, size_t length);

		virtual ~String() {};
	};
	//
	// Implemenation
	//

	template <class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	size_t st::String<E, MA>::length() const
	{
		return _length - 1;					// expect the last null character '\0'
	}

	template <class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	bool String<E, MA>::Append(const element_type* elements, size_t size)
	{
		if (0 == size)
			return true;
		Remove(_length - 1);	//reomve last '\0'
		Injure(elements, size);
		if('\0' != elements[size - 1])
			AddAtLast('\0');		//set last '\0' if the elements is not end of '\0'
		return true;
	}

	template <class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	bool String<E, MA>::Append(const element_type element)
	{
		Remove(_length - 1);	//reomve last '\0'
		AddAtLast(element);
		if ('\0' != element)
			AddAtLast('\0');	//set last '\0' if the elements is not end of '\0'
		return true;
	}

	template <class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	String<E, MA>::String()
		:List<E,MA>("\0",1,32)
	{
	}

	template<class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	String<E, MA>::String(const E* str, size_t length)
		:List<E, MA>(str, length, length < 1)
	{
	}

	typedef String<char> string;
}

#endif /* String_hpp */
