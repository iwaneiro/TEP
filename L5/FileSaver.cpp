#include "FileSaver.h"
#include <iostream>

void FileSaver::save(const std::string& filename, const Result<Tree*, Error>& result) {
    std::ofstream file(filename.c_str());
    
    if (!file.is_open()) {
        // Błąd otwarcia
        std::cout << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    if (result.isSuccess()) {
        Tree* tree = result.getValue();
        if (tree) {
            tree->print(file);
        } else {
            file << "Tree is null.";
        }
    } else {
        std::vector<Error*> errors = result.getErrors();
        file << "Errors found (" << errors.size() << "):" << std::endl;
        for (size_t i = 0; i < errors.size(); ++i) {
            file << errors[i]->getMessage() << std::endl;
        }
    }

    file.close();
    std::cout << "Saved result to " << filename << std::endl;
}