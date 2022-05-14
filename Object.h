#pragma once
#include <string>
#include <cstdlib>
#include "Container.h"

class Object{
protected:
    static unsigned int objCounter;

public:
    virtual std::string toString() const = 0;
    Object(){
        objCounter++;
    }
    ~Object(){
        objCounter--;
    }

    static const unsigned int &getObjCounter() {
        return objCounter;
    }
};



class Task : public virtual Object{
public:
    virtual bool hasResult() const = 0;
    virtual void doTask() = 0;
};

class Named: public virtual Object{
private:
    std::string name;
};

template <typename T>
class BinCalc: public Task, public Named {
private:
    T a;
    T b;
    T res;
    bool checked;
    char oper;
public:
    BinCalc(T a, T b, char oper):a(a), b(b), oper(oper), checked(false){}

    std::string toString() const override;

    bool hasResult() const override {
        return true;
    }

    void doTask() override {
        switch (oper) {
            case '+': res = a + b; break;
            case '-': res = a - b; break;
            case '/':
                if (b != 0) res = a / b;
                else throw std::runtime_error("нельзя делить на ноль!");
                break;
            case '*': res = a * b; break;
        }
        checked = true;
    }
};

class AddTask: public Task{
private:
    Task * task;
    Container<Task*> & cont;
public:
    AddTask(Task * task, Container<Task*> & cont):task(task), cont(cont){}

    std::string toString() const override {
        return "Добавление задачи";
    }

    bool hasResult() const override {
        return false;
    }

    void doTask() override {
        this->cont.PushBack(task);
    }
};

class Counter : public Task {
private:
    unsigned int res = 0;
    bool checked;
    Container<Task *> const & cont;

public:
    Counter(Container<Task *> const & cont):cont(cont), checked(false){}

    std::string toString() const override {
        if (checked)
            return std::string("Counter задача, результат:") + std::to_string(res);
        return "Counter задача";
    }

    bool hasResult() const override {
        return true;
    }

    void doTask() override {
        res = getObjCounter();
        checked = true;
    }
};

class CountResult : public Task {
private:
    unsigned int res;
    bool checked;
    Container<Task *> const & cont;

public:
    CountResult(Container<Task *> const & cont):cont(cont), checked(false), res(0){}

    std::string toString() const override {
        if (checked)
            return std::string("Задача для подсчёта количества задач с результатом. Результат:") + std::to_string(res);
        return "Задача для подсчёта количества задач с результатом.";
    }

    bool hasResult() const override {
        return true;
    }

    void doTask() override {
        unsigned int counter = 0;
        for (Container<Task *>::ConIter s = cont.GetBegin(); s != cont.GetEnd(); ++s){
            if (s.getCur()->obj->hasResult())
                ++counter;
        }
        res = counter;
        checked = true;
    }
};

class ClearCont : public Task {
private:
    Container<Task *> & cont;
public:
    ClearCont(Container<Task *> & cont):cont(cont){}

    std::string toString() const override {
        return "Задача для очистки контейнера";
    }

    bool hasResult() const override {
        return false;
    }

    void doTask() override {
        cont.Clear();
    }
};

class ObjCount: public Task {
private:
    unsigned int res;
    bool checked;
public:
    ObjCount():res(0), checked(false){}

    std::string toString() const override {
        if (checked)
            return std::string("Задача для подсчёта количества Всего Objectов. Результат:") + std::to_string(res);
        return "Задача для подсчёта количества Всего Objectов.";

    }

    bool hasResult() const override {
        return true;
    }

    void doTask() override {
        res = getObjCounter();
        checked = true;
    }
};

template<> std::string BinCalc<float>::toString() const{
        if (checked)
            return std::string("Задача для подсчёта количества задач с результатом. Результат:") + std::to_string(res);
        return "Задача для подсчёта количества задач с результатом.";
}

template<> std::string BinCalc<int>::toString() const{
        if (checked)
            return std::string("Задача для подсчёта количества задач с результатом. Результат:") + std::to_string(res);
        return "Задача для подсчёта количества задач с результатом.";
}
template<> std::string BinCalc<double>::toString() const{
    if (checked)
        return std::string("Задача для подсчёта количества задач с результатом. Результат:") + std::to_string(res);
    return "Задача для подсчёта количества задач с результатом.";
}

