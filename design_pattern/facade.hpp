#ifndef FACADE_HPP
#define FACADE_HPP

//是一种通过为多个复杂的子系统提供一个一致的接口，而使这些子系统更加容易被访问的模式。
//该模式对外有一个统一接口，外部应用程序不用关心内部子系统的具体细节，这样会大大降低应用程序的复杂度，提高了程序的可维护性。

//外观（Facade）模式是“迪米特法则”的典型应用，它有以下主要优点：
//降低了子系统与客户端之间的耦合度，使得子系统的变化不会影响调用它的客户类。
//对客户屏蔽了子系统组件，减少了客户处理的对象数目，并使得子系统使用起来更加容易。
//降低了大型软件系统中的编译依赖性，简化了系统在不同平台之间的移植过程，因为编译一个子系统不会影响其他的子系统，也不会影响外观对象。

//外观（Facade）模式的主要缺点如下：
//不能很好地限制客户使用子系统类，很容易带来未知风险。
//增加新的子系统可能需要修改外观类或客户端的源代码，违背了“开闭原则”。

#include <iostream>
using namespace std;

//电视机类
class Television {
    public:
        void on() {
            cout << "电视机打开" << endl;
        }
        void off() {
            cout << "电视机关闭" << endl;
        }
};

//灯类
class Light {
    public:
        void on() {
            cout << "灯打开" << endl;
        }
        void off() {
            cout << "灯关闭" << endl;
        }
};

//音响
class Audio {
    public:
        void on() {
            cout << "音响打开" << endl;
        }
        void off() {
            cout << "音响关闭" << endl;
        }
};

//麦克风
class Microphone {
    public:
        void on() {
            cout << "麦克风打开" << endl;
        }
        void off() {
            cout << "麦克风关闭" << endl;
        }
};

//DVD
class DVDplayer {
    public:
        void on() {
            cout << "DVD打开" << endl;
        }
        void off() {
            cout << "DVD关闭" << endl;
        }
};

//游戏机
class GameMachine {
    public:
        void on() {
            cout << "游戏机打开" << endl;
        }
        void off() {
            cout << "游戏机关闭" << endl;
        }
};

//外观模式
class KTVMode {
    public:
        KTVMode() {
            pTV = new Television;
            pLight = new Light;
            pAudio = new Audio;
            pMicrophone = new Microphone;
            pDvd = new DVDplayer;
        }

        void onKTV() {
            pTV->on();
            pLight->off();
            pAudio->on();
            pMicrophone->on();
            pDvd->on();
        }

        void offKTV() {
            pTV->off();
            pLight->off();
            pAudio->off();
            pMicrophone->off();
            pDvd->off();
        }

        ~KTVMode() {
            delete pTV;
            delete pLight;
            delete pAudio;
            delete pMicrophone;
            delete pDvd;
        }
    private:
        Television* pTV;
        Light* pLight;
        Audio* pAudio;
        Microphone* pMicrophone;
        DVDplayer* pDvd;
};

void TestKTVMode() {
    KTVMode* ktv = new KTVMode;
    //KTV包厢来人了
    ktv->onKTV();
}

#endif // FACADE_HPP
