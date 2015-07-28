#pragma once
#include "Base/base_defines.h"
#include <memory>
#include <vector>


typedef uint64 DelegateHandle;



class IDelegateInstanceBase
{
public:
	virtual ~IDelegateInstanceBase() {}
	virtual DelegateHandle GetHandle() const = 0;
	static DelegateHandle GenerateNewHandle();
};


template <class InstanceType>
class MultiDelegateBase
{
public:
	MultiDelegateBase() {}
	~MultiDelegateBase() { Clear(); }
	void Clear() 
	{
		for (auto iter = instance_list_.begin(); iter != instance_list_.end(); iter++)
		{			
			delete *iter;
		}
	}

	DelegateHandle AddInternal(InstanceType* p)
	{
		instance_list_.push_back(p);
		return p->GetHandle();
	}

	void Remove(DelegateHandle h)
	{
		for (auto iter = instance_list_.begin(); iter != instance_list_.end(); iter++)
		{	
			InstanceType* instance = *iter;
			if (instance->GetHandle() == h)
			{
				instance_list_.erase(iter);
			}
		}
	}

	const std::vector<InstanceType*>& GetInstanceList() const {
		return instance_list_;
	}

private:
	std::vector<InstanceType*> instance_list_;
};