#pragma once
#include "Delegate/DelegateBase.h"

#if 1 //接口定义

class IMethodDelegateBase_NoParams : public IDelegateInstanceBase
{
public:	
	virtual ~IMethodDelegateBase_NoParams() {}
	virtual void Execute() const = 0;
};

#endif

#if 1 //接口实现

class MethodDelegateBase_NoParams : public IMethodDelegateBase_NoParams
{
public:
	MethodDelegateBase_NoParams() : handle_(GenerateNewHandle()) {}

	virtual DelegateHandle GetHandle() const override {
		return handle_;
	}
private:
	DelegateHandle handle_;
};

#if DELEGATE_SUPPORT_STDSP
template<class UserClass>
class SPMethodDelegateBase_NoParams_NoVar : public MethodDelegateBase_NoParams
{
public:
	typedef void (UserClass::*FMethodPtr)( void );
	SPMethodDelegateBase_NoParams_NoVar(const std::shared_ptr<UserClass>& object, 
		FMethodPtr method) : weakObject_(object), methodPtr_(method) {}

	virtual void Execute() const override
	{
		std::shared_ptr<UserClass> object = weakObject_.lock();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)();
	}
		
private:
	std::weak_ptr<UserClass> weakObject_;
	FMethodPtr methodPtr_;	
};

template<class UserClass, class VarOneType>
class SPMethodDelegateBase_NoParams_OneVar : public MethodDelegateBase_NoParams
{
public:
	typedef void (UserClass::*FMethodPtr)( VarOneType );
	SPMethodDelegateBase_NoParams_OneVar(const std::shared_ptr<UserClass>& object, 
		FMethodPtr method,
		VarOneType var1) : weakObject_(object), methodPtr_(method)
		, var1_(var1)
	{}

	void Execute() const
	{
		std::shared_ptr<UserClass> object = weakObject_.lock();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)(var1_);
	}	
private:
	std::weak_ptr<UserClass> weakObject_;
	FMethodPtr methodPtr_;
	VarOneType var1_;
};

template<class UserClass, class VarOneType, class VarTwoType>
class SPMethodDelegateBase_NoParams_TwoVar : public MethodDelegateBase_NoParams
{
public:
	typedef void (UserClass::*FMethodPtr)( VarOneType, VarTwoType );
	SPMethodDelegateBase_NoParams_TwoVar(const std::shared_ptr<UserClass>& object, 
		FMethodPtr method,
		VarOneType var1, VarTwoType var2) 
		: weakObject_(object), methodPtr_(method)
		, var1_(var1), var2_(var2)
	{}

	void Execute() const
	{
		std::shared_ptr<UserClass> object = weakObject_.lock();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)(var1_, var2_);
	}

private:
	std::weak_ptr<UserClass> weakObject_;
	FMethodPtr methodPtr_;
	VarOneType var1_;
	VarTwoType var2_;
};
#endif //#if DELEGATE_SUPPORT_SP

#if DELEGATE_SUPPORT_WEAK
template<class UserClass>
class WeakMethodDelegateBase_NoParams_NoVar : public MethodDelegateBase_NoParams
{
public:
	typedef void (UserClass::*FMethodPtr)( void );
	WeakMethodDelegateBase_NoParams_NoVar(const WPtr<UserClass>& object, 
		FMethodPtr method) : weakObject_(object), methodPtr_(method) {}

	virtual void Execute() const override
	{
		SPtr<UserClass> object = weakObject_.get();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)();
	}
		
private:
	WPtr<UserClass> weakObject_;
	FMethodPtr methodPtr_;	
};

template<class UserClass, class VarOneType>
class WeakMethodDelegateBase_NoParams_OneVar : public MethodDelegateBase_NoParams
{
public:
	typedef void (UserClass::*FMethodPtr)( VarOneType );
	WeakMethodDelegateBase_NoParams_OneVar(const WPtr<UserClass>& object, 
		FMethodPtr method,
		VarOneType var1) : weakObject_(object), methodPtr_(method)
		, var1_(var1)
	{}

	void Execute() const
	{
		SPtr<UserClass> object = weakObject_.get();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)(var1_);
	}	
private:
	WPtr<UserClass> weakObject_;
	FMethodPtr methodPtr_;
	VarOneType var1_;
};

template<class UserClass, class VarOneType, class VarTwoType>
class WeakMethodDelegateBase_NoParams_TwoVar : public MethodDelegateBase_NoParams
{
public:
	typedef void (UserClass::*FMethodPtr)( VarOneType, VarTwoType );
	WeakMethodDelegateBase_NoParams_TwoVar(const WPtr<UserClass>& object, 
		FMethodPtr method,
		VarOneType var1, VarTwoType var2) 
		: weakObject_(object), methodPtr_(method)
		, var1_(var1), var2_(var2)
	{}

	void Execute() const
	{
		SPtr<UserClass> object = weakObject_.get();
		if (!object)
			return;

		UserClass* rawObject = object.get();

		return (rawObject->*methodPtr_)(var1_, var2_);
	}

private:
	WPtr<UserClass> weakObject_;
	FMethodPtr methodPtr_;
	VarOneType var1_;
	VarTwoType var2_;
};
#endif //DELEGATE_SUPPORT_WEAK

#if DELEGATE_SUPPORT_FUNCTOR
template<class FunctorType>
class FunctorMethodDelegateBase_NoParams_NoVar : public MethodDelegateBase_NoParams
{
public:
	FunctorMethodDelegateBase_NoParams_NoVar(const FunctorType& functor)
		: functor_(functor) {}

	virtual void Execute() const override
	{
		return functor_();
	}
private:
	FunctorType functor_;
};

template<class FunctorType, class VarOneType>
class FunctorMethodDelegateBase_NoParams_OneVar : public MethodDelegateBase_NoParams
{
public:
	FunctorMethodDelegateBase_NoParams_OneVar(const FunctorType& functor,
		VarOneType var1)
		: functor_(functor), var1_(var1) {}

	virtual void Execute() const override
	{
		return functor_(var1_);
	}
private:
	FunctorType functor_;
	VarOneType var1_;
};

template<class FunctorType, class VarOneType, class VarTwoType>
class FunctorMethodDelegateBase_NoParams_TwoVar : public MethodDelegateBase_NoParams
{
public:
	FunctorMethodDelegateBase_NoParams_TwoVar(const FunctorType& functor,
		VarOneType var1, VarOneType var2)
		: functor_(functor), var1_(var1), var2_(var2) {}

	virtual void Execute() const override
	{
		return functor_(var1_, var2_);
	}
private:
	FunctorType functor_;
	VarOneType var1_;
	VarTwoType var2_;
};
#endif //DELEGATE_SUPPORT_FUNCTOR

#endif

class Delegate_NoParams
{
public:	
	Delegate_NoParams() : instance_(NULL) {}
	Delegate_NoParams(IMethodDelegateBase_NoParams* instance) : instance_(instance) {}
	~Delegate_NoParams() { Unbind(); }
#if DELEGATE_SUPPORT_STDSP
	template< class UserClass>
	void Bind(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_NoParams_NoVar< UserClass >::FMethodPtr func)
	{
		Unbind();
		instance_ = new SPMethodDelegateBase_NoParams_NoVar<UserClass>(object, func);
	}

	template< class UserClass, class VarOneType>
	void Bind(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_NoParams_OneVar< UserClass, VarOneType >::FMethodPtr func
		, VarOneType var1)
	{
		Unbind();
		instance_ = new SPMethodDelegateBase_NoParams_OneVar<UserClass, VarOneType>(object, func, var1);
	}

	template< class UserClass, class VarOneType, class VarTwoType>
	void Bind(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_NoParams_TwoVar< UserClass, VarOneType, VarTwoType >::FMethodPtr func
		, VarOneType var1, VarTwoType var2)
	{
		Unbind();
		instance_ = new SPMethodDelegateBase_NoParams_TwoVar<UserClass, VarOneType, VarTwoType>(object, func, var1, var2);
	}
#endif //DELEGATE_SUPPORT_SP

#if DELEGATE_SUPPORT_WEAK
	template< class UserClass>
	void BindW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_NoParams_NoVar< UserClass >::FMethodPtr func)
	{
		Unbind();
		instance_ = new WeakMethodDelegateBase_NoParams_NoVar<UserClass>(object, func);
	}

	template< class UserClass, class VarOneType>
	void BindW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_NoParams_OneVar< UserClass, VarOneType >::FMethodPtr func
		, VarOneType var1)
	{
		Unbind();
		instance_ = new WeakMethodDelegateBase_NoParams_OneVar<UserClass, VarOneType>(object, func, var1);
	}

	template< class UserClass, class VarOneType, class VarTwoType>
	void BindW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_NoParams_TwoVar< UserClass, VarOneType, VarTwoType >::FMethodPtr func
		, VarOneType var1, VarTwoType var2)
	{
		Unbind();
		instance_ = new WeakMethodDelegateBase_NoParams_TwoVar<UserClass, VarOneType, VarTwoType>(object, func, var1, var2);
	}
#endif //DELEGATE_SUPPORT_WEAK

#if DELEGATE_SUPPORT_FUNCTOR
	template< class FunctorType>
	void BindF(const FunctorType& functor)
	{
		Unbind();
		instance_ = new FunctorMethodDelegateBase_NoParams_NoVar<FunctorType>(functor);
	}

	template< class FunctorType, class VarOneType>
	void BindF(const FunctorType& functor, VarOneType var1)
	{
		Unbind();
		instance_ = new FunctorMethodDelegateBase_NoParams_OneVar<FunctorType, VarOneType>(functor, var1);
	}

	template< class FunctorType, class VarOneType, class VarTwoType>
	void BindF(const FunctorType& functor, VarOneType var1, VarTwoType var2)
	{
		Unbind();
		instance_ = new FunctorMethodDelegateBase_NoParams_TwoVar<FunctorType, VarOneType, VarTwoType>(functor, var1, var2);
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

	void Execute() const 
	{
		if (!instance_)
			return;
		return instance_->Execute();
	}

private:
	IMethodDelegateBase_NoParams* instance_;
};

class MultiDelegate_NoParams 
	: public MultiDelegateBase<IMethodDelegateBase_NoParams>
{
public:	
#if DELEGATE_SUPPORT_STDSP
	template< class UserClass>
	DelegateHandle Add(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_NoParams_NoVar< UserClass >::FMethodPtr func)
	{		
		return AddInternal(new SPMethodDelegateBase_NoParams_NoVar<UserClass>(object, func));
	}

	template< class UserClass, class VarOneType>
	DelegateHandle Add(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_NoParams_OneVar< UserClass, VarOneType >::FMethodPtr func,
		VarOneType var1)
	{		
		return AddInternal(new SPMethodDelegateBase_NoParams_OneVar<UserClass, VarOneType>(object, func, var1));
	}

	template< class UserClass, class VarOneType, class VarTwoType>
	DelegateHandle Add(const std::shared_ptr< UserClass >& object, typename SPMethodDelegateBase_NoParams_TwoVar< UserClass, VarOneType, VarTwoType >::FMethodPtr func,
		VarOneType var1, VarTwoType var2)
	{		
		return AddInternal(new SPMethodDelegateBase_NoParams_TwoVar<UserClass, VarOneType, VarTwoType>(object, func, var1, var2));
	}
#endif //DELEGATE_SUPPORT_SP

#if DELEGATE_SUPPORT_WEAK
	template< class UserClass>
	DelegateHandle AddW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_NoParams_NoVar< UserClass >::FMethodPtr func)
	{		
		return AddInternal(new WeakMethodDelegateBase_NoParams_NoVar<UserClass>(object, func));
	}

	template< class UserClass, class VarOneType>
	DelegateHandle AddW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_NoParams_OneVar< UserClass, VarOneType >::FMethodPtr func,
		VarOneType var1)
	{		
		return AddInternal(new WeakMethodDelegateBase_NoParams_OneVar<UserClass, VarOneType>(object, func, var1));
	}

	template< class UserClass, class VarOneType, class VarTwoType>
	DelegateHandle AddW(const WPtr< UserClass >& object, typename WeakMethodDelegateBase_NoParams_TwoVar< UserClass, VarOneType, VarTwoType >::FMethodPtr func,
		VarOneType var1, VarTwoType var2)
	{		
		return AddInternal(new WeakMethodDelegateBase_NoParams_TwoVar<UserClass, VarOneType, VarTwoType>(object, func, var1, var2));
	}
#endif //DELEGATE_SUPPORT_WEAK

#if DELEGATE_SUPPORT_FUNCTOR
	template< class FunctorType>
	DelegateHandle AddF(const FunctorType& functor)
	{
		return AddInternal(new FunctorMethodDelegateBase_NoParams_NoVar<FunctorType>(functor));
	}

	template< class FunctorType, class VarOneType>
	DelegateHandle AddF(const FunctorType& functor, VarOneType var1)
	{
		return AddInternal(new FunctorMethodDelegateBase_NoParams_OneVar<FunctorType, VarOneType>(functor, var1));
	}

	template< class FunctorType, class VarOneType, class VarTwoType>
	DelegateHandle AddF(const FunctorType& functor, VarOneType var1, VarTwoType var2)
	{
		return AddInternal(new FunctorMethodDelegateBase_NoParams_TwoVar<FunctorType, VarOneType, VarTwoType>(functor, var1, var2));
	}
#endif //DELEGATE_SUPPORT_FUNCTOR
	void Execute()
	{
		const std::vector<IMethodDelegateBase_NoParams*>& instacneList = GetInstanceList();
		if (instacneList.empty())
			return;
		for (int index = instacneList.size() - 1; index >=0; index--)
		{
			IMethodDelegateBase_NoParams* instance = instacneList[index];
			instance->Execute();
		}
	}
};