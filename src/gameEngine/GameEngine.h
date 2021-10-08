#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

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

class StartState : public GameState { };

class MapLoadedState : public GameState { };

class MapValidatedState : public GameState { };

class PlayersAddedState : public GameState { };

class AssignReinforcementState : public GameState { };

class IssueOrdersState : public GameState { };

class ExecuteOrdersState : public GameState { };

class WinState : public GameState { };

class EndState : public GameState { };

class Command : public GameState { 
    public: 
    virtual void Execute();
};

class TransitionCommand : public Command { 
    public:
    void Execute();
};


#endif