//
//  DoubleList.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 11/9/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_DoubleList_h
#define SinncaEngine_DoubleList_h

namespace sinnca
{
	template<class T>
	class doubleList
	{
		struct element
		{
			t data;
			element* next, prev;
			
			element() : next(NULL), prev(NULL)
			{}
			
			typedef t value_type;
			
			void* operator new(size_t s)
			{
				return Heap->allocate((unsigned int)s, __alignof(element));
			}
			void operator delete(void* p)
			{
				Heap->deallocate(p);
			}
		};
		
		element* first;
		element* last;
		
	public:
		
		class iterator
		{
			//friend class linkList<typename t::value_type>;
			element* elementRef;
			
		public:
			
			iterator(element* ele) : elementRef(ele) {};
			
			void operator++()
			{
				// postfix
				elementRef = elementRef->next;
			}
			void operator++(int)
			{
				// prefix
				elementRef = elementRef->next;
			}
			
			void operator--()
			{
				// postfix
				elementRef = elementRef->prev;
			}
			void operator--(int)
			{
				// prefix
				elementRef = elementRef->prev;
			}
			
			iterator operator+(int i)
			{
				iterator itr = *this;
				for (int j = 0; j < i; j++)
				{
					if (itr.elementRef)
					{
						itr++;
					} else {
						break;
					}
				}
			}
			
			bool operator !=(iterator i)
			{
				return (i.elementRef != elementRef);
			}
			bool operator ==(iterator i)
			{
				return (i.elementRef == elementRef);
			}
			t& operator*()
			{
				return elementRef->data;
			}
			t* operator->()
			{
				return (&*(linkList<t>::iterator)*this);
			}
			
		};
		
		doubleList() :
		first(NULL),
		last(NULL)
		{}
		
		~doubleList()
		{
			while (first)
			{
				element* temp = first;
				first = first->next;
				Heap->deallocateDelete(temp);
			}
		}
		
		
		void pushFront(const t& x)
		{
			element* temp = new element();
			temp->data = x;
			
			if (!first)
			{
				first = temp;
				return;
			}
			temp->next = first;
			first = temp;
			
			numOfElements++;
		}
		
		void pushBack(const t& x)
		{
			element* temp = new element();
			temp->data = x;
			
			if (!first)
			{
				first = temp;
				return;
			}
			element* currentPlace = first;
			while (currentPlace)
			{
				if (!currentPlace->next)
				{
					currentPlace->next = temp;
					return;
				}
				currentPlace = currentPlace->next;
			}
			
			numOfElements++;
		}
		
		void remove(const t& x)
		{
			element* temp = first;
			
			// are there any elements?
			if (numOfElements == 0 || temp == NULL)
			{
				return;
			}
			
			for (int i = 0; i < numOfElements; i++, temp = temp->next)
			{
				if (temp->data == x)
				{
					Heap->deallocateDelete(temp);
				}
			}
		}
		
		void popFront()
		{
			element* temp = first->next;
			
			Heap->deallocateDelete(first);
			first = temp;
		}
		
		void popBack()
		{
			element* temp = first;
			
			while (temp)
			{
				if (temp->next)
				{
					temp = temp->next;
					
				} else {
					
					Heap->deallocateDelete(temp);
				}
			}
		}
		
		void clear()
		{
			while (first)
			{
				popFront();
			}
		}
		
		iterator begin()
		{
			return iterator(first);
		}
		iterator end()
		{
			return (iterator(nullptr));
		}
		
		
	};
}

#endif
