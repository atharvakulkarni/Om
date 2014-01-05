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

\defgroup om__operation__swap_operation__ swap
	\ingroup om__operation__
	\brief
		Swaps two \ref om__operand__ "Operands".
	\par Input
		<tt>{A}{B}</tt>
	\par Output
		<tt>{B}{A}</tt>
	\par Implementation
		Om::Operation::SwapOperation
*/

#ifndef Om_Operation_SwapOperation_

	#define Om_Operation_SwapOperation_ \
	Om::Operation::SwapOperation

	#include "om/operation/default_incomplete_operation.hpp"
	#include "om/system.hpp"

	#define Om_Operation_SwapOperation_GetName_() \
	"swap"

namespace Om {

	namespace Operation {

		// MARK: - Om::Operation::SwapOperation

		/*!
		\brief
			The \ref om__operation__swap_operation__ operation implementation.
		*/
		class SwapOperation:
		public DefaultIncompleteOperation<SwapOperation> {

		public: // MARK: public (static)

			static char const * GetName();

			template <typename TheSwapOperation>
			static void GiveElements(
				TheSwapOperation &,
				Consumer &
			);

		public: // MARK: public (non-static)

			SwapOperation();

			template <typename TheOperand>
			bool TakeOperand(
				Evaluation &,
				TheOperand &
			);

			template <typename TheProducer>
			bool TakeQuotedProducer(
				Evaluation &,
				TheProducer &
			);

		private: // MARK: private (non-static)

			/*!
			\brief
				The Operand to swap with.
			*/
			Operand thisOperand;

		};

		namespace {

			static System::Definition<SwapOperation> const theSwapDefinition;

		}

	}

}

	#include "om/operation/swap_operation.cpp"

#endif
