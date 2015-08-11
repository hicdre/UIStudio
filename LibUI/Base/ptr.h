#pragma once
#include "base/basictypes.h"


template <class T>
class SPtr
{
public:
	SPtr()
	{
		p_ = NULL;
	}
	SPtr(T* t)
	{
		p_ = t;
		if (p_)
			p_->AddRef();
	}
	~SPtr()
	{
		Clear();
	}
	SPtr(const SPtr& r) : p_(NULL) {
		reset(r.get());
	}
	SPtr(SPtr&& r) : p_(NULL) {
		reset(r.get());
	}
	template <class U>
	SPtr(const SPtr<U>& r) : p_(NULL) {
		reset(dynamic_cast<T*>(r.get()));
	}
	template <class U>
	SPtr<T>& operator=(const SPtr<U>& r) {
		reset(dynamic_cast<T*>(r.get()));
		return (*this);
	}

	void Clear()
	{
		if (p_)
			p_->Release();
	}
	T* operator->() const
	{
		return p_;
	}
	T*& operator&()
	{
		return p_;
	}
	const T*& operator&() const
	{
		return p_;
	}
	T* get() const
	{
		return p_;
	}
	void reset(T* p = NULL)
	{
		Clear();
		p_ = p;
		if (p_)
			p_->AddRef();
	}

	bool operator!() const {
		return !p_;
	}

	explicit operator bool() const {
		return !!p_;
	}

	bool operator==(const SPtr<T>& other) const {
		return p_ == other.p_;
	}

	bool operator!=(const SPtr<T>& other) const {
		return p_ != other.p_;
	}
private:
	T* p_;
};

class RefCount;

template <class T>
class WPtr
{
public:
	WPtr() : ptr_(nullptr) {}
	WPtr(const SPtr<RefCount>& ref, T* ptr) 
		: ref_(ref), ptr_(ptr) {}

	template <class U>
	WPtr(const WPtr<U>& r) {
		reset(r);
	}

	template <class U>
	void reset(const SPtr<U>& r) {
		reset(r->GetWeak<T>());
	}

	template <class U>
	void reset(const WPtr<U>& r) {
		ptr_ = dynamic_cast<T*>(r.ptr_);
		ref_ = r.ref_;
	}

	void reset() {
		ref_ = nullptr;
		ptr_ = nullptr;
	}

	SPtr<T> get() const {		
		SPtr<T> ptr;
		if (!ref_)
			return ptr;
		if (ref_->Increment() >= 1) //add and lock
			ptr.reset(ptr_);
		ref_->Decrement();
		return ptr;
	}

// 	SPtr<T>&& get() const {
// 		SPtr<T> ptr;
// 		if (!ref_)
// 			return ptr;
// 		if (ref_->AddRef() >= 1) //add and lock
// 			ptr.reset(ptr_);
// 		ref_->Release();
// 		return std::move(ptr);
// 	}
private:
	SPtr<RefCount> ref_;
	T* ptr_;
};