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

#if !defined( Om_Operations_OperandOperation_ )

	#define Om_Operations_OperandOperation_ \
	Om::Operations::OperandOperation

	#include "om/definition.hpp"
	#include "om/operations/program_operation.hpp"

namespace Om {

	namespace Operations {

		/*!
		\brief
			The \ref operand_operation Operation implementation.
		*/
		typedef ProgramOperation< Operand > OperandOperation;

		namespace {

			static Definition< OperandOperation > const theOperandDefinition;

		}

	}

}

#endif
