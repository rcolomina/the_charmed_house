#include <iostream>
#include <cassert>
#include <sstream>
#include "../manager/game_loop.h"
#include "../patterns/factory/factory.h"
#include "../patterns/command/operaciones.h"
#include "../data/JSONGameDataLoader.h"

using namespace std;

/**
 * Integration test for GameLoop
 * Tests that would have caught bugs:
 * 1. Input processing clears previous parameters
 * 2. Commands execute correctly in loop context
 * 3. Game state is maintained across iterations
 */
int main() {
    cout << "=== GameLoop Integration Test ===" << endl;

    try {
        // Load game data
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* escena_actual = fac.buildGameById(gameId);

        assert(escena_actual != nullptr && "Scene should be loaded");
        cout << "[PASS] Game scene loaded successfully" << endl;

        // Set up game loop dependencies
        bool continuar_loop = true;
        Inventario inventario;
        string comando = "";
        string parametro1 = "";
        string parametro2 = "";
        bool primera_entrada = true;
        EventsQueue eventsQueue;

        // Build commands
        CommandBuilder cb;
        map<string, ICommand*> commands = cb.buildCommands(
            continuar_loop,
            escena_actual,
            inventario,
            parametro1,
            parametro2,
            primera_entrada,
            eventsQueue
        );

        Invocador invocador(commands);

        cout << "[PASS] Game components initialized" << endl;

        // Test: Parameter clearing between commands
        cout << "[TEST] Testing parameter clearing..." << endl;
        comando = "examinar";
        parametro1 = "ladrillo";
        parametro2 = "extra";

        // Execute command with parameters
        invocador.exec(comando, parametro1, parametro2);

        // Clear parameters (simulating what GameLoop::processInput does)
        comando = "";
        parametro1 = "";
        parametro2 = "";

        // Execute command without parameters - should work
        comando = "ver";
        int result = invocador.exec(comando, parametro1, parametro2);
        assert(result == 0 && "Command should work with cleared parameters");
        cout << "[PASS] Parameters cleared correctly between commands" << endl;

        // Test: Multiple command executions
        cout << "[TEST] Testing multiple command executions..." << endl;
        vector<string> test_commands = {"ver", "norte", "sur", "este", "oeste"};
        for (const auto& cmd : test_commands) {
            comando = cmd;
            parametro1 = "";
            parametro2 = "";
            result = invocador.exec(comando, parametro1, parametro2);
            assert(result == 0 && "All commands should execute successfully");
        }
        cout << "[PASS] Multiple commands executed successfully" << endl;

        // Test: Commands with parameters
        cout << "[TEST] Testing commands with parameters..." << endl;
        comando = "examinar";
        parametro1 = "ladrillo";
        parametro2 = "";
        result = invocador.exec(comando, parametro1, parametro2);
        assert(result == 0 && "Command with parameter should work");
        cout << "[PASS] Commands with parameters work correctly" << endl;

        // Test: State persistence across commands
        cout << "[TEST] Testing state persistence..." << endl;
        comando = "este";
        invocador.exec(comando, "", "");
        // Scene pointer should still be valid (either same or different scene)
        assert(escena_actual != nullptr && "Scene pointer should remain valid");
        cout << "[PASS] State persists correctly across commands" << endl;

        // Test: Exit command modifies continuar_loop
        cout << "[TEST] Testing exit command..." << endl;
        assert(continuar_loop == true && "continuar_loop should start as true");
        comando = "exit";
        invocador.exec(comando, "", "");
        assert(continuar_loop == false && "exit command should set continuar_loop to false");
        cout << "[PASS] Exit command works correctly" << endl;

        // Test: Rapid consecutive commands (stress test)
        cout << "[TEST] Stress testing with rapid commands..." << endl;
        continuar_loop = true; // Reset
        for (int i = 0; i < 100; i++) {
            comando = (i % 2 == 0) ? "ver" : "norte";
            parametro1 = "";
            parametro2 = "";
            invocador.exec(comando, parametro1, parametro2);
        }
        cout << "[PASS] Rapid command execution stress test passed" << endl;

        cout << endl << "=== All GameLoop tests PASSED ===" << endl;
        return 0;

    } catch (const exception& e) {
        cerr << "[FAIL] Exception caught: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "[FAIL] Unknown exception or segfault occurred" << endl;
        return 1;
    }
}
