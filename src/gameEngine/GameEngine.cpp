#include "GameEngine.h"

// GameEngine class definition

GameEngine::GameEngine()
{

    //Initializing all pointers to their respective game states

    startState = new StartState("start", {LOAD_MAP_CMD}, this);
    mapLoadedState = new MapLoadedState("map loaded", {LOAD_MAP_CMD, VALIDATE_MAP_CMD}, this);
    mapValidatedState = new MapValidatedState("map validated", {ADD_PLAYER_CMD}, this);
    playersAddedState = new PlayersAddedState("players added", {ADD_PLAYER_CMD, ASSIGN_COUNTRIES_CMD}, this);
    assignReinforcementState = new AssignReinforcementState("assign reinforcement", {ISSUE_ORDER_CMD}, this);
    issueOrdersState = new IssueOrdersState("issue orders", {ISSUE_ORDER_CMD, END_ISSUE_ORDERS_CMD}, this);
    executeOrdersState = new ExecuteOrdersState("execute orders", {EXEC_ORDER_CMD, END_EXEC_ORDERS_CMD, WIN_CMD}, this);
    winState = new WinState("win", {PLAY_CMD, END_CMD}, this);

    SetCommands();

    std::cout << "\nGame Engine initialized." << std::endl;
};

GameEngine::~GameEngine()
{

    delete startState;
    delete mapLoadedState;
    delete mapValidatedState;
    delete playersAddedState;
    delete assignReinforcementState;
    delete issueOrdersState;
    delete executeOrdersState;
    delete winState;

    cmds.clear();
};

GameEngine::GameEngine(const GameEngine &engine)
{
    running = engine.running;

    startState = (StartState *)engine.startState->clone();
    mapLoadedState = (MapLoadedState *)engine.mapLoadedState->clone();
    mapValidatedState = (MapValidatedState *)engine.mapValidatedState->clone();
    playersAddedState = (PlayersAddedState *)engine.playersAddedState->clone();
    assignReinforcementState = (AssignReinforcementState *)engine.assignReinforcementState->clone();
    issueOrdersState = (IssueOrdersState *)engine.issueOrdersState->clone();
    executeOrdersState = (ExecuteOrdersState *)engine.executeOrdersState->clone();
    winState = (WinState *)engine.winState->clone();

    SetCommands();
}

GameEngine &GameEngine::operator=(GameEngine &&engine)
{
    if (this != &engine)
    {
        running = engine.running;

        startState = engine.startState;
        mapLoadedState = engine.mapLoadedState;
        mapValidatedState = engine.mapValidatedState;
        playersAddedState = engine.playersAddedState;
        assignReinforcementState = engine.assignReinforcementState;
        issueOrdersState = engine.issueOrdersState;
        executeOrdersState = engine.executeOrdersState;
        winState = engine.winState;

        currentState = engine.currentState;

        cmds = engine.cmds;
    }
    return *this;
}

/**
 * Assigns commands to pointers to the state they lead to.
 **/

void GameEngine::SetCommands()
{
    //Adding the pair of command strings and a pointer to the state they lead to to a <string, GameState*>

    cmds.clear();

    cmds[PLAY_CMD] = startState;
    cmds[LOAD_MAP_CMD] = mapLoadedState;
    cmds[VALIDATE_MAP_CMD] = mapValidatedState;
    cmds[ADD_PLAYER_CMD] = playersAddedState;
    cmds[ASSIGN_COUNTRIES_CMD] = assignReinforcementState;
    cmds[ISSUE_ORDER_CMD] = issueOrdersState;
    cmds[END_ISSUE_ORDERS_CMD] = executeOrdersState;
    cmds[EXEC_ORDER_CMD] = executeOrdersState;
    cmds[END_EXEC_ORDERS_CMD] = assignReinforcementState;
    cmds[WIN_CMD] = winState;
}

/**
 * Starts the main GameEngine loop.
 **/

void GameEngine::Run()
{
    startupPhase();

    //Program loops until reaching the end command is executed
    while (running)
    {

        //Take in the user input
        std::string cmd;
        std::cout << "\nEnter your command: " << std::endl;
        std::cin.clear();
        std::cin.sync();

        std::cin >> cmd;
        std::cout << std::endl;

        //Validates the command and execute the appropriate state transition
        ExecuteCmd(cmd);
    }

    std::cout << "\nEnd of program." << std::endl;
}

/**
 * Check if the cmdID string corresponds to a valid command in the GameEngine that is allowed by the current game state.
 * If the command is valid, executes it.
 * 
 * @return true if the command was validated and executed; false otherwise.
 **/

bool GameEngine::ExecuteCmd(std::string cmdID)
{

    //Check if the current state has a matching command ID
    std::vector<std::string> stateCmds = currentState->getCmds();
    if (std::find(stateCmds.begin(), stateCmds.end(), cmdID) != stateCmds.end())
    {

        //Check if the current state considers the command valid
        if (cmdID == END_CMD)
        {
            running = false;
            return true;
        }

        std::map<std::string, GameState *>::iterator cmd = cmds.find(cmdID);
        if (cmd != cmds.end())
        {
            TransitionTo(cmd->second); //If the command is valid, transition to the state the command points to
            return true;
        }
        else
        {
            std::cout << "Command '" << cmdID << "' not found." << std::endl; //Otherwise, prints an error message
            return false;
        }
    }
    else
    {
        //If the current state does not consider the command valid, prints an error message
        std::cout << "State '" << currentState->getName() << "' doesn't recognize command '" << cmdID << "'." << std::endl;
        return false;
    }
}

/**
 * Sets the current game state of the GameEngine to a new state.
 **/

void GameEngine::SetState(GameState *nextState)
{
    currentState = nextState;
    if (currentState != nullptr)
        currentState->onStateEnter();
}

/**
 * Exit the current game state and sets a new state as the current game state of the GameEngine.
 **/

void GameEngine::TransitionTo(GameState *nextState)
{
    if (currentState != nullptr)
        currentState->onStateExit();
    SetState(nextState);

    // Notifies observer of the new game state.
    Notify(this);
}

std::ostream &operator<<(std::ostream &os, const GameEngine &engine)
{
    os << "Game Engine - current state: " << engine.currentState;
    return os;
}

bool GameEngine::isRunning() { return running; }

GameState *GameEngine::getCurrentState() { return currentState; }

std::map<std::string, GameState *> GameEngine::getCmds() { return cmds; }

Map *GameEngine::getMap() { return gameMap; }

void GameEngine::setMap(Map *m)
{
    gameMap = m;
}

vector<Player *> GameEngine::getPlayers() { return playersList; }

void GameEngine::addPlayer(Player *player)
{
    playersList.push_back(player);
}

GameEngine *GameEngine::clone() { return new GameEngine(*this); }

void GameEngine::startupPhase()
{
    MapLoader loader;
    Map *map;
    bool gameStarted = false;
    ;
    //Sets the startState as the current state
    SetState(startState);
    PrintMapFiles();

    //Program loops until reaching the end command is executed
    while (running && !gameStarted)
    {
        //Take in the user input
        std::string cmd;
        std::cout << "\nEnter your command: " << std::endl;
        std::cin >> cmd;

        if (cmd == "loadmap")
        {
            string filename;
            std::cin >> filename;
            map = loader.loadMap(MAPS_FOLDER + filename);
            if (map != NULL)
            {
                setMap(map);
                cout << "Map "
                     << "'" << filename << "'"
                     << " is loaded. Please validate it" << endl;
                if (currentState->getName() == "map loaded")
                {
                    continue;
                }
            }
            else
            {
                cout << "Invalid file, please select another map file" << endl;
                continue;
            }
        }
        else if (cmd == "validatemap")
        {
            if (map->validate())
            {
                cout << "Map is valid" << endl;
                cout << *map << endl;
                cout << "Add players into the game(2-6 players).\nEnter: addplayer <playername>\n";
            }
            else
            {
                cout << "Map is invalid, please select another map file" << endl;
                PrintMapFiles();
                continue; // don't execute command if invalid
            }
        }
        else if (cmd == "addplayer")
        {
            string playername;
            std::cin >> playername;
            Player *player = new Player(playername);
            addPlayer(player);
            cout << "Player " << playername << " added" << endl;
            if (currentState->getName() == "players added")
            {
                continue;
            }
        }
        else if (cmd == "gamestart")
        {
            // do stuffs
            gameStarted = true;
        }
        else
        {
            //temp error msg
            cout << "Invalid command" << endl;
        }

        //Validates the command and execute the appropriate state transition
        ExecuteCmd(cmd);
    }
}

void GameEngine::PrintMapFiles()
{
    for (const auto &entry : fs::directory_iterator(MAPS_FOLDER))
    {
        cout << entry.path().filename() << endl;
    }
    std::cout << "Please select the map file you would like to load from the following options.\nEnter: loadmap <filename>" << std::endl;
}

/**
 * Returns an entry of the new game state to be logged.
 * 
 * @return entry as a string.
 * */
string GameEngine::stringToLog()
{
    stringstream ss;
    ss << "Game Engine new state: " << *currentState;
    return ss.str();
}

// GameState class definition

GameState::GameState(std::string _name)
{
    name = _name;
}

GameState::GameState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine)
{
    name = _name;
    cmds = _cmds;
    gameEngine = _gameEngine;
}

GameState::~GameState()
{
    cmds.clear();
};

GameState::GameState(const GameState &state) : GameState(state.name, state.cmds, state.gameEngine) {}

GameState &GameState::operator=(GameState &&state)
{
    if (this != &state)
    {
        name = state.name;
        cmds = state.cmds;
        gameEngine = state.gameEngine;
    }
    return *this;
}

/**
 * Method executed upon entering the state. Is meant to be overitten to implement the functionality specific to each game state.
 **/
void GameState::onStateEnter()
{
    std::cout << "Entered gamestate '" << name << "'." << std::endl;
}

/**
 * Method executed upon exiting the state. Is meant to be overitten to implement the functionality specific to each game state.
 **/
void GameState::onStateExit()
{
    std::cout << "Exited gamestate '" << name << "'." << std::endl;
}

std::ostream &operator<<(std::ostream &os, const GameState &state)
{
    os << state.name << " state";
    return os;
}

std::string GameState::getName() { return name; }
std::vector<std::string> GameState::getCmds() { return cmds; }

GameState *GameState::clone() { return new GameState(*this); }

// StartState class definition
StartState::StartState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine) : GameState(_name, _cmds, _gameEngine) {}
StartState::~StartState(){};
StartState::StartState(const StartState &state) : StartState(state.name, state.cmds, state.gameEngine) {}

// MapLoadedState class definition

MapLoadedState::MapLoadedState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine) : GameState(_name, _cmds, _gameEngine) {}
MapLoadedState::~MapLoadedState(){};
MapLoadedState::MapLoadedState(const MapLoadedState &state) : MapLoadedState(state.name, state.cmds, state.gameEngine) {}

// MapValidatedState class definition

MapValidatedState::MapValidatedState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine) : GameState(_name, _cmds, _gameEngine) {}
MapValidatedState::~MapValidatedState(){};
MapValidatedState::MapValidatedState(const MapValidatedState &state) : MapValidatedState(state.name, state.cmds, state.gameEngine) {}

// PlayersAddedState class definition

PlayersAddedState::PlayersAddedState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine) : GameState(_name, _cmds, _gameEngine) {}
PlayersAddedState::~PlayersAddedState(){};
PlayersAddedState::PlayersAddedState(const PlayersAddedState &state) : PlayersAddedState(state.name, state.cmds, state.gameEngine) {}

// AssignReinforcementState class definition

AssignReinforcementState::AssignReinforcementState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine) : GameState(_name, _cmds, _gameEngine) {}
AssignReinforcementState::~AssignReinforcementState(){};
AssignReinforcementState::AssignReinforcementState(const AssignReinforcementState &state) : AssignReinforcementState(state.name, state.cmds, state.gameEngine) {}

// IssueOrdersState class definition

IssueOrdersState::IssueOrdersState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine) : GameState(_name, _cmds, _gameEngine) {}
IssueOrdersState::~IssueOrdersState(){};
IssueOrdersState::IssueOrdersState(const IssueOrdersState &state) : IssueOrdersState(state.name, state.cmds, state.gameEngine) {}

// ExecuteOrdersState class definition

ExecuteOrdersState::ExecuteOrdersState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine) : GameState(_name, _cmds, _gameEngine) {}
ExecuteOrdersState::~ExecuteOrdersState(){};
ExecuteOrdersState::ExecuteOrdersState(const ExecuteOrdersState &state) : ExecuteOrdersState(state.name, state.cmds, state.gameEngine) {}

// WinState class definition

WinState::WinState(std::string _name, std::vector<std::string> _cmds, GameEngine *_gameEngine) : GameState(_name, _cmds, _gameEngine) {}
WinState::~WinState(){};
WinState::WinState(const WinState &state) : WinState(state.name, state.cmds, state.gameEngine) {}