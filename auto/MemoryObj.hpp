#pragma once

#include <sal.h>
#include <memory>

template<typename Type_t>
class CMemObj
{
	static
	void
	MemObjDisposer(
		__inout void* objects
		)
	{
		delete objects;
	}
public:
	CMemObj(
		__in size_t count
		) : m_buff(static_cast<Type_t*>(calloc(count, sizeof(Type_t))), MemObjDisposer),
			m_count(0)
	{
		if (!m_buff.get())
			return;

		m_count = count;
		memset(m_buff.get(), 0, m_count * sizeof(Type_t));
	}

	~CMemObj()
	{
		//if not allocated at all, GetCount returns 0
		for (size_t i = 0; i < GetCount(); i++)
			m_buff.get()[i].~Type_t();
	}

	size_t 
	GetCount()
	{
		return m_count;
	}

	__checkReturn
	bool 
	IsAllocated()
	{
		return !!GetCount();
	}

	//unsafe to use whithout IsAllocated() 
	Type_t* 
	operator&()
	{
		return m_buff.get();
	}

	//unsafe to use whithout IsAllocated() 
	Type_t& 
	operator[](
		__in size_t index
		)
	{
		return m_buff.get()[index];
	}

protected:
	size_t m_count;
	std::unique_ptr<Type_t, decltype(&MemObjDisposer)> m_buff;
};
