#include <iostream>
#include <stdlib.h>

#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>

#include "scene.h"

using namespace std;
using namespace glm;

#define Nx 512 // image resolution weight
#define Ny 512 // image resolution height
unsigned char Image[Nx*Ny*3]; //pixel

int main(){

    vec3 backgroundColor = vec3(0,0,0);
    
    Light light = {vec3(-4,4,-3), vec3(1,1,1), 1}; 

    list<Surface*> surfaceList; 

    Plane* p1 = new Plane(vec3(0,-2,0),vec3(0,1,0)); // point(평면 위의 한점), n(법선 벡터)
    surfaceList.push_back(p1);

    Sphere* s1 = new Sphere(vec3(-4,0,-7), 1); // center(구의 중심), radius(반지름)
    surfaceList.push_back(s1);

    Sphere* s2 = new Sphere(vec3(0,0,-7), 2); // center(구의 중심), radius(반지름)
    surfaceList.push_back(s2);
                            
    Sphere* s3 = new Sphere(vec3(4,0,-7), 1); // center(구의 중심), radius(반지름)
    surfaceList.push_back(s3);

    Scene* scene = new Scene(surfaceList, backgroundColor, light); // 한 scene에 객체들 저장

    Camera cam = {vec3(0,0,0), vec3(1,0,0), vec3(0,1,0), vec3(0,0,1)}; // eyePoint_e, eyePoint_u, eyePoint_v, eyePoint_w

    ViewingRegion vr = {-0.1, 0.1, -0.1, 0.1, 0.1}; // l, r, b, t, d

    vec3 color;
    for(int iy = 0; iy<Ny ; iy++){
        for(int ix = 0; ix<Nx ; ix++){
            int idx = (iy * Nx + ix) * 3;

            Ray ray = cam.getRay(vr, ix, iy, Nx, Ny);
            color = scene -> whiteTrace(ray, 0, pow(2, 31)-1);

            for (int i = 0; i < 3; i ++){
                Image[idx+i] = color[i] * 255;
            }
        }
    }

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(512, 512, "Ray Intersection HW 202372001_김소영", NULL, NULL);

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


