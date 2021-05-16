#include <new>
#include <cerrno>

std::new_handler std::get_new_handler() noexcept {
    return nullptr;
}

extern "C" int posix_memaglign(void**, size_t, size_t) {
    return ENOMEM;
}