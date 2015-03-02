#ifndef _MY_CAMERA_H_
#define _MY_CAMERA_H_

#include <vector>
#include <algorithm>

#include "cse452.h"
#include "Matrix4.h"

// you must implement all of the following methods

class Camera {
public:
    Camera() {
        _from = Point3(0, 0, 0);
        _look = Vector3(0, 0, 1);
        _up = Vector3(0, 1, 0);
        _fov = 3.1415/2;
        _near = 0.1;
        _far = 30;
        _width = 640;
        _height = 480;
        
        initialize();
    };
    Camera(Point3 from, Point3 at, Vector3 up, double fov, double near, double far, int width, int height)
    : _from(from), _look(at - from), _up(up), _fov(fov), _near(near), _far(far), _width(width), _height(height) {
        initialize();
    };
    
    ~Camera();
    
    // Perspective plus scale (x,y, and z)
    Matrix4 getProjection() const;

    // Rotation and translation from world to camera
    Matrix4 getWorldToCamera() const;
    // Rotation, translation and scale from camera to world
    Matrix4 getCameraToWorld() const;
    // Just rotation from x,y,z axes to u,v,n
    Matrix4 getRotationFromXYZ() const;
    // Just rotation from u,v,n to x,y,z axes (canonical)
    Matrix4 getRotationToXYZ() const;

    // screen width/height
    int getWidth() const;
    int getHeight() const;

    // Camera orientation, position _after_ normalization
    Point3 getEye() const;
    // These should be unit length and orthogonal to each other
    // u vector
    Vector3 getRight() const;
    // v vector
    Vector3 getUp() const;
    // -n vector
    Vector3 getLook() const;

    // Perspective data
    Point3 getProjectionCenter() const;
    double getZoom() const;
    double getSkew() const;
    // "Squishing" in x,y (not Width/Heigh)
    double getAspectRatioScale() const;

    // For setting camera
    void setFrom(const Point3& from);
    void setAt(const Point3& at);
    void setLook(const Vector3& l);
    void setUp(const Vector3& up);
    void setWidthHeight(int w, int h);
    void setZoom(double z);
    void setNearFar(double n, double f);
    void setProjectionCenter( const Point3 &in_pt );
    // Extra "squishing" in x,y (not Width/Height)
    void setAspectRatioScale( double );
    void setSkew( double );

    // This is what gets called when a key is pressed
    void moveKeyboard();

    // user interaction methods
    // These rotate the camera around itself
    void moveForward(double dist);
    void moveSideways(double dist);
    void moveVertical(double dist);
    void rotateYaw(double angle);
    void rotatePitch(double angle);

    // IBar: This rotates the camera around a point at a distance focusDist
    // from the eye point of the camera. If axis is 0, it rotates the camera itself
    // around the Right vector, 1 is around the up axis, and 2 is around the look vector
    void rotateAroundAtPoint(int axis, double angle, double focusDist);

private:
    // These are the mutable, user-settable variables.
    // Everything is calculated from them.
    Point3 _from;
    Vector3 _look;
    Vector3 _up;
    
    double _fov;
    double _aspect;
    
    int _width;
    int _height;
    
    double _near;
    double _far;
    
    void initialize(std::vector<std::string> changed = std::vector<std::string>());
    
    Vector3 _u;
    Vector3 _v;
    Vector3 _n;
    
    // Component matrices
    Matrix4 _t;
    Matrix4 _tinv;
    Matrix4 _r;
    Matrix4 _rinv;
    Matrix4 _sxy;
    Matrix4 _sxyinv;
    Matrix4 _sxyz;
    Matrix4 _sxyzinv;
    Matrix4 _d;
    Matrix4 _dinv;
    
    Matrix4 _proj;
    Matrix4 _projinv;

    Matrix4 _wtc;
    Matrix4 _ctw;
};

#endif /* _MY_CAMERA_H_ */
