#include "filianore/shading/microfacets/ggx.h"
#include "filianore/core/shadingcore.h"
#include "filianore/maths/vec3_math.h"

namespace filianore
{

    GGXDistribution::GGXDistribution(float _alphax, float _alphay)
        : alphax(std::max(0.001f, _alphax)),
          alphay(std::max(0.001f, _alphay))
    {
    }

    float GGXDistribution::EvaluateD(const StaticArray<float, 3> &wh) const
    {
        float tan2Theta = Tan2Theta(wh);
        if (std::isinf(tan2Theta))
            return 0.;
        const float cos4Theta = Cos2Theta(wh) * Cos2Theta(wh);
        float e =
            (Cos2Phi(wh) / (alphax * alphax) + Sin2Phi(wh) / (alphay * alphay)) *
            tan2Theta;
        return 1.f / (Pi<float> * alphax * alphay * cos4Theta * (1 + e) * (1 + e));
    }

    float GGXDistribution::Lambda(const StaticArray<float, 3> &w) const
    {
        float absTanTheta = std::abs(TanTheta(w));
        if (std::isinf(absTanTheta))
            return 0.;
        // Compute _alpha_ for direction _w_
        float alpha = std::sqrt(Cos2Phi(w) * alphax * alphax + Sin2Phi(w) * alphay * alphay);
        float alpha2Tan2Theta = (alpha * absTanTheta) * (alpha * absTanTheta);
        return (-1 + std::sqrt(1.f + alpha2Tan2Theta)) / 2;
    }

    static void TrowbridgeReitzSample11(float cosTheta, float U1, float U2,
                                        float *slope_x, float *slope_y)
    {
        // special case (normal incidence)
        if (cosTheta > .9999)
        {
            float r = sqrt(U1 / (1 - U1));
            float phi = 6.28318530718 * U2;
            *slope_x = r * cos(phi);
            *slope_y = r * sin(phi);
            return;
        }

        float sinTheta =
            std::sqrt(std::max((float)0, (float)1 - cosTheta * cosTheta));
        float tanTheta = sinTheta / cosTheta;
        float a = 1 / tanTheta;
        float G1 = 2 / (1 + std::sqrt(1.f + 1.f / (a * a)));

        // sample slope_x
        float A = 2 * U1 / G1 - 1;
        float tmp = 1.f / (A * A - 1.f);
        if (tmp > 1e10)
            tmp = 1e10;
        float B = tanTheta;
        float D = std::sqrt(
            std::max(float(B * B * tmp * tmp - (A * A - B * B) * tmp), float(0)));
        float slope_x_1 = B * tmp - D;
        float slope_x_2 = B * tmp + D;
        *slope_x = (A < 0 || slope_x_2 > 1.f / tanTheta) ? slope_x_1 : slope_x_2;

        // sample slope_y
        float S;
        if (U2 > 0.5f)
        {
            S = 1.f;
            U2 = 2.f * (U2 - .5f);
        }
        else
        {
            S = -1.f;
            U2 = 2.f * (.5f - U2);
        }
        float z =
            (U2 * (U2 * (U2 * 0.27385f - 0.73369f) + 0.46341f)) /
            (U2 * (U2 * (U2 * 0.093073f + 0.309420f) - 1.000000f) + 0.597999f);
        *slope_y = S * z * std::sqrt(1.f + *slope_x * *slope_x);
    }

    static StaticArray<float, 3> TrowbridgeReitzSample(const StaticArray<float, 3> &wi, float alpha_x,
                                                       float alpha_y, float U1, float U2)
    {
        // 1. stretch wi
        StaticArray<float, 3> wiStretched =
            (StaticArray<float, 3>(alpha_x * wi.x(), alpha_y * wi.y(), wi.z()));

        // 2. simulate P22_{wi}(x_slope, y_slope, 1, 1)
        float slope_x, slope_y;
        TrowbridgeReitzSample11(CosTheta(wiStretched), U1, U2, &slope_x, &slope_y);

        // 3. rotate
        float tmp = CosPhi(wiStretched) * slope_x - SinPhi(wiStretched) * slope_y;
        slope_y = SinPhi(wiStretched) * slope_x + CosPhi(wiStretched) * slope_y;
        slope_x = tmp;

        // 4. unstretch
        slope_x = alpha_x * slope_x;
        slope_y = alpha_y * slope_y;

        // 5. compute normal
        return (StaticArray<float, 3>(-slope_x, -slope_y, 1.f)).Normalize();
    }

    StaticArray<float, 3> GGXDistribution::SampleWh(const StaticArray<float, 3> &wo, const StaticArray<float, 2> &u) const
    {
        StaticArray<float, 3> wh;

        bool flip = wo.z() < 0;
        StaticArray<float, 3> _wo = wo;
        wh = TrowbridgeReitzSample(flip ? _wo.Neg() : _wo, alphax, alphay, u.x(), u.y());
        if (flip)
        {
            wh = wh.Neg();
        }

        return wh;
    }
}