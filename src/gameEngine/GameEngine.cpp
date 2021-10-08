#include "GameEngine.h"

class GameEngine
{
    public:

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

    static GameState* currentState;

    GameEngine(){
        
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
        TransitionCommand endCmd(END_CMD, endState);

        startState = &StartState ("start", {&loadmapCmd});
        mapLoadedState = &MapLoadedState("map loaded", {&loadmapCmd, &validateMapCmd});
        mapValidatedState = &MapValidatedState("map validated", {&addPlayerCmd});
        playersAddedState = &PlayersAddedState("players added", {&addPlayerCmd, &assignCountriesCmd});
        assignReinforcementState = &AssignReinforcementState("assign reinforcement", {&issueorderCmd});
        issueOrdersState = &IssueOrdersState("issue orders", {&issueorderCmd, &endissueordersCmd});
        executeOrdersState = &ExecuteOrdersState("execute orders", {&execorderCmd, &endexecordersCmd, &winCmd});
        winState = &WinState("win", {&playCmd, &endCmd});
        endState = &EndState("end", {});

        std::cout << "Game Engine init" << std::endl;

        TransitionTo(startState);

        /*
        cmds[playCmd.id]= &playCmd;
        cmds[loadmapCmd.id]= &(loadmapCmd);
        cmds[validateMapCmd.id]= &validateMapCmd;
        cmds[addPlayerCmd.id]= &addPlayerCmd;
        cmds[assignCountriesCmd.id]= &assignCountriesCmd;
        cmds[issueorderCmd.id]= &issueorderCmd;
        cmds[endissueordersCmd.id]= &endissueordersCmd;
        cmds[execorderCmd.id]= &execorderCmd;
        cmds[endexecordersCmd.id]= &endexecordersCmd;
        cmds[winCmd.id]= &winCmd;
        cmds[endCmd.id]= &endCmd;
        */
    };

    static bool ExecuteCmd(std::string cmdID){
        
        //Check if the command is valid
        std::map<std::string, Command*> cmds = (*currentState).cmds;
        std::map<std::string, Command*> cmds = (*currentState).cmds;

        std::map<std::string, Command*>::iterator cmd = (*currentState).cmds.find(cmdID);
        if (cmd != (*currentState).cmds.end()){
            //std::cout << "Command '" << cmdID << "' not found." << std::endl;
            cmd->second->Execute();
            return true;
        } else
            std::cout << "Command '" << cmdID << "' not found." << std::endl;
            return NULL;
    }

    static void TransitionTo(GameState* nextState){
        if(currentState != NULL) currentState->OnStateExit();
        currentState = nextState;
        if(currentState != NULL) currentState->OnStateEnter();
    }
};

class GameState
{
    public:

    std::string name;
    std::map<std::string, Command*> cmds;

    GameState(std::string _name, std::vector<Command*> _cmds){
        name = _name;
        for(Command* cmd : _cmds)
            cmds[(*cmd).id] = cmd;
    }

    virtual void OnStateEnter(){
        std::cout << "Entered gamestate " << name << "." << std::endl;
    }

    virtual void OnStateExit(){
        std::cout << "Exited gamestate " << name << "." << std::endl;
    }
};

class StartState : public GameState
{
    public:

    StartState(std::string _name, std::vector<Command*> _cmds) : GameState(_name, _cmds) {
    }

    /*
    void OnStateEnter(){
        GameState::OnStateEnter();
    }

    void OnStateExit(){
        GameState::OnStateExit();
    }*/
};

class MapLoadedState : public GameState
{
    public:
    
    MapLoadedState(std::string _name, std::vector<Command*> _cmds) : GameState(_name, _cmds) {
    }

    void OnStateEnter(){
        GameState::OnStateEnter();
    }

    void OnStateExit(){
        GameState::OnStateExit();
    }
};

class MapValidatedState : public GameState
{
    public:
    
    MapValidatedState(std::string _name, std::vector<Command*> _cmds) : GameState(_name, _cmds) {
    }
};

class PlayersAddedState : public GameState
{
    public:
    
    PlayersAddedState(std::string _name, std::vector<Command*> _cmds) : GameState(_name, _cmds) {
    }
};

class AssignReinforcementState : public GameState
{
    public:
    
    AssignReinforcementState(std::string _name, std::vector<Command*> _cmds) : GameState(_name, _cmds) {
    }
};

class IssueOrdersState : public GameState
{
    public:
    
    IssueOrdersState(std::string _name, std::vector<Command*> _cmds) : GameState(_name, _cmds) {
    }
};

class ExecuteOrdersState : public GameState
{
    public:
    
    ExecuteOrdersState(std::string _name, std::vector<Command*> _cmds) : GameState(_name, _cmds) {
    }
};

class WinState : public GameState
{
    public:
    
    WinState(std::string _name, std::vector<Command*> _cmds) : GameState(_name, _cmds) {
    }
};

class EndState : public GameState
{
    public:
    
    EndState(std::string _name, std::vector<Command*> _cmds) : GameState(_name, _cmds) {
    }
};

class Command
{
    public:

    std::string id;

    Command(const std::string _id){
        id = _id;

    }

    virtual void Execute() = 0;
};

class TransitionCommand : public Command
{
    public:

    TransitionCommand(std::string _id, GameState* _state) : Command{_id} {
        state = _state;
    }

    void Execute(){
        GameEngine::TransitionTo(state);
    }

    private:

    GameState* state;
};