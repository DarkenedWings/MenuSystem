#pragma once


template <typename Type> class SLLIter;

template <typename Type>
class SLList
{
	friend class SLLIter<Type>;
private:

	unsigned int Size;

	struct Node
	{
		Type data;
		Node* next;
	};

	Node* head;

public:
	//Constructs an empty list
	SLList() { head = nullptr; Size = 0; }

	//Destroys the list
	~SLList() { clear(); delete head; }

	//Assignmet Operator
	SLList<Type>& operator=(const SLList<Type>& that)
	{
		head = that.head;
		return *this;
	}

	//Copy Constructor
	SLList(const SLList<Type>& that)
	{
		Node* temp = new Node;
		Node* temp2 = new Node;
		head = new Node;
		head->data = that.head->data;
		temp = head;
		temp2 = that.head->next;
		Size = 1;
		while (temp2 != nullptr)
		{
			temp->next = new Node;
			temp->next->data = temp2->data;
			temp = temp->next;
			temp->next = nullptr;
			temp2 = temp2->next;
			Size++;
		}
	}

	//Add a head(v)
	void addHead(const Type& v)
	{
		if (Size == 0)
		{
			head = new Node;
			head->data = v;
			head->next = nullptr;
			Size++;
		}
		else
		{
			Node* temp = new Node;
			temp->data = v;
			temp->next = head;
			head = temp;
			Size++;
		}
	}

	//Clear the list, freeing of any dynamic memory
	void clear()
	{
		while (head != nullptr)
		{
			if (head->next == nullptr)
				head = nullptr;
			else
			{
				Node* temp = new Node;
				temp = head;
				head = head->next;
				delete temp;
			}
		}
		Size = 0;
	}

	//Insert (v) into index (index)
	void insert(SLLIter<Type>& index, const Type& v)
	{
		Node* insNode = new Node;
		insNode->data = v;
		if (index.iter == nullptr)
		{}
		else if (index.iter == head)
		{
			insNode->next = head;
			head = insNode;
			index.iter = head;
		}
		else if (index.end())
		{
			index.prev->next = insNode;
			insNode->next = nullptr;
		}
		else
		{
			index.prev->next = insNode;
			insNode->next = index.iter;
			index.iter = insNode;
		}
		Size++;
	}

	//Remove index (index), do nothing on bad index
	void remove(SLLIter<Type>& index)
	{
		Node* removeNode = new Node;
		if (head == nullptr)
		{}
		else if (head == index.iter)
		{
			removeNode = head;
			head = head->next;
			delete removeNode;
			index.iter = head;
			Size--;
		}
		else
		{
			index.prev->next = index.iter->next;
			index.iter = nullptr;

			Size--;
			index.iter = index.prev->next;
		}
	}

	//Size, return the number of items stored
	inline unsigned int size() const { return Size; }
};

template <typename Type>
class SLLIter
{
	friend class SLList<Type>;
private:
	typename SLList<Type>::Node * iter;
	typename SLList<Type>::Node * prev;
	SLList<Type>* listToStore;
public:

	//Default constructor
	SLLIter(SLList<Type>& listToIterate) { listToStore = &listToIterate; }

	//move the iterator to the head
	void begin()
	{
			iter = listToStore->head;
			prev = nullptr;
	}

	//returns true if at end, else return false
	bool end() const
	{
		if (iter == nullptr)
			return true;
		else
			return false;
	}

	//Move iter forward one node
	SLLIter<Type>& operator++()
	{
		prev = iter;
		if (iter == nullptr)
		{
		}
		else if (iter->next == nullptr)
			iter = nullptr;
		else
			iter = iter->next;
		return *this;
	}

	//Return the item at the current iter location
	Type& current() const { return iter->data; }
};