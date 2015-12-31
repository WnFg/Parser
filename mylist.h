#ifndef MYLIST
#define MYLIST

template<class T> 
	struct Node
	{
		T v;
		Node *last, *next;
		Node(){
			last = next = NULL;
		}
		Node(T val){
			v = val;
			last = next = NULL;
		}
	};

template<class T>
	struct my_List
	{
		Node<T> *head, *end;
		int size;
		void f(Node<T> *a, Node<T> *b){
			a->next = b;
			b->last = a;
		}
		Node<T>* copy(Node<T> *p, my_List<T> *a){
			Node<T> *p1 = a->head;
			while(p1->next != NULL){
				p->next = new Node<T>(p1->next->v);
				f(p, p->next);
				p = p->next;
				p1 = p1->next;
			}
			return p;
		}
		my_List()
		{
			end = head = new Node<T>;	
			size = 0;
		}
		
		my_List(my_List<T> *a)
		{
			head = new Node<T>;
			end = copy(head, a);
			size = a->size;
		}
		void del(Node<T> *p){
			if(end == p)
			{
				end = p->last;
				end->next = NULL;
			}else{
				f(p->last, p->next);
			}
			delete(p);
			size--;
		}

		void add(Node<T> *p, int t){
			if(!t){
				f(p, head->next);
				f(head ,p);
			}else{
				f(end, p);
				end = p;
			}
			size++;
		}

/*		void add(my_List<T> *ls, int t){
			if(size == 0){
				head->next = ls->head->next;
				end = ls->end;
			}else if(!t){
				f(ls->end, head->next);
				f(head, ls->head->next);
			}else{
				f(end, ls->head->next);
				end = ls->end;
			}
			size += ls->size;
		}*/
		void add(my_List<T> *ls, int t){
			if(size == 0){
				end = copy(head, ls);
			}else if(!t){
				Node<T> *p = head->next;
				(end = copy(head, ls))->next = p;
			}else{
				end = copy(end, ls);
			}
			size += ls->size;
		}
	};
void delete_list(my_List<string> *p){
	Node<string> *a = p->head, *b = p->head->next;
	delete(a);
	while(b != NULL){
		a = b;
		b = a->next;
		delete(a);
	}
	delete(p->end);
}
#endif
