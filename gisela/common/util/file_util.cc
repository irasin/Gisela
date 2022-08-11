#include "common/util/file_util.h"

#include <string>
#include <vector>

namespace gisela {
namespace common {
namespace util {

bool ReadFile(const std::string& path, char** data, size_t size) {
    return true;
}

bool ReadFile(const std::string& path, std::string* res) {
    return true;
}

bool ReadFile(const std::string& path, std::vector<std::string>* lines) {
    return true;
}

}  // namespace util
}  // namespace common
}  // namespace gisela
