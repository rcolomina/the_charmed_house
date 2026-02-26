#ifndef _ASCII_RENDERER_
#define _ASCII_RENDERER_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <sys/ioctl.h>
#include <unistd.h>

namespace view {

/**
 * ANSI Color codes for terminal rendering
 */
namespace Color {
    // Reset
    const std::string RESET = "\033[0m";
    
    // Regular colors
    const std::string BLACK = "\033[30m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    
    // Bright colors
    const std::string BRIGHT_BLACK = "\033[90m";
    const std::string BRIGHT_RED = "\033[91m";
    const std::string BRIGHT_GREEN = "\033[92m";
    const std::string BRIGHT_YELLOW = "\033[93m";
    const std::string BRIGHT_BLUE = "\033[94m";
    const std::string BRIGHT_MAGENTA = "\033[95m";
    const std::string BRIGHT_CYAN = "\033[96m";
    const std::string BRIGHT_WHITE = "\033[97m";
    
    // Background colors
    const std::string BG_BLACK = "\033[40m";
    const std::string BG_RED = "\033[41m";
    const std::string BG_GREEN = "\033[42m";
    const std::string BG_YELLOW = "\033[43m";
    const std::string BG_BLUE = "\033[44m";
    const std::string BG_MAGENTA = "\033[45m";
    const std::string BG_CYAN = "\033[46m";
    const std::string BG_WHITE = "\033[47m";
    
    // Text styles
    const std::string BOLD = "\033[1m";
    const std::string DIM = "\033[2m";
    const std::string ITALIC = "\033[3m";
    const std::string UNDERLINE = "\033[4m";
    const std::string BLINK = "\033[5m";
    const std::string REVERSE = "\033[7m";
    const std::string HIDDEN = "\033[8m";
}

/**
 * Terminal control sequences
 */
namespace Terminal {
    const std::string CLEAR_SCREEN = "\033[2J";
    const std::string CURSOR_HOME = "\033[H";
    const std::string CURSOR_HIDE = "\033[?25l";
    const std::string CURSOR_SHOW = "\033[?25h";
    const std::string CLEAR_LINE = "\033[2K";
    
    // Move cursor to position (row, col) - 1-indexed
    inline std::string moveTo(int row, int col) {
        return "\033[" + std::to_string(row) + ";" + std::to_string(col) + "H";
    }
    
    // Move cursor up/down/left/right
    inline std::string moveUp(int n = 1) { return "\033[" + std::to_string(n) + "A"; }
    inline std::string moveDown(int n = 1) { return "\033[" + std::to_string(n) + "B"; }
    inline std::string moveRight(int n = 1) { return "\033[" + std::to_string(n) + "C"; }
    inline std::string moveLeft(int n = 1) { return "\033[" + std::to_string(n) + "D"; }
}

/**
 * Animation effect types
 */
enum class AnimationType {
    NONE,
    FADE_IN,
    TYPEWRITER,
    BLINK_EFFECT,
    SLIDE_IN
};

/**
 * Render options for customizing output
 */
struct RenderOptions {
    bool centered = false;
    bool colorEnabled = true;
    std::string foregroundColor = "";
    std::string backgroundColor = "";
    AnimationType animation = AnimationType::NONE;
    int animationDelayMs = 50;
    int blinkCount = 3;
    int blinkIntervalMs = 500;
};

/**
 * ASCII Art Renderer with ANSI color support, centering, and animations
 */
class AsciiRenderer {
public:
    AsciiRenderer();
    ~AsciiRenderer() = default;
    
    // Terminal size detection
    int getTerminalWidth() const;
    int getTerminalHeight() const;
    void updateTerminalSize();
    
    // Basic rendering
    void render(const std::string& text, const RenderOptions& options = RenderOptions());
    void renderFile(const std::string& filepath, const RenderOptions& options = RenderOptions());
    void renderLines(const std::vector<std::string>& lines, const RenderOptions& options = RenderOptions());
    
    // Centered rendering
    void renderCentered(const std::string& text);
    void renderFileCentered(const std::string& filepath);
    
    // Colored rendering
    void renderColored(const std::string& text, const std::string& color);
    void renderFileColored(const std::string& filepath, const std::string& color);
    
    // Animation rendering
    void renderWithAnimation(const std::string& text, AnimationType animation, int delayMs = 50);
    void renderFileWithAnimation(const std::string& filepath, AnimationType animation, int delayMs = 50);
    
    // Blinking effect
    void renderBlinking(const std::string& text, int blinkCount = 3, int intervalMs = 500);
    
    // Transition effects
    void fadeIn(const std::string& text, int durationMs = 1000);
    void slideIn(const std::string& text, int durationMs = 500);
    void typewriter(const std::string& text, int charDelayMs = 50);
    
    // Screen control
    void clearScreen();
    void moveCursor(int row, int col);
    void hideCursor();
    void showCursor();
    
    // Box drawing
    void renderBox(const std::string& text, const std::string& title = "");
    void renderBox(const std::vector<std::string>& lines, const std::string& title = "");
    
    // Progress bar
    void renderProgressBar(int current, int total, int width = 40);
    
    // Utility
    std::string centerText(const std::string& text, int width) const;
    std::string applyColor(const std::string& text, const std::string& color) const;
    std::vector<std::string> loadFile(const std::string& filepath) const;
    int getVisibleLength(const std::string& text) const; // Length without ANSI codes
    
private:
    int terminalWidth_;
    int terminalHeight_;
    bool colorSupported_;
    
    void detectColorSupport();
    std::string stripAnsiCodes(const std::string& text) const;
};

} // namespace view

#endif
