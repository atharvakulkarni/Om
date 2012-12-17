/*!
\file
	\brief
		Om cpp file.
	\version
		0.1
	\date
		2012
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are
		made available under the terms of the
		<a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse
		Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/
#if defined( Om_Moveable_ )

// MARK: Om::Moveable

	#define Type_ Om::Moveable

// MARK: public (non-static)

inline Type_::~Moveable()
{
}

// MARK: private (non-static)

inline Type_ * Type_::Move()
{
	assert( 0 );
	throw( std::logic_error( "Pure virtual function called." ) );
}

	#undef Type_

#else
	#include "om/moveable.hpp"
#endif