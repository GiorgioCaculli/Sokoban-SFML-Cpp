#ifndef SOKOBAN_LOGGER_HPP
#define SOKOBAN_LOGGER_HPP

#include <string>

namespace util
{
    class Logger
    {
    private:
        std::string _id; /** The logger's unique ID */
        std::string _file_name; /** The logger's name */
        bool _debug;
        static void init( const std::string &file_name ) ;
    public:
        enum Level
        {
            TRACE, /** The lowest level of importance leaving nothing but the existence of the information */
            DEBUG, /** Debugging information meant for developers */
            INFO, /** Textual information meant for the user */
            WARNING, /** Warning information concerning the program's execution */
            ERROR, /** Critical information that requires patch fix */
            FATAL /** Priority level of logging that requires immediate fix */
        };
        Logger( std::string id, std::string file_name, bool debug );
        ~Logger();
        std::string get_id() const;
        std::string get_file_name() const;
        void log( Level, const std::string &log_message ) const;
    };
}

#endif //SOKOBAN_LOGGER_HPP
