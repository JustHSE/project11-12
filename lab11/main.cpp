#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>

void print_inventory(const std::vector<std::string>& inv) {
    std::cout << "Текущий инвентарь: [ ";
    std::copy(inv.begin(), inv.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << "]\n";
}

int main() {
    std::vector<std::string> inventory;
    std::string input_line;

    std::cout << "Команды: add <предметы...>, remove <предмет>, exit" << std::endl;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, input_line)) break;

        std::istringstream iss(input_line);
        std::string command;
        iss >> command;

        if (command == "exit") {
            break;
        } 
        else if (command == "add") {
            std::copy(std::istream_iterator<std::string>(iss),
                      std::istream_iterator<std::string>(),
                      std::back_inserter(inventory));
        } 
        else if (command == "remove") {
            std::string item;
            iss >> item;
            auto new_end = std::remove(inventory.begin(), inventory.end(), item);
            if (new_end != inventory.end()) {
                inventory.erase(new_end, inventory.end());
                std::cout << "Предмет '" << item << "' удален" << std::endl;
            } else {
                std::cout << "Предмет не найден." << std::endl;
            }
        } 
        else if (!command.empty()) {
            std::cout << "Неизвестная команда!" << std::endl;
        }

        if (!command.empty() && command != "exit") {
            print_inventory(inventory);
        }
    }

    return 0;
}
