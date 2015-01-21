// generated by Fast Light User Interface Designer (fluid) version 1.0303

#ifndef ShellInterface_h
#define ShellInterface_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <string>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>
#include "GLWindow.h"

class ShellInterface {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *m_mainWindow;
  Fl_Text_Display *strMyName;
  static Fl_Menu_Item menu_[];
private:
  inline void cb_Read_i(Fl_Menu_*, void*);
  static void cb_Read(Fl_Menu_*, void*);
  inline void cb_Screen_i(Fl_Menu_*, void*);
  static void cb_Screen(Fl_Menu_*, void*);
  inline void cb_Exit_i(Fl_Menu_*, void*);
  static void cb_Exit(Fl_Menu_*, void*);
  inline void cb_Brush_i(Fl_Menu_*, void*);
  static void cb_Brush(Fl_Menu_*, void*);
  inline void cb_Shapes_i(Fl_Menu_*, void*);
  static void cb_Shapes(Fl_Menu_*, void*);
  inline void cb_Camera_i(Fl_Menu_*, void*);
  static void cb_Camera(Fl_Menu_*, void*);
  inline void cb_Intersection_i(Fl_Menu_*, void*);
  static void cb_Intersection(Fl_Menu_*, void*);
  inline void cb_Sceneview_i(Fl_Menu_*, void*);
  static void cb_Sceneview(Fl_Menu_*, void*);
  inline void cb_Interactive_i(Fl_Menu_*, void*);
  static void cb_Interactive(Fl_Menu_*, void*);
  inline void cb_Rendering_i(Fl_Menu_*, void*);
  static void cb_Rendering(Fl_Menu_*, void*);
public:
  GLWindow *glWindow;
  ShellInterface();
private:
  std::string strImageName; 
  std::string strScreenshotName; 
};
#endif
