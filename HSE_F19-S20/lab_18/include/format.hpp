#include <cstddef>  // std::size_t
#include <string>  // std::string

#if __cplusplus < 201703L
#error At least C++17 is required
#endif

namespace format {
template<typename> struct FormatHelper {
    // To demonstrate the public interface.
    std::size_t estimate_size() const = delete;
    void append_to(std::string &) const = delete;
};

template<typename T>
std::string make_string(const T &value) {
    FormatHelper<T> helper(value);  // Explicit!
    std::string formatted;
    formatted.reserve(helper.estimate_size());
    helper.append_to(formatted);
    formatted.shrink_to_fit();
    return formatted;
}
}  // namespace format
