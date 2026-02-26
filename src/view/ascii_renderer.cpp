#include "ascii_renderer.h"
#include <algorithm>
#include <regex>
#include <cstdlib>

namespace view {

AsciiRenderer::AsciiRenderer() : terminalWidth_(80), terminalHeight_(24), colorSupported_(true) {
    updateTerminalSize();
    detectColorSupport();
}

void AsciiRenderer::detectColorSupport() {
    // Check if terminal supports colors
    const char* term = std::getenv("TERM");
    if (term == nullptr) {
        colorSupported_ = false;
        return;
    }
    
    std::string termStr(term);
    colorSupported_ = (termStr.find("color") != std::string::npos ||
                       termStr.find("xterm") != std::string::npos ||
                       termStr.find("screen") != std::string::npos ||
                       termStr.find("vt100") != std::string::npos ||
                       termStr.find("linux") != std::string::npos ||
                       termStr.find("ansi") != std::string::npos);
}

int AsciiRenderer::getTerminalWidth() const {
    return terminalWidth_;
}

int AsciiRenderer::getTerminalHeight() const {
    return terminalHeight_;
}

void AsciiRenderer::updateTerminalSize() {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        terminalWidth_ = w.ws_col > 0 ? w.ws_col : 80;
        terminalHeight_ = w.ws_row > 0 ? w.ws_row : 24;
    }
}

std::string AsciiRenderer::stripAnsiCodes(const std::string& text) const {
    // Regex to match ANSI escape sequences
    std::regex ansiRegex("\033\\[[0-9;]*[mGKHF]");
    return std::regex_replace(text, ansiRegex, "");
}

int AsciiRenderer::getVisibleLength(const std::string& text) const {
    return stripAnsiCodes(text).length();
}

std::string AsciiRenderer::centerText(const std::string& text, int width) const {
    int visibleLen = getVisibleLength(text);
    if (visibleLen >= width) {
        return text;
    }
    
    int padding = (width - visibleLen) / 2;
    return std::string(padding, ' ') + text;
}

std::string AsciiRenderer::applyColor(const std::string& text, const std::string& color) const {
    if (!colorSupported_ || color.empty()) {
        return text;
    }
    return color + text + Color::RESET;
}

std::vector<std::string> AsciiRenderer::loadFile(const std::string& filepath) const {
    std::vector<std::string> lines;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        lines.push_back("[Error: No se pudo abrir el archivo: " + filepath + "]");
        return lines;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();
    return lines;
}

void AsciiRenderer::render(const std::string& text, const RenderOptions& options) {
    std::vector<std::string> lines;
    std::istringstream stream(text);
    std::string line;
    
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    
    renderLines(lines, options);
}

void AsciiRenderer::renderFile(const std::string& filepath, const RenderOptions& options) {
    std::vector<std::string> lines = loadFile(filepath);
    renderLines(lines, options);
}

void AsciiRenderer::renderLines(const std::vector<std::string>& lines, const RenderOptions& options) {
    updateTerminalSize();
    
    for (const auto& line : lines) {
        std::string outputLine = line;
        
        // Apply colors if enabled
        if (options.colorEnabled && !options.foregroundColor.empty()) {
            outputLine = applyColor(outputLine, options.foregroundColor);
        }
        
        // Center if requested
        if (options.centered) {
            outputLine = centerText(outputLine, terminalWidth_);
        }
        
        // Apply animation
        switch (options.animation) {
            case AnimationType::TYPEWRITER:
                for (char c : outputLine) {
                    std::cout << c << std::flush;
                    std::this_thread::sleep_for(std::chrono::milliseconds(options.animationDelayMs));
                }
                std::cout << std::endl;
                break;
                
            case AnimationType::FADE_IN:
                // Simulate fade by showing progressively
                std::cout << Color::DIM << outputLine << Color::RESET << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(options.animationDelayMs));
                std::cout << "\r" << Terminal::CLEAR_LINE;
                std::cout << outputLine << std::endl;
                break;
                
            case AnimationType::BLINK_EFFECT:
                for (int i = 0; i < options.blinkCount; ++i) {
                    std::cout << outputLine << std::flush;
                    std::this_thread::sleep_for(std::chrono::milliseconds(options.blinkIntervalMs));
                    std::cout << "\r" << Terminal::CLEAR_LINE << std::flush;
                    std::this_thread::sleep_for(std::chrono::milliseconds(options.blinkIntervalMs / 2));
                }
                std::cout << outputLine << std::endl;
                break;
                
            case AnimationType::SLIDE_IN:
                {
                    int visibleLen = getVisibleLength(outputLine);
                    for (int i = terminalWidth_; i >= 0; i -= 2) {
                        std::cout << "\r" << Terminal::CLEAR_LINE;
                        std::cout << std::string(i, ' ') << outputLine.substr(0, std::min((int)outputLine.length(), terminalWidth_ - i)) << std::flush;
                        std::this_thread::sleep_for(std::chrono::milliseconds(options.animationDelayMs / 5));
                    }
                    std::cout << "\r" << Terminal::CLEAR_LINE << outputLine << std::endl;
                }
                break;
                
            case AnimationType::NONE:
            default:
                std::cout << outputLine << std::endl;
                break;
        }
    }
}

void AsciiRenderer::renderCentered(const std::string& text) {
    RenderOptions options;
    options.centered = true;
    render(text, options);
}

void AsciiRenderer::renderFileCentered(const std::string& filepath) {
    RenderOptions options;
    options.centered = true;
    renderFile(filepath, options);
}

void AsciiRenderer::renderColored(const std::string& text, const std::string& color) {
    RenderOptions options;
    options.foregroundColor = color;
    render(text, options);
}

void AsciiRenderer::renderFileColored(const std::string& filepath, const std::string& color) {
    RenderOptions options;
    options.foregroundColor = color;
    renderFile(filepath, options);
}

void AsciiRenderer::renderWithAnimation(const std::string& text, AnimationType animation, int delayMs) {
    RenderOptions options;
    options.animation = animation;
    options.animationDelayMs = delayMs;
    render(text, options);
}

void AsciiRenderer::renderFileWithAnimation(const std::string& filepath, AnimationType animation, int delayMs) {
    RenderOptions options;
    options.animation = animation;
    options.animationDelayMs = delayMs;
    renderFile(filepath, options);
}

void AsciiRenderer::renderBlinking(const std::string& text, int blinkCount, int intervalMs) {
    for (int i = 0; i < blinkCount; ++i) {
        std::cout << text << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
        
        // Move cursor back and clear
        int lines = std::count(text.begin(), text.end(), '\n') + 1;
        for (int j = 0; j < lines; ++j) {
            std::cout << Terminal::moveUp() << Terminal::CLEAR_LINE;
        }
        std::cout << std::flush;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs / 2));
    }
    std::cout << text << std::endl;
}

void AsciiRenderer::fadeIn(const std::string& text, int durationMs) {
    // Simulate fade-in with dim -> normal transition
    int steps = 5;
    int stepDelay = durationMs / steps;
    
    // Show dim version
    std::cout << Color::DIM << text << Color::RESET << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(stepDelay * 2));
    
    // Clear and show normal
    int lines = std::count(text.begin(), text.end(), '\n') + 1;
    for (int i = 0; i < lines; ++i) {
        std::cout << Terminal::moveUp() << Terminal::CLEAR_LINE;
    }
    
    std::cout << text << std::endl;
}

void AsciiRenderer::slideIn(const std::string& text, int durationMs) {
    updateTerminalSize();
    std::vector<std::string> lines;
    std::istringstream stream(text);
    std::string line;
    
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    
    int steps = 20;
    int stepDelay = durationMs / steps;
    
    for (int step = steps; step >= 0; --step) {
        int offset = (terminalWidth_ * step) / steps;
        
        for (size_t i = 0; i < lines.size(); ++i) {
            std::cout << std::string(offset, ' ') << lines[i];
            if (i < lines.size() - 1) std::cout << std::endl;
        }
        std::cout << std::flush;
        
        if (step > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(stepDelay));
            // Move cursor back
            for (size_t i = 0; i < lines.size(); ++i) {
                std::cout << Terminal::moveUp() << Terminal::CLEAR_LINE;
            }
        }
    }
    std::cout << std::endl;
}

void AsciiRenderer::typewriter(const std::string& text, int charDelayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        if (c != ' ' && c != '\n') {
            std::this_thread::sleep_for(std::chrono::milliseconds(charDelayMs));
        }
    }
    std::cout << std::endl;
}

void AsciiRenderer::clearScreen() {
    std::cout << Terminal::CLEAR_SCREEN << Terminal::CURSOR_HOME << std::flush;
}

void AsciiRenderer::moveCursor(int row, int col) {
    std::cout << Terminal::moveTo(row, col) << std::flush;
}

void AsciiRenderer::hideCursor() {
    std::cout << Terminal::CURSOR_HIDE << std::flush;
}

void AsciiRenderer::showCursor() {
    std::cout << Terminal::CURSOR_SHOW << std::flush;
}

void AsciiRenderer::renderBox(const std::string& text, const std::string& title) {
    std::vector<std::string> lines;
    std::istringstream stream(text);
    std::string line;
    
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    
    renderBox(lines, title);
}

void AsciiRenderer::renderBox(const std::vector<std::string>& lines, const std::string& title) {
    // Find max line length
    size_t maxLen = 0;
    for (const auto& line : lines) {
        size_t visLen = getVisibleLength(line);
        if (visLen > maxLen) maxLen = visLen;
    }
    
    if (!title.empty() && title.length() > maxLen) {
        maxLen = title.length();
    }
    
    // Box characters (Unicode)
    const std::string topLeft = "┌";
    const std::string topRight = "┐";
    const std::string bottomLeft = "└";
    const std::string bottomRight = "┘";
    const std::string horizontal = "─";
    const std::string vertical = "│";
    
    // Top border
    std::cout << topLeft;
    if (!title.empty()) {
        std::cout << horizontal << " " << title << " ";
        for (size_t i = title.length() + 3; i < maxLen + 2; ++i) {
            std::cout << horizontal;
        }
    } else {
        for (size_t i = 0; i < maxLen + 2; ++i) {
            std::cout << horizontal;
        }
    }
    std::cout << topRight << std::endl;
    
    // Content
    for (const auto& line : lines) {
        std::cout << vertical << " " << line;
        int padding = maxLen - getVisibleLength(line);
        std::cout << std::string(padding, ' ') << " " << vertical << std::endl;
    }
    
    // Bottom border
    std::cout << bottomLeft;
    for (size_t i = 0; i < maxLen + 2; ++i) {
        std::cout << horizontal;
    }
    std::cout << bottomRight << std::endl;
}

void AsciiRenderer::renderProgressBar(int current, int total, int width) {
    float progress = static_cast<float>(current) / total;
    int filled = static_cast<int>(progress * width);
    
    std::cout << "[";
    for (int i = 0; i < width; ++i) {
        if (i < filled) {
            std::cout << Color::GREEN << "█" << Color::RESET;
        } else if (i == filled) {
            std::cout << Color::YELLOW << "▓" << Color::RESET;
        } else {
            std::cout << "░";
        }
    }
    std::cout << "] " << static_cast<int>(progress * 100) << "%" << std::flush;
}

} // namespace view
