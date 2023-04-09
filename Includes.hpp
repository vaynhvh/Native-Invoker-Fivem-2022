#pragma once
/* C++ include */
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <random>
#include <regex>
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <xstring>
/* SDK */
#include "ResourceManager.h"
#include "ResourceCache.h"
#include "ResourceMetaDataComponent.h"
#include "VFSManager.h"

using namespace fx;
auto ManageResources = Instance<ResourceManager>::Get();

/* Imgui */

/* system */
#include "system/filesystem.hpp"


#include "Main.h"
#include "client.h"
#include "../Directories/ImGui/imgui.h"
bool Menu_Open = false;
int tab = 0;
ImFont* rudy10;
ImFont* rudy14;
ImFont* rudy16;
ImFont* rudy18;
ImFont* rudy22;
ImFont* rudy30;
int seatbelt_button_counter = 0;

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;