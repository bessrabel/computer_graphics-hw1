#include <iostream>
#include <glm.hpp>

#include "camera.h"
#include "light.h"
#include "hitSurface.h"
  
using namespace glm;
using namespace std;

class Surface{
    public:
        vec3 ka;
        vec3 kd;
        vec3 ks;
        int p;

        Surface() {}
        Surface(vec3 ka, vec3 kd, vec3 ks, int power) : ka(ka), kd(kd), ks(ks), p(power) {}
        virtual ~Surface() {}

        float dot(vec3 a, vec3 b){ // 두벡터의 곱 계산
            float result = a.x * b.x + a.y * b.y + a.z * b.z;
            return result;
        }
        
        vec3 getAmbient(Light light){
            return ka * light.getColor() * light.getIntensity();
        }

        virtual HitSurface intersect(Ray ray, float tMin, float tMax){ // 가상 HitSurface 함수
            HitSurface hsf = {false, 0};
            return hsf;
        }

        virtual vec3 getNormal(vec3 point){ // 가상 getNormal 함수
            vec3 n;
            return n;
        }

        vec3 shade(Ray ray, vec3 point, vec3 n, Light light){ // phongShading
            
            vec3 v = normalize(-ray.getD());
            vec3 l = normalize(light.getPoint() - point);
            vec3 h = normalize(v + l);

            vec3 ambient = getAmbient(light);
            vec3 diffuse = kd * light.getColor() * std::max(dot(n,l), 0.0f);
            vec3 phong = ks * light.getColor() * float(pow(std::max(dot(n,h), 0.0f), p));

            vec3 color = vec3(ambient + diffuse + phong) * light.getColor();
            return color;
        }

};

class Plane : public Surface{ // 객체가 평면일 시 
    public:
        vec3 point;
        vec3 plane_n;

        Plane(vec3 pt, vec3 n) : point(pt), plane_n(n) {}
        Plane(vec3 pt, vec3 n, vec3 ka, vec3 kd, vec3 ks, int p) : Surface(ka, kd, ks, p){
            this -> point = pt;
            this -> plane_n = n;
        }

        HitSurface intersect(Ray ray, float tMin, float tMax){
            HitSurface hsf = {false};
            if (dot(ray.getD(), plane_n) < 0 ){
                float t = dot(point - ray.getP(), plane_n) / dot(ray.getD(), plane_n);
                if (tMin < t && t < tMax)
                    hsf = {true, t};
            }
            return hsf;
        }
        
        vec3 getNormal(vec3 point){
            vec3 n = normalize(plane_n);
            return n;
        }
};

class Sphere : public Surface{ // 객체가 구일 시 
    public:
        vec3 center;
        float radius;

        Sphere(vec3 pt, float r) : center(pt), radius(r) {}
        Sphere(vec3 pt, float r, vec3 ka, vec3 kd, vec3 ks, int p) : Surface(ka, kd, ks, p){
            this -> center = pt;
            this -> radius = r;
        }

        HitSurface intersect(Ray ray, float tMin, float tMax){
            HitSurface hsf = {false};
            float a = dot(ray.getD(), ray.getD());
            float b = 2.0 * dot(ray.getD(), ray.getP() - center);
            float c = dot(ray.getP() - center, ray.getP() - center) - radius * radius;
    
            if (b * b - 4 * a * c > 0){
                float t = (-1 * b - sqrt(b * b - 4 * a * c)) / (2 * a);
                if (tMin < t && t < tMax)
                    hsf = {true, t}; 
            }
            return hsf; 
        }

        vec3 getNormal(vec3 point){
            vec3 n = normalize(point-center);
            return n;
        }
};