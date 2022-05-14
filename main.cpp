#include <iostream>
#include "Container.h"
#include "Object.h"


unsigned int Object::objCounter = 0;

int main() {
    setlocale(LC_ALL, "Russian");

    Container<Task *> container;

    auto b1 = new BinCalc<int>(42, 2, '/');
    auto b2 = new BinCalc<double>(2022, 1205, '/');
    auto b3 = new BinCalc<float>(1984, 1985, '+');
    auto b4 = new BinCalc<double>(1337, 42, '-');

    auto s1 = new AddTask(b1, container);
    auto s2 = new AddTask(b2, container);
    auto s3 = new AddTask(b3, container);
    auto s4 = new AddTask(b4, container);
    s1->doTask();
    s2->doTask();
    s3->doTask();
    s4->doTask();
    ObjCount *b5 = new ObjCount();
    auto s5 = new AddTask(b5, container);
    Counter *b6 = new Counter(container);
    container.PushBack(b6);
    CountResult *b7 = new CountResult(container);
    container.PushBack(b7);
    ObjCount *b8 = new ObjCount();
    container.PushBack(b8);
    BinCalc<float> *b9 = new BinCalc<float>(54.f, 0, '*');
    auto s6 = new AddTask(b9, container);
    BinCalc<int> *b10 = new BinCalc<int>(21, 30, '/');
    auto s7 = new AddTask(b10, container);
    BinCalc<double> *b11 = new BinCalc<double>(3.1415926535, 2.718281828, '-');
    auto s8 = new AddTask(b11, container);

    BinCalc<float> *b12 = new BinCalc<float>(20.07, 18.05, '-');
    container.PushBack(b12);
    s5->doTask();
    s6->doTask();
    s7->doTask();
    s8->doTask();
    ClearCont *b13 = new ClearCont(container);
    container.PushBack(b13);

    Container<std::string> info{};

    std::cout << "общее количество объектов" << Object::getObjCounter() << std::endl;

    while(!container.IsEmpty()){
        Task * curTask = container.GetHead();
        container.PopHead();
        curTask->doTask();
        info.PushBack(curTask->toString());
    }

    for (Container<std::string>::ConIter el = info.GetBegin(); el != info.GetEnd(); ++el){
        std::cout << el.getCur()->obj << std::endl;
    }


    info.Clear();
    container.Clear();

    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s5;
    delete s6;
    delete s7;
    delete s8;

    delete b1;
    delete b2;
    delete b3;
    delete b4;
    delete b5;
    delete b6;
    delete b7;
    delete b8;
    delete b9;
    delete b10;
    delete b11;
    delete b12;
    delete b13;

    std::cout << "общее количество объектов" << Object::getObjCounter() << std::endl;

    return 0;
}
