//
// Created by Administrator on 2020/6/23.
//

#ifndef CPLAY_CTHREAD_H
#define CPLAY_CTHREAD_H

void CSleep(int mis);

//c++ 11 线程库
class CThread {
public:
    //启动线程
    virtual void Start();

    //通过控制isExit安全停止线程（不一定成功）
    virtual void Stop();

    //入口主函数
    virtual void Main() {
    }

protected:
    bool isExit = false;
    bool isRunning = false;

private:
    void ThreadMain();
};


#endif //CPLAY_CTHREAD_H
