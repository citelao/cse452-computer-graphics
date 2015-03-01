#ifndef _MY_CAMERA_H_
#define _MY_CAMERA_H_

#include "cse452.h"
#include "Matrix4.h"

// you must implement all of the following methods

class Camera {
public:
    Camera()
    : Camera(Point3(0, 0, 0), Point3(0, 0, 1), Vector3(0, 1, 0), 3.1415/2, 0.1, 30, 640, 480) {};
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
    
    void initialize();
    
    Vector3 _u;
    Vector3 _v;
    Vector3 _n;
    
    Matrix4 _proj;
    Matrix4 _wtc;
    Matrix4 _ctw;
    Matrix4 _r;
    Matrix4 _rinv;
    
};

#endif /* _MY_CAMERA_H_ */
