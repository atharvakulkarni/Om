/*!
\file
	\brief
		Om hpp file.
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
#if !defined( Om_Sinks_StreamSink_ )
	#define Om_Sinks_StreamSink_ Om::Sinks::StreamSink

	#include "om/sinks/iterator_sink.hpp"

namespace Om
{
	namespace Sinks
	{
		// MARK: - Om::Sinks::StreamSink
		/*!
		\brief
			A Sink adapter for an output stream.
		*/
		template< typename ThisItem = char >
		struct StreamSink
		:
		IteratorSink< ThisItem const, std::ostreambuf_iterator< ThisItem > >
		{
			// MARK: public (non-static)
			explicit StreamSink( std::ostream & );
		};
	}
}

	#include "om/sinks/stream_sink.cpp"
#endif