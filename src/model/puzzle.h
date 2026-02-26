#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>

// Forward declarations
class Objeto;
class Escenario;
class Inventario;

namespace PuzzleSystem {

/**
 * Enum for puzzle types
 */
enum class PuzzleType {
    COMBINATION,    // Combine two items (llave + puerta)
    SEQUENCE,       // Press buttons in order
    RIDDLE,         // Text input answer
    LOCKED_DOOR,    // Requires specific item to unlock
    CODE_INPUT,     // Enter numeric code
    ITEM_PLACEMENT  // Place item in specific location
};

/**
 * Enum for puzzle state
 */
enum class PuzzleState {
    LOCKED,         // Not yet accessible
    AVAILABLE,      // Can be attempted
    IN_PROGRESS,    // Partially solved
    SOLVED,         // Completed
    FAILED          // Failed (if applicable)
};

/**
 * Base class for all puzzles
 */
class Puzzle {
public:
    Puzzle(const std::string& id, const std::string& name, 
           const std::string& description, PuzzleType type);
    virtual ~Puzzle() = default;
    
    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getName() const { return name_; }
    const std::string& getDescription() const { return description_; }
    PuzzleType getType() const { return type_; }
    PuzzleState getState() const { return state_; }
    const std::string& getHint() const { return hint_; }
    const std::string& getSolvedMessage() const { return solvedMessage_; }
    
    // Setters
    void setHint(const std::string& hint) { hint_ = hint; }
    void setSolvedMessage(const std::string& msg) { solvedMessage_ = msg; }
    void setState(PuzzleState state) { state_ = state; }
    
    // Virtual methods for puzzle interaction
    virtual bool attempt(const std::string& input) = 0;
    virtual bool attempt(Objeto* item1, Objeto* item2 = nullptr) { return false; }
    virtual std::string getPrompt() const = 0;
    virtual void reset();
    
    // Callback for when puzzle is solved
    void setOnSolvedCallback(std::function<void()> callback) { onSolved_ = callback; }
    
protected:
    void markSolved();
    
    std::string id_;
    std::string name_;
    std::string description_;
    PuzzleType type_;
    PuzzleState state_;
    std::string hint_;
    std::string solvedMessage_;
    std::function<void()> onSolved_;
};

/**
 * Combination puzzle - combine two items
 */
class CombinationPuzzle : public Puzzle {
public:
    CombinationPuzzle(const std::string& id, const std::string& name,
                      const std::string& description,
                      const std::string& item1Id, const std::string& item2Id,
                      const std::string& resultItemId);
    
    bool attempt(const std::string& input) override { return false; }
    bool attempt(Objeto* item1, Objeto* item2) override;
    std::string getPrompt() const override;
    
    const std::string& getItem1Id() const { return item1Id_; }
    const std::string& getItem2Id() const { return item2Id_; }
    const std::string& getResultItemId() const { return resultItemId_; }
    
private:
    std::string item1Id_;
    std::string item2Id_;
    std::string resultItemId_;
};

/**
 * Sequence puzzle - press buttons/items in correct order
 */
class SequencePuzzle : public Puzzle {
public:
    SequencePuzzle(const std::string& id, const std::string& name,
                   const std::string& description,
                   const std::vector<std::string>& correctSequence);
    
    bool attempt(const std::string& input) override;
    std::string getPrompt() const override;
    void reset() override;
    
    // Add an input to the current sequence
    bool addInput(const std::string& input);
    int getCurrentProgress() const { return currentIndex_; }
    int getSequenceLength() const { return correctSequence_.size(); }
    
private:
    std::vector<std::string> correctSequence_;
    int currentIndex_;
};

/**
 * Riddle puzzle - answer a riddle with text
 */
class RiddlePuzzle : public Puzzle {
public:
    RiddlePuzzle(const std::string& id, const std::string& name,
                 const std::string& riddle,
                 const std::vector<std::string>& acceptedAnswers);
    
    bool attempt(const std::string& input) override;
    std::string getPrompt() const override;
    
    const std::string& getRiddle() const { return riddle_; }
    void addAcceptedAnswer(const std::string& answer);
    
private:
    std::string riddle_;
    std::vector<std::string> acceptedAnswers_;
    
    std::string normalizeAnswer(const std::string& answer) const;
};

/**
 * Locked door puzzle - requires specific item
 */
class LockedDoorPuzzle : public Puzzle {
public:
    LockedDoorPuzzle(const std::string& id, const std::string& name,
                     const std::string& description,
                     const std::string& requiredItemId,
                     const std::string& doorSceneId,
                     const std::string& doorDirection);
    
    bool attempt(const std::string& input) override { return false; }
    bool attempt(Objeto* item1, Objeto* item2 = nullptr) override;
    std::string getPrompt() const override;
    
    const std::string& getRequiredItemId() const { return requiredItemId_; }
    const std::string& getDoorSceneId() const { return doorSceneId_; }
    const std::string& getDoorDirection() const { return doorDirection_; }
    bool consumesKey() const { return consumesKey_; }
    void setConsumesKey(bool consumes) { consumesKey_ = consumes; }
    
private:
    std::string requiredItemId_;
    std::string doorSceneId_;
    std::string doorDirection_;
    bool consumesKey_;
};

/**
 * Code input puzzle - enter numeric/alphanumeric code
 */
class CodeInputPuzzle : public Puzzle {
public:
    CodeInputPuzzle(const std::string& id, const std::string& name,
                    const std::string& description,
                    const std::string& correctCode);
    
    bool attempt(const std::string& input) override;
    std::string getPrompt() const override;
    
    int getAttempts() const { return attempts_; }
    int getMaxAttempts() const { return maxAttempts_; }
    void setMaxAttempts(int max) { maxAttempts_ = max; }
    
private:
    std::string correctCode_;
    int attempts_;
    int maxAttempts_;  // -1 for unlimited
};

/**
 * PuzzleManager - manages all puzzles in the game
 */
class PuzzleManager {
public:
    PuzzleManager();
    ~PuzzleManager() = default;
    
    // Puzzle registration
    void registerPuzzle(std::unique_ptr<Puzzle> puzzle);
    Puzzle* getPuzzle(const std::string& id);
    
    // Puzzle queries
    std::vector<Puzzle*> getAvailablePuzzles();
    std::vector<Puzzle*> getSolvedPuzzles();
    std::vector<Puzzle*> getPuzzlesByType(PuzzleType type);
    
    // Item combination system
    bool canCombineItems(const std::string& item1Id, const std::string& item2Id);
    CombinationPuzzle* getCombinationPuzzle(const std::string& item1Id, const std::string& item2Id);
    
    // Check if item can unlock something
    LockedDoorPuzzle* getLockedDoorForItem(const std::string& itemId);
    
    // Statistics
    int getTotalPuzzles() const { return puzzles_.size(); }
    int getSolvedCount() const;
    float getCompletionPercentage() const;
    
private:
    std::map<std::string, std::unique_ptr<Puzzle>> puzzles_;
    std::map<std::pair<std::string, std::string>, std::string> combinationMap_; // (item1, item2) -> puzzleId
};

} // namespace PuzzleSystem

#endif
