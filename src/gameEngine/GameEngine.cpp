#include "GameEngine.h"
#include "CommandProcessor.h"

// GameEngine class definition
// 
//Dummy Data

Continent NA = Continent(0, "NA", 4);
Territory CANADA = Territory(0, "CANADA", &NA);
Territory US = Territory(1, "US", &NA);
Territory MEXICO = Territory(2, "MEXICO", &NA);
std::vector<Player> playerList;






using std::cout, std::cin, std::endl, std::vector, std::string;

GameEngine::GameEngine(){
    
    //Initializing all pointers to their respective game states

    startState = new StartState ("start", {LOAD_MAP_CMD, EXIT_CMD});
    mapLoadedState = new MapLoadedState("map loaded", {LOAD_MAP_CMD, VALIDATE_MAP_CMD, EXIT_CMD});
    mapValidatedState = new MapValidatedState("map validated", {ADD_PLAYER_CMD, EXIT_CMD});
    playersAddedState = new PlayersAddedState("players added", {ADD_PLAYER_CMD, GAMESTART_CMD, EXIT_CMD});
    assignReinforcementState = new AssignReinforcementState("assign reinforcement", {ISSUE_ORDER_CMD, EXIT_CMD});
    issueOrdersState = new IssueOrdersState("issue orders", {ISSUE_ORDER_CMD, END_ISSUE_ORDERS_CMD, EXIT_CMD});
    executeOrdersState = new ExecuteOrdersState("execute orders", {EXEC_ORDER_CMD, END_EXEC_ORDERS_CMD, WIN_CMD, EXIT_CMD});
    winState = new WinState("win", {PLAY_CMD, QUIT_CMD, EXIT_CMD});

    CANADA.addAdjacentTerritory(&US);
    US.addAdjacentTerritory(&CANADA);
    US.addAdjacentTerritory(&MEXICO);
    MEXICO.addAdjacentTerritory(&US);

    NA.addTerritory(&US);
    NA.addTerritory(&CANADA);
    NA.addTerritory(&MEXICO);

    Deck deck = Deck();
    Hand hand1 = Hand();
    Hand hand2 = Hand();
    CardType temp;
    for (int i = 0; i < 5; i++) {
        temp = deck.draw();
        hand1.setHand(i, temp);
        temp = deck.draw();
        hand2.setHand(i, temp);
    }
    playerList.push_back(Player());
    playerList.push_back(Player());
    playerList.push_back(Player());
    playerList[0].setHandOfCards(&hand1);
    playerList[1].setHandOfCards(&hand2);
    playerList[1].addTerritory(&CANADA);
    playerList[0].setName("Ted");
    playerList[0].addTerritory(&US);
    playerList[1].addTerritory(&MEXICO);
    playerList[1].setName("Hillary");
    playerList[2].setName("Terry");


    SetCommands();

    currentState = nullptr;

    std::cout << "\nGame Engine initialized." << std::endl;
};

GameEngine::GameEngine(CommandProcessor* _cmdProcessor) : GameEngine(){
    SetCmdProcessor(_cmdProcessor);
}

GameEngine::~GameEngine(){

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

GameEngine::GameEngine(const GameEngine& engine) { 
    running = engine.running;

    startState = (StartState*) engine.startState->clone();
    mapLoadedState = (MapLoadedState*) engine.mapLoadedState->clone();
    mapValidatedState = (MapValidatedState*) engine.mapValidatedState->clone();
    playersAddedState = (PlayersAddedState*) engine.playersAddedState->clone();
    assignReinforcementState = (AssignReinforcementState*) engine.assignReinforcementState->clone();
    issueOrdersState = (IssueOrdersState*) engine.issueOrdersState->clone();
    executeOrdersState = (ExecuteOrdersState*) engine.executeOrdersState->clone();
    winState = (WinState*) engine.winState->clone();

    SetCommands();
}

GameEngine& GameEngine::operator=(GameEngine&& engine) {
    if (this != &engine) {
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

void GameEngine::SetCommands(){
    //Adding the pair of command strings and a pointer to the state they lead to to a <string, GameState*>

    cmds.clear();

    cmds[PLAY_CMD] = startState;
    cmds[LOAD_MAP_CMD] = mapLoadedState;
    cmds[VALIDATE_MAP_CMD] = mapValidatedState;
    cmds[ADD_PLAYER_CMD] = playersAddedState;
    cmds[GAMESTART_CMD] = assignReinforcementState;
    cmds[ISSUE_ORDER_CMD] = issueOrdersState;
    cmds[END_ISSUE_ORDERS_CMD] = executeOrdersState;
    cmds[EXEC_ORDER_CMD] = executeOrdersState;
    cmds[END_EXEC_ORDERS_CMD] = assignReinforcementState;
    cmds[WIN_CMD] = winState;
}

/**
 * Starts the main GameEngine loop.
 **/

void GameEngine::Run(){

    //Sets the startState as the current state
    SetState(startState, {});
    
    //Program loops until reaching the end command is executed 
    while(running){
        
        Command* cmd = cmdProcessor->getCommand();
        //Validates the command and execute the appropriate state transition
        if(cmd) ExecuteCmd(cmd);
    }

    std::cout << "\nEnd of program." << std::endl;
}

/**
 * Check if the cmdID string corresponds to a valid command in the GameEngine that is allowed by the current game state.
 * If the command is valid, executes it.
 * 
 * @return true if the command was validated and executed; false otherwise.
 **/

bool GameEngine::ExecuteCmd(Command* command){

        std::string cmdID = command->getEffect();

        if(cmdID == QUIT_CMD || cmdID == EXIT_CMD){
            running = false;
            return true;
        }
        
        std::map<std::string, GameState*>::iterator cmd = cmds.find(cmdID);
        if (cmd != cmds.end()){
            SetState(cmd->second, command->getParams()); //If the command is valid, transition to the state the command points to
            return true;
        } else {
            std::cout << "Command '" << cmdID << "' not found." << std::endl; //Otherwise, prints an error message
            return false;
        }
}

/**
 * Sets the current game state of the GameEngine to a new state.
 **/
void GameEngine::SetState(GameState* nextState, vector<string> params){
    if(currentState) currentState->onStateExit();
    currentState = nextState;
    if(currentState) currentState->onStateEnter(params);
}

std::ostream& operator<<(std::ostream& os, const GameEngine& engine)
{
    os << "Game Engine - current state: " << engine.currentState;
    return os;
}

bool GameEngine::isRunning(){return running;}
GameState* GameEngine::getCurrentState(){ return currentState;}
std::map<std::string, GameState*> GameEngine::getCmds(){return cmds;}

GameEngine* GameEngine::clone() { return new GameEngine(*this); }

void GameEngine::SetCmdProcessor(CommandProcessor* _cmdProcessor){
    cmdProcessor = _cmdProcessor;
    cmdProcessor->setGameEngine(this);
}

// GameState class definition

GameState::GameState(std::string _name){
    name = _name;
}

GameState::GameState(std::string _name, std::vector<std::string> _cmds){
    name = _name;
    cmds = _cmds;
}

GameState::~GameState(){
    cmds.clear();
};

GameState::GameState(const GameState& state) : GameState(state.name, state.cmds) { }

GameState& GameState::operator=(GameState&& state){
    if (this != &state){
        name = state.name;
        cmds = state.cmds;
    }
    return *this;
}

/**
 * Method executed upon entering the state. Is meant to be overitten to implement the functionality specific to each game state.
 **/
void GameState::onStateEnter(vector<string> params){
    std::cout << "Entered gamestate '" << name << "'." << std::endl;
}

/**
 * Method executed upon exiting the state. Is meant to be overitten to implement the functionality specific to each game state.
 **/
void GameState::onStateExit(){
    std::cout << "Exited gamestate '" << name << "'." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const GameState& state)
{
    os << state.name << " state";
    return os;
}

std::string GameState::getName() {return name;}
std::vector<std::string> GameState::getCmds() {return cmds;}

GameState* GameState::clone() { return new GameState(*this); }

// StartState class definition

StartState::StartState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }
StartState::~StartState(){};
StartState::StartState(const StartState& state) : StartState(state.name, state.cmds) { }

// MapLoadedState class definition

MapLoadedState::MapLoadedState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }
MapLoadedState::~MapLoadedState(){};
MapLoadedState::MapLoadedState(const MapLoadedState& state) : MapLoadedState(state.name, state.cmds) { }

// MapValidatedState class definition

MapValidatedState::MapValidatedState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }
MapValidatedState::~MapValidatedState(){};
MapValidatedState::MapValidatedState(const MapValidatedState& state) : MapValidatedState(state.name, state.cmds) { }

// PlayersAddedState class definition

PlayersAddedState::PlayersAddedState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }
PlayersAddedState::~PlayersAddedState(){};
PlayersAddedState::PlayersAddedState(const PlayersAddedState& state) : PlayersAddedState(state.name, state.cmds) { }

// AssignReinforcementState class definition

AssignReinforcementState::AssignReinforcementState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) {}
AssignReinforcementState::~AssignReinforcementState(){};
AssignReinforcementState::AssignReinforcementState(const AssignReinforcementState& state) : AssignReinforcementState(state.name, state.cmds) { }

void AssignReinforcementState::onStateEnter() {
    std::cout << "Entered gamestate '" << name << "'." << std::endl; 
    //the ammount of reinforcements a player will have
    int reinforcementCount = 0;
    //displays the countries and their units to the console
    for (Player player : playerList) {
        std::cout << "Player " << player.getName() << " has the following countries with these army counts: " << std::endl;
        for (Territory* territory : player.getTerritories()) {
            std::cout << territory->getName() << " with " << territory->getUnits() << std::endl;
        }
    }
    //Iterates through the players to let them add units to their country
    int choice;
    bool fullContinent = true;
    for (Player player : playerList) {
        if (player.getTerritories().size() == 0) { continue; }
        reinforcementCount = (player.getTerritories().size())/3;
        //checks to see for full continents (right now just NA)
        for (Territory* territory : NA.getTerritories()) {
            bool inContinent = false;
            for (Territory* territoryPlayer : player.getTerritories()) {
                if (territory->getId() == territoryPlayer->getId()) { inContinent = true; }
            }
            if (inContinent == false) { fullContinent = false; }

        }
        if (fullContinent == true) { reinforcementCount = reinforcementCount + NA.getArmyValue(); }
        if (reinforcementCount < 3) reinforcementCount = 3;
        player.setReinforcementPool(player.getReinforcementPool() + reinforcementCount);
    }
}

/**
 * Method executed upon exiting the state. Is meant to be overitten to implement the functionality specific to each game state.
 **/
void AssignReinforcementState::onStateExit() {
    std::cout << "Exited gamestate '" << name << "'." << std::endl;
}

void IssueOrdersState::onStateEnter() {
    for(Player player: playerList){
        player.getPlayersBeingNegotiatedWith().clear();
    }

    for (Player player : playerList) {
        std::cout << "Player " << player.getName() << " has the following countries to attack: " << std::endl;
        for (Territory* territory : player.toAttack()) {
            std::cout << territory->getName() << std::endl;
        }
    }
    for (Player player : playerList) {
        std::cout << "Player " << player.getName() << " has the following countries to defend: " << std::endl;
        for (Territory* territory : player.toDefend()) {
            std::cout << territory->getName() << std::endl;
        }
    }
    for (Player player : playerList) {
        player.issueOrder();
    }
}
void IssueOrdersState::onStateExit() {
    std::cout << "Exited gamestate '" << name << "'." << std::endl;
}

void ExecuteOrdersState::onStateEnter() {
    for (Player player : playerList) {

        for (int i = 0; i < player.getOrdersList()->size(); i++) {
            player.getOrdersList()->get(i)->execute();
        }
    }
}
void ExecuteOrdersState::onStateExit() {
    std::cout << "Exited gamestate '" << name << "'." << std::endl;
    vector <int> indeces;
    int index = 0;
    for (Player player : playerList) {
        if (player.getTerritories().size() == 0) {
            std::cout << "Player " << player.getName() << " has no territories and has been eliminated from the game" << std::endl;
            indeces.push_back(index);
        }
        index++;
    }
    int tempSize = indeces.size();
    for (int i = 0; i < tempSize; i++) {
        playerList.erase(playerList.begin() + indeces.back());
        indeces.pop_back();
    }
    if (playerList.size() == 1) {
        std::cout << "Player " << playerList.at(0).getName() << " has won the game!" << std::endl;
        exit(0);
    }
}

// IssueOrdersState class definition

IssueOrdersState::IssueOrdersState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }
IssueOrdersState::~IssueOrdersState(){};
IssueOrdersState::IssueOrdersState(const IssueOrdersState& state) : IssueOrdersState(state.name, state.cmds) { }

// ExecuteOrdersState class definition

ExecuteOrdersState::ExecuteOrdersState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }
ExecuteOrdersState::~ExecuteOrdersState(){};
ExecuteOrdersState::ExecuteOrdersState(const ExecuteOrdersState& state) : ExecuteOrdersState(state.name, state.cmds) { }

// WinState class definition

WinState::WinState(std::string _name, std::vector<std::string> _cmds) : GameState(_name, _cmds) { }
WinState::~WinState(){};
WinState::WinState(const WinState& state) : WinState(state.name, state.cmds) { }
