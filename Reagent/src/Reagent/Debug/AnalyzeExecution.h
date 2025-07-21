#pragma once

#include "../../rgpch.h"
#include "../Log.h"

#include <thread>
#include <mutex>
#include <chrono>


namespace rg
{
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;


	struct ExecutionResult
	{
		std::string Name;
		
		FloatingPointMicroseconds Start;
		std::chrono::microseconds Duration;
		std::thread::id ThreadID;

	};

	struct AnalyzeExecutionSession
	{
		std::string Name;
	};

	class AnalyzeExecution
	{
	public:
		AnalyzeExecution(const AnalyzeExecution&) = delete;
		AnalyzeExecution(AnalyzeExecution&&) = delete;

		void StartSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(m_Mutex);

			if (m_CurrentSession)
			{
				// if there is a current session, then close it before beginning a new one (race condition)
				// profiling ouput meant for original session will end up in new session better than badly formatted output

				if (Log::GetClientLogger()) // Begin session might be called before the logger is initialized
				{
					RG_CORE_ERROR("AnalyzeExecution: StartSession({0}) when session '{1}' already open", name, m_CurrentSession->Name);
				}
				InternalEndSession();
			}
			m_OutputStream.open(filepath);

			if (m_OutputStream.is_open())
			{
				m_CurrentSession = new AnalyzeExecutionSession({ name });
				WriteHeader();
			}
			else
			{
				if(Log::GetCoreLogger()) // Begin session might be called before the logger is initialized
				{
					RG_CORE_ERROR("AnalyzeExecution: Failed to open file '{0}' for writing", filepath);
				}
			}
		}

		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		void WriteExecutionResult(const ExecutionResult& result)
		{
			std::lock_guard lock(m_Mutex);

			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.Duration.count()) << ',';
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			if (m_CurrentSession)
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		static AnalyzeExecution& Get()
		{
			static AnalyzeExecution instance;
			return instance;
		}

	private:
		AnalyzeExecution()
			:m_CurrentSession(nullptr)
		{ }

		~AnalyzeExecution()
		{
			EndSession();
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {}, \"traceEvents\":[";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		// you must already have a lock on m_Mutex when calling this end session
		void InternalEndSession()
		{
			if (m_CurrentSession)
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}
	private:
		std::mutex m_Mutex;
		AnalyzeExecutionSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	};

	class ExecutionTimer
	{
	public:
		ExecutionTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::steady_clock::now();
		}

		~ExecutionTimer()
		{
			if (!m_Stopped)
			{
				Stop();
			}
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };
			auto durationTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

			AnalyzeExecution::Get().WriteExecutionResult({m_Name, highResStart, durationTime, std::this_thread::get_id()});

			m_Stopped = true;
		}
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};

	namespace AnalyzeExecutionUtils
	{
		template <size_t N>

		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanOutputString(const char (&str)[N], const char (&replace)[K]) -> ChangeResult<N + 1 - K>
		{
			ChangeResult<N + 1 - K> result = { 0 };
			size_t j = 0;
			for (size_t i = 0; i < N; ++i)
			{
				if (i < N - K + 1 && std::equal(str + i, str + i + K, replace))
				{
					i += K - 1; // Skip the length of the replace string
				}
				else
				{
					result.Data[j++] = str[i];
				}
			}
			result.Data[j] = '\0'; // Null-terminate the string
			return result;
		}
	}
}


#define RG_PROFILE 0 
#if RG_PROFILE

// This macro is used to profile a function or a block of code
// It will create a timer that will log the execution time of the code block
// Usage: RG_PROFILE_SCOPE("MyFunction"); // This will profile the function MyFunction

	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define RG_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define RG_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define RG_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define RG_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define RG_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define RG_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define RG_FUNC_SIG __func__
	#else
		#define RG_FUNC_SIG "RG_FUNC_SIG unknown!"
	#endif


	#define RG_PROFILE_START_SESSION(name, filepath) ::rg::AnalyzeExecution::Get().StartSession(name, filepath)
	#define RG_PROFILE_END_SESSION() ::rg::AnalyzeExecution::Get().EndSession()
	#define RG_PROFILE_SCOPE_LINER(name, line) constexpr auto fixedName##line = ::rg::AnalyzeExecutionUtils::CleanupOutputString(name, "__cdecl");\
																													::rg::ExecutionTimer timer##line(fixedName##line.Data)

	#define RG_PROFILE_SCOPE_LINE(name, line) RG_PROFILE_SCOPE_LINER(name, line)
	#define RG_PROFILE_SCOPE(name) RG_PROFILE_SCOPE_LINE(name, __LINE__)
	#define RG_PROFILE_FUNCTION() RG_PROFILE_SCOPE(RG_FUNC_SIG)
#else
	#define RG_PROFILE_BEGIN_SESSION(name, filepath)
	#define RG_PROFILE_END_SESSION()
	#define RG_PROFILE_SCOPE(name)
	#define RG_PROFILE_FUNCTION()
#endif