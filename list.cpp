template <typename T>
class List
{
	struct node
	{
		T data;
		node *next;
	};
private:
	node * fst_node, *lst_node;
	int size;
public:
	class Iterator
	{
		friend Iterator List<T>::begin();
		friend Iterator List<T>::end();
		friend void List<T>::insert(Iterator iter, T data);
		friend void List<T>::remove(Iterator iter);
	public:
		Iterator(const Iterator &copy)
		{
			pointer = copy.pointer;
		}
		Iterator operator++(int)
		{
			pointer = pointer->next;
			return *this;
		}
		T operator*()
		{
			return pointer->data;
		}
		Iterator &operator=(const Iterator& right)
		{
			pointer = right.pointer;
			return *this;
		}
		bool operator==(const Iterator& right)
		{
			return (pointer == right.pointer);
		}
		bool operator!=(const Iterator& right) 
		{
			return (pointer != right.pointer);
		}
	private:
		node * pointer;
		Iterator(node * pointer)
		{
			this->pointer = pointer;
		}
	};
	List()
	{
		fst_node = nullptr;
		lst_node = nullptr;
		size = 0;
	}
	List(List &copy)
	{
		for (List<T>::Iterator i = copy.begin(); i != copy.end(); i++)
			push_back(*i);
	}
	~List()
	{
		for (int i = 0; i < size; i++)
		{
			remove(begin());
		}
	}
	void insert(Iterator iter, T data)
	{
		node *cnt_node = new node;
		cnt_node->data = data;
		if (iter.pointer == fst_node)
		{
			cnt_node->next = fst_node;
			fst_node = cnt_node;
		}
		else if (iter.pointer == nullptr)
		{
			cnt_node->next = nullptr;
			lst_node->next = cnt_node;
		}
		else
		{
			node *pre_node = fst_node;
			while (pre_node->next != iter.pointer)
				pre_node = pre_node->next;
			cnt_node->next = iter.pointer;
			pre_node->next = cnt_node;
		}
		size++;
		if (iter.pointer == nullptr) lst_node = cnt_node;
	}
	void remove(Iterator iter)
	{
		if (iter.pointer == fst_node)
		{
			node *del_fst = fst_node;
			if (iter.pointer == lst_node)
			{
				lst_node = nullptr;
				fst_node = nullptr;
			}
			else
			{
				iter++;
				fst_node = fst_node->next;
			}
			delete del_fst;
		}
		else
		{
			node *pre_node = fst_node;
			while (pre_node->next != iter.pointer)
				pre_node = pre_node->next;
			node *del = pre_node->next;
			if (iter.pointer == lst_node) lst_node = pre_node;
			iter++;
			pre_node->next = pre_node->next->next;
			delete del;
		}
		size--;
	}
	void push_back(T data)
	{
		insert(end(), data);
	}
	T operator[](int index)
	{
		if (index >= size) throw;
		node *cnt_node = fst_node;
		while (index > 0)
		{
			cnt_node = cnt_node->next;
			index--;
		}
		return cnt_node->data;
	}
	List &operator=(List &copy)
	{
		for (List<T>::Iterator i = copy.begin(); i != copy.end(); i++)
			push_back(*i);
		return *this;
	}
	Iterator begin()
	{
		return List<T>::Iterator(fst_node);
	}
	Iterator end()
	{
		return List<T>::Iterator(nullptr);
	}
};
