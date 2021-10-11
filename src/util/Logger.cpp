#include "Logger.hpp"

#include <iostream>

#include <boost/locale/generator.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>

using namespace sokoban::util;
namespace logging = boost::log;

template< typename CharT, typename TraitsT >
    inline std::basic_ostream< CharT, TraitsT > &operator<<(
            std::basic_ostream< CharT, TraitsT > &strm, logging::trivial::severity_level lvl )
    {
        static const char *const str[] =
                {
                        "trace", "debug", "info", "warning", "error", "fatal"
                };
        if ( static_cast< std::size_t >(lvl) < ( sizeof( str ) / sizeof( *str ) ) )
        {
            strm << str[ lvl ];
        }
        else
        {
            strm << static_cast< int >(lvl);
        }
        return strm;
    }

BOOST_LOG_ATTRIBUTE_KEYWORD( severity, "Severity", logging::trivial::severity_level )
BOOST_LOG_ATTRIBUTE_KEYWORD( timestamp, "TimeStamp", boost::posix_time::ptime )

Logger::Logger( const std::string &id, const std::string &file_name )
{
    this->_id = id;
    this->_file_name = file_name;

    boost::shared_ptr< logging::sinks::synchronous_sink< logging::sinks::text_file_backend > > sink = logging::add_file_log
            (
                    logging::keywords::file_name = get_file_name(),
                    logging::keywords::rotation_size = 10 * 1024 * 1024,
                    logging::keywords::time_based_rotation = logging::sinks::file::rotation_at_time_point( 0, 0, 0 ),
                    logging::keywords::format = logging::expressions::stream
                            << logging::expressions::format_date_time( timestamp, "%Y-%m-%d, %H:%M:%S.%f" )
                            << " <" << severity.or_default( logging::trivial::trace )
                            << "> " << logging::expressions::message,
                    logging::keywords::auto_flush = true,
                    logging::keywords::open_mode = std::ios_base::app
            );

    std::locale loc = boost::locale::generator()( "en_US.UTF-8" );
    sink->imbue( loc );

    //logging::core::get()->set_filter( severity >= logging::trivial::info );

    logging::add_common_attributes();

    //logging::sources::severity_logger<logging::trivial::severity_level> lg;
}

Logger::Logger( const std::string &id )
        : Logger( id, "sokoban.log" )
{

}

Logger::~Logger()
{
    std::cout << "logger ID: " << get_id() << std::endl;
}

std::string Logger::get_id()
{
    return _id;
}

std::string Logger::get_file_name()
{
    return _file_name;
}

void Logger::log( int level, const std::string &log_message )
{
    using namespace logging::trivial;

    const char *message = log_message.c_str();

    switch ( level )
    {
    case LoggerLevel::TRACE:
        BOOST_LOG_TRIVIAL( trace ) << message;
        break;
    case LoggerLevel::DEBUG:
        BOOST_LOG_TRIVIAL( debug ) << message;
        break;
    case LoggerLevel::INFO:
        BOOST_LOG_TRIVIAL( info ) << message;
        break;
    case LoggerLevel::WARNING:
        BOOST_LOG_TRIVIAL( warning ) << message;
        break;
    case LoggerLevel::ERROR:
        BOOST_LOG_TRIVIAL( error ) << message;
        break;
    case LoggerLevel::FATAL:
        BOOST_LOG_TRIVIAL( fatal ) << message;
        break;
    default:
        BOOST_LOG_TRIVIAL( trace ) << message;
        break;
    }
}
