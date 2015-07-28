#pragma once
#include "Base/object.h"

#define DELEGATE_SUPPORT_STDSP 0
#define DELEGATE_SUPPORT_WEAK 1
#define DELEGATE_SUPPORT_FUNCTOR 1
#include "Delegate/Delegate_NoParams.h"
#include "Delegate/Delegate_OneParam.h"
#include "Delegate/Delegate_TwoParams.h"

template <class Sig>
class Event;

template <>
class Event<void(void)> : public MultiDelegate_NoParams
{

};

template <class A>
class Event<void(A)> : public MultiDelegate_OneParam<A>
{

};

template <class A, class B>
class Event<void(A, B)> : public MultiDelegate_TwoParams < A, B >
{

};