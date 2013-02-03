/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if defined( Om_Operations_FrontPullSeparatorOperation_ )

	#include "om/literal.hpp"
	#include "om/operations/pull_operation.hpp"

// MARK: Om::Operations::FrontPullSeparatorOperation

	#define Type_ \
	Om::Operations::FrontPullSeparatorOperation

// MARK: public (static)

inline char const * Type_::GetName() {
	return( Om_Operations_FrontPullSeparatorOperation_GetName_() );
}

inline void Type_::Give( Evaluation & theEvaluation ) {
	theEvaluation.TakeOperation(
		std::auto_ptr< Operation >(
			new PullOperation<
				Literal,
				FrontPullSeparatorOperation
			>
		)
	);
}

template< typename TheQueue >
inline void Type_::Pull(
	Literal & theLiteral,
	TheQueue & theQueue
) {
	theLiteral.FrontGive< Separator >( theQueue );
}

	#undef Type_

#else

	#include "om/operations/front_pull_separator_operation.hpp"

	#if defined( Om_Macros_Test_ )

		#include "om/system.hpp"
		#include "UnitTest++.h"

// MARK: -

namespace Om {

	namespace Operations {

		SUITE( FrontPullSeparatorOperation ) {

			TEST( Definition ) {
				CHECK_EQUAL(
					"{separator<-elements}",
					System::Get().Evaluate( "drop find {separator<-elements} system" )
				);
			}

			TEST( General ) {
				CHECK_EQUAL(
					"{ }{1{2}}",
					System::Get().Evaluate( "separator<-elements { 1{2}}" )
				);

				CHECK_EQUAL(
					"{}{1{2}}",
					System::Get().Evaluate( "separator<-elements {1{2}}" )
				);

				CHECK_EQUAL(
					"{}{1 2}",
					System::Get().Evaluate( "separator<-elements {1 2}" )
				);

				CHECK_EQUAL(
					"{}{}",
					System::Get().Evaluate( "separator<-elements {}" )
				);

				CHECK_EQUAL(
					"{ }{}",
					System::Get().Evaluate( "separator<-elements { }" )
				);

				CHECK_EQUAL(
					"separator<-elements",
					System::Get().Evaluate( "separator<-elements" )
				);
			}

		}

	}

}

	#endif

#endif
