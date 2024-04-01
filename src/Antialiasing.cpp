#include <iostream>
#include <stdlib.h>
# include <list>

#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>

#include "scene.h"

using namespace std;
using namespace glm;

#define Nx 512
#define Ny 512
#define N 64

unsigned char Image[Nx*Ny*3];

int main(){
    vec3 backgroundColor = vec3(0,0,0);
    
    Light light = {vec3(-4,4,-3), vec3(1,1,1), 1}; 

    list<Surface*> surfaceList;

    Plane* p1 = new Plane(vec3(0,-2,0),vec3(0,1,0), 
                          vec3(0.2,0.2,0.2), vec3(1,1,1), vec3(0,0,0), 0);
    surfaceList.push_back(p1);

    Sphere* s1 = new Sphere(vec3(-4,0,-7), 1, 
                            vec3(0.2,0,0), vec3(1,0,0), vec3(0,0,0), 0);
    surfaceList.push_back(s1);

    Sphere* s2 = new Sphere(vec3(0,0,-7), 2,
                            vec3(0,0.2,0), vec3(0,0.5,0), vec3(0.5,0.5,0.5), 32);
    surfaceList.push_back(s2);
                            
    Sphere* s3 = new Sphere(vec3(4,0,-7), 1,
                            vec3(0,0,0.2), vec3(0,0,1), vec3(0,0,0), 0);
    surfaceList.push_back(s3);

    Scene* scene = new Scene(surfaceList, backgroundColor, light);

    Camera cam = {vec3(0,0,0), vec3(1,0,0), vec3(0,1,0), vec3(0,0,1)};

    ViewingRegion vr = {-0.1, 0.1, -0.1, 0.1, 0.1};

    vec3 color;
    for(int iy = 0; iy<Ny ; iy++){
        for(int ix = 0; ix<Nx ; ix++){
            int idx = (iy * Nx + ix) * 3;

            for (int sample = 0; sample < N; sample++) {
                Ray ray = cam.getRandomRay(vr, ix, iy, Nx, Ny);
                vec3 colors = scene -> trace(ray, 0, pow(2, 31)-1);
                color += colors;
            }
            color  = color / float(N);

            float gamma = 2.2;
            
            for (int i = 0; i < 3; i ++){
                color[i] = color[i] > 1 ? 1: color[i];
                color[i] = pow(color[i], 1 / gamma);
                Image[idx+i] = color[i] * 255;
            }
        }
    }

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(512, 512, "Antialiasing HW 202372001_김소영", NULL, NULL);

    if(window == NULL) 
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }   
    
    glViewport(0, 0, Nx, Ny);
    while(!glfwWindowShouldClose(window))
    {   
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glad_glDrawPixels(Nx, Ny, GL_RGB, GL_UNSIGNED_BYTE, Image);
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();

    return 0;
}


