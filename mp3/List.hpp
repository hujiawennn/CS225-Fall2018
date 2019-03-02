/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
#include <stack>
using namespace std;
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode * temp;
  ListNode * current;
  current = head_;
  while(current != NULL){
    temp = current->next;
    delete current;
    current = temp;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if(head_ == NULL) {
    head_ = new ListNode(ndata);
    length_++;
    tail_ = head_;
  } else {
   ListNode* temp = new ListNode(ndata);
   head_->prev = temp;
   temp->next = head_;
   head_ = temp;
   length_++;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if(tail_ == NULL){
    ListNode * temp = new ListNode(ndata);
    tail_ = temp;
    length_++;
    head_ = tail_;
  } else {
    ListNode * temp = new ListNode(ndata);
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = temp;
    length_++;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
//@todo Graded in MP3.1
stack<ListNode*> s;
if(startPoint == NULL || endPoint == NULL) {
  return;
}
ListNode * temp1 = startPoint->prev;
ListNode * temp2 = endPoint->next;
ListNode * current = startPoint;
if(startPoint == endPoint) {
  return;
}
while (current != temp2) {
        s.push(current);
        current = current->next;
      }
startPoint = s.top();
while (!s.empty()){
        current = s.top();
        s.pop();
        current->prev = temp1;
        if(temp1 != NULL) {
        temp1->next = current;
        }
        temp1 = current;
}

  endPoint = temp1;
  endPoint->next = temp2;
  if(temp2 != NULL) {
  temp2->prev = endPoint;
}
}



/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if (n < 0 || n == 0 || n == 1 || length_ == 0 || head_ == NULL){
    return;
  }
  int blockNumber;
  int x = length_;
  bool leftover = false;
  ListNode * currentEnd;
  ListNode * currentStart;
  ListNode * temp;
  if (n >= x) {
    reverse();
    return;
  } else {
  blockNumber = x / n;
  currentStart = head_;
  currentEnd = currentStart;
  }
  if(x % n != 0) {
    leftover = true;
  }
  for (int i = 1; i <= blockNumber; i++) {
      for (int j = 1; j < n; j++) {
      currentEnd = currentEnd->next;
      }
    reverse(currentStart, currentEnd);
    if(i == 1) {
      head_ = currentStart;
    }
    if(i < blockNumber){
    currentStart = currentEnd->next;
    currentEnd = currentStart;
  } else {
    if(leftover) {
      currentStart = currentEnd->next;
      reverse(currentStart,tail_);
    } else {
      tail_ = currentEnd;
    }
  }
  }
}



/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
// @todo Graded in MP3.1
ListNode * curr = head_;
ListNode * tail = tail_;
ListNode * currSKT = (head_->next)->next;
ListNode * temp = curr->next;
while(curr != tail) {
  tail->next = temp;
  temp->prev = tail;
  curr->next = currSKT;
  currSKT->prev = curr;
  curr = currSKT;
  if(curr == tail) {
    temp->next = NULL;
    tail = temp;
    tail_ = tail;
    break;
  }
  currSKT = (curr->next)->next;
  tail = temp;
  temp = curr->next;
}
}

/**
 * Splits the list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_) {
        return List<T>(); }

    if (splitPoint < 0) {
        splitPoint = 0;
        }
    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }
    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode* current = start;
  ListNode* newHead = start;
  for(int i = 0; i < splitPoint; i++) {
    current = current->next;
  }
  newHead = current;
  current = newHead->prev;
  current->next = NULL;
  newHead->prev = NULL;
  return newHead;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  if (first == NULL) {
    return second;
  } else if (second == NULL) {
    return first;
  }
  ListNode* current = first;
  if (!(current->data < second->data) && second != NULL) {
    ListNode* temp = second->next;
    second->next = current;
    current->prev = second;
    second->prev = NULL;
    first = second;
    second = temp;
    current = first;
  }
    while (second != NULL) {
        if(current->next == NULL) {
          current->next = second;
          second->prev = current;
          break;
        } else {
          if ((current->next->data) < second->data) {
            current = current->next;
          } else {
          ListNode* temp = second->next;
          ListNode* pushAfterwards = current->next;
          current->next = second;
          second->prev = current;
          pushAfterwards->prev = second;
          second->next = pushAfterwards;
          current = current->next;
          second = temp;
        }
      }
      }
      return first;
  }



/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  if (chainLength == 1) {
    return start;
  }
  ListNode* second = split(start, chainLength/2);
  start = mergesort(start, chainLength/2);
  second = mergesort(second, chainLength- chainLength/2);
  return merge(start, second);
}
