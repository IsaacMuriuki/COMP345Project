#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "CommandProcessor.h"
#include "LoggingObserver.h"
#include "map.h"
#include "Player.h"
#include "Orders.h"
#include "OrdersList.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;
using std::vector, std::string;

class Command;
class CommandProcessor;
class GameEngine;
class GameState
{
protected:
    string name;
    vector<string> cmds;
public:
    GameState(std::string _name = "gamestate");
    GameState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    ~GameState();
    GameState(const GameState& state);
    GameState& operator=(GameState&& state);
    virtual void onStateEnter(vector<string> params);
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
    MapValidatedState(std::string _name, std::vector<std::string> _cmds);
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
    virtual void onStateEnter();
    virtual void onStateExit();
};

class IssueOrdersState : public GameState
{
public:
    IssueOrdersState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    IssueOrdersState(const IssueOrdersState &state);
    ~IssueOrdersState();
    virtual void onStateEnter();
    virtual void onStateExit();
};

class ExecuteOrdersState : public GameState
{
public:
    ExecuteOrdersState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine);
    ExecuteOrdersState(const ExecuteOrdersState &state);
    ~ExecuteOrdersState();
    virtual void onStateEnter();
    virtual void onStateExit();
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
    CommandProcessor* cmdProcessor;

    const std::string PLAY_CMD = "play";
    const std::string LOAD_MAP_CMD = "loadmap";
    const std::string VALIDATE_MAP_CMD = "validatemap";
    const std::string ADD_PLAYER_CMD = "addplayer";
    const std::string GAMESTART_CMD = "gamestart";
    const std::string ISSUE_ORDER_CMD = "issueorder";
    const std::string END_ISSUE_ORDERS_CMD = "endissueorders";
    const std::string EXEC_ORDER_CMD = "execorder";
    const std::string END_EXEC_ORDERS_CMD = "endexecorders";
    const std::string WIN_CMD = "win";
    const std::string QUIT_CMD = "quit";
    const std::string EXIT_CMD = "exit";
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
    bool ExecuteCmd(Command* cmd);
    void SetState(GameState* state, vector<string> params);
    void PrintMapFiles();

public:
    GameEngine();
    GameEngine(CommandProcessor* _cmdProcessor);
    ~GameEngine();
    GameEngine(const GameEngine& engine);
    GameEngine& operator=(GameEngine&& gameEngine);

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
    void SetCmdProcessor(CommandProcessor* _cmdProcessor);
    string stringToLog();
};

#endif