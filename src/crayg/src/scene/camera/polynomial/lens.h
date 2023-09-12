#pragma once

#include "PolynomialLenses.h"
#include <limits>
#include <math.h>

/*static inline float dotproduct(float *u, float *v)
{
    return raytrace_dot(u, v);
}

static inline void crossproduct(const float *r, const float *u, float *v)
{
    return raytrace_cross(v, r, u);
}*/

#define crossproduct(v1, v2, res)                                                                                      \
    (res)[0] = (v1)[1] * (v2)[2] - (v2)[1] * (v1)[2];                                                                  \
    (res)[1] = (v1)[2] * (v2)[0] - (v2)[2] * (v1)[0];                                                                  \
    (res)[2] = (v1)[0] * (v2)[1] - (v2)[0] * (v1)[1]

#define dotproduct(u, v) ((u)[0] * (v)[0] + (u)[1] * (v)[1] + (u)[2] * (v)[2])

static inline void normalise(float *f) {
    const float len = 1.0f / sqrtf(dotproduct(f, f));
    for (int k = 0; k < 3; k++) {
        f[k] *= len;
    }
}

static inline float MAX(float a, float b) {
    return a > b ? a : b;
}

// helper function for dumped polynomials to compute integer powers of x:
static inline float lens_ipow(const float x, const int exp) {
    if (exp == 0) {
        return 1.0f;
    }
    if (exp == 1) {
        return x;
    }
    if (exp == 2) {
        return x * x;
    }
    if (exp == 3) {
        return x * x * x;
    }
    if (exp == 4) {
        return x * x * x * x;
    }
    if (exp == 5) {
        return x * x * x * x * x;
    }
    if (exp == 6) {
        return x * x * x * x * x * x;
    }
    if (exp == 7) {
        return x * x * x * x * x * x * x;
    }
    if (exp == 8) {
        return x * x * x * x * x * x * x * x;
    }
    if (exp == 9) {
        return x * x * x * x * x * x * x * x * x;
    }
    return std::pow<float>(x, exp);
}

static inline void lens_sphereToCs(const float *inpos, const float *indir, float *outpos, float *outdir,
                                   const float sphereCenter, const float sphereRad) {
    const float normal[3] = {inpos[0] / sphereRad, inpos[1] / sphereRad,
                             sqrtf(MAX(0, sphereRad * sphereRad - inpos[0] * inpos[0] - inpos[1] * inpos[1])) /
                                 fabsf(sphereRad)};
    const float tempDir[3] = {indir[0], indir[1], sqrtf(MAX(0.0, 1.0f - indir[0] * indir[0] - indir[1] * indir[1]))};

    float ex[3] = {normal[2], 0, -normal[0]};
    normalise(ex);
    float ey[3];
    crossproduct(normal, ex, ey);

    outdir[0] = tempDir[0] * ex[0] + tempDir[1] * ey[0] + tempDir[2] * normal[0];
    outdir[1] = tempDir[0] * ex[1] + tempDir[1] * ey[1] + tempDir[2] * normal[1];
    outdir[2] = tempDir[0] * ex[2] + tempDir[1] * ey[2] + tempDir[2] * normal[2];
    outpos[0] = inpos[0];
    outpos[1] = inpos[1];
    outpos[2] = normal[2] * sphereRad + sphereCenter;
}

static inline void lens_csToSphere(const float *inpos, const float *indir, float *outpos, float *outdir,
                                   const float sphereCenter, const float sphereRad) {
    const float normal[3] = {inpos[0] / sphereRad, inpos[1] / sphereRad, fabsf((inpos[2] - sphereCenter) / sphereRad)};
    float tempDir[3] = {indir[0], indir[1], indir[2]};
    normalise(tempDir);

    float ex[3] = {normal[2], 0, -normal[0]};
    normalise(ex);
    float ey[3];
    crossproduct(normal, ex, ey);
    outdir[0] = dotproduct(tempDir, ex);
    outdir[1] = dotproduct(tempDir, ey);
    outpos[0] = inpos[0];
    outpos[1] = inpos[1];
}

// evaluates from sensor (in) to outer pupil (out).
// input arrays are 5d [x,y,dx,dy,lambda] where dx and dy are the direction in
// two-plane parametrization (that is the third component of the direction would be 1.0).
// units are millimeters for lengths and micrometers for the wavelength (so visible light is about 0.4--0.7)
// returns the transmittance computed from the polynomial.
static inline float lens_evaluate(const float *in, float *out, crayg::PolynomialLens polynomialLens) {
    /*__attribute__ ((unused))*/ const float x = in[0], y = in[1], dx = in[2], dy = in[3], lambda = in[4];
    switch (polynomialLens) {
    case crayg::BICONVEX: {
#include "biconvex-50/pt_evaluate.h"
        out[0] = out_x;
        out[1] = out_y;
        out[2] = out_dx;
        out[3] = out_dy;
        return MAX(0.0f, out_transmittance);
    }
    case crayg::ANGENIEUX_DOUBLE_GAUSS: {
#include "double-gauss-angenieux-50mm/pt_evaluate.h"
        out[0] = out_x;
        out[1] = out_y;
        out[2] = out_dx;
        out[3] = out_dy;
        return MAX(0.0f, out_transmittance);
    }
    case crayg::CANON_70MM: {
#include "canon-70mm//pt_evaluate.h"
        out[0] = out_x;
        out[1] = out_y;
        out[2] = out_dx;
        out[3] = out_dy;
        return MAX(0.0f, out_transmittance);
    }
    }
}

// solves for the two directions [dx,dy], keeps the two positions [x,y] and the
// wavelength, such that the path through the lens system will be valid, i.e.
// lens_evaluate_aperture(in, out) will yield the same out given the solved for in.
// in: point on sensor. out: point on aperture.
static inline void lens_pt_sample_aperture(float *in, float *out, float dist, crayg::PolynomialLens polynomialLens) {
    /*__attribute__ ((unused))*/ float out_x = out[0], out_y = out[1], out_dx = out[2], out_dy = out[3],
                                       out_transmittance = 1.0f;
    /*__attribute__ ((unused))*/ float x = in[0], y = in[1], dx = in[2], dy = in[3], lambda = in[4];
    switch (polynomialLens) {
    case crayg::BICONVEX: {
#include "biconvex-50/pt_sample_aperture.h"
        // directions may have changed, copy all to be sure.
        out[0] = out_x;
        out[1] = out_y;
        out[2] = out_dx;
        out[3] = out_dy;
        in[0] = x;
        in[1] = y;
        in[2] = dx;
        in[3] = dy;
    } break;
    case crayg::ANGENIEUX_DOUBLE_GAUSS: {
#include "double-gauss-angenieux-50mm/pt_sample_aperture.h"
        // directions may have changed, copy all to be sure.
        out[0] = out_x;
        out[1] = out_y;
        out[2] = out_dx;
        out[3] = out_dy;
        in[0] = x;
        in[1] = y;
        in[2] = dx;
        in[3] = dy;
    } break;
    case crayg::CANON_70MM: {
#include "canon-70mm/pt_sample_aperture.h"
        // directions may have changed, copy all to be sure.
        out[0] = out_x;
        out[1] = out_y;
        out[2] = out_dx;
        out[3] = out_dy;
        in[0] = x;
        in[1] = y;
        in[2] = dx;
        in[3] = dy;
    } break;
    }
}
