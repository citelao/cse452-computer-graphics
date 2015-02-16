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
    shapes = {
        {SHAPE_SPHERE, {}},
        {SHAPE_CONE, {}},
        {SHAPE_CYLINDER, {}},
        {SHAPE_CUBE, {}}
    };
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

    // ToDo: draw your shape here
    // DO NOT put the actual draw OpenGL code here - put it in the shape class and call the draw method
    
    // OK, this isn't hard
    // Draw some axes
    glBegin(GL_LINES);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glEnd();
    
    if (currentShape != nullptr) {
        currentShape->draw();
    }
    
    endDrawing();
}

int ShapesUI::handle(int event) {
    return 0;
}

void ShapesUI::change() {
    auto shapeMap = shapes.find(shapesUI->getShapeType());
    
    if (shapeMap == shapes.end()) {
        // Could not find this type of shape.
        // This is an error
        throw(new std::invalid_argument("We can't draw this shape"));
    }
    
    auto keyPair = std::make_pair(shapesUI->getTessel1(), shapesUI->getTessel2());
    auto cachedShape = shapeMap->second.find(keyPair);
    
    // If we have not cached this shape yet, create one and store it.
    // Otherwise use the cache.
    if(cachedShape == shapeMap->second.end()) {
        switch (shapesUI->getShapeType()) {
            default:
            case SHAPE_CONE:
                currentShape = new Cone(shapesUI->getTessel1(),
                                        shapesUI->getTessel2());
                break;
                
            case SHAPE_CYLINDER:
                currentShape = new Cylinder(shapesUI->getTessel1(),
                                            shapesUI->getTessel2());
                break;
                
            case SHAPE_CUBE:
                currentShape = new Cube(shapesUI->getTessel1(),
                                        shapesUI->getTessel2());
                break;
        }
        
        
        std::pair<std::pair<int, int>, Shape*> shapePair = {
            keyPair,
            currentShape
        };
        shapeMap->second.insert(shapePair);
        
    } else {
        currentShape = cachedShape->second;
    }
    
    RedrawWindow();
}

void ShapesUI::changedShape()
{
    change();
}

void ShapesUI::changedTessel( ) {
    change();
}

