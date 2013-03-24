/*!
\file
	\brief
		<a href="http://om-language.org">Om</a> source file.
	\version
		0.1.2
	\date
		2012-2013
	\copyright
		Copyright (c) <a href="http://sparist.com">Sparist</a>. All rights reserved. This program and the accompanying materials are made available under the terms of the <a href="http://www.eclipse.org/legal/epl-v10.html">Eclipse Public License, Version 1.0</a>, which accompanies this distribution.
	\authors
		Jason Erb - Initial API, implementation, and documentation.
*/

#ifndef Om_Evaluator_

	#include "om/evaluator.hpp"

	#ifdef Om_Macros_Test_

		#ifndef Om_Macros_Precompilation_

			#include "boost/test/unit_test.hpp"

		#endif

namespace Om {

	BOOST_AUTO_TEST_SUITE(EvaluatorTest)

	BOOST_AUTO_TEST_SUITE_END()

}

	#endif

#else

	#include "om/evaluation.hpp"
	#include "om/operation.hpp"
	#include "om/operator.hpp"
	#include "om/translator.hpp"

// MARK: - Om::Evaluator

	#define Type_ \
	Om::Evaluator

// MARK: public (non-static)

inline Type_::~Evaluator() {
	try {
		if (
			!this->IsEmpty()
		) {
			if (this->thisGaveElementToOutput) {
				this->thisOutput.TakeElement(
					Separator::GetLineSeparator()
				);
			}
			this->GiveElements(this->thisOutput);
		}
	} catch (...) {}
}

inline Type_::Evaluator(
	Consumer & theOutput,
	Translator const & theTranslator
):
thisOutput(theOutput),
thisTranslator(theTranslator),
thisOperationVector(),
thisGaveElementToOutput() {}

inline void Type_::Clear() {
	this->thisOperationVector.clear();
}

inline Om::Translator const & Type_::GetTranslator() const {
	return this->thisTranslator;
}

inline void Type_::GiveElements(Consumer & theConsumer) {
	this->GiveElements(
		this->thisOperationVector.begin(),
		this->thisOperationVector.end(),
		theConsumer
	);
	this->Clear();
}

inline void Type_::GiveElements(Consumer & theConsumer) const {
	this->GiveElements(
		this->thisOperationVector.begin(),
		this->thisOperationVector.end(),
		theConsumer
	);
}

inline std::auto_ptr<Om::Program> Type_::GiveProgram() {
	return this->GiveProgram(*this);
}

inline std::auto_ptr<Om::Program> Type_::GiveProgram() const {
	return this->GiveProgram(*this);
}

inline bool Type_::IsEmpty() const {
	return this->thisOperationVector.empty();
}

inline void Type_::ReadElements(Parser & theParser) {
	while (theParser) {
		assert(Symbols::theEndOperandSymbol != *theParser);
		switch (*theParser) {
		case Symbols::theStartOperandSymbol:
			theParser.Pop();
			{
				// Ensure that this does not resolve to the copy constructor.
				Source<CodePoint const> & theCodePointSource = theParser;

				Parser theOperandParser(theCodePointSource);
				this->ReadQuotedElements(theOperandParser);
			}
			if (!theParser) {
				return;
			}
			assert(Symbols::theEndOperandSymbol == *theParser);
			// Fall through.
		Om_Symbols_SeparatorSymbol_GetCases_():
			theParser.Pop();
			continue;
		}
		Operator theOperator(theParser);
		this->TakeOperator(theOperator);
	}
}

inline void Type_::ReadQuotedElements(Parser & theParser) {
	Evaluation theEvaluation(*this);
	this->ReadQuotedElements(
		theEvaluation,
		theParser
	);
	this->Evaluate(theEvaluation);
}

inline void Type_::ReadQuotedElements(
	Evaluation & theEvaluation,
	Parser & theParser
) {
	if (
		this->thisOperationVector.empty()
	) {
		this->thisOutput.ReadQuotedElements(theParser);
		this->thisGaveElementToOutput = true;
	} else {
		std::auto_ptr<Operation> theOperation(
			this->thisOperationVector.pop_back().release()
		);
		assert(
			theOperation.get()
		);
		if (
			!theOperation->ReadQuotedElements(
				theEvaluation,
				theParser
			)
		) {
			this->thisOperationVector.push_back(theOperation);
		}
	}
}

template <typename TheOperand>
inline void Type_::TakeOperand(TheOperand & theOperand) {
	assert(
		!theOperand.IsEmpty()
	);
	Evaluation theEvaluation(*this);
	this->TakeOperand(
		theEvaluation,
		theOperand
	);
	this->Evaluate(theEvaluation);
}

template <typename TheOperand>
inline void Type_::TakeOperand(
	Evaluation & theEvaluation,
	TheOperand & theOperand
) {
	assert(
		!theOperand.IsEmpty()
	);
	if (
		this->thisOperationVector.empty()
	) {
		this->thisOutput.TakeElement(theOperand);
		this->thisGaveElementToOutput = true;
	} else {
		std::auto_ptr<Operation> theOperation(
			this->thisOperationVector.pop_back().release()
		);
		assert(
			theOperation.get()
		);
		if (
			!theOperation->TakeElement(
				theEvaluation,
				theOperand
			)
		) {
			this->thisOperationVector.push_back(theOperation);
		}
	}
}

template <typename TheOperation>
inline void Type_::TakeOperation(
	std::auto_ptr<TheOperation> theOperation
) {
	this->thisOperationVector.push_back(theOperation);
}

template <typename TheOperator>
inline void Type_::TakeOperator(TheOperator & theOperator) {
	Evaluation theEvaluation(*this);
	this->TakeOperator(
		theEvaluation,
		theOperator
	);
	this->Evaluate(theEvaluation);
}

template <typename TheOperator>
inline void Type_::TakeOperator(
	Evaluation & theEvaluation,
	TheOperator & theOperator
) {
	assert(
		!theOperator.IsEmpty()
	);
	if (
		!this->thisTranslator.Translate(
			theEvaluation,
			theOperator
		) &&
		!this->thisTranslator.Translate(
			theEvaluation,
			Operator()
		)
	) {
		// Flush everything up to, and including, the operator.
		// At the very least, the operator will be flushed.
		if (this->thisGaveElementToOutput) {
			this->thisOutput.TakeElement(
				Separator::GetLineSeparator()
			);
		}

		// Flush the evaluation.
		// Starts with Operator; leading Operands would have been sent.
		if (
			!this->IsEmpty()
		) {
			this->GiveElements(this->thisOutput);
			this->thisOutput.TakeElement(
				Separator::GetLineSeparator()
			);
		}

		// Flush the operator.
		this->thisOutput.TakeElement(theOperator);
		this->thisGaveElementToOutput = true;
	}
}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(TheProducer & theProducer) {
	Evaluation theEvaluation(*this);
	this->TakeQuotedProducer(
		theEvaluation,
		theProducer
	);
	this->Evaluate(theEvaluation);
}

template <typename TheProducer>
inline void Type_::TakeQuotedProducer(
	Evaluation & theEvaluation,
	TheProducer & theProducer
) {
	if (
		this->thisOperationVector.empty()
	) {
		this->thisOutput.TakeQuotedElements(theProducer);
		this->thisGaveElementToOutput = true;
	} else {
		std::auto_ptr<Operation> theOperation(
			this->thisOperationVector.pop_back().release()
		);
		assert(
			theOperation.get()
		);
		if (
			!theOperation->TakeQuotedElements(
				theEvaluation,
				theProducer
			)
		) {
			this->thisOperationVector.push_back(theOperation);
		}
	}
}

template <typename TheSeparator>
inline void Type_::TakeSeparator(TheSeparator &) {}

// MARK: private (static)

template <typename TheIterator>
inline void Type_::GiveElements(
	TheIterator theCurrent,
	TheIterator const theEnd,
	Consumer & theConsumer
) {
	if (theEnd != theCurrent) {
		for (
			;
			;
			theConsumer.TakeElement(
				Separator::GetLineSeparator()
			)
		) {
			theCurrent->GiveElements(theConsumer);
			if (theEnd == ++theCurrent) {
				return;
			}
		}
	}
}

template <typename TheEvaluator>
inline std::auto_ptr<Om::Program> Type_::GiveProgram(TheEvaluator & theEvaluator) {
	std::auto_ptr<Program> theExpression(new Expression);
	assert(
		theExpression.get()
	);
	theEvaluator.GiveElements(*theExpression);
	return theExpression;
}

// MARK: private (non-static)

inline void Type_::Evaluate(Evaluation & theEvaluation) {
	while (
		theEvaluation.GiveTerm(*this)
	) {}
}

	#undef Type_

#endif