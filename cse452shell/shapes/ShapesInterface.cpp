// generated by Fast Light User Interface Designer (fluid) version 1.0303

#include "ShapesInterface.h"

void ShapesInterface::cb_Sphere_i(Fl_Menu_*, void*) {
  myShapes.changedShape();
}
void ShapesInterface::cb_Sphere(Fl_Menu_* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_Sphere_i(o,v);
}

void ShapesInterface::cb_Cone_i(Fl_Menu_*, void*) {
  myShapes.changedShape();
}
void ShapesInterface::cb_Cone(Fl_Menu_* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_Cone_i(o,v);
}

void ShapesInterface::cb_Cylinder_i(Fl_Menu_*, void*) {
  myShapes.changedShape();
}
void ShapesInterface::cb_Cylinder(Fl_Menu_* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_Cylinder_i(o,v);
}

void ShapesInterface::cb_Cube_i(Fl_Menu_*, void*) {
  myShapes.changedShape();
}
void ShapesInterface::cb_Cube(Fl_Menu_* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_Cube_i(o,v);
}

void ShapesInterface::cb_Cow_i(Fl_Menu_*, void*) {
  myShapes.changedShape();
}
void ShapesInterface::cb_Cow(Fl_Menu_* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_Cow_i(o,v);
}

Fl_Menu_Item ShapesInterface::menu_m_iShapeType[] = {
 {"Sphere", 0,  (Fl_Callback*)ShapesInterface::cb_Sphere, 0, 4, FL_NORMAL_LABEL, 0, 14, 0},
 {"Cone", 0,  (Fl_Callback*)ShapesInterface::cb_Cone, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Cylinder", 0,  (Fl_Callback*)ShapesInterface::cb_Cylinder, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Cube", 0,  (Fl_Callback*)ShapesInterface::cb_Cube, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Cow", 0,  (Fl_Callback*)ShapesInterface::cb_Cow, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0}
};

void ShapesInterface::cb_Wireframe_i(Fl_Menu_*, void*) {
  RedrawWindow();
}
void ShapesInterface::cb_Wireframe(Fl_Menu_* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_Wireframe_i(o,v);
}

void ShapesInterface::cb_Flat_i(Fl_Menu_*, void*) {
  RedrawWindow();
}
void ShapesInterface::cb_Flat(Fl_Menu_* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_Flat_i(o,v);
}

void ShapesInterface::cb_Smooth_i(Fl_Menu_*, void*) {
  RedrawWindow();
}
void ShapesInterface::cb_Smooth(Fl_Menu_* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_Smooth_i(o,v);
}

Fl_Menu_Item ShapesInterface::menu_m_iDisplayType[] = {
 {"Wireframe", 0,  (Fl_Callback*)ShapesInterface::cb_Wireframe, 0, 4, FL_NORMAL_LABEL, 0, 14, 0},
 {"Flat shading", 0,  (Fl_Callback*)ShapesInterface::cb_Flat, 0, 4, FL_NORMAL_LABEL, 0, 14, 0},
 {"Smooth shading", 0,  (Fl_Callback*)ShapesInterface::cb_Smooth, 0, 4, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0}
};

void ShapesInterface::cb_m_dXRot_i(Fl_Value_Slider*, void*) {
  RedrawWindow();
}
void ShapesInterface::cb_m_dXRot(Fl_Value_Slider* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_m_dXRot_i(o,v);
}

void ShapesInterface::cb_m_dYRot_i(Fl_Value_Slider*, void*) {
  RedrawWindow();
}
void ShapesInterface::cb_m_dYRot(Fl_Value_Slider* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_m_dYRot_i(o,v);
}

void ShapesInterface::cb_Tessellate_i(Fl_Button*, void*) {
  myShapes.changedTessel();
}
void ShapesInterface::cb_Tessellate(Fl_Button* o, void* v) {
  ((ShapesInterface*)(o->parent()->user_data()))->cb_Tessellate_i(o,v);
}

Fl_Double_Window* ShapesInterface::make_window() {
  { m_shapesWindow = new Fl_Double_Window(395, 145, "Shapes UI");
    m_shapesWindow->user_data((void*)(this));
    { m_iShapeType = new Fl_Choice(5, 25, 180, 25, "Shape Type");
      m_iShapeType->down_box(FL_BORDER_BOX);
      m_iShapeType->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      m_iShapeType->menu(menu_m_iShapeType);
    } // Fl_Choice* m_iShapeType
    { m_iDisplayType = new Fl_Choice(5, 70, 180, 25, "Display Style");
      m_iDisplayType->down_box(FL_BORDER_BOX);
      m_iDisplayType->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      m_iDisplayType->menu(menu_m_iDisplayType);
    } // Fl_Choice* m_iDisplayType
    { m_dXRot = new Fl_Value_Slider(190, 25, 200, 25, "X Rotation");
      m_dXRot->type(5);
      m_dXRot->box(FL_BORDER_BOX);
      m_dXRot->maximum(360);
      m_dXRot->step(1);
      m_dXRot->callback((Fl_Callback*)cb_m_dXRot);
      m_dXRot->align(Fl_Align(FL_ALIGN_TOP));
    } // Fl_Value_Slider* m_dXRot
    { m_dYRot = new Fl_Value_Slider(190, 70, 200, 25, "Y Rotation");
      m_dYRot->type(5);
      m_dYRot->box(FL_BORDER_BOX);
      m_dYRot->maximum(180);
      m_dYRot->step(1);
      m_dYRot->value(90);
      m_dYRot->callback((Fl_Callback*)cb_m_dYRot);
      m_dYRot->align(Fl_Align(FL_ALIGN_TOP));
    } // Fl_Value_Slider* m_dYRot
    { Fl_Button* o = new Fl_Button(105, 115, 100, 25, "Tessellate");
      o->callback((Fl_Callback*)cb_Tessellate);
    } // Fl_Button* o
    { m_iTessel1 = new Fl_Value_Input(6, 115, 45, 25, "Tessellation:");
      m_iTessel1->maximum(100);
      m_iTessel1->step(1);
      m_iTessel1->value(5);
      m_iTessel1->align(Fl_Align(FL_ALIGN_TOP_LEFT));
    } // Fl_Value_Input* m_iTessel1
    { m_iTessel2 = new Fl_Value_Input(55, 115, 45, 25);
      m_iTessel2->maximum(100);
      m_iTessel2->step(1);
      m_iTessel2->value(5);
      m_iTessel2->align(Fl_Align(FL_ALIGN_TOP_LEFT));
    } // Fl_Value_Input* m_iTessel2
    m_shapesWindow->end();
    m_shapesWindow->resizable(m_shapesWindow);
  } // Fl_Double_Window* m_shapesWindow
  return m_shapesWindow;
}

ShapesInterface::ShapesInterface() {
  m_shapesWindow = make_window();
  myShapes.setUI( this );
  myShapes.changedShape();
  myShapes.changedTessel();
}

ShapesUI::ShapeType ShapesInterface::getShapeType() const {
  return (ShapesUI::ShapeType) m_iShapeType->value();
}

ShapesUI::DisplayType ShapesInterface::getDisplayType() const {
  return (ShapesUI::DisplayType) m_iDisplayType->value();
}

int ShapesInterface::getTessel1() const {
  return (int) m_iTessel1->value();
}

int ShapesInterface::getTessel2() const {
  return (int) m_iTessel2->value();
}

UIInterface * ShapesInterface::getUI() {
  return &myShapes;
}

double ShapesInterface::getXRot() const {
  return M_PI * m_dXRot->value() / 180.0;
}

double ShapesInterface::getYRot() const {
  return M_PI * m_dYRot->value() / 180.0 - M_PI / 2.0;
}
