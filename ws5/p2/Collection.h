/*
*****************************************************************************
                          OOP345 Workshop - #5 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <string>
#include <stdexcept>
#include <iostream>

namespace seneca {
    template<typename T>
    class Collection {
    private:
        std::string name_m;
        T* items_m;
        size_t size_m ;
        void (*observer_m)(const Collection<T>&, const T&);

    public:
        Collection(const std::string& name);
        ~Collection() ;
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        const std::string& name() const ;
        size_t size() const;
        void setObserver(void (*observer)(const Collection<T>&, const T&));
        Collection<T>& operator+=(const T& item) ;
        T& operator[](size_t idx) const;
        T* operator[](const std::string& title) const;

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const Collection<U>& collection);
    };

    template<typename T>
    Collection<T>::Collection(const std::string& name) :name_m(name),items_m(nullptr), size_m(0),observer_m(nullptr) {}

    template<typename T>
    Collection<T>::~Collection() {
        delete[] items_m ;
    }

    template<typename T>
    const std::string& Collection<T>::name() const {
        return name_m;
    }

    template<typename T>
    size_t Collection<T>::size() const {
        return size_m;
    }

    template<typename T>
    void Collection<T>::setObserver(void (*observer)(const Collection<T>&, const T&)) {
        observer_m = observer;}

    template<typename T>
    Collection<T>& Collection<T>::operator+=(const T& item) {
        for (size_t i= 0;i < size_m;++i) {
            if (items_m[i].title()== item.title()) {
                return *this; 
            }
        }

        T* temp= new T[size_m +1];
        for (size_t i =0; i < size_m; ++i) {
            temp[i]= items_m[i];
        }temp[size_m]= item;

        delete[] items_m;
        items_m =temp;
        ++size_m;

        if (observer_m!= nullptr) {
            observer_m(*this,item);
        }
    return *this;
    }

    template<typename T>
    T& Collection<T>::operator[](size_t idx) const {
        if (idx >=size_m) {
            throw std::out_of_range("Bad index [" +std::to_string(idx)+"]. Collection has ["+std::to_string(size_m) +"] items.");
        }
        return items_m[idx];
    }

    template<typename T>
    T* Collection<T>::operator[](const std::string& title) const {
        for (size_t i =0; i< size_m;++i) {
            if (items_m[i].title()== title) {
                return &items_m[i];
            }
        }return nullptr;
    }

    template<typename U>
    std::ostream& operator<<(std::ostream& os, const Collection<U>& collection) {
        for (size_t i= 0; i <collection.size();++i) {
            os<<collection[i];
        }return os;
    }

} 

#endif 
