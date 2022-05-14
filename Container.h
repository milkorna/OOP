#pragma once

#include <cstdlib>
#include <exception>

namespace exceptions{
    class ContainerException: public std::exception{};
    class PopEmptyException: public ContainerException {};
    class GetHeadOfEmptyContainer: public ContainerException {};
}


template <typename T>
class Container{
private:
    struct el {
        T obj;
        el *prev;
        el *next;
    };

    el *end;
    el *first;
    el *last;
    int size;

public:
    class ConIter;
    Container(): first(nullptr), last(nullptr), size(0), end(nullptr){}

    void PushFront(T const & obj){
        el * newEl = new el(obj, nullptr, nullptr);
        if (size == 0) {
            first = last = newEl;
            first->next = end;
        } else {
            el * prevHead = first;
            first = newEl;
            first->next = prevHead;
            prevHead->prev = first;
        }
        ++size;

    }


    void PushBack(T const & obj){
        el * newEl = new el;
        newEl->obj = obj;
        newEl->next = newEl->prev = nullptr;

       if (size == 0){
           first = last = newEl;
           last->next = end;
       } else {
           last->next = newEl;
           newEl->prev = last;
           last = newEl;
           last->next = end;
       }
        ++size;

    }

    void PopHead(){
        if (size == 0)
            throw exceptions::PopEmptyException();
        if (size == 1){
            delete first;
            first = last = nullptr;
        } else {
            el *nextEl = first->next;
            delete first;
            first = nextEl;
            first->prev = nullptr;

        }
        --size;
    }

     void PopTail(){
        if (size == 0)
            throw exceptions::PopEmptyException();

        if (size == 1){
            delete last;
            first = last = nullptr;
        } else {
            el * tailPrev = last->prev;
            delete last;
            last = tailPrev;
            last->next = end;
        }
        --size;
    }


    T const & GetHead(){
        if (first == nullptr)
            throw exceptions::GetHeadOfEmptyContainer();
        return first->obj;
    }


    T const & GetTail(){
        if (last != nullptr)
            return last->obj;
        throw exceptions::GetHeadOfEmptyContainer();
    }

    ConIter GetBegin() const{
        if (first == nullptr)
            return ConIter(end);
        else
            return ConIter(this->first);
    }

    ConIter GetEnd() const{
       return ConIter(end);
    }

    unsigned int GetSize() const {
        return size;
    }

    bool IsEmpty() {return size == 0;}

    void SwapConts(Container<T> & obj){
        std::swap(this->first, obj.first);
        std::swap(this->last, obj.last);
        std::swap(this->size, obj.size);
    }

    void Reverse(){

        if (size == 1){
            return;
        }

        el * curElem = first;
        while (curElem != last){
            curElem->prev = curElem->next;
            curElem->next = curElem->prev;
            curElem = curElem->prev;
        }

        first->next = end;
        last->next = last->prev;
        last->prev = nullptr;

        el * s = first;
        first = last;
        last = s;

    }

    void Clear(){
        if (size == 0)
            return;
        if (size == 1){
            delete first;
        } else {
            el * tmp = first;
            while (tmp != end) {
                el *newTmp = tmp->next;
                delete tmp;
                tmp = newTmp;
            }
        }
        first = last = nullptr;
        size = 0;
    }

    ~Container(){
        Clear();
    }

    class ConIter{
    private:
        el *cur;
    public:
        explicit ConIter(el * node): cur(node){}

        ConIter& operator--(){
            if (this->cur != nullptr)
                this->cur = this->cur->prev;
            return *this;
        }

        ConIter& operator++(){
            if (this->cur != nullptr)
                this->cur = this->cur->next;
            return *this;
        }

        el *getCur() const {
            return this->cur;
        }

        bool operator==(const ConIter & other){
            return this->cur == other.cur;
        }
        bool operator!=(const ConIter & other){
            return this->cur != other.cur;
        }
    };

};

