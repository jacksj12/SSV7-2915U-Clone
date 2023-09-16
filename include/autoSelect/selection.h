/// @author Copyright (c) 2019 Kunwar Sahni
#pragma once

#include <string>

//selector configuration
#define HUE 360
#define DEFAULT 2
#define AUTONS "default", "1 ball in goal", "Nothing!"

namespace selector
{

    extern int auton;
    const char *b[] = {AUTONS, ""};
    void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = b);

}
