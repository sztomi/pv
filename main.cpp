#include <iostream>
#include <memory>

#include "SDL/SDL.h"

#include "logger.h"
#include "cli_parser.h"

using namespace pv;
using std::auto_ptr;

int main( int argc, char* argv[] )
{
	CliParser cpar( argc, argv );
	cpar.display();

	auto_ptr<SDL_Surface> screen( SDL_SetVideoMode(640, 480, 24, SDL_HWSURFACE) );

	if ( screen.get() == NULL )
	{
		Logger::error( "Could not SDL_SetVideoMode" );
	}
}

