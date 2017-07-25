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
		public List<E, MA>
    {
	public:
		size_t length() const;				//character count expect null character

		bool Append(const String<E,MA> &str);

		//append string whether the elements is or not end of '\0'
		bool Append(const E* elements, size_t size);

		bool Append(const E element);

		String();

		String(const E* e);

		String(const E* e, size_t length);

		virtual ~String() {};
	};


	//
	// Implemenation
	//



	template <class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	size_t st::String<E, MA>::length() const
	{
        return List<E,MA>::_length - 1;					// expect the last null character '\0'
	}

	template <class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	bool String<E, MA>::Append(const String<E, MA> &str)
	{
		return this->Append(str.GetElements(),str._length);
	}

	template <class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	bool String<E, MA>::Append(const E* elements, size_t size)
	{
		if (0 == size)
			return true;
		this -> Remove(List<E,MA>::_length - 1);	//reomve last '\0'
		this -> Injure(elements, size);
		if('\0' != elements[size - 1])
			List<E,MA>::AddAtLast('\0');		//set last '\0' if the elements is not end of '\0'
		return true;
	}

	template <class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	bool String<E, MA>::Append(const E element)
	{
		this -> Remove(List<E,MA>::_length - 1);	//reomve last '\0'
		this -> AddAtLast(element);
		if ('\0' != element)
			List<E,MA>::AddAtLast('\0');	//set last '\0' if the elements is not end of '\0'
		return true;
	}

	template <class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	String<E, MA>::String()
		:List<E,MA>("\0",1,32)
	{
	}

	template <class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	String<E, MA>::String(const E* e)
		: String<E, MA>(e, strlen(e) + 1)
	{
	}
	template<class E /*Element*/, class MA /*Memry Allocation*/ /*= Mallocation*/>
	String<E, MA>::String(const E* str, size_t length)
		:List<E, MA>(str, length, length << 1)
	{
	}

	typedef String<char> string;

	size_t strlen(const char *str);
	size_t strsize(const char *strs[], const char endChar);
}

#endif /* String_hpp */
