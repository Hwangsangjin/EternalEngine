#pragma once

#include "Core.h"

class ENGINE_API RTTI
{
public:
	virtual const size_t& TypeIdInstance() const = 0;

	virtual bool Is(const size_t id) const
	{
		return false;
	}

	template <typename T>
	T* As()
	{
		if (Is(T::TypeIdClass()))
			return (T*)this;

		return nullptr;
	}

	template <typename T>
	const T* As() const
	{
		if (Is(T::TypeIdClass()))
			return (T*)this;

		return nullptr;
	}
};

#define RTTI_DECL(Type, BaseType)														\
public:																					\
	using Super = BaseType;																\
																						\
	virtual const size_t& TypeIdInstance() const { return Type::TypeIdClass(); }		\
																						\
	static const size_t TypeIdClass()													\
	{																					\
		static size_t RunTimeTypeId = 0;												\
		return reinterpret_cast<size_t>(&RunTimeTypeId);								\
	}																					\
																						\
	virtual bool Is(const size_t Id) const												\
	{																					\
		if (Id == TypeIdClass())														\
			return true;																\
		else																			\
			return Super::Is(Id);														\
	}
