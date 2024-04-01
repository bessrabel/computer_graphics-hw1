#include <glm.hpp>

using namespace glm;

class Light{
    vec3 point;
    vec3 color;
    float intensity;

    public: 
        Light(vec3 point, vec3 color, float intensity) : point(point), color(color), intensity(intensity) {}
        
        vec3 getPoint(){ return point; }
        vec3 getColor(){ return color; }
        float getIntensity(){ return intensity; }
};