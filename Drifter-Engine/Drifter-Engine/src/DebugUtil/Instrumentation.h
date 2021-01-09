//
// Basic instrumentation profiler by Cherno

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Instrumentor::Get().BeginSession("Session Name");        // Begin session 
// {
//     InstrumentationTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// Instrumentor::Get().EndSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.
//
#pragma once

#include "Drifter/Core/Base.h"

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

#include <filesystem>
namespace Drifter {
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        uint32_t ThreadID;

        inline float GetDuration() const {
            return (End - Start) * 0.001f;
        }
    };

    struct ProfileSession {
        ProfileSession(const std::string& filepath) : m_SessionName(filepath), m_OutputStream(filepath) {
            StartSession();
        }
        ~ProfileSession() {
            EndSession();
        }

        void EndSession() {
            if (m_OutputStream.is_open()) {
                FlushLog();
                WriteFooter();
            }
            m_OutputStream.close();
        }
        
        void LogEntry(const ProfileResult& result) {
            m_CachedResults.push_back(result);
        }

        std::vector<ProfileResult>& GetLog() {
            return m_CachedResults;
        }

        void FlushLog() {
            for (auto& profileResult : m_CachedResults) {
                WriteEntry(profileResult);
            }
            m_CachedResults.clear();
        }
    private:


        
        void WriteEntry(const ProfileResult& result) {
            if (m_OutputStream.is_open() == false) { return; }
            if (m_CommaNeeded) { m_OutputStream << ","; }
            m_CommaNeeded = true;

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            m_OutputStream << "{";
            m_OutputStream << "\"cat\":\"function\",";
            m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
            m_OutputStream << "\"name\":\"" << name << "\",";
            m_OutputStream << "\"ph\":\"X\",";
            m_OutputStream << "\"pid\":0,";
            m_OutputStream << "\"tid\":" << result.ThreadID << ",";
            m_OutputStream << "\"ts\":" << result.Start;
            m_OutputStream << "}";
            
            m_OutputStream.flush();
        }

        //state variables
        std::ofstream m_OutputStream; 
        std::string m_SessionName;
        bool m_CommaNeeded = false;
        std::vector<ProfileResult> m_CachedResults;
    private:
        void StartSession() {
            WriteHeader();
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }
    };

    class Instrumentor
    {
    public:
        static bool HasActiveSession() {
            return GetActiveSession() != nullptr;
        }
        static Ref<ProfileSession> BeginSession(const std::string& filepath) {
            if (HasActiveSession()) {
                EndSession();
            }
            GetActiveSession() = CreateRef<ProfileSession>(filepath);
            return GetActiveSession();
        }

        static void EndSession() {
            if (HasActiveSession()) {
                GetActiveSession()->EndSession();
                GetActiveSession().reset();
            }
        }

        static void DeleteLogs(const std::string& dir_path) {
            if (!std::filesystem::exists(dir_path)) {
                std::filesystem::create_directory(dir_path);
            }
            for (const auto & entry : std::filesystem::directory_iterator(dir_path))
                std::filesystem::remove_all(entry.path());
        }

        static Ref<ProfileSession>& GetActiveSession(){
            static Ref<ProfileSession> activeSession;
            return activeSession;
        }

    };

    template<typename Fn>
    class Timer {
    public:
        Timer(const char* name, Fn&& callback)
            :
            m_Name(name),
            m_Callback(callback)
        {
            m_Start = GetTime();
        }

        ~Timer() {
            auto endTimepoint = std::chrono::high_resolution_clock::now();
            auto finish = GetTime();
            uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

            m_Callback({ m_Name, m_Start, finish, threadID});
        }

    private:
        inline long long GetTime() {
            return std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()).time_since_epoch().count();
        }

    private:
        const char* m_Name;
        const Fn m_Callback;
        long long m_Start{ 0 };
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name, Ref<ProfileSession> session = Instrumentor::GetActiveSession())
            : m_Name(name), m_Session(session)
        {
            m_Start = GetTime();
        }

        ~InstrumentationTimer()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            std::true_type myValue{};
            std::true_type::value_type value = myValue();

            long long end = GetTime();
            uint32_t threadID = static_cast<uint32_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));

            if (m_Session) {
                m_Session->LogEntry({ m_Name, m_Start, end, threadID });
            }
        }
    private:
        inline long long GetTime() {
            return std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()).time_since_epoch().count();
        }
    private:
        const char* m_Name;
        long long m_Start{ 0 };
        Ref<ProfileSession> m_Session;
    };
}

#define TOKENPASTE2(x, y) x ## y
#define TOKENPASTE(x, y) TOKENPASTE2(x, y)


#define DF_PROFILE_LEVEL_RENDERER 2
#define DF_PROFILE_LEVEL_BASIC 1
#define DF_PROFILE_LEVEL_NONE 0

#define DF_PROFILE_LEVEL DF_PROFILE_LEVEL_BASIC

//basic profiling macros
#if DF_PROFILE_LEVEL >= DF_PROFILE_LEVEL_BASIC
#define BEGIN_PROFILING_SESSION(name) Drifter::Instrumentor::BeginSession(std::string(".Benchmarking/") + name)
#define END_PROFILING_SESSION() Drifter::Instrumentor::EndSession()

#define PROFILE_SCOPE(name) Drifter::InstrumentationTimer TOKENPASTE(timer,__LINE__) { name }
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define BEGIN_PROFILING_SESSION(name) 
#define END_PROFILING_SESSION 

#define PROFILE_SCOPE(name, list)
#define PROFILE_FUNCTION(list)
#endif

//render profiling macros
#if DF_PROFILE_LEVEL >= DF_PROFILE_LEVEL_RENDERER
#define PROFILE_RENDERER_SCOPE(name) PROFILE_SCOPE(name)
#define PROFILE_RENDERER_FUNCTION() PROFILE_FUNCTION()
#else
#define PROFILE_RENDERER_SCOPE(name)
#define PROFILE_RENDERER_FUNCTION() 
#endif