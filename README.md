*This project has been created as part of the 42 curriculum by skirwan, aramos.*

<p align="center">
  <img src="media/minirtn.png" alt="miniRT badge" width="150"/>
</p>

---

## Description
The goal of this project is to demonstrate that complex mathematical concepts can be applied effectively in programming without requiring advanced mathematical expertise. By implementing a simple Ray Tracing (RT) algorithm, this project explores how vector mathematics and physics can be used to render images from a structured scene description.

Ray tracing simulates the behavior of light in a virtual scene. In the real world, light (composed of mixed colors) travels through space and interacts with objects such as walls, glass, or water. Depending on the material properties of these objects, light can reflect, refract, change direction, or be partially absorbed. The absorbed portion of light determines the color we perceive when light reaches our eyes.

In this program:
- The camera represents the viewer's eye.
- The light source is placed at configurable coordinates in the scene.
- Objects interact with light to produce visual effects such as shading and shadows.

To optimize performance, the ray tracing algorithm used here casts rays from the camera rather than the light source. Since many rays emitted from light sources would never reach the camera, this approach avoids unnecessary calculations, managing resources properly.

Each ray is cast from the camera through each pixel on the screen. When a ray intersects with an object defined in the scene file (.rt format), the program computes information such as:
- The object's color
- Surface properties
- Lighting interaction

Using this information, the renderer calculates the final pixel color, gradually building the image displayed in the window. With more advanced calculations, materials like reflective surfaces (such as glass) can simulate realistic light behavior like reflection.

---

## Features
- Implementation of a basic ray tracing engine
- Scene rendering from `.rt` description files
- Camera-based ray generation
- Light interaction with objects
- Basic shading and shadow effects
- Rendering using the MiniLibX graphics library
- Error handling for invalid scene files

---

## Instructions

### Requirements
This project uses the MiniLibX graphical library. If it is not already installed on your system, it can be obtained from:

https://github.com/42paris/minilibx-linux

### Compilation

Some Linux distributions may fail to compile MiniLibX due to stricter compilation rules. If this occurs, add the following flag to both `Makefile.md` and `Makefile.gen` in the root directory and the test directory:

```
-std=gnu11
```

This flag relaxes some compilation constraints, allowing MiniLibX to compile correctly even when certain function prototypes differ slightly from their implementations.

### Build the Project

From the root directory of the repository, run:

```
make
```

This command will recursively compile all required libraries and source files to generate the executable.

---

## Usage

Run the program using:

```
./miniRT [scene_file.rt]
```

Example:

```
./miniRT scene.rt
```

- If the `.rt` file is invalid, an error message will be displayed and the program will terminate.
- If the `.rt` file is valid, a window will open and the rendering process will begin.

You can view the generated scene or experiment by creating your own `.rt` files.

---

## Resources

The following resources were used to understand ray tracing concepts and implement this project:

- https://42-cursus.gitbook.io/guide/4-rank-04/minirt  
- https://raytracing.github.io/books/RayTracingInOneWeekend.html  
- https://computergraphics.stackexchange.com/questions/9157/color-shading-and-light-calculation-for-ray-tracing  
- https://www.youtube.com/@TheCherno/search  
- https://www.davepagurek.com/blog/how-raytracing-works/  

---

## AI Usage

AI tools were used to assist with the following tasks:

- Structuring and improving the clarity of the README documentation
- Refining explanations of ray tracing concepts, math and physics concepts
- Grammar correction and formatting improvements

---

## Contributors

- skirwan  
- aramos  

---

## License

This project was developed as part of the 42 School curriculum and is intended for educational purposes.

Unless otherwise specified, the code in this repository is free to use, study, and modify for learning purposes.

MiniLibX is distributed under its own license and belongs to the 42 Network.
