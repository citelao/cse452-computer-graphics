#ifndef _SHAPES_UI_H_
#define _SHAPES_UI_H_

#include <unordered_map>
#include <sstream>
#include <utility>

#include "../UIInterface.h"
#include "../cse452.h"
#include "Shape.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Cone.h"
#include "Raw.h"
#include <FL/Fl_Window.H>

class ShapesInterface;
class ShapesUI : public UIInterface {
public:
    ShapesUI();
    ~ShapesUI();

    // Inherited from UIInterface
    void resize(int width, int height);
    void draw();
    int handle(int event);
    
    enum ShapeType {
        SHAPE_SPHERE,
        SHAPE_CONE,
        SHAPE_CYLINDER,
        SHAPE_CUBE,
        SHAPE_COW
    };

    enum DisplayType {
        DISPLAY_WIREFRAME,
        DISPLAY_FLAT_SHADING,
        DISPLAY_SMOOTH_SHADING
    };

    void changedTessel();
    void changedShape();
    
    // Link to the shapes widget
    void setUI( const ShapesInterface *in_ui ) { shapesUI = in_ui; }

private:
    Shape* change(ShapeType type, int tessel1, int tessel2);
    Shape* getCached(ShapeType type, int tessel1, int tessel2);
    void cache(Shape* shape, ShapeType type, int tessel1, int tessel2);
    
    int width, height;
    const ShapesInterface *shapesUI;
    
    Shape *currentShape;
    std::unordered_map<std::string, Shape*> shapes;
};

#endif /* _SHAPES_UI_H_ */
