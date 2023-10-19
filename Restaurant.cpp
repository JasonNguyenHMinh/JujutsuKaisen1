#include "main.h"

class imp_res : public Restaurant
{
public:
	
	public:	
		imp_res() {};

		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			if (energy == 0) { return; }

			if (table.findNameofDCLL(cus)) { return; }
					else if (table.isEmpty()) {
						table.addCusFirst(cus);
						order.add(cus);
					}
			        else if (table.getCount() < MAXSIZE/2) {
						if (table.getCurr()->energy <= energy) {
							table.addCusRight(cus);
						}
						else {
							table.addCusLeft(cus);
						}
						order.add(cus);
					}
					else if(table.getCount()<=MAXSIZE){
						customer* the_x = table.BiggestRESValue(cus);
						table.setCurr(the_x);
						if (energy - the_x->energy < 0) {
							table.addCusLeft(cus);
						}
						else {
							table.addCusRight(cus);
						}
						order.add(cus);
					}
					else {
						if (order.findNameofDLL(cus)) { return; }
						if (queue.getCount() > MAXSIZE) { return; }

						queue.push(cus);
						order.add(cus);
					}

		}
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;

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
				current = k;
			}
			customer* BiggestRESValue(customer*the_one) {
				//Kiem vi tri ma hieu tri tuyet doi la lon nhat
				//DCM sao mình lại đi làm cái củ lìn này nhỉ ???
				customer* check = current;
				customer* result = nullptr;
				int RES = 0;
				while (check->next != current) {
					if (abs((the_one->energy) - (check->energy)) > RES) {
						RES = abs((the_one->energy) - (check->energy));
						result = check;
					}
					check = check->next;
				}
				return result;
			}
			bool findNameofDCLL(customer* checker) {
				//kiem coi trong DCLL co customer cung ten ko ?
				if (current == nullptr) { return true; }
				customer* run = current;
				while (run->next != current) {
					if (checker->name == run->name) {
						return true;
					}
					run = run->next;
				}
				return false;
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
			customer* pop() {
				customer* result = first;
				first = first->next;
				delete first->prev;
				first->prev = nullptr;
				count--;
				return result;
			}
			int getCount() {
				return count;
			}
			bool isEmpty() {
				return first == nullptr;
			}
			void delFirstCus() {
				first = first->next;
				delete first->prev;
				first->prev = nullptr;
			}
			bool findNameofDLL(customer* checker) {
				//kiem coi trong DLL co customer cung ten ko ?
				if (first == nullptr) { return true; }
				customer* run = first;
				while (run->next != nullptr) {
					if (checker->name == run->name) {
						return true;
					}
					run = run->next;
				}
				return false;
			}
		} queue,order;
};