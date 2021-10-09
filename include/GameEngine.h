#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>

class GameState
{
    public:
    std::string stateID;
    std::vector<std::string> cmds;
    bool running;

    GameState(std::string _stateID, std::vector<std::string> _cmds);
    ~GameState();
    virtual void OnStateEnter();
    virtual void OnStateExit();
};

class StartState : public GameState { 
    public:
    StartState(std::string _stateID, std::vector<std::string> _cmds);
    ~StartState();
};

class MapLoadedState : public GameState { 
    public:
    MapLoadedState(std::string _stateID, std::vector<std::string> _cmds);
    ~MapLoadedState();
};

class MapValidatedState : public GameState { 
    public:
    MapValidatedState(std::string _stateID, std::vector<std::string> _cmds);
    ~MapValidatedState();
};

class PlayersAddedState : public GameState { 
    public:
    PlayersAddedState(std::string _stateID, std::vector<std::string> _cmds);
    ~PlayersAddedState();
};

class AssignReinforcementState : public GameState { 
    public:
    AssignReinforcementState(std::string _stateID, std::vector<std::string> _cmds);
    ~AssignReinforcementState();
};

class IssueOrdersState : public GameState { 
    public:
    IssueOrdersState(std::string _stateID, std::vector<std::string> _cmds);
    ~IssueOrdersState();
};

class ExecuteOrdersState : public GameState { 
    public:
    ExecuteOrdersState(std::string _stateID, std::vector<std::string> _cmds);
    ~ExecuteOrdersState();
};

class WinState : public GameState { 
    public:
    WinState(std::string _stateID, std::vector<std::string> _cmds);
    ~WinState();
};

class EndState : public GameState { 
    public:
    EndState(std::string _stateID, std::vector<std::string> _cmds);
    ~EndState();
};

class GameEngine
{
    public:

    bool running;

    const std::string PLAY_CMD = "play";
    const std::string LOAD_MAP_CMD = "loadmap";
    const std::string VALIDATE_MAP_CMD = "validatemap";
    const std::string ADD_PLAYER_CMD = "addplayer";
    const std::string ASSIGN_COUNTRIES_CMD = "assigncountries";
    const std::string ISSUE_ORDER_CMD = "issueorder";
    const std::string END_ISSUE_ORDERS_CMD = "endissueorders";
    const std::string EXEC_ORDER_CMD = "execorder";
    const std::string END_EXEC_ORDERS_CMD = "endexecorders";
    const std::string WIN_CMD = "win";
    const std::string END_CMD = "end";

    StartState* startState;
    MapLoadedState* mapLoadedState;
    MapValidatedState* mapValidatedState;
    PlayersAddedState* playersAddedState;
    AssignReinforcementState* assignReinforcementState;
    IssueOrdersState* issueOrdersState;
    ExecuteOrdersState* executeOrdersState;
    WinState* winState;
    EndState* endState;

    GameState* currentState;

    std::map<std::string, GameState*> cmds;

    GameEngine();
    ~GameEngine();
    GameEngine& operator=(GameEngine&& gameEngine);
    void Run();
    bool ExecuteCmd(std::string);
    void SetState(GameState* );
    void TransitionTo(GameState* );
};

#endif