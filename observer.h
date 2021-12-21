/*
 * Observer class.  Abstract class for Observer Pattern
 *
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009, 2017 UW. All rights reserved.
 *
 */


#ifndef OBSERVER_H
#define OBSERVER_H

#include "subscriptions.h"

class Subject;

class Observer {
  public:
    virtual void update() = 0;
    virtual ~Observer() = default;
    virtual SubscriptionType subType() const = 0;
};


#endif
