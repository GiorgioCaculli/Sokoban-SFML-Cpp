#ifndef SOKOBAN_LOGGER_HPP
#define SOKOBAN_LOGGER_HPP

#include <string>

namespace sokoban
{
    namespace util
    {
        enum LoggerLevel
        {
            TRACE,
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            FATAL
        };

        class Logger
        {
        private:
            std::string _id;
            std::string _file_name;
        public:
            Logger( const std::string &id, const std::string &file_name );
            explicit Logger( const std::string &id );
            ~Logger();
            std::string get_id();
            std::string get_file_name();
            void log( int level, const std::string &log_message );
        };
    }
}

#endif //SOKOBAN_LOGGER_HPP
