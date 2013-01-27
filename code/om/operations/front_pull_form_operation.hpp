/*!
\file
	\brief
		Om hpp file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) Jason Erb.
		All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_FrontPullFormOperation_ )

	#define Om_Operations_FrontPullFormOperation_ \
	Om::Operations::FrontPullFormOperation

	#include "om/definition.hpp"

	#define Om_Operations_FrontPullFormOperation_GetName_() \
	"<-forms"

namespace Om
{
	//! \cond
	struct Expression;
	//! \endcond

	namespace Operations
	{
		// MARK: - Om::Operations::FrontPullFormOperation
		/*!
		\brief
			The \ref front_pull_form_operation Operation implementation.
		*/
		struct FrontPullFormOperation
		{
		public: // MARK: public (static)

			static char const * GetName();

			static void Give( Evaluation & );

			//! The callback for PullOperation.
			template< typename TheQueue >
			static void Pull(
				Expression &,
				TheQueue &
			);
		};

		namespace
		{
			static Definition< FrontPullFormOperation > const theFrontPullFormDefinition;
		}
	}
}

	#include "om/operations/front_pull_form_operation.cpp"

#endif