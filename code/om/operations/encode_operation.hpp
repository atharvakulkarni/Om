/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> header file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>.  All rights reserved.  This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#if !defined( Om_Operations_EncodeOperation_ )

	#define Om_Operations_EncodeOperation_ \
	Om::Operations::EncodeOperation

	#include "om/default_operation.hpp"
	#include "om/definition.hpp"

	#define Om_Operations_EncodeOperation_GetName_() \
	"encode"

namespace Om {

	namespace Operations {

		// MARK: - Om::Operations::EncodeOperation
		/*!
		\brief
			The \ref encode_operation Operation implementation.
		*/
		class EncodeOperation:
		public DefaultOperation< EncodeOperation > {
		public: // MARK: public (static)

			static char const * GetName();

			template< typename TheEncodeOperation >
			static void GiveElements(
				TheEncodeOperation &,
				Queue &
			);

		public: // MARK: public (non-static)

			template< typename TheOperand >
			bool TakeOperand(
				Evaluation &,
				TheOperand &
			);

			template< typename TheQueue >
			bool TakeQuotedQueue(
				Evaluation &,
				TheQueue &
			);

		};

		namespace {

			static Definition< EncodeOperation > const theEncodeDefinition;

		}

	}

}

	#include "om/operations/encode_operation.cpp"

#endif
