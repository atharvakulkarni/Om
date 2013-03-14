/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Sources_ContainerBackSource_

	#include "om/sources/container_back_source.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	namespace Sources {

		BOOST_AUTO_TEST_SUITE(ContainerBackSourceTest)

		BOOST_AUTO_TEST_SUITE_END()

	}

}

	#endif

#else

// MARK: - Om::Sources::ContainerBackSource

	#define Template_ \
	template < \
		typename ThisItem, \
		typename ThisContainer \
	>

	#define Type_ \
	Om::Sources::ContainerBackSource< \
		ThisItem, \
		ThisContainer \
	>

// MARK: public (non-static)

Template_
inline Type_::ContainerBackSource(ThisContainer & theContainer):
thisContainer(theContainer) {}

Template_
inline Type_ & Type_::operator =(ContainerBackSource theContainerBackSource) {
	this->Swap(theContainerBackSource);
	return *this;
}

Template_
inline bool Type_::operator !() const {
	return this->thisContainer.empty();
}

Template_
inline ThisItem & Type_::operator *() const {
	assert(
		!this->thisContainer.empty()
	);
	return this->thisContainer.back();
}

Template_
inline void Type_::Pop() {
	assert(
		!this->thisContainer.empty()
	);
	this->thisContainer.pop_back();
}

Template_
inline void Type_::Swap(ContainerBackSource & theContainerBackSource) {
	boost::swap(
		this->thisContainer,
		theContainerBackSource.thisContainer
	);
}

	#undef Type_
	#undef Template_

// MARK: - Om::Sources::

	#define Template_ \
	template < \
		typename TheItem, \
		typename TheContainer \
	>

	#define Type_ \
	Om::Sources::ContainerBackSource< \
		TheItem, \
		TheContainer \
	>

Template_
inline bool Om::Sources::operator ==(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return (
		(&theFirst.thisContainer == &theSecond.thisContainer) ||
		(
			theFirst.thisContainer.empty() &&
			theSecond.thisContainer.empty()
		)
	);
}

Template_
inline bool Om::Sources::operator !=(
	Type_ const & theFirst,
	Type_ const & theSecond
) {
	return !(theFirst == theSecond);
}

// MARK: - boost::

Template_
inline void boost::swap(
	Type_ & theFirst,
	Type_ & theSecond
) {
	theFirst.Swap(theSecond);
}

	#undef Type_
	#undef Template_

#endif
