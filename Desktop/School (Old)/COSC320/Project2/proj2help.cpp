// List of strings
class LinkedList {
  struct ListNode {
    ListNode *next, *prev;
    std::string word;
  };

  ListNode* head = nullptr;

  // grab your 220 hat...
  
  putFront(std::string s){
    // insert at front...
    ListNode n = new ListNode();
    n->next = head;
    n->word = s;

    head = n;
  }
};

class Dictionary {
  LinkedList* T;

  Dictionary(int size){
    // allocate the new linked lists
    // (check) calls LinkedList() for each element of array
    T = new LinkedList[size];
  }

  void insert(std::string word){
    // check if already in?
    T[hash(text2int(word))].putFront(word);
  }

  size_t hash(size_t key){
    // do the fancy numeric stuff
  }

  // edit distance, search, etc.
};


int main(){

}