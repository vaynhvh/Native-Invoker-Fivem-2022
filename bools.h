#pragma once
#include "customapi.h"
#include "../Directories/ImGui/imgui.h"
#include <Windows.h>
#include <iostream>

class scrNativeCallContext
{
protected:
    void* m_pReturn;
    uint32_t m_nArgCount;
    void* m_pArgs;

    uint32_t m_nDataCount;

public:
    template<typename T>
    inline T GetArgument(int idx)
    {
        intptr_t* arguments = (intptr_t*)m_pArgs;

        return *(T*)&arguments[idx];
    }

    inline void* GetArgumentBuffer()
    {
        return m_pArgs;
    }

    template<typename T>
    inline void SetResult(int idx, T value)
    {
        intptr_t* returnValues = (intptr_t*)m_pReturn;

        *(T*)&returnValues[idx] = value;
    }

    inline int GetArgumentCount()
    {
        return m_nArgCount;
    }

    template<typename T>
    inline T GetResult(int idx)
    {
        intptr_t* returnValues = (intptr_t*)m_pReturn;

        return *(T*)&returnValues[idx];
    }

    inline void SetVectorResults() { }
};

class NativeContext :
    public scrNativeCallContext
{
private:
    // Configuration
    enum
    {
        MaxNativeParams = 16,
        ArgSize = 4,
    };

    // Anything temporary that we need
    uint8_t m_TempStack[MaxNativeParams * ArgSize];

public:
    inline NativeContext()
    {
        m_pArgs = &m_TempStack;
        m_pReturn = &m_TempStack;
        m_nArgCount = 0;
        m_nDataCount = 0;
    }

    template <typename T>
    inline void Push(T value)
    {
        if (sizeof(T) > ArgSize)
        {
            throw "Argument has an invalid size";
        }
        else if (sizeof(T) < ArgSize)
        {
            *reinterpret_cast<uintptr_t*>(m_TempStack + ArgSize * m_nArgCount) = 0;
        }

        *reinterpret_cast<T*>(m_TempStack + ArgSize * m_nArgCount) = value;
        m_nArgCount++;
    }

    inline void Reverse()
    {
        uintptr_t tempValues[MaxNativeParams];
        uintptr_t* args = (uintptr_t*)m_pArgs;

        for (int i = 0; i < m_nArgCount; i++)
        {
            int target = m_nArgCount - i - 1;

            tempValues[target] = args[i];
        }

        memcpy(m_TempStack, tempValues, sizeof(m_TempStack));
    }

    template <typename T>
    inline T GetResult()
    {
        return *reinterpret_cast<T*>(m_TempStack);
    }
};

typedef void(__cdecl* NativeHandler)(scrNativeCallContext* context);

using GetNativeHandler_t = NativeHandler(__fastcall*)(__int64 hash);
using CallNativeHandler_t = void(__fastcall*)(NativeContext*);

struct pass
{
    template<typename ...T> pass(T...) {}
};

class NativeInvoke
{
private:

    static inline void Invoke(NativeContext* cxt, __int64 hash)
    {
        auto mod = GetModuleHandleA("rage-scripting-five.dll");
        auto inset = GetProcAddress(mod, "?GetNativeHandler@scrEngine@rage@@SAP6AXPEAVscrNativeCallContext@2@@Z_K@Z");

        NativeHandler fn = ((GetNativeHandler_t)(inset))(hash);

        if (fn != 0)
        {
            (fn)(cxt);
        }
    }

public:

    template<__int64 Hash, typename R, typename... Args>
    static inline R Invoke(Args... args)
    {
        NativeContext cxt;

        pass{ ([&]()
        {
            cxt.Push(args);
        }(), 1)... };

        Invoke(&cxt, Hash);

        return cxt.GetResult<R>();
    }

};
uintptr_t gworldptr = CustomAPII::ScanSignature((uintptr_t)(CustomAPI::GetModuleW(nullptr)), "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81");
uintptr_t gworld = *(uint64_t*)(gworldptr + *(int*)(gworldptr + 0x3) + 0x7);
uintptr_t replayptr = CustomAPII::ScanSignature((uintptr_t)(CustomAPI::GetModuleW(nullptr)), "48 8D 0D ?? ?? ?? ?? 89 44 24 30 E8 ?? ?? ?? ?? 48 83 C4 28 C3 48 8B 05");
uintptr_t w2sptr = CustomAPII::ScanSignature((uintptr_t)(CustomAPI::GetModuleW(nullptr)), "48 89 5C 24 ?? 55 56 57 48 83 EC 70 65 4C 8B 0C 25");
uintptr_t boneptr = CustomAPII::ScanSignature((uintptr_t)(CustomAPI::GetModuleW(nullptr)), "48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 48 83 EC 60 48 8B 01 41 8B E8 48 8B F2 48 8B F9 33 DB");

template <typename T> T Read(uint64_t addr)
{
    T Novalue = {};
    if (!IsBadReadPtr((const void*)addr, sizeof(T)))
    {
        return *(T*)(addr);
    }
    else
    {
        return Novalue;
    }

};

uintptr_t localplayer;
int selectedbox = 0;
const char* boxtype[]{ "2D Box", "2D Filled" };

int selectedaimkey = 0;
const char* aimkey[]{ "Right Click", "Left Click" };

int selectedaim = 0;
const char* aimtype[]{ "All", "Only Ped", "Only Player" };

namespace offsetadress
{
    uintptr_t weaponmanager;
    DWORD recoil;
    DWORD spread;
    DWORD armor;

}

namespace SettingsBool
{
    bool Esp = false;
    bool PedEsp = true;
    bool ignoreselfEsp = false;

    bool BoxEnable = false;
    bool BoxEsp = false;
    bool CornerEsp = false;
    bool FilledEsp = false;

    bool skeletonesp = false;

    bool HealthEsp = false;
    bool ArmorEsp = false;
    bool HealthBarEsp = false;
    //bool ArmorBarEsp = false;
    float distancelimite = 500;
    bool DistanceEsp = false;
    //bool nametag = false;  // 0x6D0DE6A7B5DA71F8  X  0x406B4B20







    bool enableaimbot = true;
    bool aimatped = false;
    bool aimatplayer = false;
    bool mouseaim = false;
    bool memoryaim = false;
    bool entityvisible = false;

    bool Crosshair = false;
    bool fovenabled = false;

    float fov = 50;
    float smooth = 5;



    bool semigodmode = false;

    bool noclip = false;



    bool norecoil = false;
    bool nospread = false;
    bool noreload = false;
    bool infiniteammo = false;




}