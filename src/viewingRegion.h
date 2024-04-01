class ViewingRegion{
    float l;
    float r;
    float b;
    float t;
    float d;

    public:
        ViewingRegion(float l, float r, float b, float t, float d) :l(l), r(r), b(b), t(t), d(d) {}

        float getL(){ return l; }
        float getR(){ return r; }
        float getB(){ return b; }
        float getT(){ return t; }
        float getD(){ return d; }
};