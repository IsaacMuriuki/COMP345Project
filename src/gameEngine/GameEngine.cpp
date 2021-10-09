#include "GameEngine.h"

GameEngine::GameEngine(){
    
    startState = &StartState ("start", {LOAD_MAP_CMD});
    mapLoadedState = &MapLoadedState("map loaded", {LOAD_MAP_CMD, VALIDATE_MAP_CMD});
    mapValidatedState = &MapValidatedState("map validated", {ADD_PLAYER_CMD});
    playersAddedState = &PlayersAddedState("players added", {ADD_PLAYER_CMD, ASSIGN_COUNTRIES_CMD});
    assignReinforcementState = &AssignReinforcementState("assign reinforcement", {ISSUE_ORDER_CMD});
    issueOrdersState = &IssueOrdersState("issue orders", {ISSUE_ORDER_CMD, END_ISSUE_ORDERS_CMD});
    executeOrdersState = &ExecuteOrdersState("execute orders", {EXEC_ORDER_CMD, END_EXEC_ORDERS_CMD, WIN_CMD});
    winState = &WinState("win", {PLAY_CMD, END_CMD});
    endState = &EndState("end", {});

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

    std::cout << "Game Engine initialized." << std::endl;
    std::cout << "Start State: " << startState->stateID << std::endl;
};

void GameEngine::Run(){
    
    SetState(startState);
    std::cout << "Current state: " << currentState->stateID;

    while(running){
        
    }

    std::cout << "End of program." << std::endl;
}

void GameEngine::ListenForCommand(){

}

bool GameEngine::ExecuteCmd(std::string cmdID){

    //Check if the current state has a matching command ID
    if(std::find(currentState->cmds.begin(), currentState->cmds.end(), cmdID) != currentState->cmds.end()) {
        //Check if the command is valid
        std::map<std::string, GameState*>::iterator cmd = cmds.find(cmdID);
        if (cmd != cmds.end()){
            //std::cout << "Command '" << cmdID << "' not found." << std::endl;
            TransitionTo(cmd->second);
            return true;
        } else {
            std::cout << "Command '" << cmdID << "' not found." << std::endl;
            return NULL;
        }
    } else{
        std::cout << "State '" << currentState->stateID << "' doesn't recognize command '" << cmdID << "' found." << std::endl;
        return NULL;
    }
}

void GameEngine::SetState(GameState* nextState){
    currentState = nextState;
    if(currentState != NULL) currentState->OnStateEnter();
}

void GameEngine::TransitionTo(GameState* nextState){
    if(currentState != NULL) currentState->OnStateExit();
    SetState(nextState);
}

GameState::GameState(std::string _stateID, std::vector<std::string> _cmds){
    stateID = _stateID;
    cmds = _cmds;
    std::cout << "State '"<< stateID << "' initialized" << std::endl;
}

void GameState::OnStateEnter(){
    std::cout << "Entered gamestate '" << stateID << "'." << std::endl;
}

void GameState::OnStateExit(){
    std::cout << "Exited gamestate '" << stateID << "'." << std::endl;
}

StartState::StartState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }

MapLoadedState::MapLoadedState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }

MapValidatedState::MapValidatedState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }

PlayersAddedState::PlayersAddedState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }

AssignReinforcementState::AssignReinforcementState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }

IssueOrdersState::IssueOrdersState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }

ExecuteOrdersState::ExecuteOrdersState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }

WinState::WinState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }

EndState::EndState(std::string _stateID, std::vector<std::string> _cmds) : GameState(_stateID, _cmds) { }

void EndState::OnStateEnter(){
    GameState::OnStateEnter();
    //gameEngine.running = false;
}
