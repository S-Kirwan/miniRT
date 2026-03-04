This project has been created as part of the 42 curriculum by skirwan, aramos.

Description: The goal of the project is to prove we don't need to be mathematicians to do some crazy math. By being able to implement a simple RT (RayTracing) algorithm, which uses vector mathematics, applied physics and all of this to render nice images that are created from nothing but a specific combination of letters and numbers in a map-like format. The idea is simple: usually light (made up of all mixed colors) travels and hits an object. Depending on the type of object (glass, wall, water, etc) the light reacts in different ways, and bounces, refracts, changes direction and so on. During this actions, the object that was hit by the light, absorbs some of it (which gives its color) and by the time the light hits our eyes, we see an object of a specific color and a specific texture. 

For this program, the camera will be the representation of our eyes, and the light will come from a source that we can position in different places (coordinates) in the space. Depending on the configurations of this, an object can create or be affected by shadows. For the purpose of saving resources, when a RT algorithm is used, the light is not the origin of the rays, but the camera is. This is because a big quantity of rays do not reach our eyes and it would be a waste of resources to calculate the rays that we do not get to see on screen. To solve this, the rays origin is in the camera, then it goes pixel by pixel until it hits an object according to the information on the map-like file passed as argument. Then, information is extracted from that "hit" such as color of the object and if desired, the texture. 

With this information (per pixel) we can start to create an image. With advanced calculations, we can then determine if the object has texture of glass and then reflect accordingly.

Instructions: To use the program, we have used the minilibx library, which would need to be installed if it is not already. This can be found online at: https://github.com/42paris/minilibx-linux.

For some linux distributions, the minilibx will not compile and the following flag must be added in both the Makefile.md and Makefile.gen of the root directory and the test directory: -std=gnu11. This allows the library to compile with older and not so strict rules, at some of the prototypes of the functions do not match the actual code of the libraries functions.

After, you can go to the root repository of this project and simply type "make", this will go to all the necessary library directories and recursively compile them to get the program created. After this, the usage of the program is simply ./miniRT [valid .rt file]. If the .rt file is not valid, you will get an error and you will get the prompt back. If the .rt is valid, a window will open and the rendering process will begin. Enjoy viewing the images, or create your own .rt file!

Resources: 
https://42-cursus.gitbook.io/guide/4-rank-04/minirt
https://raytracing.github.io/books/RayTracingInOneWeekend.html
https://computergraphics.stackexchange.com/questions/9157/color-shading-and-light-calculation-for-ray-tracing
https://www.youtube.com/@TheCherno/search
https://www.davepagurek.com/blog/how-raytracing-works/
