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

    /**
     * @class DlException
     * @brief Exception class for dlloader
     *
     */
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

    /**
     * @brief DlLoader is a class to load shared libraries to unique_ptr of the TLoad type
     *
     * @tparam TLoad - template class to load into unique_ptr
     * @return - TLoad &
     */
    template <class TLoad> class DlLoader
    {
        public:
            DlLoader() = default;

            DlLoader(DlLoader const &to_copy) = delete;
            DlLoader(DlLoader &&to_move) = default;

            /**
             * @brief Destructor for DlLoader. Release unique_ptr and dlclose handler
             */
            ~DlLoader()
            {
                this->element.release();
                if (this->handle)
                    dlclose(this->handle);
            }

            DlLoader &operator=(DlLoader const &to_copy) = delete;
            DlLoader &operator=(DlLoader &&to_move) = default;

            /* methods */
            /**
             * @brief Get a reference to TLoad
             *
             * @return TLoad &
             */
            TLoad &get_class() const
            {
                return *this->element.get();
            }

            /**
             * @brief Release the pointer to TLoad. Will then be equal to nullptr
             */
            void release()
            {
                this->element.release();
                this->element = nullptr;
            }

            /**
             * @brief Init the class. Load the TLoad class from a shared library using a function
             * with TSignature * signature
             *
             * @tparam TSignature - signature for the function -
             * https://stackoverflow.com/questions/26792750/function-signatures-in-c-templates
             * @tparam TValues - variadic templates, values to pass to TSignature loading function
             * @param path - path to shared libraries
             * @param loader_func - name of the loader function
             * @param values - TValues ...
             */
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
            explicit DlException(std::string p_error = "Error") : error_msg{std::move(p_error)}
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

    /**
     * @brief Windows version of dlloader class
     *
     * @tparam TLoad - template of the class to load
     * @return TLoad &
     */
    template <class TLoad> class DlLoader
    {
        public:
            DlLoader() = default;

            DlLoader(DlLoader const &to_copy) = delete;
            DlLoader(DlLoader &&to_move) = default;

            /**
             * @brief delete pointer to TLoad, and free handle to shared library
             */
            ~DlLoader()
            {
                delete this->element;
                if (this->handle)
                    FreeLibrary(this->handle);
            }

            DlLoader &operator=(DlLoader const &to_copy) = delete;
            DlLoader &operator=(DlLoader &&to_move) = default;

            /* methods */
            /**
             * @brief Get a reference of TLoad
             *
             * @return TLoad &
             */
            TLoad &get_class() const
            {
                return *this->element;
            }

            /**
             * @brief Release the pointer to TLoad. Will then be equal to nullptr
             */
            void release()
            {
                delete this->element;
                this->element = nullptr;
            }

            /**
             * @brief Load shared library element into TLoad * with windows methods LoadLibrary and
             * GetProcAddress
             *
             * @tparam TSignature - signature for the function - must return void * -
             * https://stackoverflow.com/questions/26792750/function-signatures-in-c-templates
             * @tparam TValues - variadic templates, values to pass to TSignature loading function
             * @param path - path to shared libraries
             * @param loader_func - name of the loader function
             * @param values - TValues ...
             */
            template <typename TSignature, typename... TValues>
            void init_class(std::string const &path,
                            std::string const &loader_func = DEFAULT_LOADER.data(),
                            TValues &&...values)
            {
                this->handle = LoadLibrary(path.c_str());
                void *load_variable{nullptr};

                if (!this->handle) {
                    throw DlException(std::string{"error"});
                }
                auto *loader{reinterpret_cast<TSignature *>(
                    GetProcAddress(this->handle, loader_func.data()))};
                if (!loader)
                    throw DlException(ERROR_FETCH_LOADER.data());
                if (!(load_variable = loader(std::forward<TValues>(values)...)))
                    throw DlException(ERROR_LOAD_CLASS.data());
                this->element = static_cast<TLoad *>(load_variable);
            }

            /* exception */

        private:
            HMODULE handle{nullptr};
            TLoad *element{nullptr};
    };

} // namespace dl

#endif /* __linux */
