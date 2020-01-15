#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_


template <typename T>
struct LinkedListNode
{
	T element;
	LinkedListNode* next;
};

template <typename T>
class LinkedList
{
public:
	LinkedList() : head(NULL), tail(NULL) {}
	~LinkedList();

	const LinkedListNode<T>* get_head() const { return head; }
	void push_back(const T &x);
	void clear();

	void insertion_sort();

private:
	LinkedListNode<T> *head;
	LinkedListNode<T> *tail;
};

template <typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

template <typename T>
void LinkedList<T>::push_back(const T &x)
{
	LinkedListNode<T> *node = new LinkedListNode<T>;
	node->element = x;
	node->next = NULL;

	if (tail != NULL)
		tail->next = node;
	else
		head = node;

	tail = node;
}

template <typename T>
void LinkedList<T>::clear()
{
	while (head != NULL)
	{
		LinkedListNode<T> *node = head;
		head = head->next;
		delete node;
	}

	tail = NULL;
}

template <typename T>
void LinkedList<T>::insertion_sort()
{
	if (head == NULL)
		return;

	LinkedListNode<T> *q = head;
	LinkedListNode<T> *p = head->next;

	while (p != NULL)
	{
		LinkedListNode<T> *pre = NULL;
		LinkedListNode<T> *cur = head;

		while (cur != p)
		{
			if (cur->element <= p->element)
			{
				pre = cur;
				cur = cur->next;
			}
			else
			{
				break;
			}
		}

		if (cur != p)
		{
			if (pre != NULL)
			{
				q->next = p->next;
				pre->next = p;
				p->next = cur;
				p = q->next;
			}
			else
			{
				q->next = p->next;
				head = p;
				p->next = cur;
				p = q->next;
			}
		}
		else
		{
			q = p;
			p = p->next;
		}
	}

	tail = q;
}


#endif // #ifndef _LINKED_LIST_H_
