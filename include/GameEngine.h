#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include "Player.h"
#include "map.h"

class GameState
{
    protected:
    std::string name;
    std::vector<std::string> cmds;

    public:
    GameState(std::string _name = "gamestate");
    GameState(std::string _name, std::vector<std::string> _cmds);
    ~GameState();
    GameState(const GameState& state);
    GameState& operator=(GameState&& state);
    virtual void onStateEnter();
    virtual void onStateExit();
    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
    std::string getName();
    std::vector<std::string> getCmds();
    GameState* clone();
};

class StartState : public GameState { 
    public:
    StartState(std::string _name, std::vector<std::string> _cmds);
    StartState(const StartState& state);
    ~StartState();
};

class MapLoadedState : public GameState { 
    public:
    MapLoadedState(std::string _name, std::vector<std::string> _cmds);
    MapLoadedState(const MapLoadedState& state);
    ~MapLoadedState();
};

class MapValidatedState : public GameState { 
    public:
    MapValidatedState(std::string _name, std::vector<std::string> _cmds);
    MapValidatedState(const MapValidatedState& state);
    ~MapValidatedState();
};

class PlayersAddedState : public GameState { 
    public:
    PlayersAddedState(std::string _name, std::vector<std::string> _cmds);
    PlayersAddedState(const PlayersAddedState& state);
    ~PlayersAddedState();
};

class AssignReinforcementState : public GameState { 
    public:
    AssignReinforcementState(std::string _name, std::vector<std::string> _cmds);
    AssignReinforcementState(const AssignReinforcementState& state);
    ~AssignReinforcementState();
    virtual void onStateEnter();
    virtual void onStateExit();
};

class IssueOrdersState : public GameState { 
    public:
    IssueOrdersState(std::string _name, std::vector<std::string> _cmds);
    IssueOrdersState(const IssueOrdersState& state);
    ~IssueOrdersState();
};

class ExecuteOrdersState : public GameState { 
    public:
    ExecuteOrdersState(std::string _name, std::vector<std::string> _cmds);
    ExecuteOrdersState(const ExecuteOrdersState& state);
    ~ExecuteOrdersState();
};

class WinState : public GameState { 
    public:
    WinState(std::string _name, std::vector<std::string> _cmds);
    WinState(const WinState& state);
    ~WinState();
};

class GameEngine
{
    private:

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

    bool running;
    GameState* currentState;
    std::map<std::string, GameState*> cmds;

    void SetCommands();
    bool ExecuteCmd(std::string);
    void SetState(GameState* );
    void TransitionTo(GameState* );

    public:

    GameEngine();
    ~GameEngine();
    GameEngine(const GameEngine& engine);
    GameEngine& operator=(GameEngine&& gameEngine);

    void Run();
    friend std::ostream& operator<<(std::ostream& os, const GameEngine& engine);
    bool isRunning();
    GameState* getCurrentState();
    std::map<std::string, GameState*> getCmds();
    GameEngine* clone();
    
};

#endif