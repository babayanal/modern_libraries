#include <iostream>
using namespace std;

struct Node {
   int val;
   Node* next;
   Node(int v): val(v), next(nullptr) {}
};

bool hasCycle(Node* head) {
   Node *slow = head, *fast = head;
   while (fast && fast->next) {
       slow = slow->next;
       fast = fast->next->next;
       if (slow == fast) return true;
   }
   return false;
}

Node* cycleStart(Node* head) {
   Node *slow = head, *fast = head;
   do {
       if (!fast || !fast->next) return nullptr;
       slow = slow->next;
       fast = fast->next->next;
   } while (slow != fast);
   slow = head;
   while (slow != fast) {
       slow = slow->next;
       fast = fast->next;
   }
   return slow;
}

int cycleLength(Node* head) {
   Node *slow = head, *fast = head;
   while (fast && fast->next) {
       slow = slow->next;
       fast = fast->next->next;
       if (slow == fast) {
           int len = 1;
           fast = fast->next;
           while (fast != slow) {
               fast = fast->next;
               ++len;
           }
           return len;
       }
   }
   return 0;
}

int main() {
   Node* head = new Node(1);
   head->next = new Node(2);
   head->next->next = new Node(3);
   head->next->next->next = new Node(4);
   head->next->next->next->next = new Node(5);
   head->next->next->next->next->next = head->next->next;
   if (hasCycle(head)) {
       cout << "Cycle detected" << endl;
       Node* start = cycleStart(head);
       cout << "Cycle starts at node with value: " << start->val << endl;
       cout << "Cycle length: " << cycleLength(head) << endl;
   } else {
       cout << "No cycle detected" << endl;
   }
   return 0;
}