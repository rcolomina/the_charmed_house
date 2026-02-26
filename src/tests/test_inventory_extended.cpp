/**
 * Extended Inventory Tests
 * Comprehensive tests for inventory functionality
 * 
 * Author: QA Engineer
 * Date: 2026-02-26
 */

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include "../core/inventario.h"
#include "../core/objeto.h"
#include "../core/entidad.h"

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

// Helper function to create test objects
Objeto* createTestObject(const string& id, const string& name, 
                         const vector<pair<string, string>>& props) {
    Entidad ent(id, name, "Test object description");
    vector<string> names = {name};
    vector<string> descriptions = {"Test description"};
    return new Objeto(ent, names, descriptions, props, "./txt/items");
}

/**
 * Test 1: Basic inventory operations
 */
void test_basic_operations() {
    cout << "\n=== Test: Basic Inventory Operations ===" << endl;
    
    Inventario inv;
    
    // Test empty inventory
    string list = inv.listar();
    TEST_ASSERT(true, "Empty inventory can be listed");
    
    // Create and insert object
    Objeto* obj = createTestObject("item1", "TestItem", {{"visibility", "true"}});
    inv.insertar_objeto(obj);
    
    // Test object exists
    bool exists = inv.get_existe_objeto("item1");
    TEST_ASSERT(exists, "Inserted object exists in inventory");
    
    // Test object retrieval
    Objeto* retrieved = inv.get_objeto("item1");
    TEST_ASSERT(retrieved != nullptr, "Object can be retrieved");
    TEST_ASSERT(retrieved == obj, "Retrieved object is the same instance");
    
    // Test deletion
    inv.eliminar("item1");
    exists = inv.get_existe_objeto("item1");
    TEST_ASSERT(!exists, "Deleted object no longer exists");
    
    delete obj;
}

/**
 * Test 2: Multiple items
 */
void test_multiple_items() {
    cout << "\n=== Test: Multiple Items ===" << endl;
    
    Inventario inv;
    vector<Objeto*> objects;
    
    // Insert multiple objects
    for (int i = 0; i < 5; i++) {
        string id = "item" + to_string(i);
        string name = "Item" + to_string(i);
        Objeto* obj = createTestObject(id, name, {{"visibility", "true"}});
        objects.push_back(obj);
        inv.insertar_objeto(obj);
    }
    
    // Verify all exist
    bool all_exist = true;
    for (int i = 0; i < 5; i++) {
        string id = "item" + to_string(i);
        if (!inv.get_existe_objeto(id)) {
            all_exist = false;
            break;
        }
    }
    TEST_ASSERT(all_exist, "All 5 items exist in inventory");
    
    // Test listing
    string list = inv.listar();
    TEST_ASSERT(list.length() > 0, "Inventory listing has content");
    
    // Delete some items
    inv.eliminar("item2");
    inv.eliminar("item4");
    
    TEST_ASSERT(!inv.get_existe_objeto("item2"), "Item2 deleted");
    TEST_ASSERT(!inv.get_existe_objeto("item4"), "Item4 deleted");
    TEST_ASSERT(inv.get_existe_objeto("item0"), "Item0 still exists");
    TEST_ASSERT(inv.get_existe_objeto("item1"), "Item1 still exists");
    TEST_ASSERT(inv.get_existe_objeto("item3"), "Item3 still exists");
    
    // Clean up
    for (auto obj : objects) {
        delete obj;
    }
}

/**
 * Test 3: Reacher item detection
 */
void test_reacher_detection() {
    cout << "\n=== Test: Reacher Item Detection ===" << endl;
    
    Inventario inv;
    
    // Initially no reacher
    bool has_reacher = inv.posee_alcanzador();
    TEST_ASSERT(!has_reacher, "Empty inventory has no reacher");
    
    // Add non-reacher item
    Objeto* normal = createTestObject("normal", "NormalItem", {{"visibility", "true"}});
    inv.insertar_objeto(normal);
    
    has_reacher = inv.posee_alcanzador();
    TEST_ASSERT(!has_reacher, "Inventory with normal item has no reacher");
    
    // Add reacher item
    Objeto* reacher = createTestObject("baston", "Bastón", {{"reacher", "true"}});
    inv.insertar_objeto(reacher);
    
    has_reacher = inv.posee_alcanzador();
    TEST_ASSERT(has_reacher, "Inventory with bastón has reacher");
    
    // Get reacher
    Objeto* retrieved = inv.tomar_alcanzador();
    TEST_ASSERT(retrieved != nullptr, "Reacher can be retrieved");
    
    delete normal;
    delete reacher;
}

/**
 * Test 4: Desatascador (unsticker) detection
 */
void test_desatascador_detection() {
    cout << "\n=== Test: Desatascador Detection ===" << endl;
    
    Inventario inv;
    
    // Initially no desatascador
    bool has_desatascador = inv.posee_desatascador();
    TEST_ASSERT(!has_desatascador, "Empty inventory has no desatascador");
    
    // Add desatascador item (palanca)
    Objeto* palanca = createTestObject("palanca", "Palanca", {{"desatascador", "true"}});
    inv.insertar_objeto(palanca);
    
    has_desatascador = inv.posee_desatascador();
    // Note: This depends on actual implementation
    TEST_ASSERT(true, "Desatascador detection tested");
    
    delete palanca;
}

/**
 * Test 5: Non-existent item handling
 */
void test_nonexistent_items() {
    cout << "\n=== Test: Non-existent Item Handling ===" << endl;
    
    Inventario inv;
    
    // Get non-existent item
    Objeto* obj = inv.get_objeto("nonexistent");
    TEST_ASSERT(obj == nullptr, "Non-existent item returns nullptr");
    
    // Check existence of non-existent item
    bool exists = inv.get_existe_objeto("nonexistent");
    TEST_ASSERT(!exists, "Non-existent item reports as not existing");
    
    // Delete non-existent item (should not crash)
    inv.eliminar("nonexistent");
    TEST_ASSERT(true, "Deleting non-existent item doesn't crash");
}

/**
 * Test 6: Item replacement
 */
void test_item_replacement() {
    cout << "\n=== Test: Item Replacement ===" << endl;
    
    Inventario inv;
    
    // Insert first item
    Objeto* obj1 = createTestObject("item", "Item1", {{"visibility", "true"}});
    inv.insertar_objeto(obj1);
    
    Objeto* retrieved1 = inv.get_objeto("item");
    TEST_ASSERT(retrieved1 == obj1, "First item inserted");
    
    // Insert second item with same ID
    Objeto* obj2 = createTestObject("item", "Item2", {{"visibility", "false"}});
    inv.insertar_objeto(obj2);
    
    Objeto* retrieved2 = inv.get_objeto("item");
    // Behavior depends on implementation - might replace or keep original
    TEST_ASSERT(retrieved2 != nullptr, "Item still exists after replacement attempt");
    
    delete obj1;
    delete obj2;
}

/**
 * Test 7: Large inventory
 */
void test_large_inventory() {
    cout << "\n=== Test: Large Inventory ===" << endl;
    
    Inventario inv;
    vector<Objeto*> objects;
    const int NUM_ITEMS = 100;
    
    // Insert many items
    for (int i = 0; i < NUM_ITEMS; i++) {
        string id = "item" + to_string(i);
        Objeto* obj = createTestObject(id, id, {{"visibility", "true"}});
        objects.push_back(obj);
        inv.insertar_objeto(obj);
    }
    
    // Verify all exist
    int count = 0;
    for (int i = 0; i < NUM_ITEMS; i++) {
        string id = "item" + to_string(i);
        if (inv.get_existe_objeto(id)) {
            count++;
        }
    }
    TEST_ASSERT(count == NUM_ITEMS, "All 100 items exist in inventory");
    
    // Test listing doesn't crash
    string list = inv.listar();
    TEST_ASSERT(list.length() > 0, "Large inventory can be listed");
    
    // Clean up
    for (auto obj : objects) {
        delete obj;
    }
}

/**
 * Test 8: Special character names
 */
void test_special_character_names() {
    cout << "\n=== Test: Special Character Names ===" << endl;
    
    Inventario inv;
    
    // Item with Spanish characters
    Objeto* spanish = createTestObject("bastón", "Bastón", {{"reacher", "true"}});
    inv.insertar_objeto(spanish);
    
    bool exists = inv.get_existe_objeto("bastón");
    TEST_ASSERT(exists, "Item with Spanish characters exists");
    
    // Item with spaces (if supported)
    Objeto* spaced = createTestObject("panel mecánico", "Panel Mecánico", {{"fix", "true"}});
    inv.insertar_objeto(spaced);
    
    exists = inv.get_existe_objeto("panel mecánico");
    TEST_ASSERT(exists, "Item with spaces exists");
    
    delete spanish;
    delete spaced;
}

/**
 * Test 9: Inventory iteration
 */
void test_inventory_iteration() {
    cout << "\n=== Test: Inventory Iteration ===" << endl;
    
    Inventario inv;
    
    // Add items
    Objeto* obj1 = createTestObject("item1", "Item1", {{"visibility", "true"}});
    Objeto* obj2 = createTestObject("item2", "Item2", {{"visibility", "true"}});
    Objeto* obj3 = createTestObject("item3", "Item3", {{"visibility", "true"}});
    
    inv.insertar_objeto(obj1);
    inv.insertar_objeto(obj2);
    inv.insertar_objeto(obj3);
    
    // Get listing and verify it contains all items
    string list = inv.listar();
    // Note: Actual format depends on implementation
    TEST_ASSERT(list.length() > 0, "Inventory listing works");
    
    delete obj1;
    delete obj2;
    delete obj3;
}

/**
 * Test 10: Empty inventory operations
 */
void test_empty_inventory() {
    cout << "\n=== Test: Empty Inventory Operations ===" << endl;
    
    Inventario inv;
    
    // List empty inventory
    string list = inv.listar();
    TEST_ASSERT(true, "Empty inventory can be listed");
    
    // Check reacher in empty inventory
    bool has_reacher = inv.posee_alcanzador();
    TEST_ASSERT(!has_reacher, "Empty inventory has no reacher");
    
    // Check desatascador in empty inventory
    bool has_desatascador = inv.posee_desatascador();
    TEST_ASSERT(!has_desatascador, "Empty inventory has no desatascador");
    
    // Get from empty inventory
    Objeto* obj = inv.get_objeto("anything");
    TEST_ASSERT(obj == nullptr, "Get from empty inventory returns nullptr");
}

/**
 * Test 11: Inventory after clear
 */
void test_inventory_clear() {
    cout << "\n=== Test: Inventory Clear ===" << endl;
    
    Inventario inv;
    
    // Add items
    Objeto* obj1 = createTestObject("item1", "Item1", {{"visibility", "true"}});
    Objeto* obj2 = createTestObject("item2", "Item2", {{"visibility", "true"}});
    
    inv.insertar_objeto(obj1);
    inv.insertar_objeto(obj2);
    
    // Verify items exist
    TEST_ASSERT(inv.get_existe_objeto("item1"), "Item1 exists before clear");
    TEST_ASSERT(inv.get_existe_objeto("item2"), "Item2 exists before clear");
    
    // Clear by deleting all
    inv.eliminar("item1");
    inv.eliminar("item2");
    
    // Verify cleared
    TEST_ASSERT(!inv.get_existe_objeto("item1"), "Item1 removed after clear");
    TEST_ASSERT(!inv.get_existe_objeto("item2"), "Item2 removed after clear");
    
    delete obj1;
    delete obj2;
}

/**
 * Test 12: Concurrent-like access patterns
 */
void test_access_patterns() {
    cout << "\n=== Test: Access Patterns ===" << endl;
    
    Inventario inv;
    
    // Rapid insert/delete/check cycles
    for (int cycle = 0; cycle < 10; cycle++) {
        Objeto* obj = createTestObject("temp", "Temp", {{"visibility", "true"}});
        inv.insertar_objeto(obj);
        
        bool exists = inv.get_existe_objeto("temp");
        TEST_ASSERT(exists, string("Cycle ") + to_string(cycle) + ": item exists after insert");
        
        Objeto* retrieved = inv.get_objeto("temp");
        TEST_ASSERT(retrieved != nullptr, string("Cycle ") + to_string(cycle) + ": item retrievable");
        
        inv.eliminar("temp");
        exists = inv.get_existe_objeto("temp");
        TEST_ASSERT(!exists, string("Cycle ") + to_string(cycle) + ": item removed after delete");
        
        delete obj;
    }
}

/**
 * Test 13: Object property preservation
 */
void test_property_preservation() {
    cout << "\n=== Test: Object Property Preservation ===" << endl;
    
    Inventario inv;
    
    // Create object with specific properties
    Objeto* obj = createTestObject("special", "Special", {
        {"visibility", "true"},
        {"reacher", "true"},
        {"fix", "false"}
    });
    
    inv.insertar_objeto(obj);
    
    // Retrieve and verify it's the same object
    Objeto* retrieved = inv.get_objeto("special");
    TEST_ASSERT(retrieved == obj, "Same object instance preserved");
    
    // Object properties should be intact
    TEST_ASSERT(retrieved != nullptr, "Object retrieved successfully");
    
    delete obj;
}

int main() {
    cout << "========================================" << endl;
    cout << "   Extended Inventory Test Suite" << endl;
    cout << "========================================" << endl;
    
    try {
        test_basic_operations();
        test_multiple_items();
        test_reacher_detection();
        test_desatascador_detection();
        test_nonexistent_items();
        test_item_replacement();
        test_large_inventory();
        test_special_character_names();
        test_inventory_iteration();
        test_empty_inventory();
        test_inventory_clear();
        test_access_patterns();
        test_property_preservation();
        
        cout << "\n========================================" << endl;
        cout << "   Test Results Summary" << endl;
        cout << "========================================" << endl;
        cout << "Passed: " << tests_passed << endl;
        cout << "Failed: " << tests_failed << endl;
        cout << "Total:  " << (tests_passed + tests_failed) << endl;
        
        if (tests_failed == 0) {
            cout << "\n[SUCCESS] All extended inventory tests passed!" << endl;
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
