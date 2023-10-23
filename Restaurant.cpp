#include "main.h"

class imp_res : public Restaurant
{
public:
	
	public:	
		imp_res() {};
		~imp_res(){};
		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			if (energy == 0) { return; }

			if (table.findNameofDCLL(cus)!=nullptr) { return; }
					else if (table.isEmpty()) {
						table.addCusFirst(cus);
						order.add(new customer(name,energy,nullptr,nullptr));
					}
			        else if (table.getCount() < MAXSIZE/2) {
						if (table.getCurr()->energy <= energy) {
							table.addCusRight(cus);
						}
						else {
							table.addCusLeft(cus);
						}
						order.add(new customer(name,energy,nullptr,nullptr));
					}
					else if(table.getCount()<MAXSIZE){
						customer* the_x = table.BiggestRESValue(cus);
						table.setCurr(the_x);
						if (energy - the_x->energy < 0) {
							table.addCusLeft(cus);
						}
						else {
							table.addCusRight(cus);
						}
						order.add(new customer(name,energy,nullptr,nullptr));
					}
					else {
						if (order.findNameofDLL(cus)!=nullptr) { return; }
						if (queue.getCount() >= MAXSIZE) { return; }

						queue.push(new customer(name,energy,nullptr,nullptr));
						order.add(new customer(name,energy,nullptr,nullptr));
					}

		}
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;
			int num_2 = num;
			num = num < table.getCount() ? num : table.getCount();
			for (int i = 0; i < num; i++) {
				table.setCurr(table.findNameofDCLL(order.top()));
				table.DelCurrCustomer();
				order.pop();
			}
			num = num_2;
			num = num < MAXSIZE ? num : MAXSIZE;
			if (queue.isEmpty()) return;
			for (int k = num; k > 0; k--) {
				order.pop();
				RED(queue.top()->name, queue.top()->energy);
				queue.pop();
			}


			order.readQueue();
		}
		void PURPLE()
		{
			cout << "purple"<< endl;
		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;
			if (num != 0) {
				table.readTable(num);
			}
			else { queue.readQueue(); }

		}

		class DCLinkedList {
		private:
			int count;
			customer* current;
		public:
			DCLinkedList() {
				count = 0;
				current = nullptr;
			}
			~DCLinkedList() {}
			void addCusFirst(customer* new_one) {
				//Neu DCLL rong thi xai ham nay trc
				current = new_one;
				current->next = current;
				current->prev = current;
				count++;
			}
			void addCusLeft(customer* new_one) {
				//Them 1 node vao ben trai (con goi la dau LL)
				new_one->next = current;
				current->prev->next = new_one;
				new_one->prev = current->prev;
				current->prev = new_one;
				setCurr(new_one);
				count++;
			}
			void addCusRight(customer* new_one) {
				//them 1 node vao ben phai (con goi la cuoi LL)
				new_one->prev = current;
				current->next->prev = new_one;
				new_one->next = current->next;
				current->next = new_one;
				setCurr(new_one);
				count++;
			}
			bool isEmpty() {
				//coi CDLL co dang rong hay ko
				return current == nullptr;
			}
			int getCount() {
				//lay so phan tu
				return count;
			}
			customer* getCurr() {
				return current;
			}
			void setCurr(customer* k) {
				//sua vi tri gan nhat co su thay doi
				if (k == nullptr) return;
				current = k;
			}
			
			 void DelCurrCustomer(){
				 if (current == nullptr) return;
				 if (count == 1) {
					 delete current;
					 current = nullptr;
					 count = 0;
					 return;
				 }
				 customer* del = current;
				 if (current->energy < 0) {
					 current = current->prev;
				 }
				 else current = current->next;
				 del->next->prev = del->prev;
				 del->prev->next = del->next;
				 del->next = nullptr;
				 del->prev = nullptr;
				 delete del;
				 count--;
			 }
			customer* BiggestRESValue(customer*the_one) {
				//Kiem vi tri ma hieu tri tuyet doi la lon nhat
				customer* check = current;
				customer* result = nullptr;
				int RES = 0;
				for (int i = 0; i < count;i++) {
					if (abs((the_one->energy) - (check->energy)) > RES) {
						RES = abs((the_one->energy) - (check->energy));
						result = check;
					}
					check = check->next;
				}
				return result;
			}
			customer* findNameofDCLL(customer* checker) {
				//kiem coi trong DCLL co customer cung ten ko ?
				if (current == nullptr) { return nullptr; }
				customer* run = current;
				for (int i = 0; i < count;i++) {
					if (checker->name == run->name) {
						return run;
					}
					run = run->next;
				}
				return nullptr;
			}
			void readTable(int num) {
				customer* run = current;
				if (num > 0) {
					for (int k = 0; k < count;k++) {
						run->print();
						run = run->next;
					}
				}
				else {
					for (int k = 0; k < count; k++) {
						run->print();
						run = run->prev;
					}
				}
			}
		} table;
		class DLinkedList {
		private:
			int count;
			customer* last;
			customer* first;
		public:
			DLinkedList() {
				count = 0;
				first = last = nullptr;
			}
			void add(customer* new_one) {
				//Them 1 node vao DLL ko vong
				if (count == 0) {
					first = last = new_one;
					count++;
				}
				else {
					new_one->prev = last;
					last->next = new_one;
					last = new_one;
					count++;
				}
			}
			void push(customer* waiting) {
				add(waiting);
			}
			void pop() {
				if (count == 1) {
					delete first;
					first = last = nullptr;
					return;
					count == 0;
				}
				first = first->next;
				delete first->prev;
				first->prev = nullptr;
				count--;
			}
			int getCount() {
				return count;
			}
			bool isEmpty() {
				return first == nullptr ? 1 : 0;
			}
			customer* top() {
				customer* deeep = new customer(first->name, first->energy, nullptr, nullptr);
				return deeep;
			}
			
			customer* findNameofDLL(customer* checker) {
				//kiem coi trong DLL co customer cung ten ko ?
				if (first == nullptr) { return nullptr; }
				customer* run = first;
				while (run->next != nullptr) {
					if (checker->name == run->name) {
						return run;
					}
					run = run->next;
				}
				return nullptr;
			}

			void readQueue() {
				if (count == 0) return;
				customer* running = first;
				for (int i = 0; i < count;i++) {
					running->print();
					running = running->next;
				}
			}
		} queue,order;
};