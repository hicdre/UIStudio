#include "stdafx.h"
#include "DelegateBase.h"

DelegateHandle gHandle = 1;


DelegateHandle IDelegateInstanceBase::GenerateNewHandle()
{
	return gHandle++;
}
