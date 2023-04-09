#pragma once
#include <xmmintrin.h>
#include <stdlib.h>
#include <corecrt_math.h>
#include <cstdint>
#include "../Directories/ImGui/imgui.h"
#include "bools.h"
struct Vec2
{
    float x, y;
};

struct Vec3
{
    float x, y, z;
    void Normalize() {
        while (y < -180) {
            y = 360;
        }
        while (y > 180) {
            y = -360;
        }

        while (x > 89) {
            x = -89;
        }
        while (x < -89) {
            x = 89;
        }
    }

    Vec3 operator - (Vec3 i) {
        return {
          x - i.x,
          y - i.y,
          z - i.z
        };
    }

    Vec3 operator + (Vec3 i) {
        return {
          x + i.x,
          y + i.y,
          z + i.z
        };
    }

    Vec3 operator / (float i) {
        return {
          x / i,
          y / i,
          z / i
        };
    }

    Vec3 operator * (float i) {
        return {
          x * i,
          y * i,
          z * i
        };
    }

    static Vec3 FromM128(__m128 in)
    {
        return Vec3
        {
            in.m128_f32[0],
            in.m128_f32[1],
            in.m128_f32[2]
        };
    }
};

struct Vec4
{
    float x, y, z, w;
};
ImVec2 WorldToScreen(Vec3 pos)
{
    auto& io = ImGui::GetIO();
    ImVec2 tempVec2;
    reinterpret_cast<bool(__fastcall*)(Vec3*, float*, float*)>(w2sptr)(&pos, &tempVec2.x, &tempVec2.y);
    tempVec2.x *= io.DisplaySize.x;
    tempVec2.y *= io.DisplaySize.y;
    return tempVec2;
}
ImVec2 GetBonePosW2S(const int64_t cPed, const int32_t wMask)
{
    __m128 tempVec4;
    reinterpret_cast<void* (__fastcall*)(int64_t, __m128*, int32_t)>(boneptr)(cPed, &tempVec4, wMask);
    return WorldToScreen(Vec3::FromM128(tempVec4));
}

Vec3 GetBonePos(const int64_t cPed, const int32_t wMask)
{
    __m128 tempVec4;
    reinterpret_cast<void* (__fastcall*)(int64_t, __m128*, int32_t)>(boneptr)(cPed, &tempVec4, wMask);
    return Vec3::FromM128(tempVec4);
}

float best_fov = 25.f;

float pythag(ImVec2 src, ImVec2 dst)
{
    return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2));
}

float pythagVec3(Vec3 src, Vec3 dst)
{
    return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2) + pow(src.z - dst.z, 2));
}


int roll(int min, int max)
{
    // x is in [0,1[
    double x = rand() / static_cast<double>(RAND_MAX + 1);

    // [0,1[ * (max - min) + min is in [min,max[
    int that = min + static_cast<int>(x * (max - min));

    return that;
}