#include <glm.hpp>

using namespace glm;

class Ray{
    vec3 p;
    vec3 d;
    
    public: 
        Ray(vec3 p, vec3 d) : p(p), d(d) {}

        vec3 getP(){ return p; }
        vec3 getD(){ return d; }
        vec3 evaluate(float t){
            vec3 result = p + t * d; 
            return result;
        }
};