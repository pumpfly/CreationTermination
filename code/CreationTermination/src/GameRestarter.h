#pragma once
#include <string>
#include <Windows.h>

class GameRestarter {
public:
    static GameRestarter& getInstance() {
        static GameRestarter instance;
        return instance;
    }
    void init(char* argv0) {
        this->path = argv0;
    }
    void restart() {
        STARTUPINFOA startupInfo = {};
        PROCESS_INFORMATION processInformation = {};
        startupInfo.cb = sizeof(startupInfo);
        CreateProcessA(path.c_str(),
            nullptr,
            nullptr,
            nullptr,
            false,
            0,
            nullptr,
            nullptr,
            &startupInfo,
            &processInformation);

        CloseHandle(processInformation.hProcess);
        CloseHandle(processInformation.hThread);
        exit(0);
    }
private:
    std::string path;
};
