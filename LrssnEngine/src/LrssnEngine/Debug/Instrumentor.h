#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include "LrssnEngine/Core/Base.h"
#include "LrssnEngine/Core/Log.h"


namespace LrssnEngine {
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;
	struct ProfileResult {
		std::string Name;
		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession {
		std::string Name;
	};

	class Instrumentor 	{

	public:
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		void BeginSession(const std::string& name, const std::string& filepath = "results.json") {
			std::lock_guard lock(mMutex);
			if (mCurrentSession) {
				// If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead.  That's better than having badly formatted
				// profiling output.
				if (Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
					LE_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, mCurrentSession->Name);
				}
				InternalEndSession();
			}
			mOutputStream.open(filepath);
			if (mOutputStream.is_open()) {
				mCurrentSession = new InstrumentationSession({ name });
				WriteHeader();
			} else {
				if (Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
					LE_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
				}
			}
		}

		void EndSession() {
			std::lock_guard lock(mMutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result) {
			std::stringstream json;

			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(mMutex);
			if (mCurrentSession) {
				mOutputStream << json.str();
				mOutputStream.flush();
			}
		}
		static Instrumentor& Get() {
			static Instrumentor instance;
			return instance;
		}
	private:
		Instrumentor()
			: mCurrentSession(nullptr) 		{
		}

		~Instrumentor() 		{
			EndSession();
		}
		void WriteHeader() {
			mOutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			mOutputStream.flush();
		}

		void WriteFooter() {
			mOutputStream << "]}";
			mOutputStream.flush();
		}
		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void InternalEndSession() {
			if (mCurrentSession) {
				WriteFooter();
				mOutputStream.close();
				delete mCurrentSession;
				mCurrentSession = nullptr;
			}
		}
	
		std::mutex mMutex;
		InstrumentationSession* mCurrentSession;
		std::ofstream mOutputStream;
	};

	class InstrumentationTimer {
	public:
		InstrumentationTimer(const char* name)
			: mName(name), mStopped(false) {
			mStartTimepoint = std::chrono::steady_clock::now();
		}

		~InstrumentationTimer() {
			if (!mStopped)
				Stop();
		}

		void Stop() {
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ mStartTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimepoint).time_since_epoch();

			uint32_t threadID = (uint32_t)(std::hash<std::thread::id>{}(std::this_thread::get_id()));
			Instrumentor::Get().WriteProfile({ mName, highResStart, elapsedTime, std::this_thread::get_id() });

			mStopped = true;
		}
	private:
		const char* mName;
		std::chrono::time_point<std::chrono::steady_clock> mStartTimepoint;
		bool mStopped;
	};
	namespace InstrumentorUtils {

		template <size_t N>
		struct ChangeResult 		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K]) 		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N) 			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}

#define LE_PROFILE 0
#if LE_PROFILE
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define LE_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define LE_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined((__FUNCSIG__) || (_MSC_VER))
		#define LE_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define LE_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define LE_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define LE_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define LE_FUNC_SIG __func__
	#else
		#define LE_FUNC_SIG "LE_FUNC_SIG unknown!"
	#endif

	#define LE_PROFILE_BEGIN_SESSION(name, filepath) ::LrssnEngine::Instrumentor::Get().BeginSession(name, filepath)
	#define LE_PROFILE_END_SESSION() ::LrssnEngine::Instrumentor::Get().EndSession()
	#define LE_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::LrssnEngine::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
											   ::LrssnEngine::InstrumentationTimer timer##line(fixedName##line.Data)
	#define LE_PROFILE_SCOPE_LINE(name, line) LE_PROFILE_SCOPE_LINE2(name, line)
	#define LE_PROFILE_SCOPE(name) LE_PROFILE_SCOPE_LINE(name, __LINE__)
	#define LE_PROFILE_FUNCTION() LE_PROFILE_SCOPE(LE_FUNC_SIG)
#else
	#define LE_PROFILE_BEGIN_SESSION(name, filepath)
	#define LE_PROFILE_END_SESSION()
	#define LE_PROFILE_SCOPE(name)
	#define LE_PROFILE_FUNCTION()
#endif 