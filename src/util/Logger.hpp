#ifndef SOKOBAN_LOGGER_HPP
#define SOKOBAN_LOGGER_HPP

#include <string>

namespace sokoban
{
    namespace util
    {
        enum LoggerLevel
        {
            TRACE, /** The lowest level of importance leaving nothing but the existance of the information */
            DEBUG, /** Debugging information meant for developers */
            INFO, /** Textual information meant for the user */
            WARNING, /** Warning information concerning the program's execution */
            ERROR, /** Critical information that requires patch fix */
            FATAL /** Prioritary level of logging that requires immediate fix */
        };

        class Logger
        {
        private:
            std::string _id; /** The logger's unique ID */
            std::string _file_name; /** The logger's name */
        public:
            Logger( const std::string &id, const std::string &file_name );
            explicit Logger( const std::string &id );
            ~Logger();
            std::string get_id();
            std::string get_file_name();
            static void log( int level, const std::string &log_message );
        };
    }
}

#endif //SOKOBAN_LOGGER_HPP
