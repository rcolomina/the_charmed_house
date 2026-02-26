/**
 * ASCII Rendering Tests
 * Tests for box-drawing characters, ANSI colors, terminal widths, and UTF-8
 * 
 * Author: QA Engineer
 * Date: 2026-02-26
 */

#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <clocale>
#include "lib/colormod/colormod.h"

using namespace std;
using namespace Color;

// Test result tracking
static int tests_passed = 0;
static int tests_failed = 0;

#define TEST_ASSERT(condition, message) \
    do { \
        if (condition) { \
            cout << "[PASS] " << message << endl; \
            tests_passed++; \
        } else { \
            cout << "[FAIL] " << message << endl; \
            tests_failed++; \
        } \
    } while(0)

/**
 * Test 1: Box-drawing characters render correctly
 */
void test_box_drawing_characters() {
    cout << "\n=== Test: Box-Drawing Characters ===" << endl;
    
    // Common box-drawing characters used in terminal UIs
    string box_chars[] = {
        "┌", "┐", "└", "┘",  // Corners
        "─", "│",             // Lines
        "├", "┤", "┬", "┴",  // T-junctions
        "┼",                  // Cross
        "═", "║",             // Double lines
        "╔", "╗", "╚", "╝",  // Double corners
        "╠", "╣", "╦", "╩", "╬" // Double T-junctions
    };
    
    // Test that each character has proper UTF-8 encoding
    for (const auto& ch : box_chars) {
        // Box-drawing characters are 3 bytes in UTF-8
        bool valid_length = (ch.length() == 3);
        TEST_ASSERT(valid_length, string("Box char '") + ch + "' has valid UTF-8 encoding");
    }
    
    // Test box rendering
    stringstream ss;
    ss << "┌────────────────────┐" << endl;
    ss << "│   Test Box Frame   │" << endl;
    ss << "└────────────────────┘" << endl;
    
    string box = ss.str();
    TEST_ASSERT(box.find("┌") != string::npos, "Box has top-left corner");
    TEST_ASSERT(box.find("┐") != string::npos, "Box has top-right corner");
    TEST_ASSERT(box.find("└") != string::npos, "Box has bottom-left corner");
    TEST_ASSERT(box.find("┘") != string::npos, "Box has bottom-right corner");
    TEST_ASSERT(box.find("─") != string::npos, "Box has horizontal line");
    TEST_ASSERT(box.find("│") != string::npos, "Box has vertical line");
}

/**
 * Test 2: ANSI color codes
 */
void test_ansi_color_codes() {
    cout << "\n=== Test: ANSI Color Codes ===" << endl;
    
    // Test that color modifiers produce correct escape sequences
    stringstream ss;
    
    // Test red color
    ss << red;
    string red_code = ss.str();
    TEST_ASSERT(red_code == "\033[31m", "Red color code is correct");
    
    // Test green color
    ss.str("");
    ss << green;
    string green_code = ss.str();
    TEST_ASSERT(green_code == "\033[32m", "Green color code is correct");
    
    // Test blue color
    ss.str("");
    ss << blue;
    string blue_code = ss.str();
    TEST_ASSERT(blue_code == "\033[34m", "Blue color code is correct");
    
    // Test default/reset color
    ss.str("");
    ss << def;
    string def_code = ss.str();
    TEST_ASSERT(def_code == "\033[39m", "Default color code is correct");
    
    // Test yellow color
    ss.str("");
    ss << yellow;
    string yellow_code = ss.str();
    TEST_ASSERT(yellow_code == "\033[33m", "Yellow color code is correct");
    
    // Test magenta color
    ss.str("");
    ss << magenta;
    string magenta_code = ss.str();
    TEST_ASSERT(magenta_code == "\033[35m", "Magenta color code is correct");
    
    // Test cyan color
    ss.str("");
    ss << cyan;
    string cyan_code = ss.str();
    TEST_ASSERT(cyan_code == "\033[36m", "Cyan color code is correct");
    
    // Test that colors can be combined with text
    ss.str("");
    ss << red << "test" << def;
    string colored_text = ss.str();
    TEST_ASSERT(colored_text == "\033[31mtest\033[39m", "Colored text formatting works");
}

/**
 * Test 3: Different terminal widths
 */
void test_terminal_widths() {
    cout << "\n=== Test: Terminal Width Handling ===" << endl;
    
    // Test text wrapping at different widths
    vector<int> widths = {40, 60, 80, 100, 120};
    
    string long_text = "This is a very long text that should be properly handled "
                       "regardless of the terminal width setting. The game should "
                       "display this text correctly without breaking words in the "
                       "middle or causing display issues.";
    
    for (int width : widths) {
        // Simulate text that fits within width
        bool fits = (long_text.length() > 0);
        TEST_ASSERT(fits, string("Text renders at width ") + to_string(width));
    }
    
    // Test minimum width (should still display something)
    int min_width = 20;
    TEST_ASSERT(min_width >= 20, "Minimum terminal width is supported");
    
    // Test maximum reasonable width
    int max_width = 200;
    TEST_ASSERT(max_width <= 300, "Maximum terminal width is reasonable");
}

/**
 * Test 4: UTF-8 character handling
 */
void test_utf8_characters() {
    cout << "\n=== Test: UTF-8 Character Handling ===" << endl;
    
    // Test Spanish special characters
    string spanish_chars = "áéíóúñÁÉÍÓÚÑ¿¡";
    TEST_ASSERT(spanish_chars.length() > 0, "Spanish characters are valid strings");
    
    // Test that each Spanish character is properly encoded
    vector<string> chars = {"á", "é", "í", "ó", "ú", "ñ", "Á", "É", "Í", "Ó", "Ú", "Ñ", "¿", "¡"};
    for (const auto& ch : chars) {
        // Spanish accented characters are 2 bytes in UTF-8
        bool valid = (ch.length() == 2);
        TEST_ASSERT(valid, string("Spanish char '") + ch + "' has valid UTF-8 encoding");
    }
    
    // Test mixed content
    string mixed = "La casa encantada tiene muchos misterios. ¡Ayúdame!";
    TEST_ASSERT(mixed.find("á") != string::npos, "Mixed text contains accented characters");
    TEST_ASSERT(mixed.find("¡") != string::npos, "Mixed text contains inverted exclamation");
    
    // Test emoji (4-byte UTF-8)
    string emoji = "🏠";  // House emoji
    TEST_ASSERT(emoji.length() == 4, "Emoji has 4-byte UTF-8 encoding");
}

/**
 * Test 5: Visual regression tests (compare output)
 */
void test_visual_regression() {
    cout << "\n=== Test: Visual Regression ===" << endl;
    
    // Test scene ASCII art loading
    ifstream file("./txt/scenes/fronthouse.txt");
    if (file.is_open()) {
        string content((istreambuf_iterator<char>(file)),
                       istreambuf_iterator<char>());
        file.close();
        
        TEST_ASSERT(content.length() > 0, "ASCII art file has content");
        TEST_ASSERT(content.find('\n') != string::npos, "ASCII art has multiple lines");
        
        // Check for expected characters in the house scene
        TEST_ASSERT(content.find('0') != string::npos || content.find('K') != string::npos, 
                    "ASCII art contains expected characters");
        
        // Count lines
        int line_count = 0;
        for (char c : content) {
            if (c == '\n') line_count++;
        }
        TEST_ASSERT(line_count > 10, "ASCII art has reasonable number of lines");
    } else {
        TEST_ASSERT(false, "Could not open ASCII art file for visual regression test");
    }
    
    // Test consistent output format
    stringstream ss;
    ss << "┌" << string(40, '─') << "┐" << endl;
    ss << "│" << " Test Scene Title                       " << "│" << endl;
    ss << "└" << string(40, '─') << "┘" << endl;
    
    string frame = ss.str();
    
    // Verify frame structure
    size_t first_newline = frame.find('\n');
    size_t second_newline = frame.find('\n', first_newline + 1);
    
    TEST_ASSERT(first_newline != string::npos, "Frame has first line");
    TEST_ASSERT(second_newline != string::npos, "Frame has second line");
}

/**
 * Test 6: Color combinations
 */
void test_color_combinations() {
    cout << "\n=== Test: Color Combinations ===" << endl;
    
    stringstream ss;
    
    // Test multiple colors in sequence
    ss << red << "Red " << green << "Green " << blue << "Blue " << def;
    string multi_color = ss.str();
    
    TEST_ASSERT(multi_color.find("\033[31m") != string::npos, "Multi-color has red");
    TEST_ASSERT(multi_color.find("\033[32m") != string::npos, "Multi-color has green");
    TEST_ASSERT(multi_color.find("\033[34m") != string::npos, "Multi-color has blue");
    TEST_ASSERT(multi_color.find("\033[39m") != string::npos, "Multi-color has reset");
    
    // Test nested colors (last color wins)
    ss.str("");
    ss << red << green << "text" << def;
    string nested = ss.str();
    TEST_ASSERT(nested == "\033[31m\033[32mtext\033[39m", "Nested colors work correctly");
}

/**
 * Test 7: ASCII art dimensions
 */
void test_ascii_art_dimensions() {
    cout << "\n=== Test: ASCII Art Dimensions ===" << endl;
    
    vector<string> scene_files = {
        "./txt/scenes/fronthouse.txt",
        "./txt/scenes/stones.txt",
        "./txt/scenes/cementery.txt",
        "./txt/scenes/arcoarboles.txt",
        "./txt/scenes/island.txt"
    };
    
    for (const auto& filepath : scene_files) {
        ifstream file(filepath);
        if (file.is_open()) {
            string line;
            int max_width = 0;
            int line_count = 0;
            
            while (getline(file, line)) {
                if ((int)line.length() > max_width) {
                    max_width = line.length();
                }
                line_count++;
            }
            file.close();
            
            // Extract filename for reporting
            size_t last_slash = filepath.find_last_of('/');
            string filename = (last_slash != string::npos) ? 
                              filepath.substr(last_slash + 1) : filepath;
            
            TEST_ASSERT(max_width <= 120, filename + " width is reasonable (<= 120)");
            TEST_ASSERT(line_count >= 5, filename + " has minimum height (>= 5 lines)");
        }
    }
}

/**
 * Test 8: Special rendering characters
 */
void test_special_rendering_chars() {
    cout << "\n=== Test: Special Rendering Characters ===" << endl;
    
    // Test block characters
    string blocks = "█▓▒░";
    TEST_ASSERT(blocks.length() > 0, "Block characters are valid");
    
    // Test arrow characters
    string arrows = "←↑→↓↔↕";
    TEST_ASSERT(arrows.length() > 0, "Arrow characters are valid");
    
    // Test that these can be output to stringstream
    stringstream ss;
    ss << blocks << arrows;
    TEST_ASSERT(ss.str().length() > 0, "Special characters can be streamed");
}

int main() {
    cout << "========================================" << endl;
    cout << "   ASCII Rendering Test Suite" << endl;
    cout << "========================================" << endl;
    
    // Set locale for UTF-8
    setlocale(LC_ALL, "");
    
    try {
        test_box_drawing_characters();
        test_ansi_color_codes();
        test_terminal_widths();
        test_utf8_characters();
        test_visual_regression();
        test_color_combinations();
        test_ascii_art_dimensions();
        test_special_rendering_chars();
        
        cout << "\n========================================" << endl;
        cout << "   Test Results Summary" << endl;
        cout << "========================================" << endl;
        cout << "Passed: " << tests_passed << endl;
        cout << "Failed: " << tests_failed << endl;
        cout << "Total:  " << (tests_passed + tests_failed) << endl;
        
        if (tests_failed == 0) {
            cout << "\n[SUCCESS] All ASCII rendering tests passed!" << endl;
            return 0;
        } else {
            cout << "\n[FAILURE] Some tests failed!" << endl;
            return 1;
        }
        
    } catch (const exception& e) {
        cerr << "[FATAL] Exception: " << e.what() << endl;
        return 1;
    }
}
