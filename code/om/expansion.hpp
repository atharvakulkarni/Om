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
#if !defined( Om_Expansion_ )
	#define Om_Expansion_ Om::Expansion

	#include "om/expression.hpp"

namespace Om
{
	//! \cond
	struct Evaluator;
	//! \endcond

	// MARK: - Om::Expansion
	/*!
	\brief
		The current state of an in-progress Operator resolution.

	Contains an Expression and a reference to an Evaluator, and prevents a more
	recursive evaluation algorithm that would overflow the stack in the event of
	a recursive Om program.

	Each Element that it takes is pushed onto a stack, resulting in a
	LIFO-ordered application of each Element to the Evaluator.  This is designed
	to be used from an Operator resolution algorithm.
	*/
	struct Expansion
	{
	public: // MARK: public (non-static)

		virtual ~Expansion();

		//! Constructs an Expansion on the given Evaluator.
		explicit Expansion( Evaluator & );

		//! Gives each Operand, if any, from the top of the Expression.
		void GiveOperands( Queue & );

		//! Gives the Operator, if any, from the top of the Expression.
		void GiveOperator( Queue & );

		//! Takes the Evaluand, and gives it to the Evaluator.
		template< typename TheEvaluand >
		void TakeEvaluand( std::auto_ptr< TheEvaluand > );

		//! Pushes the Operand onto the front of the Expression.
		template< typename TheOperand >
		void TakeOperand( TheOperand & );

		//! Pushes the Operator onto the front of the Expression.
		template< typename TheOperator >
		void TakeOperator( TheOperator & );

		//! Pushes the quoted Queue onto the front of the Expression.
		template< typename TheQueue >
		void TakeQuotedQueue( TheQueue & );

		//! Pushes the Queue onto the front of the Expression, last first.
		template< typename TheQueue >
		void TakeQueue( TheQueue & );

	private: // MARK: private (non-static)

		Expansion( Expansion const & );

		Expansion const & operator =( Expansion const & );

		//! The Expression.
		Expression thisExpression;

		//! The Evaluator.
		Evaluator & thisEvaluator;
	};
}

	#include "om/expansion.cpp"
#endif