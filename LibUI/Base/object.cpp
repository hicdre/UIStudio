#include "stdafx.h"
#include "object.h"

Object::Object() 
	: ref_(new RefCount)
{

}

Object::~Object()
{

}

void Object::AddRef()
{
	ref_->AddRef();
}

void Object::Release()
{
	if (ref_->Release() <= 0) {
		delete this;
	}
}


