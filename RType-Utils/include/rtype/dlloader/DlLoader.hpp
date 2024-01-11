/*
** EPITECH PROJECT, 2023
** dlloader
** File description:
** DlLoader
*/

#pragma once

#ifdef __linux

    #include <algorithm>
    #include <dlfcn.h>
    #include <exception>
    #include <functional>
    #include <iostream>
    #include <memory>
    #include <string>
    #include <string_view>
    #include <utility>

namespace dl
{
    constexpr std::string_view DEFAULT_LOADER{"entrypoint"};
    constexpr std::string_view ERROR_FETCH_LOADER{"Unable to fetch loader function."};
    constexpr std::string_view ERROR_LOAD_CLASS{"Could not load class."};

    class DlException : public std::exception
    {
        public:
            DlException(std::string p_error) : error_msg{std::move(p_error)}
            {
            }

            DlException(DlException const &to_copy) = default;
            DlException(DlException &&to_move) = default;
            ~DlException() override = default;
            DlException &operator=(DlException const &to_copy) = default;
            DlException &operator=(DlException &&to_move) = default;

            /* methods */
            [[nodiscard]] const char *what() const noexcept override
            {
                return this->error_msg.c_str();
            }

        private:
            std::string error_msg{"Error"};
    };

    template <class TLoad> class DlLoader
    {
        public:
            DlLoader() = default;

            DlLoader(DlLoader const &to_copy) = delete;
            DlLoader(DlLoader &&to_move) = default;

            ~DlLoader()
            {
                this->element.release();
                if (this->handle)
                    dlclose(this->handle);
            }

            DlLoader &operator=(DlLoader const &to_copy) = delete;
            DlLoader &operator=(DlLoader &&to_move) = default;

            /* methods */
            TLoad &get_class() const
            {
                return *this->element.get();
            }

            template <typename TSignature, typename... TValues>
            void init_class(std::string const &path,
                            std::string const &loader_func = DEFAULT_LOADER.data(),
                            TValues &&...values)
            {
                this->handle = dlopen(path.c_str(), RTLD_LAZY);

                if (!this->handle) {
                    throw DlException(std::string{dlerror()});
                }
                auto *loader{
                    reinterpret_cast<TSignature *>(dlsym(this->handle, loader_func.data()))};
                if (!loader)
                    throw DlException(ERROR_FETCH_LOADER.data());
                if (!(this->element = loader(std::forward<TValues>(values)...)))
                    throw DlException(ERROR_LOAD_CLASS.data());
            }

            /* exception */

        private:
            void *handle{nullptr};
            std::unique_ptr<TLoad> element{nullptr};
    };

} // namespace dl

#else // if _WIN32

    #include <windows.h>

namespace dl
{
    constexpr std::string_view DEFAULT_LOADER{"entrypoint"};
    constexpr std::string_view ERROR_FETCH_LOADER{"Unable to fetch loader function."};
    constexpr std::string_view ERROR_LOAD_CLASS{"Could not load class."};

    class DlException : public std::exception
    {
        public:
            DlException(std::string p_error) : error_msg{std::move(p_error)}
            {
            }

            DlException(DlException const &to_copy) = default;
            DlException(DlException &&to_move) = default;
            ~DlException() override = default;
            DlException &operator=(DlException const &to_copy) = default;
            DlException &operator=(DlException &&to_move) = default;

            /* methods */
            [[nodiscard]] const char *what() const noexcept override
            {
                return this->error_msg.c_str();
            }

        private:
            std::string error_msg{"Error"};
    };

    template <class TLoad> class DlLoader
    {
        public:
            DlLoader() = default;

            DlLoader(DlLoader const &to_copy) = delete;
            DlLoader(DlLoader &&to_move) = default;

            ~DlLoader()
            {
                this->element.release();
                if (this->handle)
                    FreeLibrary(this->handle);
            }

            DlLoader &operator=(DlLoader const &to_copy) = delete;
            DlLoader &operator=(DlLoader &&to_move) = default;

            /* methods */
            TLoad &get_class() const
            {
                return *this->element.get();
            }

            template <typename TSignature, typename... TValues>
            void init_class(std::string const &path,
                            std::string const &loader_func = DEFAULT_LOADER.data(),
                            TValues &&...values)
            {
                this->handle = LoadLibrary(path.c_str(), RTLD_LAZY);

                if (!this->handle) {
                    throw DlException(std::string{dlerror()});
                }
                auto *loader{reinterpret_cast<TSignature *>(
                    GetProcAddress(this->handle, loader_func.data()))};
                if (!loader)
                    throw DlException(ERROR_FETCH_LOADER.data());
                if (!(this->element = loader(std::forward<TValues>(values)...)))
                    throw DlException(ERROR_LOAD_CLASS.data());
            }

            /* exception */

        private:
            HMODULE *handle{nullptr};
            std::unique_ptr<TLoad> element{nullptr};
    };

} // namespace dl

#endif /* os */
