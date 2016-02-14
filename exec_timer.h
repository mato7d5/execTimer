/*
 * Name: ExecTimer
 * Description: measures execution time of code. Required C++ 11 compiler at least.
 * License: GNU GPL 2.1
 * Contact: martin@borg.sk
 */

#ifndef __EXEC_TIMER_H__
#define __EXEC_TIMER_H__

#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include <chrono>

using std::string;
using std::map;
using std::ofstream;

namespace met {
    /* Main class for measuring time of executed code */
    class ExecTimer {
        private:
            /* begin and end points of measuring */
            struct StartEnd {
                std::chrono::time_point<std::chrono::high_resolution_clock> start;
                std::chrono::time_point<std::chrono::high_resolution_clock> end;
                StartEnd() : start(), end() { }
            };

            string mName;
            map<const string, StartEnd> mSections;

        public:
            ExecTimer() : mName("exec_timer") { }
           
            explicit ExecTimer(const string& name) : mName(name) {
            
            }

            ~ExecTimer() { }
            ExecTimer(const ExecTimer& et) = delete;
            ExecTimer& operator=(const ExecTimer& et) = delete;

            void start(const string& label) {
                StartEnd se;
                mSections.insert(std::pair<const string, StartEnd> (label, se));
                StartEnd& seStart = mSections.at(label);
                seStart.start = std::chrono::high_resolution_clock::now();
            }

            void stop(const string& label) {
                std::chrono::time_point<std::chrono::high_resolution_clock> endNow = std::chrono::high_resolution_clock::now();
                StartEnd& se = mSections.at(label);
                se.end = endNow;
            }

            void print() {
                string filename(mName);
                filename.append(".log");
                ofstream out(filename, std::ios::out | std::ios::trunc);

   
                out << std::left << std::setw(30) << "Section" << std::setw(20) << "Time (microseconds)" << std::endl;
                out << std::left << std::setw(30) << "-------" << std::setw(20) << "-------------------" << std::endl;

                for (auto& section : mSections) {
                    auto diff = std::chrono::duration_cast<std::chrono::microseconds> (section.second.end - section.second.start).count();
                    out << std::left << std::setw(30) << section.first << std::setw(20) << diff << std::endl;
                }
            }
    };

    /* auto measuring of given scope */
    class ExecTimerAuto {
        private:
            ExecTimer mET;
            string mLabel;

        public:
            explicit ExecTimerAuto(const string& label) : mET(), mLabel(label)
            {
                mET.start(mLabel);
            }

            ExecTimerAuto(const string& name, const string& label) : mET(name), mLabel(label) 
            {
                mET.start(mLabel);
            }
            
            ~ExecTimerAuto() {
                mET.stop(mLabel);
                mET.print();
            }

            ExecTimerAuto(const ExecTimerAuto& eta) = delete;
            ExecTimerAuto& operator=(const ExecTimerAuto& eta) = delete;
    };

    /* helper scope class */
    class ExecTimerScope {
        private:
            ExecTimer& mEt;
            string mLabel;
        public:
            ExecTimerScope(ExecTimer& et, const string& label) : mEt(et), mLabel(label) { mEt.start(mLabel); }
            ExecTimerScope(ExecTimer& et, const string& label, const int idx) : mEt(et), mLabel(label + std::to_string(idx)) { mEt.start(mLabel); }
            ~ExecTimerScope() { mEt.stop(mLabel); }
    };
}

#define MET_AUTO_BENCHMARK_FUNCTION         met::ExecTimerAuto autoBenchETA(__func__);

#define MET_BENCHMARK_CREATE(NAME)          met::ExecTimer NAME(#NAME);
#define MET_BENCHMARK_START(NAME, SECTION)  NAME.start(#SECTION);
#define MET_BENCHMARK_STOP(NAME, SECTION)   NAME.stop(#SECTION);
#define MET_BENCHMARK_PRINT(NAME)           NAME.print();
#define MET_BENCHMARK_SCOPE(NAME, SECTION)  met::ExecTimerScope scopedEt(NAME, #SECTION);  
#define MET_BENCHMARK_LOOP(NAME, SECTION)   static int SECTION##_idx = 0; \
                                            met::ExecTimerScope SECTION##_scopedEt(NAME, #SECTION, SECTION##_idx); \
                                            ++SECTION##_idx; \

#endif
