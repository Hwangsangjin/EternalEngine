#pragma once

#pragma warning (disable : 4251)

#include "Iterator.h"

template <typename T>
class TArray
{
public:
	using ValueType = T;
	using Iterator = Iterator<TArray<T>>;

	Iterator begin()
	{
		return Iterator(DataPtr);
	}

	const Iterator begin() const
	{
		return Iterator(DataPtr);
	}

	Iterator end()
	{
		return Iterator(DataPtr + ArrayNum);
	}

	const Iterator end() const
	{
		return Iterator(DataPtr + ArrayNum);
	}

	Iterator rbegin()
	{
		return Iterator(DataPtr + ArrayNum - 1);
	}

	const Iterator rbegin() const
	{
		return Iterator(DataPtr + ArrayNum - 1);
	}

	Iterator rend()
	{
		return Iterator(DataPtr - 1);
	}

	const Iterator rend() const
	{
		return Iterator(DataPtr - 1);
	}

public:
	// 생성자
	TArray()
		: ArrayNum(0)
		, ArrayMax(2)
	{
		DataPtr = new T[NewArrayMax];
		std::fill(DataPtr, DataPtr + NewArrayMax, T());
	}

	// 초기화 목록 생성자
	TArray(const std::initializer_list<T>& Initializer_List)
		: ArrayNum(Initializer_List.size())
		, ArrayMax(ArrayNum == 0 ? 2 : ArrayNum)
	{
		DataPtr = new T[ArrayMax];
		std::copy(Initializer_List.begin(), Initializer_List.end(), DataPtr);
	}

	// 복사 생성자
	TArray(const TArray& Other)
		: ArrayNum(Other.ArrayNum)
		, ArrayMax(Other.ArrayMax)
	{
		DataPtr = new T[ArrayMax];
		std::copy(Other.DataPtr, Other.DataPtr + ArrayNum, DataPtr);
	}

	// 이동 생성자
	TArray(TArray&& Other) noexcept
		: ArrayNum(Other.ArrayNum)
		, ArrayMax(Other.ArrayMax)
		, DataPtr(Other.DataPtr)
	{
		Other.ArrayNum = 0;
		Other.ArrayMax = 0;
		Other.DataPtr = nullptr;
	}

	// 대입 연산자
	TArray& operator=(const TArray& Other)
	{
		if (this != &Other)
		{
			delete[] DataPtr;

			ArrayNum = Other.ArrayNum;
			ArrayMax = Other.ArrayMax;
			DataPtr = new T[ArrayMax];

			std::copy(Other.DataPtr, Other.DataPtr + ArrayNum, DataPtr);
		}
		
		return *this;
	}

	// 이동 대입 연산자
	TArray& operator=(TArray&& Other) noexcept
	{
		if (this != &Other)
		{
			delete[] DataPtr;

			DataPtr = std::move(Other.DataPtr);
			ArrayMax = std::move(Other.ArrayMax);
			ArrayNum = std::move(Other.ArrayNum);

			Other.ArrayNum = 0;
			Other.ArrayMax = 0;
			Other.DataPtr = nullptr;
		}
		
		return *this;
	}

	// 소멸자
	~TArray()
	{
		delete[] DataPtr;
		DataPtr = nullptr;
	}

	T* GetData()
	{
		return DataPtr;
	}

	const T* GetData() const
	{
		return DataPtr;
	}

	size_t GetSlack() const
	{
		return ArrayMax - ArrayNum;
	}

	bool IsValidIndex(size_t Index) const
	{
		return Index < ArrayNum;
	}

	bool IsEmpty() const
	{
		return ArrayNum == 0;
	}

	T& operator[](size_t Index)
	{
		assert(Index < ArrayNum);
		return DataPtr[Index];
	}

	const T& operator[](size_t Index) const
	{
		assert(Index < ArrayNum);
		return DataPtr[Index];
	}

	void Add(const T& Value)
	{
		if (ArrayNum == ArrayMax)
			Resize(ArrayMax * 2);

		DataPtr[ArrayNum++] = Value;
	}

	void Add(T&& Value) noexcept
	{
		if (ArrayNum == ArrayMax)
			Resize(ArrayMax * 2);

		DataPtr[ArrayNum++] = std::move(Value);
	}

	void Reset(size_t NewSize = 0)
	{
		if (NewSize == 0)
		{
			for (size_t i = 0; i < ArrayNum; ++i)
				DataPtr[i].~T();
		}

		ArrayNum = 0;
	}

	void Empty(size_t Slack = 0)
	{
		if (Slack > 0)
		{
			Resize(Slack);
			ArrayNum = 0;
		}
		else
		{
			Reset();
		}
	}

	void Resize(size_t Size) noexcept
	{
		T* NewDataPtr = new T[Size];
		std::move(DataPtr, DataPtr + ArrayNum, NewDataPtr);
		delete[] DataPtr;
		DataPtr = NewDataPtr;
		ArrayMax = Size;
	}

	void RemoveAt(size_t Index) noexcept
	{
		assert(Index < ArrayNum);

		for (size_t i = Index; i < ArrayNum - 1; ++i)
			DataPtr[i] = std::move(DataPtr[i + 1]);

		--ArrayNum;
	}

	void Remove(const T& Value) noexcept
	{
		for (size_t i = 0; i < ArrayNum; ++i)
		{
			if (DataPtr[i] == Value)
			{
				RemoveAt(i);
				return;
			}
		}
	}

	constexpr size_t Num() const
	{
		return ArrayNum;
	}

	constexpr size_t Max() const
	{
		return ArrayMax;
	}

private:
	size_t ArrayNum;
	size_t ArrayMax;
	T* DataPtr;
};
