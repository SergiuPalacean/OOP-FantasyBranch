#pragma once
#include <exception>
#include <string>
#include <stdexcept>


class RepositoryError : public std::exception
{
public:
    explicit RepositoryError(const std::string& error_message) :
        what_(error_message) {}

    virtual const char* what() const throw ()
    {
        return what_.c_str();
    }

    virtual ~RepositoryError() throw () {}
private:
    std::string what_;
};

class ValidationError : public std::exception
{
public:
    explicit ValidationError(const std::string& error_message) :
        what_(error_message) {}

    virtual const char* what() const throw ()
    {
        return what_.c_str();
    }

    virtual ~ValidationError() throw () {}
private:
    std::string what_;
};

class ServiceError : public std::exception
{
public:
    explicit ServiceError(const std::string& error_message) :
        what_(error_message) {}

    virtual const char* what() const throw ()
    {
        return what_.c_str();
    }

    virtual ~ServiceError() throw () {}
private:
    std::string what_;
};

class ServiceWatchmenError : public std::exception
{
public:
    explicit ServiceWatchmenError(const std::string& error_message) :
        what_(error_message) {}

    virtual const char* what() const throw ()
    {
        return what_.c_str();
    }

    virtual ~ServiceWatchmenError() throw () {}
private:
    std::string what_;
};
