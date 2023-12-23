#include <iostream>
#include <vector>
#include <climits>


template<typename T>
class priorityqueue {//max heap
private:
    std::vector<T> vec;
public:
    priorityqueue(){}

    bool insert(T key) {
        vec.push_back(INT_MIN);
         return increasekey(vec.size() - 1, key);
    }

    T extractmax() {
        T max = vec[0];
        vec[0] = vec[vec.size() - 1];
        vec.resize(vec.size() - 1);
        Maxheapify(0, vec.size());
        return max;
    }

    bool increasekey(int i, T key) {
        if (vec[i] > key)
            return false;
        vec[i] = key;
        while (i >= 0 && vec[(i - 1) / 2] < vec[i]) {
            std::swap(vec[i], vec[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
        return true;
    }

    T top() {
        return vec[0];
    }

    void print() {
        for (int i = 0; i < vec.size(); i++) {
            std::cout << vec[i] << " ";
        }
    }
    
private:
    void Maxheapify(int index, int heapsize) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int largest = index;

        if (left < heapsize && vec[left] > vec[largest])
            largest = left;
        if (right < heapsize && vec[right] > vec[largest])
            largest = right;

        if (largest != index) {
            std::swap(vec[largest], vec[index]);
            Maxheapify(largest, heapsize);
        }
    }

};


void maxheapify(std::vector<int> &vec, int index, int heapsize) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int largest = index;
    
    if (left < heapsize && vec[left] > vec[largest])
        largest = left;
    if (right < heapsize && vec[right] > vec[largest])
        largest = right;

    if (largest != index) {
        std::swap(vec[largest], vec[index]);
        maxheapify(vec, largest, heapsize);
    }
}


std::vector<int> buildmaxheap(std::vector<int>& vec) {
    int lastparent = (vec.size() - 2) / 2;
    int hs = vec.size();
    for (int i = lastparent; i >= 0; i--) {
        maxheapify(vec, i , hs);
    }
    return vec;
}


void heapsort(std::vector<int> &vec) {
    buildmaxheap(vec);
    int heapsize = vec.size() - 1;
    for (int i = vec.size() - 1; i > 0; i--) {
        std::swap(vec[heapsize], vec[0]);
        --heapsize;
        maxheapify(vec, 0, heapsize);
    }
}



int main(){
    //std::vector<int> myvec = { 4, 10, 24, 3, 7 };
    std::vector<int> myvec = { 4, 10, 24, 3, 7 , 15, 0, 30, 11, 4, -5, 17, -1 };
    //buildmaxheap(myvec);
    //heapsort(myvec);
    priorityqueue<int> pq;
    for (int j = 0; j < myvec.size(); j++) {
        pq.insert(myvec[j]);
    }
    //pq.insert(4);
    //pq.insert(10);
    //pq.insert(0);
    //pq.insert(-5);
    //pq.insert(15);
    //pq.insert(20);
    //pq.insert(8);
    //pq.insert(4);
    pq.extractmax();
    /*pq.extractmax();
    pq.extractmax();*/
    pq.increasekey(8, 19);
    pq.print();
    //std::cout << pq.top();
}

