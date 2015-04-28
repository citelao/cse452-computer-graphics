//
//  Node.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/1/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Node__
#define __cse452shellXC__Node__

#include <stdio.h>
#ifdef __APPLE__
// because Apple is stupid and I hate everyone
#include <OpenGL/glu.h>
#else
#include <Windows.h>
#include <GL/glu.h>
#endif
#include <vector>

#include "../vecmath/Vector3.h"

#include "IDrawable.h"
#include "ITransform.h"

class Node : public IDrawable {
    public:
        Node() : _valid(false), _matrix(Matrix4::identity()) {};
        Node(IDrawable* child)
        : _child(child), _valid(true), _matrix(Matrix4::identity())  {};
    
        ~Node();
    
        Node* setChild(IDrawable* child);
        Node* addTransform(ITransform* t);
        bool isValid() const;
    
        void draw() const;
        std::tuple<const Object*, HitRecord> intersect(Point3 pt, Vector3 dir) const;
    
    private:
        bool _valid = false;
        IDrawable* _child = nullptr;
    
        std::vector<ITransform*> _transforms;
        Matrix4 _matrix;
        Matrix4 _inv;
        Matrix4 _invtranspose;
};

#endif /* defined(__cse452shellXC__Node__) */
