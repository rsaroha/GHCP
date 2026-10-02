#pragma once

#include <array>
#include <cmath>
#include <algorithm>

// ─── Math types ─────────────────────────────────────────────────────────────
struct Vec3 { float x, y, z; };
struct Quat { float w, x, y, z; };
using Mat4 = std::array<float, 16>;  // column-major

inline Vec3  v3cross(Vec3 a, Vec3 b)  { return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x}; }
inline float v3dot  (Vec3 a, Vec3 b)  { return a.x*b.x+a.y*b.y+a.z*b.z; }
inline Vec3  v3norm (Vec3 v)           { float l=std::sqrt(v3dot(v,v)); return {v.x/l,v.y/l,v.z/l}; }
inline Quat  qnorm  (Quat q)           { float l=std::sqrt(q.w*q.w+q.x*q.x+q.y*q.y+q.z*q.z); return {q.w/l,q.x/l,q.y/l,q.z/l}; }
inline Quat  qmul   (Quat a, Quat b)  {
    return { a.w*b.w-a.x*b.x-a.y*b.y-a.z*b.z,
             a.w*b.x+a.x*b.w+a.y*b.z-a.z*b.y,
             a.w*b.y-a.x*b.z+a.y*b.w+a.z*b.x,
             a.w*b.z+a.x*b.y-a.y*b.x+a.z*b.w };
}
inline Mat4 quatToMat4(Quat q) {
    float xx=q.x*q.x, yy=q.y*q.y, zz=q.z*q.z;
    float xy=q.x*q.y, xz=q.x*q.z, yz=q.y*q.z;
    float wx=q.w*q.x, wy=q.w*q.y, wz=q.w*q.z;
    Mat4 m{};
    m[ 0]=1-2*(yy+zz); m[ 1]=2*(xy+wz);   m[ 2]=2*(xz-wy);   m[ 3]=0;
    m[ 4]=2*(xy-wz);   m[ 5]=1-2*(xx+zz); m[ 6]=2*(yz+wx);   m[ 7]=0;
    m[ 8]=2*(xz+wy);   m[ 9]=2*(yz-wx);   m[10]=1-2*(xx+yy); m[11]=0;
    m[12]=0;           m[13]=0;           m[14]=0;            m[15]=1;
    return m;
}
inline Mat4 mat4mul(const Mat4& a, const Mat4& b) {
    Mat4 c{};
    for (int col=0;col<4;col++)
        for (int row=0;row<4;row++)
            for (int k=0;k<4;k++)
                c[col*4+row] += a[k*4+row] * b[col*4+k];
    return c;
}
// Left-hand lookAt (forward = +Z from eye to center)
inline Mat4 lookAt(Vec3 eye, Vec3 center, Vec3 up) {
    Vec3 z = v3norm({center.x-eye.x, center.y-eye.y, center.z-eye.z});
    Vec3 x = v3norm(v3cross(up, z));
    Vec3 y = v3cross(z, x);
    Mat4 m{};
    m[ 0]=x.x; m[ 1]=y.x; m[ 2]=z.x; m[ 3]=0;
    m[ 4]=x.y; m[ 5]=y.y; m[ 6]=z.y; m[ 7]=0;
    m[ 8]=x.z; m[ 9]=y.z; m[10]=z.z; m[11]=0;
    m[12]=-(x.x*eye.x+x.y*eye.y+x.z*eye.z);
    m[13]=-(y.x*eye.x+y.y*eye.y+y.z*eye.z);
    m[14]=-(z.x*eye.x+z.y*eye.y+z.z*eye.z);
    m[15]=1;
    return m;
}
// Vulkan perspective: depth [0,1], Y-flipped so world +Y = screen up
inline Mat4 perspective(float fovY, float aspect, float zNear, float zFar) {
    float f = 1.0f / std::tan(fovY * 0.5f);
    Mat4 m{};
    m[ 0] = f / aspect;
    m[ 5] = -f;                              // flip Y for Vulkan
    m[10] = zFar / (zFar - zNear);           // depth [0,1]
    m[11] = 1.0f;                            // w_clip = z_view
    m[14] = -(zNear * zFar) / (zFar - zNear);
    return m;
}

inline Mat4 mat4inverse(const Mat4& m) {
    float s0 = m[0]*m[5]  - m[4]*m[1];   float s1 = m[0]*m[9]  - m[8]*m[1];
    float s2 = m[0]*m[13] - m[12]*m[1];  float s3 = m[4]*m[9]  - m[8]*m[5];
    float s4 = m[4]*m[13] - m[12]*m[5];  float s5 = m[8]*m[13] - m[12]*m[9];
    float c5 = m[10]*m[15]- m[14]*m[11]; float c4 = m[6]*m[15] - m[14]*m[7];
    float c3 = m[6]*m[11] - m[10]*m[7];  float c2 = m[2]*m[15] - m[14]*m[3];
    float c1 = m[2]*m[11] - m[10]*m[3];  float c0 = m[2]*m[7]  - m[6]*m[3];
    float det = s0*c5 - s1*c4 + s2*c3 + s3*c2 - s4*c1 + s5*c0;
    if (det == 0.0f) return {};
    float r = 1.0f / det;
    Mat4 o{};
    o[0]  = ( m[5]*c5 - m[9]*c4 + m[13]*c3)*r; o[1]  = (-m[1]*c5 + m[9]*c2 - m[13]*c1)*r;
    o[2]  = ( m[1]*c4 - m[5]*c2 + m[13]*c0)*r; o[3]  = (-m[1]*c3 + m[5]*c1 - m[9]*c0 )*r;
    o[4]  = (-m[4]*c5 + m[8]*c4 - m[12]*c3)*r; o[5]  = ( m[0]*c5 - m[8]*c2 + m[12]*c1)*r;
    o[6]  = (-m[0]*c4 + m[4]*c2 - m[12]*c0)*r; o[7]  = ( m[0]*c3 - m[4]*c1 + m[8]*c0 )*r;
    o[8]  = ( m[7]*s5 - m[11]*s4+ m[15]*s3)*r; o[9]  = (-m[3]*s5 + m[11]*s2- m[15]*s1)*r;
    o[10] = ( m[3]*s4 - m[7]*s2 + m[15]*s0)*r; o[11] = (-m[3]*s3 + m[7]*s1 - m[11]*s0)*r;
    o[12] = (-m[6]*s5 + m[10]*s4- m[14]*s3)*r; o[13] = ( m[2]*s5 - m[10]*s2+ m[14]*s1)*r;
    o[14] = (-m[2]*s4 + m[6]*s2 - m[14]*s0)*r; o[15] = ( m[2]*s3 - m[6]*s1 + m[10]*s0)*r;
    return o;
}

// ─── Arcball ─────────────────────────────────────────────────────────────────
struct Arcball {
    Quat current{1,0,0,0}, saved{1,0,0,0};
    Vec3 startVec{0,0,1};
    bool dragging = false;

    Vec3 toSphere(double px, double py, int w, int h) {
        float x =  (2.0f*(float)px/w - 1.0f);
        float y = -(2.0f*(float)py/h - 1.0f);
        float len2 = x*x + y*y;
        if (len2 <= 1.0f) return {x, y, std::sqrt(1.0f-len2)};
        return v3norm({x, y, 0.0f});
    }
    void beginDrag(double px, double py, int w, int h) {
        startVec = toSphere(px, py, w, h);
        saved    = current;
        dragging = true;
    }
    void drag(double px, double py, int w, int h) {
        if (!dragging) return;
        Vec3 endVec = toSphere(px, py, w, h);
        Vec3 axis   = v3cross(endVec, startVec);
        float d     = std::clamp(v3dot(startVec, endVec), -1.0f, 1.0f);
        current     = qnorm(qmul({d, axis.x, axis.y, axis.z}, saved));
    }
    Mat4 matrix() const { return quatToMat4(current); }
};
