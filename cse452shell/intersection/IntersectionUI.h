#ifndef _INTERSECTION_UI_H_
#define _INTERSECTION_UI_H_

#include "../cse452.h"
#include "../shapes/ShapesUI.h"
#include "HitRecord.h"
#include "../UIInterface.h"
#include <FL/Fl_Window.H>

#include "RayShape.h"
#include "RaySphere.h"
#include "RayCylinder.h"
#include "RayCone.h"
#include "RayCube.h"
#include "../shapes/Sphere.h"
#include "../shapes/Cylinder.h"
#include "../shapes/Cone.h"
#include "../shapes/Cube.h"

class IntersectionInterface;
class IntersectionUI : public UIInterface {
public:
    IntersectionUI();
    ~IntersectionUI();

    // Inherited from userInterface
    void resize(int width, int height);
    void draw();
    int handle(int event);

    // Link to the intersection widget
    void setUI( const IntersectionInterface *in_ui ) { intersectionUI = in_ui; }
    void changeShape( ShapesUI::ShapeType type );

    void writeTest() const;

private:
    const IntersectionInterface *intersectionUI;
    int width, height;

    void drawHits(HitRecord& hr);

    // declare your variables here
    Shape *currentClassicShape;
    RayShape *currentShape;
    
    Sphere *classicSphere;
    RaySphere *sphere;
    
    Cylinder *classicCylinder;
    RayCylinder *cylinder;
    
    Cone *classicCone;
    RayCone *cone;
    
    Cube *classicCube;
    RayCube *cube;
};

#endif /* _INTERSECTION_UI_H_ */
