#include "../cse452.h"
#include "ShapesUI.h"
#include "ShapesInterface.h"
#include "../Color.h"
#include <FL/Fl.H>
#include <FL/gl.h>
#ifdef __APPLE__
// because Apple is stupid and I hate everyone
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

ShapesUI::ShapesUI() {
    width = height = 0;

    currentShape = nullptr;
}

ShapesUI::~ShapesUI() {
    // ToDo: delete your variables here
}

void ShapesUI::resize(int w, int h) {
    width = w;
    height = h;
}

void ShapesUI::draw() {
    // Sets up the viewport and background color
    setup3DDrawing( Color( 0,0,0 ), width, height, true );

    // Changes the way triangles are drawn
    switch ( shapesUI->getDisplayType() ) {
        case DISPLAY_WIREFRAME: {
            glDisable(GL_LIGHTING);
            glPolygonMode(GL_FRONT, GL_LINE);
            glColor3f(1.0f, 1.0f, 1.0f);
        } break;
        case DISPLAY_FLAT_SHADING: {
            glEnable(GL_LIGHTING);
            glPolygonMode(GL_FRONT, GL_FILL);
            glColor3f(1.0f, 1.0f, 1.0f);
            glShadeModel(GL_FLAT);
        } break;
        case DISPLAY_SMOOTH_SHADING: {
            glEnable(GL_LIGHTING);
            glPolygonMode(GL_FRONT, GL_FILL);
            glColor3f(1.0f, 1.0f, 1.0f);
            glShadeModel(GL_SMOOTH);
        } break;
        default: break;
    }

    // Setup the camera
    gluLookAt( 3.5 * cos( shapesUI->getYRot() ) * cos( shapesUI->getXRot() ), 
               3.5 * sin( shapesUI->getYRot() ), 
               3.5 * cos( shapesUI->getYRot() ) * sin( shapesUI->getXRot() ), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // OK, this isn't hard
    // Draw some axes
//    glBegin(GL_LINES);
//    glVertex3f(0.0, 1.0, 0.0);
//    glVertex3f(0.0, 0.0, 0.0);
//    
//    glVertex3f(0.0, 0.0, 1.0);
//    glVertex3f(0.0, 0.0, 0.0);
//    
//    glVertex3f(1.0, 0.0, 0.0);
//    glVertex3f(0.0, 0.0, 0.0);
//    
//    glVertex3f(0.0, 0.0, 0.0);
//    glVertex3f(1.0, 1.0, 1.0);
//    glEnd();
    
    if (currentShape != nullptr) {
        currentShape->draw();
    }
    
    endDrawing();
}

int ShapesUI::handle(int event) {
    return 0;
}

Shape* ShapesUI::change(ShapeType type, int tessel1, int tessel2) {
    auto cachedShape = getCached(type, tessel1, tessel2);
    
    // If we have not cached this shape yet, create one and store it.
    // Otherwise use the cache.
    if(cachedShape == nullptr) {
        Shape* ret;
        
        switch (type) {
            default:
            case SHAPE_SPHERE: {
                // Minimum values
                auto ct1 = 1;
                auto ct2 = (tessel2 >= 1) ? tessel2 : 1;
                ct2 = (ct2 <= 7) ? ct2 : 7;
                if (ct1 != tessel1 || ct2 != tessel2) {
                    return change(SHAPE_SPHERE, ct1, ct2);
                }
                
                ret = new Sphere(ct1, ct2);
                break;
            }
                
            case SHAPE_CONE: {
                // Minimum values
                auto ct1 = (tessel1 >= 3) ? tessel1 : 3;
                auto ct2 = (tessel2 >= 2) ? tessel2 : 2;
                if (ct1 != tessel1 || ct2 != tessel2) {
                    return change(SHAPE_CONE, ct1, ct2);
                }
                
                ret = new Cone(ct1, ct2);
                break;
            }
                
            case SHAPE_CYLINDER: {
                auto ct1 = (tessel1 >= 3) ? tessel1 : 3;
                auto ct2 = (tessel2 >= 1) ? tessel2 : 1;
                if (ct1 != tessel1 || ct2 != tessel2) {
                    return change(SHAPE_CYLINDER, ct1, ct2);
                }
                
                ret = new Cylinder(ct1, ct2);
                break;
            }
                
            case SHAPE_CUBE: {
                auto ct1 = (tessel1 >= 1) ? tessel1 : 1;
                ct1 = (tessel1 <= 7) ? tessel1 : 7;
                auto ct2 = 1;
                if (ct1 != tessel1 || ct2 != tessel2) {
                    return change(SHAPE_CUBE, ct1, ct2);
                }
                
                ret = new Cube(ct1, ct2);
                break;
            }
        }
        
        cache(ret, type, tessel1, tessel2);
        return ret;
    }
    
    return cachedShape;
}

Shape* ShapesUI::getCached(ShapeType type, int tessel1, int tessel2) {
    std::stringstream keystm;
    keystm << "a " << type << " " << tessel1 << " " << tessel2;
    auto key = keystm.str();
    auto cachedShape = shapes.find(key);
    
    if (cachedShape == shapes.end()) {
        std::cout << "No cached shape for " <<
            type << " (" << tessel1 << ", " <<
            tessel2 << ")" << std::endl;
        
        return nullptr;
    }
    
    
    std::cout << "Found cached shape for " <<
    type << " (" << tessel1 << ", " <<
    tessel2 << ")" << std::endl;
    
    return cachedShape->second;
    
}

void ShapesUI::cache(Shape* shape, ShapeType type, int tessel1, int tessel2) {
    std::stringstream keystm;
    keystm << "a " << type << " " << tessel1 << " " << tessel2;
    auto key = keystm.str();
    
    std::pair<std::string, Shape*> pair = {
        key,
        shape
    };
    shapes.insert(pair);
}

void ShapesUI::changedShape()
{
    currentShape = change(shapesUI->getShapeType(),
           shapesUI->getTessel1(),
           shapesUI->getTessel2());
    
    RedrawWindow();
}

void ShapesUI::changedTessel() {
    currentShape = change(shapesUI->getShapeType(),
           shapesUI->getTessel1(),
           shapesUI->getTessel2());

    RedrawWindow();
}

