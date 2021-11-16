#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "LoggingObserver.h"
#include "map.h"

#include < iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>

#include < filesystem>
namespace fs = std::filesystem;

class GameEngine;
class GameState
{
protected:
    std::string name;
    std::vector<std::string> cmds;
    GameEngine *gameEngine;

public:
    GameState(std::string _name = "gamestate");
    GameState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    ~GameState();
    GameState(const GameState &state);
    GameState &operator=(GameState &&state);
    virtual void onStateEnter();
    virtual void onStateExit();
    friend std::ostream &operator<<(std::ostream &os, const GameState &state);
    std::string getName();
    std::vector<std::string> getCmds();
    GameState *clone();
};

class StartState : public GameState
{
public:
    StartState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    StartState(const StartState &state);
    ~StartState();
};

class MapLoadedState : public GameState
{
public:
    MapLoadedState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    MapLoadedState(const MapLoadedState &state);
    ~MapLoadedState();
};

class MapValidatedState : public GameState
{
public:
    MapValidatedState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    MapValidatedState(const MapValidatedState &state);
    ~MapValidatedState();
};

class PlayersAddedState : public GameState
{
public:
    PlayersAddedState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    PlayersAddedState(const PlayersAddedState &state);
    ~PlayersAddedState();
};

class AssignReinforcementState : public GameState
{
public:
    AssignReinforcementState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    AssignReinforcementState(const AssignReinforcementState &state);
    ~AssignReinforcementState();
};

class IssueOrdersState : public GameState
{
public:
    IssueOrdersState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    IssueOrdersState(const IssueOrdersState &state);
    ~IssueOrdersState();
};

class ExecuteOrdersState : public GameState
{
public:
    ExecuteOrdersState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    ExecuteOrdersState(const ExecuteOrdersState &state);
    ~ExecuteOrdersState();
};

class WinState : public GameState
{
public:
    WinState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    WinState(const WinState &state);
    ~WinState();
};

class GameEngine : public ILoggable, public Subject
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
    const std::string MAPS_FOLDER = "../../maps/"; // for mac this works ->   const string MAPS_FOLDER = "../maps";

    StartState *startState;
    MapLoadedState *mapLoadedState;
    MapValidatedState *mapValidatedState;
    PlayersAddedState *playersAddedState;
    AssignReinforcementState *assignReinforcementState;
    IssueOrdersState *issueOrdersState;
    ExecuteOrdersState *executeOrdersState;
    WinState *winState;

    bool running;
    Map *gameMap;
    vector<Player *> playersList;
    GameState *currentState;
    std::map<std::string, GameState *> cmds;

    void SetCommands();
    bool ExecuteCmd(std::string);
    void SetState(GameState *);
    void TransitionTo(GameState *);
    void PrintMapFiles();

public:
    GameEngine();
    ~GameEngine();
    GameEngine(const GameEngine &engine);
    GameEngine &operator=(GameEngine &&gameEngine);

    void Run();
    friend std::ostream &operator<<(std::ostream &os, const GameEngine &engine);
    bool isRunning();

    GameState *getCurrentState();
    std::map<std::string, GameState *> getCmds();
    Map *getMap();
    void setMap(Map *);
    vector<Player *> getPlayers();
    void addPlayer(Player *);
    GameEngine *clone();
    void startupPhase();
    string stringToLog();
};

#endif