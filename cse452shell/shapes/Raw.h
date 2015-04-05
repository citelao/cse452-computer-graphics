//
//  Raw.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/24/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Raw__
#define __cse452shellXC__Raw__

#ifdef __APPLE__
// because Apple is stupid and I hate everyone
#include <OpenGL/glu.h>
#else
#include <Windows.h>
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

#include "../vecmath/Vector3.h"

#include "Shape.h"


class Raw : public Shape {
public:
    Raw(std::string filename);
    Raw(int unused, int alsoUnused) : Raw("../data/cow.raw") {};
    
    ~Raw();
    
    void draw() const;
    
private:
    std::vector<Vector3*> pts;
    std::vector<Vector3*> normals;
};


#endif /* defined(__cse452shellXC__Raw__) */
