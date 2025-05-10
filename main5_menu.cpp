// === main5_menu.cpp ===
#include "functions.h"
#include <iostream>
#include <limits>

int main() {
    // Load all blocks from the "data" directory
    std::vector<Block> blocks = LoadDatabase("data");
    int choice;

    // Main menu loop
    do {
        std::cout << "\n==== Bitcoin Block Menu ====" << std::endl;
        std::cout << "1. Print all blocks" << std::endl;
        std::cout << "2. Search block by hash" << std::endl;
        std::cout << "3. Search block by height" << std::endl;
        std::cout << "4. Export blocks to CSV" << std::endl;
        std::cout << "5. Reload new blocks from API" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Select option: ";

        std::cin >> choice;

        // Handle invalid input (e.g. letters instead of numbers)
        if (std::cin.fail()) {
            std::cin.clear(); // Reset the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue; // Restart the loop
        }

        std::cin.ignore(); // Clear leftover newline from buffer

        switch (choice) {
            case 1:
                // Print all loaded blocks
                PrintAllBlocks(blocks);
                break;
            case 2: {
                // Search block by its hash
                std::string hash;
                std::cout << "Enter hash: ";
                std::getline(std::cin, hash);
                const Block* result = FindBlockByHash(blocks, hash);
                if (result) {
                    PrintBlock(*result);
                } else {
                    std::cout << "Block with hash " << hash << " not found." << std::endl;
                }
                break;
            }
            case 3: {
                // Search block by its height
                int height;
                std::cout << "Enter height: ";
                std::cin >> height;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Height must be a number." << std::endl;
                    break;
                }
                std::cin.ignore();
                const Block* result = FindBlockByHeight(blocks, height);
                if (result) {
                    PrintBlock(*result);
                } else {
                    std::cout << "Block with height " << height << " not found." << std::endl;
                }
                break;
            }
            case 4:
                // Export all blocks to a CSV file
                ExportToCSV(blocks, "output.csv");
                break;
            case 5: {
                // Download new blocks from API and reload the database
                int count;
                std::cout << "Enter number of blocks to download: ";
                std::cin >> count;
                if (std::cin.fail() || count <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a positive number." << std::endl;
                    break;
                }
                std::cin.ignore();
                ReloadBlocksFromScript("./fetch_blocks.sh", count);
                blocks = LoadDatabase("data"); // Reload updated blocks
                break;
            }
            case 0:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
