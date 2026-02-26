#ifndef _GAME_STATE_
#define _GAME_STATE_

#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace manager {

// Forward declaration
class GameStateMachine;

/**
 * Game state enumeration
 */
enum class StateType {
    NONE,
    PROLOGUE,
    PLAYING,
    PAUSED,
    INVENTORY,
    DIALOG,
    CUTSCENE,
    GAME_OVER,
    VICTORY,
    MENU,
    QUIT
};

/**
 * Base class for game states
 */
class IGameState {
public:
    IGameState(GameStateMachine* machine, StateType type)
        : machine_(machine), type_(type) {}
    virtual ~IGameState() = default;
    
    // State lifecycle
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handleInput(const std::string& input) = 0;
    
    // State info
    StateType getType() const { return type_; }
    std::string getName() const;
    
protected:
    GameStateMachine* machine_;
    StateType type_;
};

/**
 * Prologue state - shows introduction text
 */
class PrologueState : public IGameState {
public:
    PrologueState(GameStateMachine* machine, const std::string& language);
    
    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;
    void handleInput(const std::string& input) override;
    
private:
    std::string language_;
    bool completed_;
};

/**
 * Playing state - main game loop
 */
class PlayingState : public IGameState {
public:
    PlayingState(GameStateMachine* machine);
    
    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;
    void handleInput(const std::string& input) override;
    
    // Callbacks for game logic
    void setUpdateCallback(std::function<void()> callback) { updateCallback_ = callback; }
    void setRenderCallback(std::function<void()> callback) { renderCallback_ = callback; }
    void setInputCallback(std::function<int(const std::string&)> callback) { inputCallback_ = callback; }
    
private:
    std::function<void()> updateCallback_;
    std::function<void()> renderCallback_;
    std::function<int(const std::string&)> inputCallback_;
    bool firstEntry_;
};

/**
 * Paused state
 */
class PausedState : public IGameState {
public:
    PausedState(GameStateMachine* machine, const std::string& language);
    
    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;
    void handleInput(const std::string& input) override;
    
private:
    std::string language_;
};

/**
 * Game Over state
 */
class GameOverState : public IGameState {
public:
    GameOverState(GameStateMachine* machine, const std::string& language, bool victory = false);
    
    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;
    void handleInput(const std::string& input) override;
    
private:
    std::string language_;
    bool victory_;
};

/**
 * Quit state - cleanup and exit
 */
class QuitState : public IGameState {
public:
    QuitState(GameStateMachine* machine, const std::string& language, int badBehaviorCount = 0);
    
    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;
    void handleInput(const std::string& input) override;
    
private:
    std::string language_;
    int badBehaviorCount_;
};

/**
 * State Machine for managing game states
 */
class GameStateMachine {
public:
    GameStateMachine();
    ~GameStateMachine();
    
    // State management
    void changeState(std::unique_ptr<IGameState> newState);
    void pushState(std::unique_ptr<IGameState> newState);
    void popState();
    
    // Get current state
    IGameState* getCurrentState() const;
    StateType getCurrentStateType() const;
    
    // Update and render
    void update();
    void render();
    void handleInput(const std::string& input);
    
    // Running state
    bool isRunning() const { return running_; }
    void stop() { running_ = false; }
    
private:
    std::vector<std::unique_ptr<IGameState>> stateStack_;
    bool running_;
};

} // namespace manager

#endif
