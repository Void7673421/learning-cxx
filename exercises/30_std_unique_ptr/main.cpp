#include "../exercise.h"
#include <memory>
#include <cstring>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;
Unique reset(Unique ptr) {
    if (ptr) {
        ptr->record('r');
    }
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) {
        ptr->record('d');
    }
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) {
        ptr->record('f');
    }
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);
    // reset []
    // forward f
    // drop fd
    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);
    // reset []
    // forward f
    // forward ff
    // reset ffr->[]
    // drop d
    // forward [x]
    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);
    // reset []
    // reset r->[]
    // drop d->[x]
    // reset [x]->[]
    // drop d->[x]
    // drop 
    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        {"d","ffr"},
        {"d","d","r"},
        // {"f", "f", "r", "d", "", "", "", ""},
        // {"r", "d", "d", "", "", "", "", ""},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        printf("%d\n",i);
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
