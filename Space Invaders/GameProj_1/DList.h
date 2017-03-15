#pragma once
template<typename myGame>
class DList
{
private:
	struct node
	{
		node *prev, *next;
		myGame data;
		node(myGame& _data, node* _prev, node* _next) : data(_data), prev(_prev), next(_next){}
	};
	node *first, *last;
	int count;
public:
	DList(){ count = 0; first = last = NULL; };
	~DList();
	void push_back(myGame _data);
	void push_front(myGame _data);
	unsigned int size() const { return count; }

	myGame& operator[](int index);
	const myGame& operator[](int index) const;

	bool erase(int index);
	void clear();
};

template<typename myGame >
DList<myGame>::~DList()
{
	node* temp = first;
	while (first)
	{
		first = first->next;
		delete temp;

		temp = first;
	}
}

template<typename myGame >
void DList < myGame >::push_front(myGame _data)
{
	node* n = new node(_data, NULL, first);
	if (!last)
		last = n;
	if (first != NULL)
	{
		first->prev = n;
	}

	first = n;
	++count;


}
template<typename myGame>
void DList <myGame>::push_back(myGame _data)
{
	node* n = new node(_data, last, NULL);
	if (last)
		last->next = n;
	else
		first = n;
	last = n;
	++count;

}

template<typename myGame>
myGame& DList<myGame>::operator[](int index)
{
	node* t = first;
	int i = 0;
	for (; i < index; ++i)
		t = t->next;

	return t->data;
}

template<typename myGame>
const myGame& DList<myGame>::operator[](int index) const
{
	node* t = first;
	int i = 0;
	for (; i < index; ++i)
		t = t->next;

	return t->data;
}

template<typename myGame >
void DList <myGame>::clear()
{
	node* temp = first;
	for (int i = 0; i < count; ++i)
	{
		temp = first;
		first = first->next;
		delete temp;
	}
	first = last = NULL;
	count = 0;
}

template<typename myGame >
bool DList<myGame>::erase(int index)
{
	node* temp = first;

	if (count <= 0 || count - 1 < index || index < 0)
	{
		return false;
	}
	else
	{

		for (int i = index; i > 0; i--)
		{
			temp = temp->next;
		}
		if (count == NULL)
		{
			last = first = NULL;
			delete temp;
			count = 0;
			return true;
		}

		if (temp == first)
		{
			first = first->next;

			if (first != NULL)
			{
				first->prev = NULL;
			}
			delete temp;
			count--;
			return true;
		}

		if (temp == last)
		{
			last = last->prev;
			if (last != NULL)
			{
				last->next = NULL;
			}
			delete temp;
			count--;
			return true;
		}

		if (temp != last && temp != first)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			--count;
			return true;
		}

	}
	return true;
}