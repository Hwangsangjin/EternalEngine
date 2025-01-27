#pragma once

class ENGINE_API RTTI
{
public:
	virtual const size_t& TypeIDInstance() const = 0;

	virtual bool Is(const size_t& InID) const
	{
		return false;
	}

	template <typename T>
	T* As()
	{
		if (Is(T::TypeIDClass()))
			return (T*)this;

		return nullptr;
	}

	template <typename T>
	const T* As() const
	{
		if (Is(T::TypeIDClass()))
			return (T*)this;

		return nullptr;
	}
};

#define RTTI_DECL(Type, BaseType)														\
public:																					\
	using Super = BaseType;																\
																						\
	virtual const size_t& TypeIDInstance() const { return Type::TypeIDClass(); }		\
																						\
	static const size_t TypeIDClass()													\
	{																					\
		static size_t RunTimeTypeID = 0;												\
		return reinterpret_cast<size_t>(&RunTimeTypeID);								\
	}																					\
																						\
	virtual bool Is(const size_t& InID) const											\
	{																					\
		if (InID == TypeIDClass())														\
			return true;																\
																						\
		return Super::Is(InID);															\
	}
