#pragma once
#include "Base/base_defines.h"
#include "Base/ref.h"
#include "Base/ptr.h"

class Object
{
public:
	Object();
	virtual ~Object();

	void AddRef();
	void Release();


	WPtr<Object> GetWeakObject() {
		return GetWeak<Object>();
	}

	template <class T>
	WPtr<T> GetWeak() {
		return WPtr<T>(ref_, dynamic_cast<T*>(this));
	}

	template <class T>
	SPtr<T> GetSelf() {
		return SPtr<T>(dynamic_cast<T*>(this));
	}
private:
	SPtr<RefCount> ref_;

	DISALLOW_COPY_AND_ASSIGN(Object);
};