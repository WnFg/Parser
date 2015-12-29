#ifndef MYLIST
#define MYLIST

template<class T> 
	struct Node
	{
		T v;
		Node *last, *next;
		
	};
template<class T>
	struct my_List
	{
		Node<T> *head, *end;
		int size;
		void del(Node<T> *p){
			if(end == p)
				end = p->last;
			p->last->next = p->next;
			delete(p);
		}

		void add(Node<T> *p, int t){
			if(size == 0){
				end = p;
			}
			if(!t){
				p->next = head->next;
				head->next = p->next;
				size++;
			}else{
				end->next = p;
				end = p;
			}
			size++;
		}

		void add(my_List<T> *ls, int t){
			if(size == 0)
				end = ls->end;
			if(!t){
				ls->end = head->next;
				head->next = ls->head->next;
			}else{
				end->next = ls->head->next;
				end = ls->end;
			}
			size += ls->size;
		}
	};

#endif
