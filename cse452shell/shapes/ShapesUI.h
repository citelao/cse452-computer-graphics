#ifndef _SHAPES_UI_H_
#define _SHAPES_UI_H_

#include <unordered_map>
#include <utility>

#include "../UIInterface.h"
#include "../cse452.h"
#include "Shape.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Cone.h"
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
        SHAPE_CUBE
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
    void change();
    
    int width, height;
    const ShapesInterface *shapesUI;
    
    // declare your variables here
    
    // http://stackoverflow.com/questions/20590656/error-for-hash-function-of-pair-of-ints
    struct pairhash {
    public:
        template <typename T, typename U>
        std::size_t operator()(const std::pair<T, U> &x) const
        {
            return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
        }
    };
    
    Shape *currentShape;
    std::unordered_map<int, std::unordered_map<std::pair<int, int>, Shape*, pairhash> > shapes;
};

#endif /* _SHAPES_UI_H_ */
