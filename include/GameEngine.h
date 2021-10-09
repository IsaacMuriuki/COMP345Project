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
    virtual void OnStateEnter();
    virtual void OnStateExit();
};

class StartState : public GameState { 
    public:
    StartState::StartState(std::string _stateID, std::vector<std::string> _cmds);
};

class MapLoadedState : public GameState { 
    public:
    MapLoadedState(std::string _stateID, std::vector<std::string> _cmds);
};

class MapValidatedState : public GameState { 
    public:
    MapValidatedState(std::string _stateID, std::vector<std::string> _cmds);
};

class PlayersAddedState : public GameState { 
    public:
    PlayersAddedState(std::string _stateID, std::vector<std::string> _cmds);
};

class AssignReinforcementState : public GameState { 
    public:
    AssignReinforcementState(std::string _stateID, std::vector<std::string> _cmds);
};

class IssueOrdersState : public GameState { 
    public:
    IssueOrdersState(std::string _stateID, std::vector<std::string> _cmds);
};

class ExecuteOrdersState : public GameState { 
    public:
    ExecuteOrdersState(std::string _stateID, std::vector<std::string> _cmds);
};

class WinState : public GameState { 
    public:
    WinState(std::string _stateID, std::vector<std::string> _cmds);
};

class EndState : public GameState { 
    public:
    EndState(std::string _stateID, std::vector<std::string> _cmds);
    void EndState::OnStateEnter();
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
    void Run();
    bool ExecuteCmd(std::string);
    void SetState(GameState* );
    void TransitionTo(GameState* );
};

/*
class Command { 
    
    public:
    std::string id;

    Command(const std::string _id);

    virtual void Execute() = 0;
};

class TransitionCommand : public Command { 
    
    private:
    GameState* state;
    
    public:
    TransitionCommand::TransitionCommand(std::string _id, GameState* _state);
    void Execute();
};*/

#endif