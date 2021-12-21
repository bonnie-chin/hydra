#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include "subscriptions.h"

class Observer;

class Subject {
    protected:
        virtual void notify(SubscriptionType t) const = 0;
        std::vector<Observer*> observers;
    public:
        void attach(Observer *o);
        void detach(Observer *o);
        virtual ~Subject() = default;
};

#endif