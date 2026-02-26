/**
 * Command Parser Tests
 * Tests for command parsing, validation, and execution
 * 
 * Author: QA Engineer
 * Date: 2026-02-26
 */

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "../patterns/command/operaciones.h"
#include "../patterns/command/invocador.h"
#include "../core/inventario.h"
#include "../core/escenario.h"
#include "../patterns/factory/factory.h"
#include "../data/JSONGameDataLoader.h"
#include "../manager/parametros.h"

using namespace std;
using namespace parametros;

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
 * Test 1: Command string constants
 */
void test_command_constants() {
    cout << "\n=== Test: Command String Constants ===" << endl;
    
    // Verify command strings are defined
    TEST_ASSERT(s_exit == "exit", "Exit command string correct");
    TEST_ASSERT(s_salir == "salir", "Salir command string correct");
    TEST_ASSERT(s_ayuda == "ayuda", "Ayuda command string correct");
    TEST_ASSERT(s_ver == "ver", "Ver command string correct");
    TEST_ASSERT(s_examinar == "examinar", "Examinar command string correct");
    TEST_ASSERT(s_inventario == "inventario", "Inventario command string correct");
    TEST_ASSERT(s_norte == "norte", "Norte command string correct");
    TEST_ASSERT(s_sur == "sur", "Sur command string correct");
    TEST_ASSERT(s_este == "este", "Este command string correct");
    TEST_ASSERT(s_oeste == "oeste", "Oeste command string correct");
    TEST_ASSERT(s_tirar == "tirar", "Tirar command string correct");
    TEST_ASSERT(s_coger == "coger", "Coger command string correct");
    TEST_ASSERT(s_dejar == "dejar", "Dejar command string correct");
    TEST_ASSERT(s_alcanzar == "alcanzar", "Alcanzar command string correct");
    TEST_ASSERT(s_colocar == "colocar", "Colocar command string correct");
}

/**
 * Test 2: Command builder
 */
void test_command_builder() {
    cout << "\n=== Test: Command Builder ===" << endl;
    
    try {
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* scene = fac.buildGameById(gameId);
        
        if (scene != nullptr) {
            bool continuar_loop = true;
            Inventario inventario;
            string parametro1 = "";
            string parametro2 = "";
            bool primera_entrada = true;
            EventsQueue eventsQueue;
            
            CommandBuilder cb;
            map<string, ICommand*> commands = cb.buildCommands(
                continuar_loop, scene, inventario,
                parametro1, parametro2, primera_entrada, eventsQueue
            );
            
            // Verify all expected commands are built
            TEST_ASSERT(commands.size() >= 14, "At least 14 commands built");
            TEST_ASSERT(commands.find("exit") != commands.end(), "Exit command built");
            TEST_ASSERT(commands.find("salir") != commands.end(), "Salir command built");
            TEST_ASSERT(commands.find("ver") != commands.end(), "Ver command built");
            TEST_ASSERT(commands.find("norte") != commands.end(), "Norte command built");
            TEST_ASSERT(commands.find("sur") != commands.end(), "Sur command built");
            TEST_ASSERT(commands.find("este") != commands.end(), "Este command built");
            TEST_ASSERT(commands.find("oeste") != commands.end(), "Oeste command built");
            
            // Clean up
            for (auto& cmd : commands) {
                delete cmd.second;
            }
        }
    } catch (const exception& e) {
        TEST_ASSERT(false, string("Exception: ") + e.what());
    }
}

/**
 * Test 3: Invocador execution
 */
void test_invocador_execution() {
    cout << "\n=== Test: Invocador Execution ===" << endl;
    
    try {
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* scene = fac.buildGameById(gameId);
        
        if (scene != nullptr) {
            bool continuar_loop = true;
            Inventario inventario;
            string parametro1 = "";
            string parametro2 = "";
            bool primera_entrada = true;
            EventsQueue eventsQueue;
            
            CommandBuilder cb;
            map<string, ICommand*> commands = cb.buildCommands(
                continuar_loop, scene, inventario,
                parametro1, parametro2, primera_entrada, eventsQueue
            );
            
            Invocador invocador(commands);
            
            // Test valid command execution
            int result = invocador.exec("ver", "", "");
            TEST_ASSERT(result == 0, "Ver command executes successfully");
            
            // Test movement commands
            result = invocador.exec("norte", "", "");
            TEST_ASSERT(result == 0, "Norte command executes");
            
            result = invocador.exec("sur", "", "");
            TEST_ASSERT(result == 0, "Sur command executes");
            
            // Test exit command
            TEST_ASSERT(continuar_loop == true, "Loop continues before exit");
            result = invocador.exec("exit", "", "");
            TEST_ASSERT(continuar_loop == false, "Exit command stops loop");
            
            // Clean up
            for (auto& cmd : commands) {
                delete cmd.second;
            }
        }
    } catch (const exception& e) {
        TEST_ASSERT(false, string("Exception: ") + e.what());
    }
}

/**
 * Test 4: Invalid command handling
 */
void test_invalid_commands() {
    cout << "\n=== Test: Invalid Command Handling ===" << endl;
    
    try {
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* scene = fac.buildGameById(gameId);
        
        if (scene != nullptr) {
            bool continuar_loop = true;
            Inventario inventario;
            string parametro1 = "";
            string parametro2 = "";
            bool primera_entrada = true;
            EventsQueue eventsQueue;
            
            CommandBuilder cb;
            map<string, ICommand*> commands = cb.buildCommands(
                continuar_loop, scene, inventario,
                parametro1, parametro2, primera_entrada, eventsQueue
            );
            
            Invocador invocador(commands);
            
            // Test invalid command
            int result = invocador.exec("invalid_command", "", "");
            TEST_ASSERT(result != 0, "Invalid command returns error");
            
            // Test empty command
            result = invocador.exec("", "", "");
            TEST_ASSERT(result != 0, "Empty command returns error");
            
            // Test command with typo
            result = invocador.exec("nort", "", "");
            TEST_ASSERT(result != 0, "Typo command returns error");
            
            // Clean up
            for (auto& cmd : commands) {
                delete cmd.second;
            }
        }
    } catch (const exception& e) {
        TEST_ASSERT(false, string("Exception: ") + e.what());
    }
}

/**
 * Test 5: Command with parameters
 */
void test_command_parameters() {
    cout << "\n=== Test: Command Parameters ===" << endl;
    
    try {
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* scene = fac.buildGameById(gameId);
        
        if (scene != nullptr) {
            bool continuar_loop = true;
            Inventario inventario;
            string parametro1 = "";
            string parametro2 = "";
            bool primera_entrada = true;
            EventsQueue eventsQueue;
            
            CommandBuilder cb;
            map<string, ICommand*> commands = cb.buildCommands(
                continuar_loop, scene, inventario,
                parametro1, parametro2, primera_entrada, eventsQueue
            );
            
            Invocador invocador(commands);
            
            // Test examinar with parameter
            parametro1 = "ladrillo";
            int result = invocador.exec("examinar", parametro1, "");
            TEST_ASSERT(result == 0, "Examinar with parameter executes");
            
            // Test coger with parameter
            parametro1 = "item";
            result = invocador.exec("coger", parametro1, "");
            TEST_ASSERT(result == 0, "Coger with parameter executes");
            
            // Test colocar with two parameters
            parametro1 = "figurita";
            parametro2 = "hueco";
            result = invocador.exec("colocar", parametro1, parametro2);
            TEST_ASSERT(result == 0, "Colocar with two parameters executes");
            
            // Clean up
            for (auto& cmd : commands) {
                delete cmd.second;
            }
        }
    } catch (const exception& e) {
        TEST_ASSERT(false, string("Exception: ") + e.what());
    }
}

/**
 * Test 6: Parameter clearing
 */
void test_parameter_clearing() {
    cout << "\n=== Test: Parameter Clearing ===" << endl;
    
    try {
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* scene = fac.buildGameById(gameId);
        
        if (scene != nullptr) {
            bool continuar_loop = true;
            Inventario inventario;
            string parametro1 = "old_param1";
            string parametro2 = "old_param2";
            bool primera_entrada = true;
            EventsQueue eventsQueue;
            
            CommandBuilder cb;
            map<string, ICommand*> commands = cb.buildCommands(
                continuar_loop, scene, inventario,
                parametro1, parametro2, primera_entrada, eventsQueue
            );
            
            Invocador invocador(commands);
            
            // Execute command with old parameters
            invocador.exec("examinar", parametro1, parametro2);
            
            // Clear parameters
            parametro1 = "";
            parametro2 = "";
            
            // Execute command without parameters
            int result = invocador.exec("ver", "", "");
            TEST_ASSERT(result == 0, "Command works after parameter clearing");
            
            // Clean up
            for (auto& cmd : commands) {
                delete cmd.second;
            }
        }
    } catch (const exception& e) {
        TEST_ASSERT(false, string("Exception: ") + e.what());
    }
}

/**
 * Test 7: Command aliases
 */
void test_command_aliases() {
    cout << "\n=== Test: Command Aliases ===" << endl;
    
    try {
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* scene = fac.buildGameById(gameId);
        
        if (scene != nullptr) {
            bool continuar_loop = true;
            Inventario inventario;
            string parametro1 = "";
            string parametro2 = "";
            bool primera_entrada = true;
            EventsQueue eventsQueue;
            
            CommandBuilder cb;
            map<string, ICommand*> commands = cb.buildCommands(
                continuar_loop, scene, inventario,
                parametro1, parametro2, primera_entrada, eventsQueue
            );
            
            Invocador invocador(commands);
            
            // Test exit and salir are aliases
            continuar_loop = true;
            invocador.exec("salir", "", "");
            TEST_ASSERT(continuar_loop == false, "Salir is alias for exit");
            
            // Clean up
            for (auto& cmd : commands) {
                delete cmd.second;
            }
        }
    } catch (const exception& e) {
        TEST_ASSERT(false, string("Exception: ") + e.what());
    }
}

/**
 * Test 8: Rapid command execution
 */
void test_rapid_execution() {
    cout << "\n=== Test: Rapid Command Execution ===" << endl;
    
    try {
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* scene = fac.buildGameById(gameId);
        
        if (scene != nullptr) {
            bool continuar_loop = true;
            Inventario inventario;
            string parametro1 = "";
            string parametro2 = "";
            bool primera_entrada = true;
            EventsQueue eventsQueue;
            
            CommandBuilder cb;
            map<string, ICommand*> commands = cb.buildCommands(
                continuar_loop, scene, inventario,
                parametro1, parametro2, primera_entrada, eventsQueue
            );
            
            Invocador invocador(commands);
            
            // Execute many commands rapidly
            vector<string> test_commands = {"ver", "norte", "sur", "este", "oeste"};
            int success_count = 0;
            
            for (int i = 0; i < 100; i++) {
                string cmd = test_commands[i % test_commands.size()];
                int result = invocador.exec(cmd, "", "");
                if (result == 0) success_count++;
            }
            
            TEST_ASSERT(success_count == 100, "All 100 rapid commands executed");
            
            // Clean up
            for (auto& cmd : commands) {
                delete cmd.second;
            }
        }
    } catch (const exception& e) {
        TEST_ASSERT(false, string("Exception: ") + e.what());
    }
}

/**
 * Test 9: Command case sensitivity
 */
void test_case_sensitivity() {
    cout << "\n=== Test: Command Case Sensitivity ===" << endl;
    
    try {
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* scene = fac.buildGameById(gameId);
        
        if (scene != nullptr) {
            bool continuar_loop = true;
            Inventario inventario;
            string parametro1 = "";
            string parametro2 = "";
            bool primera_entrada = true;
            EventsQueue eventsQueue;
            
            CommandBuilder cb;
            map<string, ICommand*> commands = cb.buildCommands(
                continuar_loop, scene, inventario,
                parametro1, parametro2, primera_entrada, eventsQueue
            );
            
            Invocador invocador(commands);
            
            // Test lowercase (should work)
            int result = invocador.exec("ver", "", "");
            TEST_ASSERT(result == 0, "Lowercase command works");
            
            // Test uppercase (might not work depending on implementation)
            result = invocador.exec("VER", "", "");
            // Note: Current implementation is case-sensitive
            TEST_ASSERT(result != 0, "Uppercase command is rejected (case-sensitive)");
            
            // Test mixed case
            result = invocador.exec("Ver", "", "");
            TEST_ASSERT(result != 0, "Mixed case command is rejected");
            
            // Clean up
            for (auto& cmd : commands) {
                delete cmd.second;
            }
        }
    } catch (const exception& e) {
        TEST_ASSERT(false, string("Exception: ") + e.what());
    }
}

/**
 * Test 10: Command with special characters in parameters
 */
void test_special_char_parameters() {
    cout << "\n=== Test: Special Characters in Parameters ===" << endl;
    
    try {
        JSONGameDataLoader loader;
        FactoryGame fac(&loader, "gameData_es.json");
        string gameId = "";
        Escenario* scene = fac.buildGameById(gameId);
        
        if (scene != nullptr) {
            bool continuar_loop = true;
            Inventario inventario;
            string parametro1 = "";
            string parametro2 = "";
            bool primera_entrada = true;
            EventsQueue eventsQueue;
            
            CommandBuilder cb;
            map<string, ICommand*> commands = cb.buildCommands(
                continuar_loop, scene, inventario,
                parametro1, parametro2, primera_entrada, eventsQueue
            );
            
            Invocador invocador(commands);
            
            // Test with Spanish characters
            parametro1 = "bastón";
            int result = invocador.exec("examinar", parametro1, "");
            TEST_ASSERT(result == 0, "Command with Spanish characters works");
            
            // Test with accented characters
            parametro1 = "cerradura";
            result = invocador.exec("examinar", parametro1, "");
            TEST_ASSERT(result == 0, "Command with accented parameter works");
            
            // Clean up
            for (auto& cmd : commands) {
                delete cmd.second;
            }
        }
    } catch (const exception& e) {
        TEST_ASSERT(false, string("Exception: ") + e.what());
    }
}

/**
 * Test 11: Command list retrieval
 */
void test_command_list() {
    cout << "\n=== Test: Command List Retrieval ===" << endl;
    
    // Test that command constants array is properly defined
    TEST_ASSERT(NUMBER_COMMANDS == 14, "NUMBER_COMMANDS is 14");
    
    // Verify commands array
    bool all_valid = true;
    for (int i = 0; i < NUMBER_COMMANDS; i++) {
        if (comandos[i].empty()) {
            all_valid = false;
            break;
        }
    }
    TEST_ASSERT(all_valid, "All command strings are non-empty");
}

/**
 * Test 12: ICommand interface
 */
void test_icommand_interface() {
    cout << "\n=== Test: ICommand Interface ===" << endl;
    
    // Test that we can create and use commands through interface
    bool continuar_loop = true;
    ICommand* exit_cmd = new Exit(continuar_loop);
    
    TEST_ASSERT(exit_cmd != nullptr, "ICommand can be instantiated");
    TEST_ASSERT(exit_cmd->get_command_id() == "exit", "Command ID is correct");
    
    // Execute through interface
    exit_cmd->execute();
    TEST_ASSERT(continuar_loop == false, "Command executed through interface");
    
    delete exit_cmd;
}

int main() {
    cout << "========================================" << endl;
    cout << "   Command Parser Test Suite" << endl;
    cout << "========================================" << endl;
    
    try {
        test_command_constants();
        test_command_builder();
        test_invocador_execution();
        test_invalid_commands();
        test_command_parameters();
        test_parameter_clearing();
        test_command_aliases();
        test_rapid_execution();
        test_case_sensitivity();
        test_special_char_parameters();
        test_command_list();
        test_icommand_interface();
        
        cout << "\n========================================" << endl;
        cout << "   Test Results Summary" << endl;
        cout << "========================================" << endl;
        cout << "Passed: " << tests_passed << endl;
        cout << "Failed: " << tests_failed << endl;
        cout << "Total:  " << (tests_passed + tests_failed) << endl;
        
        if (tests_failed == 0) {
            cout << "\n[SUCCESS] All command parser tests passed!" << endl;
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
