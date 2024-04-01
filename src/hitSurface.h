class HitSurface{
    bool hitSurface;
    float t;

    public:
        HitSurface(bool hitSurface) : hitSurface(hitSurface) {}
        HitSurface(bool hitSurface, float t) : hitSurface(hitSurface), t(t) {}

        bool getHitSurface(){ return hitSurface; }
        float getT(){ return t; }
};