//
//  Tree.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/1/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Tree__
#define __cse452shellXC__Tree__

#include <stdio.h>
#include <vector>

#include "IDrawable.h"
#include "Node.h"

class Tree : public IDrawable {
    public:
        Tree() : nodes(std::vector<Node*>()) {};
    
        void addNode(Node* node);
        bool isValid() const { return true; };
    
        void draw() const;
        std::tuple<const Object*, HitRecord> intersect(Point3 pt, Vector3 dir) const;
    
    private:
        std::vector<Node*> nodes;
};

#endif /* defined(__cse452shellXC__Tree__) */
