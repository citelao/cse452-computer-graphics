//
//  IDrawable.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/1/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__IDrawable__
#define __cse452shellXC__IDrawable__

#include <stdio.h>

class IDrawable {
    public:
//        virtual ~IDrawable() = 0;
    
        virtual bool isValid() const = 0;
        virtual void draw() const = 0;
};

#endif /* defined(__cse452shellXC__IDrawable__) */
