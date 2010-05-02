#include <iostream>
#include <memory>

#include "SDL/SDL.h"

#include "logger.h"

using namespace pv;
using std::auto_ptr;

int main( int argc, char* argv[] )
{
	auto_ptr<SDL_Surface> screen( SDL_SetVideoMode(640, 480, 24, SDL_HWSURFACE) );
	
	Logger::message( "Hello from pv" );

	if ( screen.get() == NULL )
	{
		Logger::error( "Could not SDL_SetVideoMode" );
	}
}

