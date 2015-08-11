#include "stdafx.h"
#include "object.h"

Object::Object() 
	: object_ref_count_(new RefCount)
{

}

Object::~Object()
{

}

void Object::AddRef()
{
	object_ref_count_->Increment();
}

void Object::Release()
{
	if (object_ref_count_->Decrement() <= 0) {
		delete this;
	}
}


