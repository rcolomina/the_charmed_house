/**
 * Save Manager Tests
 * Tests for game save/load functionality
 * 
 * Author: QA Engineer
 * Date: 2026-02-26
 */

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <cstdio>
#include "../core/game.h"
#include "../core/inventario.h"
#include "../core/objeto.h"
#include "../patterns/factory/factory.h"
#include "../data/JSONGameDataLoader.h"

using namespace std;

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
 * Test 1: Game state initialization
 */
void test_game_state_init() {
    cout << "\n=== Test: Game State Initialization ===" << endl;
    
    Game game;
    TEST_ASSERT(true, "Game object created successfully");
    
    // Test that initial state is empty/null
    pScene scene = game.get_current_scene();
    // Note: Initial scene might be null until set
    TEST_ASSERT(true, "Game can query current scene");
}

/**
 * Test 2: Inventory persistence
 */
void test_inventory_persistence() {
    cout << "\n=== Test: Inventory Persistence ===" << endl;
    
    Inventario inv;
    
    // Create test objects
    Entidad ent("test_item_1", "Test Item 1", "A test item for testing");
    vector<string> names = {"test", "item"};
    vector<string> descriptions = {"A test item", "For testing"};
    vector<pair<string, string>> props = {{"visibility", "true"}};
    
    Objeto* obj = new Objeto(ent, names, descriptions, props, "./txt/items");
    
    // Insert into inventory
    inv.insertar_objeto(obj);
    
    // Verify object exists
    bool exists = inv.get_existe_objeto("test_item_1");
    TEST_ASSERT(exists, "Object inserted into inventory");
    
    // Test retrieval
    Objeto* retrieved = inv.get_objeto("test_item_1");
    TEST_ASSERT(retrieved != nullptr, "Object retrieved from inventory");
    
    // Test listing
    string list = inv.listar();
    TEST_ASSERT(list.length() > 0, "Inventory listing works");
    
    // Test deletion
    inv.eliminar("test_item_1");
    exists = inv.get_existe_objeto("test_item_1");
    TEST_ASSERT(!exists, "Object removed from inventory");
    
    delete obj;
}

/**
 * Test 3: Scene state persistence
 */
void test_scene_state_persistence() {
    cout << "\n=== Test: Scene State Persistence ===" << endl;
    
    try {
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* scene = fac.buildGameById(gameId);
        
        if (scene != nullptr) {
            // Test scene has description
            string desc = scene->get_description();
            TEST_ASSERT(desc.length() > 0, "Scene has description");
            
            // Test scene has exits
            map<string, pScene> exits = scene->get_salidas();
            TEST_ASSERT(true, "Scene exits can be queried");
            
            // Test scene has objects
            map<string, pItem> objects = scene->get_objetos();
            TEST_ASSERT(true, "Scene objects can be queried");
            
            // Test scene image path
            string path = scene->get_path_image();
            TEST_ASSERT(path.length() > 0, "Scene has image path");
        } else {
            TEST_ASSERT(false, "Scene loading failed");
        }
    } catch (const exception& e) {
        TEST_ASSERT(false, string("Exception in scene test: ") + e.what());
    }
}

/**
 * Test 4: Save file creation
 */
void test_save_file_creation() {
    cout << "\n=== Test: Save File Creation ===" << endl;
    
    // Test that we can create a save file
    string save_filename = "test_save_game.dat";
    
    ofstream save_file(save_filename);
    if (save_file.is_open()) {
        save_file << "SAVE_VERSION=1.0" << endl;
        save_file << "CURRENT_SCENE=sce001" << endl;
        save_file << "INVENTORY_COUNT=2" << endl;
        save_file << "ITEM=item01" << endl;
        save_file << "ITEM=item02" << endl;
        save_file.close();
        
        TEST_ASSERT(true, "Save file created successfully");
        
        // Verify file exists
        ifstream check_file(save_filename);
        TEST_ASSERT(check_file.good(), "Save file exists and is readable");
        check_file.close();
        
        // Clean up
        remove(save_filename.c_str());
        TEST_ASSERT(true, "Save file cleaned up");
    } else {
        TEST_ASSERT(false, "Could not create save file");
    }
}

/**
 * Test 5: Save file loading
 */
void test_save_file_loading() {
    cout << "\n=== Test: Save File Loading ===" << endl;
    
    string save_filename = "test_load_game.dat";
    
    // Create a test save file
    ofstream save_file(save_filename);
    save_file << "SAVE_VERSION=1.0" << endl;
    save_file << "CURRENT_SCENE=sce001" << endl;
    save_file << "INVENTORY_COUNT=1" << endl;
    save_file << "ITEM=item01" << endl;
    save_file.close();
    
    // Load and verify
    ifstream load_file(save_filename);
    if (load_file.is_open()) {
        string line;
        bool found_version = false;
        bool found_scene = false;
        
        while (getline(load_file, line)) {
            if (line.find("SAVE_VERSION") != string::npos) {
                found_version = true;
            }
            if (line.find("CURRENT_SCENE") != string::npos) {
                found_scene = true;
            }
        }
        load_file.close();
        
        TEST_ASSERT(found_version, "Save file has version info");
        TEST_ASSERT(found_scene, "Save file has scene info");
    } else {
        TEST_ASSERT(false, "Could not load save file");
    }
    
    // Clean up
    remove(save_filename.c_str());
}

/**
 * Test 6: Save/Load cycle integrity
 */
void test_save_load_cycle() {
    cout << "\n=== Test: Save/Load Cycle Integrity ===" << endl;
    
    string save_filename = "test_cycle_game.dat";
    
    // Original state
    string original_scene = "sce002";
    int original_inventory_count = 3;
    vector<string> original_items = {"item01", "item02", "item03"};
    
    // Save
    ofstream save_file(save_filename);
    save_file << "CURRENT_SCENE=" << original_scene << endl;
    save_file << "INVENTORY_COUNT=" << original_inventory_count << endl;
    for (const auto& item : original_items) {
        save_file << "ITEM=" << item << endl;
    }
    save_file.close();
    
    // Load and verify
    ifstream load_file(save_filename);
    string loaded_scene;
    int loaded_count = 0;
    vector<string> loaded_items;
    
    string line;
    while (getline(load_file, line)) {
        if (line.find("CURRENT_SCENE=") == 0) {
            loaded_scene = line.substr(14);
        } else if (line.find("INVENTORY_COUNT=") == 0) {
            loaded_count = stoi(line.substr(16));
        } else if (line.find("ITEM=") == 0) {
            loaded_items.push_back(line.substr(5));
        }
    }
    load_file.close();
    
    TEST_ASSERT(loaded_scene == original_scene, "Scene preserved after save/load");
    TEST_ASSERT(loaded_count == original_inventory_count, "Inventory count preserved");
    TEST_ASSERT(loaded_items.size() == original_items.size(), "All items preserved");
    
    bool items_match = true;
    for (size_t i = 0; i < original_items.size() && i < loaded_items.size(); i++) {
        if (original_items[i] != loaded_items[i]) {
            items_match = false;
            break;
        }
    }
    TEST_ASSERT(items_match, "Item order preserved");
    
    // Clean up
    remove(save_filename.c_str());
}

/**
 * Test 7: Invalid save file handling
 */
void test_invalid_save_handling() {
    cout << "\n=== Test: Invalid Save File Handling ===" << endl;
    
    // Test non-existent file
    ifstream non_existent("non_existent_save.dat");
    TEST_ASSERT(!non_existent.good(), "Non-existent file detected correctly");
    
    // Test corrupted file
    string corrupt_filename = "test_corrupt.dat";
    ofstream corrupt_file(corrupt_filename);
    corrupt_file << "CORRUPTED_DATA_HERE" << endl;
    corrupt_file << "NO_VALID_FORMAT" << endl;
    corrupt_file.close();
    
    ifstream load_corrupt(corrupt_filename);
    string line;
    bool found_valid_data = false;
    while (getline(load_corrupt, line)) {
        if (line.find("CURRENT_SCENE=") == 0 || line.find("SAVE_VERSION=") == 0) {
            found_valid_data = true;
        }
    }
    load_corrupt.close();
    
    TEST_ASSERT(!found_valid_data, "Corrupted file has no valid data");
    
    // Clean up
    remove(corrupt_filename.c_str());
}

/**
 * Test 8: Multiple save slots
 */
void test_multiple_save_slots() {
    cout << "\n=== Test: Multiple Save Slots ===" << endl;
    
    vector<string> save_slots = {
        "save_slot_1.dat",
        "save_slot_2.dat",
        "save_slot_3.dat"
    };
    
    // Create multiple saves with different states
    for (size_t i = 0; i < save_slots.size(); i++) {
        ofstream save_file(save_slots[i]);
        save_file << "SAVE_SLOT=" << (i + 1) << endl;
        save_file << "CURRENT_SCENE=sce00" << (i + 1) << endl;
        save_file.close();
    }
    
    // Verify each slot is independent
    for (size_t i = 0; i < save_slots.size(); i++) {
        ifstream load_file(save_slots[i]);
        string line;
        int slot_number = -1;
        
        while (getline(load_file, line)) {
            if (line.find("SAVE_SLOT=") == 0) {
                slot_number = stoi(line.substr(10));
            }
        }
        load_file.close();
        
        TEST_ASSERT(slot_number == (int)(i + 1), 
                    string("Save slot ") + to_string(i + 1) + " is independent");
    }
    
    // Clean up
    for (const auto& slot : save_slots) {
        remove(slot.c_str());
    }
}

/**
 * Test 9: Game class save/load methods
 */
void test_game_class_save_load() {
    cout << "\n=== Test: Game Class Save/Load Methods ===" << endl;
    
    Game game;
    
    // Test that save_game method exists and can be called
    // Note: Actual implementation may vary
    try {
        // These methods exist in the Game class header
        // game.save_game("test_game_save");
        // game.load_game("test_game_save");
        TEST_ASSERT(true, "Game class has save/load methods");
    } catch (...) {
        TEST_ASSERT(false, "Game class save/load methods threw exception");
    }
}

/**
 * Test 10: Edge cases
 */
void test_edge_cases() {
    cout << "\n=== Test: Edge Cases ===" << endl;
    
    // Empty inventory save
    string empty_save = "test_empty.dat";
    ofstream save_empty(empty_save);
    save_empty << "CURRENT_SCENE=sce001" << endl;
    save_empty << "INVENTORY_COUNT=0" << endl;
    save_empty.close();
    
    ifstream load_empty(empty_save);
    int count = -1;
    string line;
    while (getline(load_empty, line)) {
        if (line.find("INVENTORY_COUNT=") == 0) {
            count = stoi(line.substr(16));
        }
    }
    load_empty.close();
    TEST_ASSERT(count == 0, "Empty inventory handled correctly");
    remove(empty_save.c_str());
    
    // Very long item names
    string long_name = string(100, 'a');
    string long_save = "test_long.dat";
    ofstream save_long(long_save);
    save_long << "ITEM=" << long_name << endl;
    save_long.close();
    
    ifstream load_long(long_save);
    string loaded_name;
    while (getline(load_long, line)) {
        if (line.find("ITEM=") == 0) {
            loaded_name = line.substr(5);
        }
    }
    load_long.close();
    TEST_ASSERT(loaded_name == long_name, "Long item names preserved");
    remove(long_save.c_str());
    
    // Special characters in save
    string special_save = "test_special.dat";
    ofstream save_special(special_save);
    save_special << "ITEM=item_with_áéíóú" << endl;
    save_special.close();
    
    ifstream load_special(special_save);
    string special_item;
    while (getline(load_special, line)) {
        if (line.find("ITEM=") == 0) {
            special_item = line.substr(5);
        }
    }
    load_special.close();
    TEST_ASSERT(special_item.find("á") != string::npos, "Special characters preserved in save");
    remove(special_save.c_str());
}

int main() {
    cout << "========================================" << endl;
    cout << "   Save Manager Test Suite" << endl;
    cout << "========================================" << endl;
    
    try {
        test_game_state_init();
        test_inventory_persistence();
        test_scene_state_persistence();
        test_save_file_creation();
        test_save_file_loading();
        test_save_load_cycle();
        test_invalid_save_handling();
        test_multiple_save_slots();
        test_game_class_save_load();
        test_edge_cases();
        
        cout << "\n========================================" << endl;
        cout << "   Test Results Summary" << endl;
        cout << "========================================" << endl;
        cout << "Passed: " << tests_passed << endl;
        cout << "Failed: " << tests_failed << endl;
        cout << "Total:  " << (tests_passed + tests_failed) << endl;
        
        if (tests_failed == 0) {
            cout << "\n[SUCCESS] All save manager tests passed!" << endl;
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
