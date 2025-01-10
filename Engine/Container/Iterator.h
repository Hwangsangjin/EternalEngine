#pragma once

template <typename T>
class Iterator
{
public:
	using ValueType = typename T::ValueType;
	using Pointer = ValueType*;
	using Reference = ValueType&;
	using DifferenceType = ptrdiff_t;
	using IteratorCategory = std::random_access_iterator_tag;

public:
	constexpr Iterator(Pointer Ptr)
		: Ptr(Ptr)
	{}

	Iterator& operator=(const Iterator& Other)
	{
		if (this != &Other)
			Ptr = Other.Ptr;

		return *this;
	}

	constexpr Iterator& operator++()
	{
		++Ptr;
		return *this;
	}

	constexpr Iterator& operator++(int)
	{
		Iterator Temp = *this;
		++(*this);
		return Temp;
	}

	constexpr Iterator& operator--()
	{
		--Ptr;
		return *this;
	}

	constexpr Iterator& operator--(int)
	{
		Iterator Temp = *this;
		--(*this);
		return Temp;
	}

	constexpr Iterator operator+(DifferenceType Offset) const
	{
		return Iterator(Ptr + Offset);
	}

	constexpr Iterator operator-(DifferenceType Offset) const
	{
		return Iterator(Ptr - Offset);
	}

	constexpr ptrdiff_t operator-(const Iterator& Other) const
	{
		return Ptr - Other.Ptr;
	}

	constexpr Iterator& operator+=(size_t Offset)
	{
		Ptr += Offset;
		return *this;
	}

	constexpr Iterator& operator-=(size_t Offset)
	{
		Ptr -= Offset;
		return *this;
	}

	Pointer operator->()
	{
		return Ptr;
	}

	Pointer operator->() const
	{
		return Ptr;
	}

	Reference operator*()
	{
		return *Ptr;
	}

	Reference operator*() const
	{
		return *Ptr;
	}

	Reference operator[](size_t Index)
	{
		return *(Ptr + Index);
	}

	Reference operator[](size_t Index) const
	{
		return *(Ptr + Index);
	}

	constexpr bool operator==(const Iterator& Other) const
	{
		return Ptr == Other.Ptr;
	}

	constexpr bool operator!=(const Iterator& Other) const
	{
		return Ptr != Other.Ptr;
	}

	constexpr bool operator<(const Iterator& Other) const
	{
		return Ptr < Other.Ptr;
	}

	constexpr bool operator<=(const Iterator& Other) const
	{
		return Ptr <= Other.Ptr;
	}

	constexpr bool operator>(const Iterator& Other) const
	{
		return Ptr > Other.Ptr;
	}

	constexpr bool operator>=(const Iterator& Other) const
	{
		return Ptr >= Other.Ptr;
	}

private:
	Pointer Ptr;
};
