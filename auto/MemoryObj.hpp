#pragma once

#include <sal.h>
#include <memory>

template<typename TYPE>
class CMemObj
{
public:
	CMemObj(
		__in size_t count
		) : m_buff(static_cast<TYPE*>(calloc(count, sizeof(TYPE)))),
			m_count(0)
	{
		if (!m_buff.get())
			return;
		m_count = count;
		memset(m_buff.get(), 0, m_count * sizeof(TYPE));
	}

	size_t GetCount()
	{
		return m_count;
	}

	__checkReturn
	bool IsAllocated()
	{
		return !!GetCount();
	}

	//unsafe to use whithout IsAllocated() 
	TYPE* operator&()
	{
		return m_buff.get();
	}

	//unsafe to use whithout IsAllocated() 
	TYPE& operator[](
		__in size_t index
		)
	{
		return m_buff.get()[index];
	}

protected:
	size_t m_count;
	std::unique_ptr<TYPE> m_buff;	
};

template<typename TYPE>
class CObjHolder :
	public CMemObj<TYPE>
{
public:
	CObjHolder(
		__in size_t count
		) : CMemObj(count)
	{
	}

	~CObjHolder()
	{
		//if not allocated at all, GetCount returns 0
		for (size_t i = 0; i < GetCount(); i++)
			m_buff[i].~TYPE();
 	}
};

/*
typedef std::shared_ptr< CMemObj<char> > TUserBuffer;
typedef CObjHolder<TUserModeBuffer> TSharedBuffers;
*/

