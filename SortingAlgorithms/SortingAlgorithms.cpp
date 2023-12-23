#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>


class Person {
public:
    int _age;
    std::string _name;
    Person() :_age(0), _name("default") {};
    Person(int age, std::string name) :_age(age), _name(name) {}

    friend bool operator==(const Person& p1, const Person& p2) {
        return p1._age == p2._age;
    }

    friend bool operator!=(const Person& p1, const Person& p2) {
        return p1._age != p2._age;
    }

    friend bool operator<(const Person& p1, const Person& p2) {
        return p1._age < p2._age;
    }

    friend bool operator>(const Person& p1, const Person& p2) {
        return p1._age > p2._age;
    }

    friend bool operator<=(const Person& p1, const Person& p2) {
        return p1._age <= p2._age;
    }

    friend bool operator>=(const Person& p1, const Person& p2) {
        return p1._age >= p2._age;
    }
};


void bubblesort(std::vector<Person>& vec) {
    bool swapped = 0;
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec.size(); j++) {
            if (vec[i] < vec[j]) {// this line shows that bubble sort is stable
                Person temp = vec[j];
                vec[j] = vec[i];
                vec[i] = temp;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}


void bubblesortoptimized(std::vector<Person>& vec) {
    int size = vec.size();
    bool swapped = false;
    while (size--) {
        for (int i = 1; i < size; ++i) {
            if (vec[i] < vec[i - 1]) {
                Person temp = vec[i];
                vec[i] = vec[i - 1];
                vec[i - 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;

    }

}

void insertionsort(std::vector<Person>& vec) {
    Person key;
    int j;
    for (int i = 1; i < vec.size(); i++) {
        key = vec[i];
        j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

void selectionsort(std::vector<Person>& vec) {
    int minindex = 0;
    for (int i = 0; i < vec.size(); i++) {
        minindex = i;
        for (int j = i + 1; j < vec.size(); j++)
            if (vec[j] < vec[minindex]) {
                minindex = j;
            }

        if (minindex != i)
            std::swap(vec[minindex], vec[i]);
    }
}


void merge(std::vector<Person>& vec, int first, int mid, int last) {
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = first;
    std::vector<Person> temp(vec.size());
    while (first1 <= last1 && first2 <= last2) {
        if (vec[first1] <= vec[first2])
            temp[index++] = vec[first1++];
        else
            temp[index++] = vec[first2++];
    }

    while (first1 <= last1)
        temp[index++] = vec[first1++];

    while (first2 <= last2)
        temp[index++] = vec[first2++];


    for (int i = first; i <= last; i++) {
        vec[i] = temp[i];
    }
}


void mergesort(std::vector<Person>& vec, int first, int last) {
    if (first < last) {
        int mid = first + (last - first) / 2;
        mergesort(vec, first, mid);
        mergesort(vec, mid + 1, last);
        merge(vec, first, mid, last);
    }
}

int partition(std::vector<Person>& vec, int f, int l) {
    Person pivot = vec[f];
    int i = f + 1;
    int j = l;
    while (i < j) {
        while (vec[i] < pivot)
            ++i;
        while (vec[j] > pivot)
            --j;

        if (i < j)
            std::swap(vec[i], vec[j]);
    }
    std::swap(vec[f], vec[j]);
    return j;
}

int partition2(std::vector<Person>& vec, int f, int l) {
    Person pivot = vec[l];
    int i = f - 1;
    for (int j = f; j < l; j++) {
        if (vec[j] <= pivot) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[l]);
    return i + 1;
}

void quicksort(std::vector<Person>& vec, int first, int last) {
    if (first < last) {
        int i = partition2(vec, first, last);
        quicksort(vec, first, i - 1);
        quicksort(vec, i + 1, last);
    }
}

void print(std::vector<Person>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i]._name << " " << vec[i]._age << std::endl;
    }
}
int main()
{
    auto start = std::chrono::steady_clock::now();// 2 1 2 4 4
    std::vector<Person> vec;
    Person p1(5, "Bob");
    Person p2(8, "Martin");
    Person p3(7, "Hayk");
    Person p4(1, "Arman");
    Person p5(56, "Arsen");
    Person p6(3, "Bob");
    Person p7(88, "Gago");
    Person p8(4, "Vahe");
    Person p9(-2, "Karen");
    Person p10(7, "Arsen");
    Person p11(25, "Bob");
    Person p12(45, "David");
    Person p13(122, "Armen");
    Person p14(22, "Arman");
    Person p15(6, "Arsen");
    Person p16(7, "Bob");
    Person p17(90, "Gago");
    Person p18(3, "Serob");
    Person p19(5, "Arman");
    Person p20(7, "Arsen");
    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);
    vec.push_back(p4);
    vec.push_back(p5);
    vec.push_back(p6);
    vec.push_back(p7);
    vec.push_back(p8);
    vec.push_back(p9);
    vec.push_back(p10);
    vec.push_back(p11);
    vec.push_back(p12);
    vec.push_back(p13);
    vec.push_back(p14);
    //vec.push_back(p15);
    //vec.push_back(p16);
    //vec.push_back(p17);
    //vec.push_back(p18);
    //vec.push_back(p19);
    //vec.push_back(p20);// quick sort does not work starting from 20 elemetns

    //bubblesort(vec);
    //bubblesortoptimized(vec);
    //insertionsort(vec);
    //selectionsort(vec); 
    //mergesort(vec, 0, vec.size() - 1);
    quicksort(vec, 0, vec.size() - 1);

    print(vec);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Runtime: " << duration << " milliseconds" << std::endl;
}
