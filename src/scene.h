#include <glm.hpp>
# include <list>

#include "surface.h"

using namespace glm;

class Scene{
    vec3 color;
    list<Surface *> surfaceList;
    vec3 backgroundColor;
    Light light;

    public:
        Scene(list<Surface *> surfaceList, vec3 background, Light light) : surfaceList(surfaceList), backgroundColor(background), light(light) {}

        vec3 whiteTrace(Ray ray, float tMin, float tMax){ // 충돌시 white color 반환, 아닐 시 backgroud color 반환
            float tBest = tMax; // 충돌 시 가장 가까운 t 값
            Surface* firstSurface = nullptr; // 충돌 객체 중 가장 가까운 객체
            for(Surface * s : surfaceList){
                HitSurface hsf = s -> intersect(ray, tMin, tBest);
                if (hsf.getHitSurface() == true){
                    tBest = hsf.getT();
                    firstSurface = s;
                }
            }
            if(firstSurface != nullptr) // 충돌 시 
                color = vec3(1,1,1);
            else
                color = backgroundColor;
            return color;
        }

        vec3 trace(Ray ray, float tMin, float tMax){ // 충돌시 phong shade 값 반환, 아닐 시 backgroud color 반환
            float tBest = tMax; // 충돌 시 가장 가까운 t 값
            Surface* firstSurface = nullptr; // 충돌 객체 중 가장 가까운 객체
            for(Surface * s : surfaceList){
                HitSurface hsf = s -> intersect(ray, tMin, tBest);
                if (hsf.getHitSurface() == true){
                    tBest = hsf.getT();
                    firstSurface = s;
                }
            }
            if(firstSurface != nullptr){ // 충돌 시
                vec3 point = ray.evaluate(tBest);
                vec3 normal = firstSurface -> getNormal(point);
                color = firstSurface -> shade(ray, point, normal, light);

                Ray shadowRay(point, light.getPoint() - point); // 그림자 광선 생성
                bool shadow = false; 
                for(Surface * s : surfaceList){
                    HitSurface hitshadow = s -> intersect(shadowRay, 0, pow(2, 31)-1);
                    if (hitshadow.getHitSurface() == true) //그림자 광선이 객체에 부딪히면
                        shadow = true; //그림자 생성
                }
                if (shadow == true)
                    color = firstSurface -> getAmbient(light);
            }
            else
                color = backgroundColor;
            return color;
        }       

};