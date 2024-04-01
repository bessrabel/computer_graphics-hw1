#include <glm.hpp>
#include <random>

#include "ray.h"
#include "viewingRegion.h"

using namespace glm;

class Camera{
    vec3 eyePoint_e;
    vec3 eyePoint_u;
    vec3 eyePoint_v;
    vec3 eyePoint_w;

    public:
        Camera(vec3 e, vec3 u, vec3 v, vec3 w) : eyePoint_e(e), eyePoint_u(u), eyePoint_v(v), eyePoint_w(w) {}

        Ray getRay(ViewingRegion vr, int i, int j, const int Nx, const int Ny){ 

            float u = vr.getL()+(vr.getR()-vr.getL())*(i+0.5)/Nx;
            float v = vr.getB()+(vr.getT()-vr.getB())*(j+0.5)/Ny;

            vec3 s = eyePoint_e + u*eyePoint_u + v*eyePoint_v - vr.getD()*eyePoint_w;

            vec3 p = eyePoint_e;
            vec3 d = s - eyePoint_e;
    
            return {p,d};
        }

        Ray getRandomRay(ViewingRegion vr, int i, int j, const int Nx, const int Ny){ //Antialiasing
            // 0 ~ 1 사이의 random 값 생성 
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(0, 1);

            float u = vr.getL()+(vr.getR()-vr.getL())*(i+dis(gen))/Nx;
            float v = vr.getL()+(vr.getR()-vr.getL())*(j+dis(gen))/Ny;

            vec3 s = eyePoint_e + u*eyePoint_u + v*eyePoint_v - vr.getD()*eyePoint_w;

            vec3 p = eyePoint_e;
            vec3 d = s - eyePoint_e;
    
            return {p,d};
        }
};