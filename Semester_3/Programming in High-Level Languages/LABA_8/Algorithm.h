#pragma once
#include "BinaryTree.h"

template <class T>
class Algorithm
{
public:
	typename BinaryTree<T>::Iterator findFirst(typename BinaryTree<T>::Iterator b, typename BinaryTree<T>::Iterator e, T& data);
	BinaryTree<T> findAll(typename BinaryTree<T>::Iterator b, typename BinaryTree<T>::Iterator e, T& data);
	void sort(typename BinaryTree<T>::Iterator b, typename BinaryTree<T>::Iterator e, T& data);
	void swap(typename BinaryTree<T>::Iterator first, typename BinaryTree<T>::Iterator second); //метод перестановки двух элементов
    void swap(typename multimap<int, T>::iterator first, typename multimap<int, T>::iterator second); //метод перестановки двух элементов
    void sort(typename multimap<int, T>::iterator b, typename multimap<int, T>::iterator e, T& data);
};

template <class T>
typename BinaryTree<T>::Iterator Algorithm<T>::findFirst(typename BinaryTree<T>::Iterator b, typename BinaryTree<T>::Iterator e, T& data) //метод поиска первого требуемого элемента в дереве
{
    for (auto it = b; it != nullptr; it++)
        if (*it == data)
            return it;
    return nullptr;
}

template<class T>
BinaryTree<T> Algorithm<T>::findAll(typename BinaryTree<T>::Iterator b, typename BinaryTree<T>::Iterator e, T& data)
{
    BinaryTree<T> tree;
    for (auto it = b; it != nullptr; it++)
        if (*it == data)
            tree.add(tree.getRoot(), *it);
    return tree;
}

template<class T>
void Algorithm<T>::sort(typename BinaryTree<T>::Iterator b, typename BinaryTree<T>::Iterator e, T& data)
{
    for (typename BinaryTree<T>::Iterator it1 = b; it1 != e + 1; it1++)	//проход по очереди
    {
        typename BinaryTree<T>::Iterator min = it1;
        for (typename BinaryTree<T>::Iterator it2 = it1; it2 != e + 1; it2++)
        {
            T temp = *it2;
            T tempMin = *min;
            temp.cleanSomeFields(data);
            tempMin.cleanSomeFields(data);
            if (temp < tempMin)
                min = it2;
        }
        swap(min, it1);
    }
}

template<typename T>
void Algorithm<T>::swap(typename BinaryTree<T>::Iterator first, typename BinaryTree<T>::Iterator second) //метод перестановки двух элементов
{                                                                                                           //используя итераторы
    T temp = *first;
    *first = *second;
    *second = temp;
}

template<typename T>
void Algorithm<T>::swap(typename multimap<int, T>::iterator fir, typename multimap<int, T>::iterator sec) //метод перестановки двух элементов
{                                                                                                           //используя итераторы
    T temp = fir->second;
    fir->second = sec->second;
    sec->second = temp;
}

template<class T>
void Algorithm<T>::sort(typename multimap<int, T>::iterator b, typename multimap<int, T>::iterator e, T& data)
{
    for (auto it1 = b; it1 != e; it1++)
    {
        auto min = it1;
        for (auto it2 = it1; it2 != e; it2++)
        {
            T temp = it2->second;
            T tempMin = min->second;
            temp.cleanSomeFields(data);
            tempMin.cleanSomeFields(data);
            if (temp < tempMin)
                min = it2;
        }
        swap(min, it1);
    }
}