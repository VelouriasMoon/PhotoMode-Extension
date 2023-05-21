#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

#include <ClibUtil/RNG.hpp>
#include <ClibUtil/simpleINI.hpp>
#include <ClibUtil/singleton.hpp>
#include <ClibUtil/string.hpp>
#include <DirectXMath.h>
#include <DirectXTex.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <ankerl/unordered_dense.h>
#include <rapidfuzz/rapidfuzz_all.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <srell.hpp>
#include <wrl/client.h>
#include <xbyak/xbyak.h>

#define DLLEXPORT __declspec(dllexport)

namespace logger = SKSE::log;
namespace ini = clib_util::ini;
namespace string = clib_util::string;

using namespace std::literals;
using namespace clib_util::singleton;

using RNG = clib_util::RNG;

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

namespace stl
{
	using namespace SKSE::stl;

	template <class T>
	void write_thunk_call(std::uintptr_t a_src)
	{
		SKSE::AllocTrampoline(14);

		auto& trampoline = SKSE::GetTrampoline();
		T::func = trampoline.write_call<5>(a_src, T::thunk);
	}

	template <class F, class T>
	void write_vfunc()
	{
		REL::Relocation<std::uintptr_t> vtbl{ F::VTABLE[0] };
		T::func = vtbl.write_vfunc(T::size, T::thunk);
	}
}

// short hand to avoid calling GetSingleton everytime
template <class T>
T* get()
{
	return T::GetSingleton();
}

#ifdef SKYRIM_AE
#	define OFFSET(se, ae) ae
#else
#	define OFFSET(se, ae) se
#endif

#include "Cache.h"
#include "Version.h"
