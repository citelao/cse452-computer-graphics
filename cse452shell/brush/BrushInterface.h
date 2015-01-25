// generated by Fast Light User Interface Designer (fluid) version 1.0107

#ifndef BrushInterface_h
#define BrushInterface_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "MyBrush.h"
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Box.H>

class BrushInterface {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *m_brushWindow;
  Fl_Choice *m_iBrushType;
  static Fl_Menu_Item menu_m_iBrushType[];
private:
  void cb_Constant_i(Fl_Menu_*, void*);
  static void cb_Constant(Fl_Menu_*, void*);
  void cb_Linear_i(Fl_Menu_*, void*);
  static void cb_Linear(Fl_Menu_*, void*);
  void cb_Quadratic_i(Fl_Menu_*, void*);
  static void cb_Quadratic(Fl_Menu_*, void*);
  void cb_Gaussian_i(Fl_Menu_*, void*);
  static void cb_Gaussian(Fl_Menu_*, void*);
public:
  Fl_Value_Slider *m_iRadius;
private:
  void cb_m_iRadius_i(Fl_Value_Slider*, void*);
  static void cb_m_iRadius(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *m_dPixelFlow;
  Fl_Choice *m_iToolType;
  static Fl_Menu_Item menu_m_iToolType[];
  Fl_Choice *m_iFilterType;
  static Fl_Menu_Item menu_m_iFilterType[];
  Fl_Value_Slider *m_dRed;
private:
  void cb_m_dRed_i(Fl_Value_Slider*, void*);
  static void cb_m_dRed(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *m_dGreen;
private:
  void cb_m_dGreen_i(Fl_Value_Slider*, void*);
  static void cb_m_dGreen(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *m_dBlue;
private:
  void cb_m_dBlue_i(Fl_Value_Slider*, void*);
  static void cb_m_dBlue(Fl_Value_Slider*, void*);
public:
  Fl_Box *m_boxPreview;
  BrushInterface();
  void SetPreview();
private:
  MyBrush myBrush;
public:
  MyBrush::BrushType getBrushType() const;
  MyBrush::FilterType getFilterType() const;
  int getRadius() const;
  MyBrush::ToolType getToolType() const;
  Color getColor() const;
  float getFlow() const;
  void loadImage( Fl_Image *image );
  UIInterface * getUI();
};
#endif