#include "logger.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "time.hpp"

#ifdef _WIN32
#include <windows.h>
void enable_ascii(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

std::ofstream *log_file;

void close(){
    log_file->close();
    delete log_file;
}

namespace Logger{
    void initialize(){  
        #ifdef _WIN32
        enable_ascii();
        #endif
        std::cout << "LLITE LOGGER v1.0" << std::endl;
        #ifdef DEBUG
        Logger::info("DEBUGING ENABLED!");
        #endif
    }
    void open_file(){
        Time t = getCurrentTime();
        std::string path = "logs/log_"+std::to_string(t.year)+"_"+std::to_string(t.month)+"_"+std::to_string(t.day)+"_"+std::to_string(t.hour)+"_"+std::to_string(t.minute)+"_"+std::to_string(t.second)+".log";
        log_file = new std::ofstream(path);
        std::atexit(close);
    }
    
    void info(std::string str){
        Time t = getCurrentTime();
        std::stringstream ss;
        ss << std::setfill('0');
        ss << "[" << std::setw(2) << +t.hour;
        ss << ":" << std::setw(2) << +t.minute;
        ss << ":" << std::setw(2) << +t.second;
        ss << "] INFO: " << str;
        std::cout << ss.str() << "\n";
        if(log_file){
            *log_file << ss.str() << "\n";
        }
    }
    void waning(std::string str){
        Time t = getCurrentTime();
        std::stringstream ss;
        ss << std::setfill('0');
        ss << "[" << std::setw(2) << +t.hour;
        ss << ":" << std::setw(2) << +t.minute;
        ss << ":" << std::setw(2) << +t.second;
        ss << "] ";
        ss << "\e[0;33mWARNING\e[0m: " << str;
        std::cout << ss.str() << "\n";     
        if(log_file){
            *log_file << ss.str() << "\n";
        }
    }
    void error(std::string str){
        Time t = getCurrentTime();
        std::stringstream ss;
        ss << std::setfill('0');
        ss << "[" << std::setw(2) << +t.hour;
        ss << ":" << std::setw(2) << +t.minute;
        ss << ":" << std::setw(2) << +t.second;
        ss << "] ";
        ss << "\e[0;31mERROR\e[0m: " << str;
        std::cerr << ss.str() << "\n";     
        if(log_file){
            *log_file << ss.str() << "\n";
        }
    }
    void terminate(const EXIT_INFO &_ei){
        Time t = getCurrentTime();
        std::stringstream ss;
        ss << "\e[0;31===============CRASH!===============\e[0m\n";
        ss << "What happend: " << _ei.info << '\n';
        ss << "When happen: "; 
        ss << std::setfill('0');
        ss << "[" << std::setw(2) << +t.hour;
        ss << ":" << std::setw(2) << +t.minute;
        ss << ":" << std::setw(2) << +t.second << "]\n";
        ss << "Exit code: 0x" << std::hex << std::setw(8) << '\n';
        std::cerr << ss.str() << "\n";    
        if(log_file){
            *log_file << ss.str() << "\n";
        }
    }
}