#include "GameEngine.h"

GameEngine::GameEngine(){
    
    /*
    TransitionCommand playCmd(PLAY_CMD, startState);
    TransitionCommand loadmapCmd(LOAD_MAP_CMD, mapLoadedState);
    TransitionCommand validateMapCmd(VALIDATE_MAP_CMD, mapValidatedState);
    TransitionCommand addPlayerCmd(ADD_PLAYER_CMD, playersAddedState);
    TransitionCommand assignCountriesCmd(ASSIGN_COUNTRIES_CMD, assignReinforcementState);
    TransitionCommand issueorderCmd(ISSUE_ORDER_CMD, issueOrdersState);
    TransitionCommand endissueordersCmd(END_ISSUE_ORDERS_CMD, executeOrdersState);
    TransitionCommand execorderCmd(EXEC_ORDER_CMD, executeOrdersState);
    TransitionCommand endexecordersCmd(END_EXEC_ORDERS_CMD, assignReinforcementState);
    TransitionCommand winCmd(WIN_CMD, winState);
    TransitionCommand endCmd(END_CMD, endState);*/

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

    std::cout << "Game Engine init" << std::endl;

    SetState(startState);
};

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
        std::cout << "State '" << currentState->name << "' doesn't recognize command '" << cmdID << "' found." << std::endl;
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

GameState::GameState(std::string _name, std::vector<std::string> _cmds){
    name = _name;
    cmds = _cmds;
}

void GameState::OnStateEnter(){
    std::cout << "Entered gamestate " << name << "." << std::endl;
}

void GameState::OnStateExit(){
    std::cout << "Exited gamestate " << name << "." << std::endl;
}

StartState::StartState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }

MapLoadedState::MapLoadedState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }

MapValidatedState::MapValidatedState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }

PlayersAddedState::PlayersAddedState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }

AssignReinforcementState::AssignReinforcementState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }

IssueOrdersState::IssueOrdersState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }

ExecuteOrdersState::ExecuteOrdersState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }

WinState::WinState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }

EndState::EndState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }
