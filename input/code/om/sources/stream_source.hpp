/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.3
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Sources_StreamSource_

	#define Om_Sources_StreamSource_ \
	Om::Sources::StreamSource

	#include "om/sources/default_source.hpp"

	#ifndef Om_Macros_Precompilation_

		#include "boost/optional.hpp"

	#endif

namespace Om {

	namespace Sources {

		// MARK: - Om::Sources::StreamSource

		/*!
		\brief
			A Source adapter for an input stream.
		\note
			Const methods are not thread-safe due to a non-mutexed mutable member.
		\note
			Dereferencing exposes a reference to a cache of the current item. Modifying the item will not modify the source data.
		*/
		template <typename ThisItem = char>
		class StreamSource:
		public DefaultSource<
			ThisItem const,
			StreamSource<ThisItem>
		> {

		public: // MARK: public (non-static)

			StreamSource();

			explicit StreamSource(std::istream &);

			StreamSource & operator =(StreamSource);

			virtual bool operator !() const;

			virtual ThisItem const & operator *() const;

			using DefaultSource<
				ThisItem const,
				StreamSource<ThisItem>
			>::Equals;

			bool Equals(StreamSource const &) const;

			virtual void Pop();

			void Swap(StreamSource &);

		private: // MARK: private (static)

			typedef std::istreambuf_iterator<ThisItem> StreamIterator;

		private: // MARK: private (non-static)

			StreamIterator thisStreamIterator;

			/*!
			\brief
				The current item.
			*/
			mutable boost::optional<ThisItem> thisItem;

		};

		// MARK: - Om::Sources::

		template <typename TheItem>
		bool operator ==(
			StreamSource<TheItem> const &,
			StreamSource<TheItem> const &
		);

		template <typename TheItem>
		bool operator !=(
			StreamSource<TheItem> const &,
			StreamSource<TheItem> const &
		);

	}

}

namespace boost {

	// MARK: - boost::

	template <typename TheItem>
	void swap(
		Om::Sources::StreamSource<TheItem> &,
		Om::Sources::StreamSource<TheItem> &
	);

}

	#include "om/sources/stream_source.cpp"

#endif