/*****************************************************
Template prepared by Kazumi Slott
CS311
min heap class

Your name: Scott Leyden
Your programmer number: 20
Hours spent making and testing your min heap class: 2
An y difficulties?: ????
*******************************************************/
#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream> //for operator<<()
using namespace std;
//#include "swap.h" //for mySwap().  If you didn't create it, you can use the library's swap()

template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
  friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
  T* ar; //dynamic array
  int capacity; //the size of ar
  int num; //the number of elements I have in ar
public:
  minHeap(){ar = NULL; capacity = 0; num = 0;}
  minHeap(int c);
  ~minHeap(){if(ar!=NULL)delete [] ar;}
  void min_heapify(int i);
  //void build_min_heap(); //no need to implement this. We won't use it for our application.
  void bubbleUp(int i);
  void insert(const T& el);
  int find(const T& key) const;
  void remove(int i);
  T getMin();
  T& getElem(int i) {return ar[i];};       
  const T& getElem(int i) const {return ar[i];}; 
  int getCap() const {return capacity;}; 
  int getNum() const {return num;}; 
  void updateElem(int i, const T& newValue);

  class Underflow{};
  class Overflow{};
  class BadIndex{};
  class NotFound{};
};


// You need to implement all the memeber functions above.  Don't forget operator<<().



template <class T>
inline minHeap<T>::minHeap(int c){
  ar = new T[c];
  capacity = c;
  num = 0;
}


template<class T> void minHeap<T>::min_heapify(int i){
  int l = 2*i + 1;
  int r = 2*i + 2;
  int smallest = i;

  if (l < num && ar[l] < ar[smallest]){
    smallest = l;
  }
  if (r < num && ar[r] < ar[smallest]){
    smallest = r;
  }

  if (smallest != i)
  {
    mySwap(ar[smallest], ar[i]);
    min_heapify(smallest);
  }
}


template<class T> void minHeap<T>::bubbleUp(int i){
  while (i>0 && ar[i] < ar[(i-1)/2]){
    mySwap(ar[i], ar[(i-1)/2]);
    i = (i-1)/2;
  }
}


template<class T> void minHeap<T>::insert(const T& el){
  if(num >= capacity) 
    throw Overflow(); //"The array is full"; 

  ar[num] = el;
  bubbleUp(num);
  num++;
}


template <class T>
int minHeap<T>::find(const T& key) const
{
  for(int i = 0; i < num; i++) 
    if(ar[i] == key)
      return i;

  //The element doesn't exist 
  throw NotFound();// "The element doesn't exist";                                                                                             
}


template<class T>
void minHeap<T>::remove(int i){
  if(i > num)
    throw BadIndex(); //"The element doesn't exist";                                                                       
  
  mySwap(ar[num - 1], ar[i]);
  num--;

  if (ar[i] < ar[(i-1)/2]){
    bubbleUp(i);
  } else {
    min_heapify(i);
  }
}


template<class T> T minHeap<T>::getMin()
{
  if(num == 0)
      throw Underflow();
  T temp = ar[0];
  remove(0);
  return temp;
}


template <class T> ostream &operator<<(ostream &o, const minHeap<T> &h)
{
  if (h.num != 0){
    for (int i = 0; i < h.num; i++){
      o << h.ar[i] << " ";
    }
  } else {
    o << "none" << endl;
  }
  
  return o;
}


template <class T>
inline void minHeap<T>::updateElem(int i, const T &newValue)
{
  ar[i] = newValue;
  bubbleUp(i);
}

#endif

