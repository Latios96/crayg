//
// Created by Jan Honsbrok on 2019-08-11.
//

#ifndef CRAYG_RUNCONFIG_H
#define CRAYG_RUNCONFIG_H

#include <string>

class RunConfig {
public:
    RunConfig(const std::string &outputFolder);

    const std::string outputFolder;
};


#endif //CRAYG_RUNCONFIG_H
