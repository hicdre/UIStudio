#pragma once
#include "Base\base_defines.h"

template <class T>
class Ref
{
public:
	Ref() {}
	~Ref() {}

	void AddRef() const
	{
		InterlockedIncrement(&_ref);
	}

	void Release() const
	{
		if (InterlockedDecrement(&_ref) == 0)
		{
			delete static_cast<const T*>(this);
		}
	}

private:
	mutable uint32 _ref{ 0 };

	DISALLOW_COPY_AND_ASSIGN(Ref);
};

class RefCount : public Ref < RefCount >
{
public:
	RefCount() : ref_count_(0) {}

	bool IsValid() const {
		return (int32)InterlockedCompareExchange(&ref_count_, 0, 0) > 0;
	}

	int32 Increment() const {
		return InterlockedIncrement(&ref_count_);
	}
	int32 Decrement() const {
		return InterlockedDecrement(&ref_count_);
	}

private:
	mutable uint32 ref_count_;
};