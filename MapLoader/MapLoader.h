#define MapLoader_h
#include <stdio.h>
#include <string>
#include <iostream>
#include "../Map/Map.h"
using namespace std;

#pragma once
    Map parseMap (std::string map);
    list<string> list_dir(const char *path);
    void showlist(list <string> g);


