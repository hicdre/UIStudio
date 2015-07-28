#pragma once
#include "Delegate/DelegateBase.h"

#if 1 //接口定义

template <class ParamOneType, class ParamTwoType>
class IMethodDelegateBase_TwoParams : public IDelegateInstanceBase
{
public:	
	virtual ~IMethodDelegateBase_TwoParams() {}
	virtual void Execute(ParamOneType param1, ParamTwoType param2) const = 0;
};

#endif

#if 1 //接口实现

template <class ParamOneType, class ParamTwoType>
class MethodDelegateBase_TwoParams : public IMethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>
{
public:
	MethodDelegateBase_TwoParams() : handle_(GenerateNewHandle()) {}

	virtual DelegateHandle GetHandle() const override {
		return handle_;
	}
private:
	DelegateHandle handle_;
};

#if DELEGATE_SUPPORT_STDSP
template<class UserClass, class ParamOneType, class ParamTwoType>
class SPMethodDelegateBase_TwoParams_NoVar : public MethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>
{
public:
	typedef void (UserClass::*FMethodPtr)( ParamOneType, ParamTwoType );
	SPMethodDelegateBase_TwoParams_NoVar(const std::shared_ptr<UserClass>& object, 
		FMethodPtr method) : weakObject_(object), methodPtr_(method) {}

	virtual void Execute(ParamOneType param1, ParamTwoType param2) const override
	{
		std::shared_ptr<UserClass> object = weakObject_.lock();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)(param1, param2);
	}
		
private:
	std::weak_ptr<UserClass> weakObject_;
	FMethodPtr methodPtr_;	
};

template<class UserClass, class ParamOneType, class ParamTwoType, class VarOneType>
class SPMethodDelegateBase_TwoParams_OneVar : public MethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>
{
public:
	typedef void (UserClass::*FMethodPtr)( ParamOneType, ParamTwoType, VarOneType );
	SPMethodDelegateBase_TwoParams_OneVar(const std::shared_ptr<UserClass>& object, 
		FMethodPtr method,
		VarOneType var1) : weakObject_(object), methodPtr_(method)
		, var1_(var1)
	{}

	void Execute(ParamOneType param1, ParamTwoType param2) const
	{
		std::shared_ptr<UserClass> object = weakObject_.lock();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)(param1, param2, var1_);
	}	
private:
	std::weak_ptr<UserClass> weakObject_;
	FMethodPtr methodPtr_;
	VarOneType var1_;
};

template<class UserClass, class ParamOneType, class ParamTwoType, class VarOneType, class VarTwoType>
class SPMethodDelegateBase_TwoParams_TwoVar : public MethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>
{
public:
	typedef void (UserClass::*FMethodPtr)( ParamOneType, ParamTwoType, VarOneType, VarTwoType );
	SPMethodDelegateBase_TwoParams_TwoVar(const std::shared_ptr<UserClass>& object, 
		FMethodPtr method,
		VarOneType var1, VarTwoType var2) 
		: weakObject_(object), methodPtr_(method)
		, var1_(var1), var2_(var2)
	{}

	void Execute(ParamOneType param1, ParamTwoType param2) const
	{
		std::shared_ptr<UserClass> object = weakObject_.lock();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)(param1, param2, var1_, var2_);
	}

private:
	std::weak_ptr<UserClass> weakObject_;
	FMethodPtr methodPtr_;
	VarOneType var1_;
	VarTwoType var2_;
};
#endif //#if DELEGATE_SUPPORT_SP

#if DELEGATE_SUPPORT_WEAK
template<class UserClass, class ParamOneType, class ParamTwoType>
class WeakMethodDelegateBase_TwoParams_NoVar : public MethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>
{
public:
	typedef void (UserClass::*FMethodPtr)(ParamOneType, ParamTwoType);
	WeakMethodDelegateBase_TwoParams_NoVar(const WPtr<UserClass>& object,
		FMethodPtr method) : weakObject_(object), methodPtr_(method) {}

	void Execute(ParamOneType param1, ParamTwoType param2) const override
	{
		SPtr<UserClass> object = weakObject_.get();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)(param1, param2);
	}

private:
	WPtr<UserClass> weakObject_;
	FMethodPtr methodPtr_;
};

template<class UserClass, class ParamOneType, class ParamTwoType, class VarOneType>
class WeakMethodDelegateBase_TwoParams_OneVar : public MethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>
{
public:
	typedef void (UserClass::*FMethodPtr)(ParamOneType, ParamTwoType, VarOneType);
	WeakMethodDelegateBase_TwoParams_OneVar(const WPtr<UserClass>& object,
		FMethodPtr method,
		VarOneType var1) : weakObject_(object), methodPtr_(method)
		, var1_(var1)
	{}

	void Execute(ParamOneType param1, ParamTwoType param2) const
	{
		SPtr<UserClass> object = weakObject_.get();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)(param1, param2, var1_);
	}
private:
	WPtr<UserClass> weakObject_;
	FMethodPtr methodPtr_;
	VarOneType var1_;
};

template<class UserClass, class ParamOneType, class ParamTwoType, class VarOneType, class VarTwoType>
class WeakMethodDelegateBase_TwoParams_TwoVar : public MethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>
{
public:
	typedef void (UserClass::*FMethodPtr)(ParamOneType, ParamTwoType, VarOneType, VarTwoType);
	WeakMethodDelegateBase_TwoParams_TwoVar(const WPtr<UserClass>& object,
		FMethodPtr method,
		VarOneType var1, VarTwoType var2)
		: weakObject_(object), methodPtr_(method)
		, var1_(var1), var2_(var2)
	{}

	void Execute(ParamOneType param1, ParamTwoType param2) const
	{
		SPtr<UserClass> object = weakObject_.get();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)(param1, param2, var1_, var2_);
	}

private:
	WPtr<UserClass> weakObject_;
	FMethodPtr methodPtr_;
	VarOneType var1_;
	VarTwoType var2_;
};
#endif //DELEGATE_SUPPORT_WEAK

#if DELEGATE_SUPPORT_FUNCTOR
template<class FunctorType, class ParamOneType, class ParamTwoType>
class FunctorMethodDelegateBase_TwoParams_NoVar : public MethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>
{
public:
	FunctorMethodDelegateBase_TwoParams_NoVar(const FunctorType& functor)
		: functor_(functor) {}

	virtual void Execute(ParamOneType param1, ParamTwoType param2) const override
	{
		return functor_(param1, param2);
	}
private:
	FunctorType functor_;
};

template<class FunctorType, class ParamOneType, class ParamTwoType, class VarOneType>
class FunctorMethodDelegateBase_TwoParams_OneVar : public MethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>
{
public:
	FunctorMethodDelegateBase_TwoParams_OneVar(const FunctorType& functor,
		VarOneType var1)
		: functor_(functor), var1_(var1) {}

	virtual void Execute(ParamOneType param1, ParamTwoType param2) const override
	{
		return functor_(param1, param2, var1_);
	}
private:
	FunctorType functor_;
	VarOneType var1_;
};

template<class FunctorType, class ParamOneType, class ParamTwoType, class VarOneType, class VarTwoType>
class FunctorMethodDelegateBase_TwoParams_TwoVar : public MethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>
{
public:
	FunctorMethodDelegateBase_TwoParams_TwoVar(const FunctorType& functor,
		VarOneType var1, VarOneType var2)
		: functor_(functor), var1_(var1), var2_(var2) {}

	virtual void Execute(ParamOneType param1, ParamTwoType param2) const override
	{
		return functor_(param1, param2, var1_, var2_);
	}
private:
	FunctorType functor_;
	VarOneType var1_;
	VarTwoType var2_;
};
#endif //DELEGATE_SUPPORT_FUNCTOR

#endif

template <class ParamOneType, class ParamTwoType>
class Delegate_TwoParams
{
public:	
	typedef IMethodDelegateBase_TwoParams<ParamOneType, ParamTwoType> IMethodDelegateInstanceType;
	Delegate_TwoParams() : instance_(NULL) {}
	Delegate_TwoParams(IMethodDelegateInstanceType* instance) : instance_(instance) {}
	~Delegate_TwoParams() { Unbind(); }
#if DELEGATE_SUPPORT_STDSP
	template< class UserClass>
	void Bind(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_TwoParams_NoVar< UserClass, ParamOneType, ParamTwoType >::FMethodPtr func)
	{
		Unbind();
		instance_ = new SPMethodDelegateBase_TwoParams_NoVar<UserClass, ParamOneType, ParamTwoType>(object, func);
	}

	template< class UserClass, class VarOneType>
	void Bind(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_TwoParams_OneVar< UserClass, ParamOneType, ParamTwoType, VarOneType >::FMethodPtr func
		, VarOneType var1)
	{
		Unbind();
		instance_ = new SPMethodDelegateBase_TwoParams_OneVar<UserClass, ParamOneType, ParamTwoType, VarOneType>(object, func, var1);
	}

	template< class UserClass, class VarOneType, class VarTwoType>
	void Bind(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_TwoParams_TwoVar< UserClass, ParamOneType, VarOneType, ParamTwoType, VarTwoType >::FMethodPtr func
		, VarOneType var1, VarTwoType var2)
	{
		Unbind();
		instance_ = new SPMethodDelegateBase_TwoParams_TwoVar<UserClass, ParamOneType, ParamTwoType, VarOneType, VarTwoType>(object, func, var1, var2);
	}
#endif //DELEGATE_SUPPORT_SP

#if DELEGATE_SUPPORT_WEAK
	template< class UserClass>
	void BindW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_TwoParams_NoVar< UserClass, ParamOneType, ParamTwoType >::FMethodPtr func)
	{
		Unbind();
		instance_ = new WeakMethodDelegateBase_TwoParams_NoVar<UserClass, ParamOneType, ParamTwoType>(object, func);
	}

	template< class UserClass, class VarOneType>
	void BindW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_TwoParams_OneVar< UserClass, ParamOneType, ParamTwoType, VarOneType >::FMethodPtr func
		, VarOneType var1)
	{
		Unbind();
		instance_ = new WeakMethodDelegateBase_TwoParams_OneVar<UserClass, ParamOneType, ParamTwoType, VarOneType>(object, func, var1);
	}

	template< class UserClass, class VarOneType, class VarTwoType>
	void BindW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_TwoParams_TwoVar< UserClass, ParamOneType, ParamTwoType, VarOneType, VarTwoType >::FMethodPtr func
		, VarOneType var1, VarTwoType var2)
	{
		Unbind();
		instance_ = new WeakMethodDelegateBase_TwoParams_TwoVar<UserClass, ParamOneType, ParamTwoType, VarOneType, VarTwoType>(object, func, var1, var2);
	}
#endif //DELEGATE_SUPPORT_WEAK

#if DELEGATE_SUPPORT_FUNCTOR
	template< class FunctorType>
	void BindF(const FunctorType& functor)
	{
		Unbind();
		instance_ = new FunctorMethodDelegateBase_TwoParams_NoVar<FunctorType, ParamOneType, ParamTwoType>(functor);
	}

	template< class FunctorType, class VarOneType>
	void BindF(const FunctorType& functor, VarOneType var1)
	{
		Unbind();
		instance_ = new FunctorMethodDelegateBase_TwoParams_OneVar<FunctorType, ParamOneType, ParamTwoType, VarOneType>(functor, var1);
	}

	template< class FunctorType, class VarOneType, class VarTwoType>
	void BindF(const FunctorType& functor, VarOneType var1, VarTwoType var2)
	{
		Unbind();
		instance_ = new FunctorMethodDelegateBase_TwoParams_TwoVar<FunctorType, ParamOneType, ParamTwoType, VarOneType, VarTwoType>(functor, var1, var2);
	}
#endif //DELEGATE_SUPPORT_FUNCTOR

	void Unbind()
	{
		if (instance_)
		{
			delete instance_;
			instance_ = NULL;
		}
	}

	void Execute(ParamOneType param1, ParamTwoType param2) const 
	{
		if (!instance_)
			return;
		return instance_->Execute(param1, param2);
	}

private:
	IMethodDelegateInstanceType* instance_;
};

template <class ParamOneType, class ParamTwoType>
class MultiDelegate_TwoParams 
	: public MultiDelegateBase<IMethodDelegateBase_TwoParams<ParamOneType, ParamTwoType>>
{
public:	
	typedef IMethodDelegateBase_TwoParams<ParamOneType, ParamTwoType> IMethodDelegateInstanceType;	
#if DELEGATE_SUPPORT_STDSP	
	template< class UserClass>
	DelegateHandle Add(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_TwoParams_NoVar< UserClass, ParamOneType, ParamTwoType >::FMethodPtr func)
	{		
		return AddInternal(new SPMethodDelegateBase_TwoParams_NoVar<UserClass, ParamOneType, ParamTwoType>(object, func));
	}

	template< class UserClass, class VarOneType>
	DelegateHandle Add(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_TwoParams_OneVar< UserClass, ParamOneType, ParamTwoType, VarOneType >::FMethodPtr func,
		VarOneType var1)
	{		
		return AddInternal(new SPMethodDelegateBase_TwoParams_OneVar<UserClass, ParamOneType, ParamTwoType, VarOneType>(object, func, var1));
	}

	template< class UserClass, class VarOneType, class VarTwoType>
	DelegateHandle Add(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_TwoParams_TwoVar< UserClass, ParamOneType, ParamTwoType, VarOneType, VarTwoType >::FMethodPtr func,
		VarOneType var1, VarTwoType var2)
	{		
		return AddInternal(new SPMethodDelegateBase_TwoParams_TwoVar<UserClass, ParamOneType, ParamTwoType, VarOneType, VarTwoType>(object, func, var1, var2));
	}
#endif //DELEGATE_SUPPORT_SP

#if DELEGATE_SUPPORT_WEAK
	template< class UserClass>
	DelegateHandle AddW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_TwoParams_NoVar< UserClass, ParamOneType, ParamTwoType >::FMethodPtr func)
	{
		return AddInternal(new WeakMethodDelegateBase_TwoParams_NoVar<UserClass, ParamOneType, ParamTwoType>(object, func));
	}

	template< class UserClass, class VarOneType>
	DelegateHandle AddW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_TwoParams_OneVar< UserClass, ParamOneType, ParamTwoType, VarOneType >::FMethodPtr func,
		VarOneType var1)
	{
		return AddInternal(new WeakMethodDelegateBase_TwoParams_OneVar<UserClass, ParamOneType, ParamTwoType, VarOneType>(object, func, var1));
	}

	template< class UserClass, class VarOneType, class VarTwoType>
	DelegateHandle AddW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_TwoParams_TwoVar< UserClass, ParamOneType, ParamTwoType, VarOneType, VarTwoType >::FMethodPtr func,
		VarOneType var1, VarTwoType var2)
	{
		return AddInternal(new WeakMethodDelegateBase_TwoParams_TwoVar<UserClass, ParamOneType, ParamTwoType, VarOneType, VarTwoType>(object, func, var1, var2));
	}
#endif //DELEGATE_SUPPORT_WEAK

#if DELEGATE_SUPPORT_FUNCTOR
	template< class FunctorType>
	DelegateHandle AddF(const FunctorType& functor)
	{
		return AddInternal(new FunctorMethodDelegateBase_TwoParams_NoVar<FunctorType, ParamOneType, ParamTwoType>(functor));
	}

	template< class FunctorType, class VarOneType>
	DelegateHandle AddF(const FunctorType& functor, VarOneType var1)
	{
		return AddInternal(new FunctorMethodDelegateBase_TwoParams_OneVar<FunctorType, ParamOneType, ParamTwoType, VarOneType>(functor, var1));
	}

	template< class FunctorType, class VarOneType, class VarTwoType>
	DelegateHandle AddF(const FunctorType& functor, VarOneType var1, VarTwoType var2)
	{
		return AddInternal(new FunctorMethodDelegateBase_TwoParams_TwoVar<FunctorType, ParamOneType, ParamTwoType, VarOneType, VarTwoType>(functor, var1, var2));
	}
#endif //DELEGATE_SUPPORT_FUNCTOR
	void Execute(ParamOneType param1, ParamTwoType param2)
	{
		const std::vector<IMethodDelegateInstanceType*>& instacneList = GetInstanceList();
		if (instacneList.empty())
			return;
		for (int index = instacneList.size() - 1; index >=0; index--)
		{
			IMethodDelegateInstanceType* instance = instacneList[index];
			instance->Execute(param1, param2);
		}
	}
};