#ifndef BASETHREADCLASS_H
#define BASETHREADCLASS_H
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <QObject>
#include <QDebug>

class BaseThreadClass : public QObject
{
    Q_OBJECT
public:
    explicit BaseThreadClass(QObject *parent = nullptr) {}
    ~BaseThreadClass() {/* empty */}
    /** Returns true if the thread was successfully started, false if there was an error starting the thread */
    bool StartInternalThread()
    {
        return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, NULL) == 0);
    }
    /** Will not return until the internal thread has exited. */
    void WaitForInternalThreadToExit()
    {
        (void) pthread_join(_thread, NULL);
    }
private:

    virtual void run() = 0;
    static void * InternalThreadEntryFunc(void * This) {((BaseThreadClass *)This)->run(); return NULL;}
    pthread_t _thread;
};

#endif // BASETHREADCLASS_H
