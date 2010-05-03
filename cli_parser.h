#ifndef _CMDPARSER_H
#define _CMDPARSER_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <exception>

#define log(x) std::cout << #x << std::endl

using std::vector;
using std::string;
using std::map;

namespace pv 
{

class parser_exception : public std::exception
{
};

/**
 * Class to parse commandline and call associated functions.
 */
class CliParser
{
private:
	vector<string> args;
	map<string, string> options_args;

	CliParser() {}
	CliParser(const CliParser& c) {}

	enum parser_state { WHITESPACE, ARGUMENT, SHORTOPT, LONGOPT,
						SHORTOPT_WAIT, LONGOPT_WAIT, OPT_READ, ERROR };

	void parse()
	{
		parser_state state = WHITESPACE;
		string last_opt = "";
		vector<string>::iterator it = args.begin();
		++it;

		for( ; it != args.end(); ++it )
		{
			std::cout << *it << std::endl;
			for ( int i = 0; i < (*it).length(); ++i )
			{
				switch ( state )
				{
				case WHITESPACE:
					log(WHITESPACE);
					if ( (*it)[i] == '-' )		state = SHORTOPT_WAIT;
					else if ( isspace( (*it)[i] ) )	state = WHITESPACE;
					else state = ARGUMENT;
				continue;

				case SHORTOPT_WAIT:		
					log(SHORTOPT_WAIT);
					if ( (*it)[i] == '-' )			state = LONGOPT_WAIT;
					else if ( isspace( (*it)[i] ) )	state = ERROR;
					else							state = SHORTOPT;
				continue;

				case SHORTOPT:
					log(SHORTOPT);
					if ( !isspace( (*it)[i] ) )	state = ERROR;
					else
					{
						last_opt = (*it);
						state = OPT_READ;
					}
				continue;

				case LONGOPT_WAIT:
					log(LONGOPT_WAIT);
					if ( (*it)[i] == '-' || isspace( (*it)[i] ) )	state = ERROR;
					else
					{
						state = LONGOPT;
					}
				continue;

				case LONGOPT:
					log(LONGOPT);
					if ( isspace( (*it)[i] ) )
					{
						last_opt = (*it);
						state = OPT_READ;
					}
				continue;

				case OPT_READ:
					log(OPT_READ);
					if ( (*it)[i] == '-' )
					{
						options_args[last_opt] = "";
						last_opt = "";
						state = SHORTOPT_WAIT;
					}
					else if ( isspace( (*it)[i] ) )	state = OPT_READ;
					else							state = ARGUMENT;
				continue;

				case ARGUMENT:
					log(ARGUMENT);
					if ( isspace( (*it)[i] ) )
					{
						options_args[last_opt] = (*it);
						last_opt = "";
						state = WHITESPACE;
					}
					else										state = ARGUMENT;
				continue;

				case ERROR:
					log(ERROR);
					// throw new parser_exception("A ló meghal, a madarak kirepülnek");
					throw parser_exception();
				break;

				}
			}
			
			if ( state == LONGOPT || state == SHORTOPT )
			{
				state = OPT_READ;
				last_opt = *it;
			}
			else if ( state == SHORTOPT_WAIT )
			{
				state = OPT_READ;
				last_opt = *it;
			}
			else if ( state == ARGUMENT )
			{
				options_args[last_opt] = (*it);
				last_opt = "";
				state = WHITESPACE;
			}
			else
			{
				state = WHITESPACE;
			}
		}
	}

public:

	/**
	 * Constructor.
	 * @param argc The number of arguments, usually argc param of main.
	 * @param argv Array of argument strings, usually argv param of main.
	 */
	CliParser( int argc, char* argv[] )
	{
		for ( int i = 0; i < argc; ++i )
		{
			args.push_back( string(argv[i]) );
		}

		parse();
	}

	void display()
	{
		for ( map<string, string>::iterator it = options_args.begin();
			  it != options_args.end();
			  ++it
			)
		{
			std::cout << "[" << it->first << "] = " << "'" << it->second << "'" << std::endl;
		}

	}
};

}
#endif
