#include "game_state.h"
#include <iostream>
#include <unistd.h>

namespace manager {

// ============================================================================
// IGameState
// ============================================================================

std::string IGameState::getName() const {
    switch (type_) {
        case StateType::NONE: return "None";
        case StateType::PROLOGUE: return "Prologue";
        case StateType::PLAYING: return "Playing";
        case StateType::PAUSED: return "Paused";
        case StateType::INVENTORY: return "Inventory";
        case StateType::DIALOG: return "Dialog";
        case StateType::CUTSCENE: return "Cutscene";
        case StateType::GAME_OVER: return "GameOver";
        case StateType::VICTORY: return "Victory";
        case StateType::MENU: return "Menu";
        case StateType::QUIT: return "Quit";
        default: return "Unknown";
    }
}

// ============================================================================
// PrologueState
// ============================================================================

PrologueState::PrologueState(GameStateMachine* machine, const std::string& language)
    : IGameState(machine, StateType::PROLOGUE), language_(language), completed_(false) {}

void PrologueState::onEnter() {
    completed_ = false;
}

void PrologueState::onExit() {
    std::cout << std::endl;
}

void PrologueState::update() {
    // Prologue doesn't need continuous updates
}

void PrologueState::render() {
    if (completed_) return;
    
    if (language_ == "en") {
        std::cout << std::endl << "WELCOME DEAR PLAYER! \n\nTHE CHARMED HOUSE v1.0" << std::endl << std::endl;
        std::cout << "PROLOGUE:" << std::endl;
        
        std::string text1 = "In a village far from the city, there was a ruinous and ancient house since I have eyes to see. As an adventurer that I am, I have had in mind to explore it at all times, but I have never dared. There are signs prohibiting entry in its surroundings. Whoever the owner is, they want intruders to stay away.";
        
        for (char c : text1) {
            usleep(50000);
            std::cout << c << std::flush;
        }
        
        std::cout << std::endl;
        sleep(2);
        
        std::string text2 = "For nights I had been dreaming about that ruined house, imagining what could be inside. One night, in one of my dreams, I glimpsed an unrecognizable human figure. The only thing I could decipher in that enigmatic dream was the call of that entity. It whispered, -Help me!!, help me!!-. From that moment, I could not wait any longer. I had to enter that abandoned house, despite the warnings in the surroundings.";
        
        for (char c : text2) {
            usleep(50000);
            std::cout << c << std::flush;
        }
        
        sleep(3);
        std::cout << std::endl;
        std::cout << "The adventure begins..." << std::endl;
        std::cout << std::endl;
        sleep(4);
    } else {
        std::cout << std::endl << "¡BIENVENIDO QUERIDO JUGADOR! \n\nLA CASA ENCANTADA v1.0" << std::endl << std::endl;
        std::cout << "PRELUDIO:" << std::endl;
        
        std::string text1 = "En un pueblo lejos de la ciudad, había una casa ruinosa y antigua desde que tengo ojos para ver. Como aventurero que soy, he tenido en mente explorarla en todo momento, pero nunca me he atrevido. Existen carteles prohibiendo el paso en sus alrededores. Quien quiera que sea el dueño, desea que los intrusos permanezcan lejos.";
        
        for (char c : text1) {
            usleep(50000);
            std::cout << c << std::flush;
        }
        
        std::cout << std::endl;
        sleep(2);
        
        std::string text2 = "Durante noches había estado soñando con aquella casa en ruinas, imaginando que podría haber en su interior. Una noche, en uno de mis sueños, vislumbré una figura humana irreconocible. Lo único que pude descifrar en aquel enigmático sueño, es la llamada de aquella entidad. Susurraba, -¡Ayúdame!!, ¡ayúdame!!-. Desde aquel momento, no pude esperar más. Debía entrar en aquella casa abandonada, a pesar de las advertencias en los alrededores.";
        
        for (char c : text2) {
            usleep(50000);
            std::cout << c << std::flush;
        }
        
        sleep(3);
        std::cout << std::endl;
        std::cout << "La aventura comienza..." << std::endl;
        std::cout << std::endl;
        sleep(4);
    }
    
    completed_ = true;
}

void PrologueState::handleInput(const std::string& input) {
    // Any input skips prologue
    completed_ = true;
}

// ============================================================================
// PlayingState
// ============================================================================

PlayingState::PlayingState(GameStateMachine* machine)
    : IGameState(machine, StateType::PLAYING), firstEntry_(true) {}

void PlayingState::onEnter() {
    firstEntry_ = true;
}

void PlayingState::onExit() {
    // Save state if needed
}

void PlayingState::update() {
    if (updateCallback_) {
        updateCallback_();
    }
}

void PlayingState::render() {
    if (renderCallback_) {
        renderCallback_();
    }
}

void PlayingState::handleInput(const std::string& input) {
    if (inputCallback_) {
        inputCallback_(input);
    }
}

// ============================================================================
// PausedState
// ============================================================================

PausedState::PausedState(GameStateMachine* machine, const std::string& language)
    : IGameState(machine, StateType::PAUSED), language_(language) {}

void PausedState::onEnter() {
    if (language_ == "en") {
        std::cout << "\n=== GAME PAUSED ===" << std::endl;
        std::cout << "Press ENTER to continue or type 'quit' to exit." << std::endl;
    } else {
        std::cout << "\n=== JUEGO PAUSADO ===" << std::endl;
        std::cout << "Pulsa ENTER para continuar o escribe 'salir' para terminar." << std::endl;
    }
}

void PausedState::onExit() {
    if (language_ == "en") {
        std::cout << "Resuming game..." << std::endl;
    } else {
        std::cout << "Continuando el juego..." << std::endl;
    }
}

void PausedState::update() {
    // Nothing to update while paused
}

void PausedState::render() {
    // Pause screen already rendered in onEnter
}

void PausedState::handleInput(const std::string& input) {
    if (input == "quit" || input == "salir" || input == "exit") {
        machine_->stop();
    } else {
        machine_->popState();
    }
}

// ============================================================================
// GameOverState
// ============================================================================

GameOverState::GameOverState(GameStateMachine* machine, const std::string& language, bool victory)
    : IGameState(machine, StateType::GAME_OVER), language_(language), victory_(victory) {}

void GameOverState::onEnter() {
    std::cout << std::endl;
    if (victory_) {
        if (language_ == "en") {
            std::cout << "╔════════════════════════════════════════╗" << std::endl;
            std::cout << "║         CONGRATULATIONS!               ║" << std::endl;
            std::cout << "║      You have completed the game!      ║" << std::endl;
            std::cout << "╚════════════════════════════════════════╝" << std::endl;
        } else {
            std::cout << "╔════════════════════════════════════════╗" << std::endl;
            std::cout << "║         ¡FELICIDADES!                  ║" << std::endl;
            std::cout << "║      ¡Has completado el juego!         ║" << std::endl;
            std::cout << "╚════════════════════════════════════════╝" << std::endl;
        }
    } else {
        if (language_ == "en") {
            std::cout << "╔════════════════════════════════════════╗" << std::endl;
            std::cout << "║            GAME OVER                   ║" << std::endl;
            std::cout << "║      Better luck next time!            ║" << std::endl;
            std::cout << "╚════════════════════════════════════════╝" << std::endl;
        } else {
            std::cout << "╔════════════════════════════════════════╗" << std::endl;
            std::cout << "║          FIN DEL JUEGO                 ║" << std::endl;
            std::cout << "║      ¡Mejor suerte la próxima vez!     ║" << std::endl;
            std::cout << "╚════════════════════════════════════════╝" << std::endl;
        }
    }
}

void GameOverState::onExit() {}

void GameOverState::update() {}

void GameOverState::render() {}

void GameOverState::handleInput(const std::string& input) {
    machine_->stop();
}

// ============================================================================
// QuitState
// ============================================================================

QuitState::QuitState(GameStateMachine* machine, const std::string& language, int badBehaviorCount)
    : IGameState(machine, StateType::QUIT), language_(language), badBehaviorCount_(badBehaviorCount) {}

void QuitState::onEnter() {
    std::cout << std::endl;
    
    if (badBehaviorCount_ < 3) {
        if (language_ == "en") {
            std::cout << "THANKS FOR PLAYING! :) HOPE TO SEE YOU BACK SOON." << std::endl;
        } else {
            std::cout << "¡GRACIAS POR JUGAR! :) TE ESPERO PRONTO DE VUELTA." << std::endl;
        }
    } else {
        if (language_ == "en") {
            std::cout << std::endl;
            std::cout << "You are a disgrace, you are not mentally mature enough," << std::endl;
            std::cout << "so come back only when you have solved that matter. GOODBYE!" << std::endl;
            std::cout << "YOU ARE RUDE, YOU NEED MANNERS CLASSES." << std::endl;
        } else {
            std::cout << std::endl;
            std::cout << "Eres una desgracia humana mentalmente o no tienes" << std::endl;
            std::cout << "la suficiente madurez, así que vuelve tan sólo cuando hayas solucionado ese asunto. ¡ADIÓS!" << std::endl;
            std::cout << "ERES UN MALEDUCADO, NECESITAS CLASES DE MODALES." << std::endl;
        }
    }
    
    std::cout << std::endl;
    machine_->stop();
}

void QuitState::onExit() {}

void QuitState::update() {}

void QuitState::render() {}

void QuitState::handleInput(const std::string& input) {
    machine_->stop();
}

// ============================================================================
// GameStateMachine
// ============================================================================

GameStateMachine::GameStateMachine() : running_(true) {}

GameStateMachine::~GameStateMachine() {
    // Clear all states
    while (!stateStack_.empty()) {
        stateStack_.back()->onExit();
        stateStack_.pop_back();
    }
}

void GameStateMachine::changeState(std::unique_ptr<IGameState> newState) {
    // Exit current state
    if (!stateStack_.empty()) {
        stateStack_.back()->onExit();
        stateStack_.pop_back();
    }
    
    // Enter new state
    stateStack_.push_back(std::move(newState));
    stateStack_.back()->onEnter();
}

void GameStateMachine::pushState(std::unique_ptr<IGameState> newState) {
    // Pause current state (don't call onExit)
    
    // Enter new state
    stateStack_.push_back(std::move(newState));
    stateStack_.back()->onEnter();
}

void GameStateMachine::popState() {
    if (!stateStack_.empty()) {
        stateStack_.back()->onExit();
        stateStack_.pop_back();
    }
}

IGameState* GameStateMachine::getCurrentState() const {
    if (stateStack_.empty()) {
        return nullptr;
    }
    return stateStack_.back().get();
}

StateType GameStateMachine::getCurrentStateType() const {
    if (stateStack_.empty()) {
        return StateType::NONE;
    }
    return stateStack_.back()->getType();
}

void GameStateMachine::update() {
    if (!stateStack_.empty()) {
        stateStack_.back()->update();
    }
}

void GameStateMachine::render() {
    if (!stateStack_.empty()) {
        stateStack_.back()->render();
    }
}

void GameStateMachine::handleInput(const std::string& input) {
    if (!stateStack_.empty()) {
        stateStack_.back()->handleInput(input);
    }
}

} // namespace manager
