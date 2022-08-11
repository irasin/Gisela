#ifndef GISELA_COMMON_UTIL_FILE_UTIL_H_
#define GISELA_COMMON_UTIL_FILE_UTIL_H_

#include <string>
#include <vector>

namespace gisela {
namespace common {
namespace util {

bool ReadFile(const std::string& path, char** data, size_t size);

bool ReadFile(const std::string& path, std::string* res);

bool ReadFile(const std::string& path, std::vector<std::string>* lines);

}  // namespace util
}  // namespace common
}  // namespace gisela

#endif
