# CSE 452
## Ben Stolovitz

bstolovitz@wustl.edu

## Collaborators

- Morgan Redding

## Usage

Program may be accessed in the `product/` directory.

Program may be built using the `.vcxproj`.

## Sceneview

Created bs_person.sc.

Added "raw" and "cow"

"raw" followed by a filename will load a .raw file.

## Intersections

Added abstract `RayShape` and concrete Ray shapes for all required primitives.

## Camera

### Additions

Added `unit() cost` method to Vector class. Much easier than `normalize()`.

## Shapes

### Parameters

**Cylinder**: first param is slices, second stacks

**Cone**: first param is slices, second stacks

**Sphere**: first param is tesselation depth. Second is cached & unused.

**Cube**: first param is divisions. Second is unused.

### Additions

Added a `Shape` abstract class with a draw method.

Subclassed to create Cylinder, Cone, Sphere, and Cube.

### Extra Credit

The sphere is tesselated from an icosahedron for very pretty results.

Triangle fans and strips are used for the cone and cylinder.

## Brushes

### Additions

Only modified brush files.

### Mask

My mask is a two-dimensional array of precalculated values for each pixel on the radius
that is interpolated between for each step of the loop. 

### Extra Routine

Added fat circles and lines.

### Extra credit

Implemented Gaussian and special (cosine-based) brush.

### Draw Complexity

Brush draw:

- For every pixel across x
	- for every pixel across y
		- x * x
		- y * y
		- sqrt(x * x + y * y)
		- getPixel
		- 1 - bw
		- mask[curR] * (1 - bw)
		- mask[curR+1] * bw
		- mask[curR] * (1 - bw) + mask[curR + 1] * bw
		- colBrush * curMask
		- 1.0f - curMask
		- orig * 1.0f - curMask
		- colBrush * curMask + orig * (1.0f - curMask)
		- putPixel

= O(13radius^2)

Circle draw:

- while ox <= oy
	- for outer radius to inner radius
		- ox++
		- (oy++) sometimes
		- oh +=
		- ode +=
		- odne +=
		- ix++
		- (iy++) sometimes
		- ih +=
		- ide +=
		- idne +=

O(10 * radius * pixels in radius)