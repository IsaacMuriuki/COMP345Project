#include "GameEngine.h"

// GameEngine class definition

GameEngine::GameEngine(){
    
    //Initializing all pointers to their respective game states

    startState = new StartState ("start", {LOAD_MAP_CMD});
    mapLoadedState = new MapLoadedState("map loaded", {LOAD_MAP_CMD, VALIDATE_MAP_CMD});
    mapValidatedState = new MapValidatedState("map validated", {ADD_PLAYER_CMD});
    playersAddedState = new PlayersAddedState("players added", {ADD_PLAYER_CMD, ASSIGN_COUNTRIES_CMD});
    assignReinforcementState = new AssignReinforcementState("assign reinforcement", {ISSUE_ORDER_CMD});
    issueOrdersState = new IssueOrdersState("issue orders", {ISSUE_ORDER_CMD, END_ISSUE_ORDERS_CMD});
    executeOrdersState = new ExecuteOrdersState("execute orders", {EXEC_ORDER_CMD, END_EXEC_ORDERS_CMD, WIN_CMD});
    winState = new WinState("win", {PLAY_CMD, END_CMD});
    endState = new EndState("end", {});

    //Adding the pair of command strings and a pointer to the state they lead to to a <string, GameState*>

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
    cmds[END_CMD] = endState;

    std::cout << "\nGame Engine initialized." << std::endl;
};

GameEngine::~GameEngine(){};

GameEngine& GameEngine::operator=(GameEngine&& gameEngine) {
    if (this != &gameEngine) {
        running = gameEngine.running;

        startState = gameEngine.startState;
        mapLoadedState = gameEngine.mapLoadedState;
        mapValidatedState = gameEngine.mapValidatedState;
        playersAddedState = gameEngine.playersAddedState;
        assignReinforcementState = gameEngine.assignReinforcementState;
        issueOrdersState = gameEngine.issueOrdersState;
        executeOrdersState = gameEngine.executeOrdersState;
        winState = gameEngine.winState;
        endState = gameEngine.endState;

        currentState = gameEngine.currentState;

        cmds = gameEngine.cmds;
    }
    return *this;
}

/**
 * Starts the main GameEngine loop.
 **/

void GameEngine::Run(){
    
    //Sets the startState as the current state
    SetState(startState);

    //Program loops until reaching the end state 
    while(running){
        
        //Take in the user input
        std::string cmd;
        std::cout << "\nEnter your command: " << std::endl;
        std::cin.clear(); 
        std::cin.sync();
        std::cin >> cmd; 
        std::cout << std::endl;

        //Validates the command and execute the appropriate state transition
        ExecuteCmd(cmd);
        
        //Stops the loop if the current state is the end state
        running = currentState != endState;
    }

    std::cout << "\nEnd of program." << std::endl;
}

/**
 * Check if the cmdID string corresponds to a valid command in the GameEngine that is allowed by the current game state.
 * If the command is valid, executes it.
 * 
 * @return true if the command was validated and executed; false otherwise.
 **/

bool GameEngine::ExecuteCmd(std::string cmdID){

    //Check if the current state has a matching command ID
    if(std::find(currentState->cmds.begin(), currentState->cmds.end(), cmdID) != currentState->cmds.end()) {
        //Check if the current state considers the command valid
        std::map<std::string, GameState*>::iterator cmd = cmds.find(cmdID);
        if (cmd != cmds.end()){
            TransitionTo(cmd->second); //If the command is valid, transition to the state the command points to
            return true;
        } else {
            std::cout << "Command '" << cmdID << "' not found." << std::endl; //Otherwise, prints an error message
            return false;
        }
    } else{
        //If the current state does not consider the command valid, prints an error message
        std::cout << "State '" << currentState->stateID << "' doesn't recognize command '" << cmdID << "'." << std::endl; 
        return false;
    }
}

/**
 * Sets the current game state of the GameEngine to a new state.
 **/

void GameEngine::SetState(GameState* nextState){
    currentState = nextState;
    if(currentState != NULL) currentState->OnStateEnter();
}

/**
 * Exit the current game state and sets a new state as the current game state of the GameEngine.
 **/

void GameEngine::TransitionTo(GameState* nextState){
    if(currentState != NULL) currentState->OnStateExit();
    SetState(nextState);
}

// GameState class definition

GameState::GameState(std::string _stateID, std::vector<std::string> _cmds){
    stateID = _stateID;
    cmds = _cmds;
}

GameState::~GameState(){};

/**
 * Method executed upon entering the state. Is meant to be overitten to implement the functionality specific to each game state.
 **/

void GameState::OnStateEnter(){
    std::cout << "Entered gamestate '" << stateID << "'." << std::endl;
}

/**
 * Method executed upon exiting the state. Is meant to be overitten to implement the functionality specific to each game state.
 **/

void GameState::OnStateExit(){
    std::cout << "Exited gamestate '" << stateID << "'." << std::endl;
}

// StartState class definition

StartState::StartState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }
StartState::~StartState(){};

// MapLoadedState class definition

MapLoadedState::MapLoadedState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }
MapLoadedState::~MapLoadedState(){};

// MapValidatedState class definition

MapValidatedState::MapValidatedState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }
MapValidatedState::~MapValidatedState(){};

// PlayersAddedState class definition

PlayersAddedState::PlayersAddedState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }
PlayersAddedState::~PlayersAddedState(){};

// AssignReinforcementState class definition

AssignReinforcementState::AssignReinforcementState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }
AssignReinforcementState::~AssignReinforcementState(){};

// IssueOrdersState class definition

IssueOrdersState::IssueOrdersState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }
IssueOrdersState::~IssueOrdersState(){};

// ExecuteOrdersState class definition

ExecuteOrdersState::ExecuteOrdersState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }
ExecuteOrdersState::~ExecuteOrdersState(){};

// WinState class definition

WinState::WinState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }
WinState::~WinState(){};

// EndState class definition

EndState::EndState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }
EndState::~EndState(){};
