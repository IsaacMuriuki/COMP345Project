#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <functional>

class GameEngine
{
    public:
    static bool ExecuteCmd(std::string);
    static void TransitionTo(GameState*);
};

class GameState
{
    public:
    virtual void OnStateEnter();
    static void OnStateExit();
};

#endif