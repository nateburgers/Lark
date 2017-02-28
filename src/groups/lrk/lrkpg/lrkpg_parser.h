// lrkpg_parser.h                                                     -*-C++-*-
#ifndef INCLUDED_LRKPG_PARSER
#define INCLUDED_LRKPG_PARSER

//@PURPOSE: Provide ...
//
//@TYPES:
//  lrkpg::Parser:
//
//@SEE_ALSO:
//
//@DESCRIPTION: ...
//

#ifndef INCLUDED_LRKP_BOOLEAN
#include <lrkp_boolean.h>
#endif

#ifndef INCLUDED_LRKP_CHARACTER
#include <lrkp_character.h>
#endif

#ifndef INCLDUED_LRKP_INTEGER
#include <lrkp_integer.h>
#endif

namespace LarkCompiler {
namespace lrkpg {

template <typename SIGNATURE_TYPE>
class Function;

template <typename    RETURN_TYPE,
          typename... PARAMETER_TYPES>
class Function<RETURN_TYPE(PARAMETER_TYPES...)> {

  public:
    // CREATORS
    virtual ~Function() = 0;

    // ACCESSORS
    virtual RETURN_TYPE operator()(PARAMETER_TYPES... parameters) const = 0;
};

template <typename ELEMENT_TYPE>
class Slice {

  public:
    // TYPES
    using Element = ELEMENT_TYPE;

  private:
    // DATA
    Element *d_begin_p;
    Element *d_end_p;

  public:
    // CREATORS
    Slice() = default;

    explicit Slice(Element array[]);

    template <lrkp::Integer SIZE>
    explicit Slice(Element (&array)[SIZE]);

    Slice(Element *arrayStart, Element *arrayEnd);

    Slice(const Slice&  original) = default;
    Slice(      Slice&& original) = default;

    ~Slice() = default;

    // MANIPULATORS
    Slice& operator=(const Slice&  original) = default;
    Slice& operator=(      Slice&& original) = default;

    Element& operator[](lrkp::Integer index);

    Element& head();

    Slice tail();

    Element *begin();

    Element *end();

    void advance(lrkp::Integer distance = 1);

    // ACCESSORS
    const Element& operator[](lrkp::Integer index) const;

    const Element& head() const;

    const Slice tail() const;

    const Element *begin() const;

    const Element *end() const;

    lrkp::Integer size() const;

    lrkp::Boolean empty() const;
};

// FREE OPERATORS
template <typename ELEMENT_TYPE>
lrkp::Boolean operator==(const Slice<ELEMENT_TYPE>& lhs,
                         const Slice<ELEMENT_TYPE>& rhs);

template <typename ELEMENT_TYPE>
lrkp::Boolean operator!=(const Slice<ELEMENT_TYPE>& lhs,
                         const Slice<ELEMENT_TYPE>& rhs);

                                // ============
                                // class PARSER
                                // ============

template <typename SIGNATURE_TYPE,
          typename ELEMENT_TYPE = lrkp::Character>
class Parser;

template <typename    RETURN_TYPE,
          typename... PARAMETER_TYPES,
          typename    ELEMENT_TYPE>
class Parser<RETURN_TYPE(PARAMETER_TYPES...), ELEMENT_TYPE>
    : public Function<RETURN_TYPE(Slice<ELEMENT_TYPE> *, PARAMETER_TYPES...)> {
    // This value-semantic class is primarily provided to ...

  public:
    // TYPES
    using Element = ELEMENT_TYPE;

  private:
    // DATA

  public:
    // CREATORS
    virtual ~Parser() = 0;

    // ACCESSORS
    virtual RETURN_TYPE operator()(
                          Slice<Element>       *slice,
                          PARAMETER_TYPES&&...  parameters) const override = 0;
};

template <typename SIGNATURE_TYPE,
          typename ELEMENT_TYPE = lrkp::Character>
class OptionalParser;

template <typename    RETURN_TYPE,
          typename... PARAMETER_TYPES,
          typename    ELEMENT_TYPE>
class OptionalParser<RETURN_TYPE(PARAMETER_TYPES...), ELEMENT_TYPE>
               : public Parser<lrku::Optional<RETURN_TYPE>(PARAMETER_TYPES...),
                               ELEMENT_TYPE> {

    // PRIVATE TYPES
    using Signature = RETURN_TYPE(PARAMETER_TYPES...);

    // DATA
    Parser<Signature, Element> *d_parser_p;

  public:

    // CREATORS
    ~Parser() override = default;

    // ACCESSORS
    lrku::Optional<RETURN_TYPE> operator()(
                               Slice<Element>      *slice,
                               PARAMETER_TYPE&&...  parameters) const override;

};

template <typename ELEMENT_TYPE = lrkp::Character>
class LiteralParser : public Parser<lrkp::Integer(), ELEMENT_TYPE> {

    // DATA
    Element d_literal;

  public:
    // CREATORS
    LiteralParser() = default;

    LiteralParser(const LiteralParser&  original) = default;
    LiteralParser(      LiteralParser&& original) = default;

    explicit LiteralParser(const Element&  element);
    explicit LiteralParser(      Element&& element);

    ~LiteralParser() override = default;

    // MANIPULATORS
    LiteralParser& operator=(const LiteralParser&  original) = default;
    LiteralParser& operator=(      LiteralParser&& original) = default;

    void setLiteral(const Element&  element);
    void setLiteral(      Element&& element);

    // ACCESSORS
    lrkp::Integer operator()(Slice<Element> *slice) const override;

    const Element& literal() const;
};

template <typename ELEMENT_TYPE = lrkp::Character>
class SliceParser : public Parser<lrkp::Integer(), ELEMENT_TYPE> {

    // DATA
    Slice<Element> d_slice;

  public:
    // CREATORS
    SliceParser();

    SliceParser(const SliceParser&  original) = default;
    SliceParser(      SliceParser&& original) = default;

    explicit SliceParser(const Slice<Element>&  slice);
    explicit SliceParser(      Slice<Element>&& slice);

    ~SliceParser() override = default;

    // MANIPULATORS
    SliceParser& operator=(const SliceParser&  original) = default;
    SliceParser& operator=(      SliceParser&& original) = default;

    void setSlice(const Slice<Element>&  slice);
    void setSlice(      Slice<Element>&& slice);

    // ACCESSORS
    lrkp::Integer operator()(Slice<Element> *slice) const override;

    const Slice<Element>& slice() const;
};

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                                // ------------
                                // class PARSER
                                // ------------

// CREATORS

// MANIPULATORS

// ACCESSORS

// FREE OPERATORS

} // close namespace lrkpg
} // close namespace LarkCompiler

#endif // INCLUDED_LRKPG_PARSER

// ----------------------------------------------------------------------------
// Copyright (c) 2017 Nathan Burgers
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ------------------------------ END-OF-FILE ---------------------------------
