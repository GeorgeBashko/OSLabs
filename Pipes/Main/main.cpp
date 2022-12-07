#include <iostream>
#include <unistd.h>

std::string process_a_path = "../../A/cmake-build-debug/A";
std::string process_m_path = "../../M/cmake-build-debug/M";
std::string process_p_path = "../../P/cmake-build-debug/P";
std::string process_s_path = "../../S/cmake-build-debug/S";


int RunProcess(const std::string& process_path) {
    int pipes [3];
    pipe(pipes);
    if (!fork()) {
        if (dup2(pipes[1], 1) == -1) {
            return -1;
        }
        system(process_path.c_str());
        return 0;
    } else if (dup2(pipes[0], 0) == -1) {
        close(pipes[1]);
        return -1;
    }
    return 0;
}

int main() {
    if (RunProcess(process_a_path)==0) {
        if (RunProcess(process_m_path)==0) {
            if (RunProcess(process_p_path)==0) {
                system(process_s_path.c_str());
            }
        }
    }

    return 0;
}
