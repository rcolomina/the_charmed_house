#include <iostream>
#include <cassert>
#include "../patterns/factory/factory.h"
#include "../patterns/command/invocador.h"
#include "../patterns/command/operaciones.h"
#include "../data/JSONGameDataLoader.h"

using namespace std;

/**
 * Integration test for CommandBuilder
 * Tests that would have caught the bugs:
 * 1. Commands can be built without premature execution
 * 2. References are properly maintained (not dangling)
 * 3. Commands can be executed after building
 */
int main() {
    cout << "=== CommandBuilder Integration Test ===" << endl;

    try {
        // Load game data
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* escena_actual = fac.buildGameById(gameId);

        assert(escena_actual != nullptr && "Scene should be loaded");
        cout << "[PASS] Game scene loaded successfully" << endl;

        // Set up command builder dependencies
        bool continuar_loop = true;
        Inventario inventario;
        string parametro1 = "";
        string parametro2 = "";
        bool primera_entrada = true;
        EventsQueue eventsQueue;

        cout << "[TEST] Building commands with CommandBuilder..." << endl;

        // This would have crashed with the old bug (premature execution)
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

        cout << "[PASS] Commands built successfully without premature execution" << endl;

        // Verify all expected commands exist
        assert(commands.find("norte") != commands.end() && "norte command should exist");
        assert(commands.find("sur") != commands.end() && "sur command should exist");
        assert(commands.find("este") != commands.end() && "este command should exist");
        assert(commands.find("oeste") != commands.end() && "oeste command should exist");
        assert(commands.find("ver") != commands.end() && "ver command should exist");
        assert(commands.find("exit") != commands.end() && "exit command should exist");

        cout << "[PASS] All movement and basic commands exist" << endl;

        // Create invocador
        Invocador invocador(commands);

        // Test that commands can be executed without crashing
        // (This would have crashed with dangling reference bugs)
        cout << "[TEST] Executing 'ver' command..." << endl;
        int result = invocador.exec("ver", "", "");
        assert(result == 0 && "ver command should execute successfully");
        cout << "[PASS] 'ver' command executed successfully" << endl;

        // Test movement command execution (even if no valid exit exists)
        cout << "[TEST] Executing 'norte' command..." << endl;
        result = invocador.exec("norte", "", "");
        assert(result == 0 && "norte command should execute without crashing");
        cout << "[PASS] 'norte' command executed successfully" << endl;

        // Test that continuar_loop reference works
        cout << "[TEST] Executing 'exit' command..." << endl;
        assert(continuar_loop == true && "continuar_loop should start as true");
        result = invocador.exec("exit", "", "");
        assert(continuar_loop == false && "exit command should set continuar_loop to false");
        cout << "[PASS] 'exit' command properly modified continuar_loop reference" << endl;

        // Test parameter clearing scenario
        parametro1 = "test_param";
        parametro2 = "test_param2";
        cout << "[TEST] Testing with parameters set..." << endl;
        parametro1 = "";
        parametro2 = "";
        result = invocador.exec("ver", "", "");
        assert(result == 0 && "Commands should work after parameter clearing");
        cout << "[PASS] Commands work correctly with cleared parameters" << endl;

        cout << endl << "=== All CommandBuilder tests PASSED ===" << endl;
        return 0;

    } catch (const exception& e) {
        cerr << "[FAIL] Exception caught: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "[FAIL] Unknown exception caught" << endl;
        return 1;
    }
}
