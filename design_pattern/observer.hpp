#ifndef OBSERVER_H
#define OBSERVER_H
#include <iostream>
#include <list>

using namespace std;
class Observer {
    public:
        virtual void update(float x, float y) = 0;
};

class Subject {
    public:
        virtual void registerObserver(Observer* o) = 0;
        virtual void removeObserver(Observer* o) = 0;
        virtual void notifyObservers() = 0;
};

// 实现Subject的接口
class Subject0 : public Subject
{
    public:
        void registerObserver(Observer* o)
        {
            obs.emplace_back(o);
            cout << "add observer " << o << endl;
        }
        void removeObserver(Observer* o)
        {
            obs.remove(o);
        }
        void notifyObservers()
        {
            for (auto iter : obs)
            {
                cout << "notifyObservers " << iter << endl;
                iter->update(x, y);
            }
        }

        void setMeasurtements(float x, float y)
        {
            this->x = x;
            this->y = y;
            notifyObservers();
        }

    private:
        std::list<Observer*> obs;// 记录观察者
        float x = 0;
        float y = 0;
};


class Observer0 :public Observer
{
    public:
        void update(float x, float y)
        {
            this->x = x;
            this->y = y;
            cout << "value: " << "x=" << x << " y=" << y << endl;
        }

    private:
        float x = 0;
        float y = 0;
};

class Observer1 :public Observer
{
    public:
        void update(float x, float y)
        {
            count++;
            this->x += x;
            this->y += y;

            display();
        }
        void display()
        {
            cout << "average value: " << " x=" << x / count << " y=" << y / count << endl;
        }

    private:
        float x = 0;
        float y = 0;
        int count = 0;
};

#endif // OBSERVER_H
