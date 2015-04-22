//
//  Transform.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/5/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Transform__
#define __cse452shellXC__Transform__

#include <stdio.h>
#include "../vecmath/Matrix4.h"

class ITransform {
    public:
//        virtual ~ITransform() = 0;
        virtual void apply() = 0;
        virtual Matrix4 matrix() = 0;
};

#endif /* defined(__cse452shellXC__Transform__) */
