# Original by Chris & Zach
# Modified by Doug Hyde, 1/19/2009
# You must change the paths to GL and FLTK to match your system's configuration

# CXX   = g++ -m32
GLDIR = /System/Library/Frameworks/OpenGL.framework/Libraries/

# Personal Machine
FLTKINCDIR = /usr/local/include/
FLTKLIBDIR = /usr/local/lib/

CODEDIR = cse452shell/
OBJDIR = objs/
OUTDIR = build/

MAINOBJ = $(OBJDIR)main.o $(OBJDIR)GLWindow.o $(OBJDIR)ShellInterface.o $(OBJDIR)UIInterface.o
VECMATHOBJ = $(OBJDIR)ScreenVector.o $(OBJDIR)ScreenPoint.o $(OBJDIR)Vector3.o $(OBJDIR)Point3.o $(OBJDIR)Matrix3.o $(OBJDIR)Vector4.o $(OBJDIR)Matrix4.o
BRUSHOBJ = $(OBJDIR)MyBrush_UI.o $(OBJDIR)MyBrush.o  $(OBJDIR)BrushInterface.o 
# This has been updated to add my own shapes code.
# SHAPESOBJ = $(OBJDIR)ShapesInterface.o $(OBJDIR)ShapesUI.o
SHAPESOBJ = $(OBJDIR)ShapesInterface.o $(OBJDIR)ShapesUI.o $(OBJDIR)Shape.o $(OBJDIR)Cylinder.o $(OBJDIR)Cube.o $(OBJDIR)Cone.o $(OBJDIR)Sphere.o
CAMERAOBJ = $(OBJDIR)CameraInterface.o $(OBJDIR)CameraUI.o $(OBJDIR)IBar.o $(OBJDIR)Camera.o
SCENEOBJ = $(OBJDIR)SceneviewInterface.o $(OBJDIR)SceneviewUI.o $(OBJDIR)MyScene.o $(OBJDIR)MyScene_draw.o 
INTERSECTOBJ  = $(OBJDIR)IntersectionInterface.o $(OBJDIR)IntersectionUI.o
USEROBJ =  $(OBJDIR)InteractiveInterface.o $(OBJDIR)InteractiveUI.o $(OBJDIR)InteractiveWidget.o $(OBJDIR)MyScene_select.o 
RENDEROBJ = $(OBJDIR)MyScene_render.o $(OBJDIR)RenderingUI.o $(OBJDIR)RenderingInterface.o

OBJ = $(MAINOBJ) $(VECMATHOBJ) $(RENDEROBJ)  $(USEROBJ)  $(SCENEOBJ) $(INTERSECTOBJ) $(SHAPESOBJ) $(CAMERAOBJ) $(BRUSHOBJ)

#LIBS =  -L$(GLDIR) -L$(FLTKLIBDIR) -lfltk -lfltk_gl -lfltk_images -lfltk_forms -lfltk_jpeg -lGLU -lGL -lpng
LIBS =  -L$(GLDIR) -L$(FLTKLIBDIR) -lfltk -lfltk_gl -lfltk_images -lfltk_forms -lGLU -lGL -lpng
INCS =  -I$(FLTKINCDIR) -I/usr/X11R6/iQnclude -I. -I$(CODEDIR)vecmath -I$(CODEDIR)

BIN = $(OUTDIR)cse452shell
CXXFLAGS = $(INCS) -DLINUX -Wextra -std=c++11 -g
LDFLAGS = $(INCS) -DLINUX -Wextra -std=c++11 -framework Carbon -framework AGL -g

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	rm -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o "$(OUTDIR)cse452shell" $(LIBS) $(LDFLAGS)

$(MAINOBJ): $(OBJDIR)%.o: $(CODEDIR)%.cpp $(CODEDIR)cse452.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(VECMATHOBJ): $(OBJDIR)%.o: $(CODEDIR)vecmath/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(BRUSHOBJ): $(OBJDIR)%.o: $(CODEDIR)brush/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(SHAPESOBJ): $(OBJDIR)%.o: $(CODEDIR)shapes/%.cpp $(CODEDIR)shapes/%.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(CAMERAOBJ): $(OBJDIR)%.o: $(CODEDIR)camera/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(SCENEOBJ): $(OBJDIR)%.o: $(CODEDIR)sceneview/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(INTERSECTOBJ): $(OBJDIR)%.o: $(CODEDIR)intersection/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(USEROBJ): $(OBJDIR)%.o: $(CODEDIR)interactive/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RENDEROBJ): $(OBJDIR)%.o: $(CODEDIR)rendering/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# shamelessly:
# http://stackoverflow.com/questions/16467718/how-to-print-out-a-variable-in-makefile
print-%  :
	@echo $* = $($*)