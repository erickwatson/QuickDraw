#pragma once

template<typename T>
class DoubleLinkedList
{
protected:

	class ListNode {
	public:

		ListNode* m_Next;
		ListNode* m_Prev;

		T* m_Data;
	};


public:
	
	DoubleLinkedList() {}

	~DoubleLinkedList() {}

	void push_front(T value);
	void push_back(T value);

	T pop_front();
	T pop_back();
	void set(unsigned int index, T value);
	T get(unsigned int index);


	// Sort on insert
	void Insert(T value);



	ListNode* m_First;
	ListNode* m_Last;



};

