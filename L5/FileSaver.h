#ifndef FILESAVER_H
#define FILESAVER_H

#include <string>
#include <fstream>
#include <vector>
#include "Result.h"
#include "Tree.h"
#include "Error.h"

class FileSaver {
public:
    void save(const std::string& filename, const Result<Tree*, Error>& result);


    template <typename T>
    void save(const std::string& filename, const Result<T, Error>& result) {
        std::ofstream file(filename.c_str());
        if (!file.is_open()) return;

        if (!result.isSuccess()) {
            std::vector<Error*> errors = result.getErrors();
            file << "Errors found (" << errors.size() << "):" << std::endl;
            for (size_t i = 0; i < errors.size(); ++i) {
                file << errors[i]->getMessage() << std::endl;
            }
        } else {
            file << "Operation successful. No errors to report." << std::endl;
        }
        file.close();
    }
};

#endif //FILESAVER_H