#pragma once

#include "LrssnEngine/Core/PlatformDetection.h"

#ifdef LE_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

//common
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "LrssnEngine/Core/Base.h"
#include "LrssnEngine/Core/Log.h"
#include "LrssnEngine/Debug/Instrumentor.h"
#ifdef LE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
