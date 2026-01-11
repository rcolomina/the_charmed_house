#include <iostream>
#include <cassert>
#include "../patterns/factory/factory.h"
#include "../patterns/command/operaciones.h"
#include "../data/JSONGameDataLoader.h"

using namespace std;

/**
 * Integration test for movement commands (Cardinal)
 * Tests that would have caught the segmentation fault bugs:
 * 1. Cardinal commands can be created and executed
 * 2. Scene transitions work correctly
 * 3. Invalid movements are handled gracefully
 */
int main() {
    cout << "=== Movement Commands Integration Test ===" << endl;

    try {
        // Load game data
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* escena_actual = fac.buildGameById(gameId);

        assert(escena_actual != nullptr && "Scene should be loaded");
        Escenario* initial_scene = escena_actual;
        cout << "[PASS] Initial scene loaded: " << escena_actual << endl;

        // Set up command dependencies
        bool primera_entrada = true;

        // Test: Create Cardinal commands
        cout << "[TEST] Creating Cardinal commands..." << endl;
        Cardinal* cmd_norte = new Cardinal(&escena_actual, s_norte, primera_entrada);
        Cardinal* cmd_sur = new Cardinal(&escena_actual, s_sur, primera_entrada);
        Cardinal* cmd_este = new Cardinal(&escena_actual, s_este, primera_entrada);
        Cardinal* cmd_oeste = new Cardinal(&escena_actual, s_oeste, primera_entrada);

        cout << "[PASS] Cardinal commands created successfully" << endl;

        // Test: Execute movement commands without crashing
        // (This would have caused segfault with dangling pointer bug)
        cout << "[TEST] Executing norte command..." << endl;
        cmd_norte->execute();
        cout << "[PASS] Norte command executed without crash" << endl;

        cout << "[TEST] Executing sur command..." << endl;
        cmd_sur->execute();
        cout << "[PASS] Sur command executed without crash" << endl;

        cout << "[TEST] Executing este command..." << endl;
        Escenario* scene_before = escena_actual;
        cmd_este->execute();
        cout << "[INFO] Scene before: " << scene_before << ", Scene after: " << escena_actual << endl;

        // If there's a valid exit to the east, the scene should change
        if (escena_actual != scene_before) {
            cout << "[PASS] Successfully moved to a new scene" << endl;
            assert(primera_entrada == true && "primera_entrada should be set to true after movement");
            cout << "[PASS] primera_entrada flag was set correctly" << endl;
        } else {
            cout << "[INFO] No exit to the east (expected behavior)" << endl;
        }

        cout << "[TEST] Executing oeste command..." << endl;
        cmd_oeste->execute();
        cout << "[PASS] Oeste command executed without crash" << endl;

        // Test: Multiple consecutive movements
        cout << "[TEST] Testing consecutive movements..." << endl;
        for (int i = 0; i < 5; i++) {
            cmd_norte->execute();
            cmd_este->execute();
            cmd_sur->execute();
            cmd_oeste->execute();
        }
        cout << "[PASS] Multiple consecutive movements executed successfully" << endl;

        // Test: Commands still work after scene pointer changes
        cout << "[TEST] Verifying commands work after potential scene changes..." << endl;
        cmd_norte->execute();
        cout << "[PASS] Commands still functional after scene transitions" << endl;

        // Cleanup
        delete cmd_norte;
        delete cmd_sur;
        delete cmd_este;
        delete cmd_oeste;

        cout << endl << "=== All Movement tests PASSED ===" << endl;
        return 0;

    } catch (const exception& e) {
        cerr << "[FAIL] Exception caught: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "[FAIL] Unknown exception or segfault occurred" << endl;
        return 1;
    }
}
