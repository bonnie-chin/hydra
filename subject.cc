#include "subject.h"
#include "subject.h"
#include "observer.h"

void Subject::attach(Observer * view) {
    observers.push_back(view);
}

void Subject::detach(Observer * view) {
    for (long unsigned int i = 0; i < observers.size(); i++) {
        if (view == observers[i]) {
            observers.erase(observers.begin() + i);
        }
    }
}
