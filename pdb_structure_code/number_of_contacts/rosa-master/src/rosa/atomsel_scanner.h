/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2008 by Roberto Mosca.                                  *
 *                                                                         *
 *   E-mail: info@librosa.org                                              *
 *                                                                         *
 *   This file is part of Rosa.                                            *
 *                                                                         *
 *   Rosa is free software: you can redistribute it and/or modify          *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3, or (at your option)   *
 *   any later version.                                                    *
 *                                                                         *
 *   Rosa is distributed in the hope that it will be useful,               *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with Rosa. If not, see <http://www.gnu.org/licenses/>.          *
 *                                                                         *
 ***************************************************************************/

/*! \file atomsel_scanner.h
 *  \brief Declares the class AtomSelectScanner class which embeds the lexical
 *         analyzer needed by the parser of atom selection strings.
 */

#ifndef ROSA_ATOMSEL_SCANNER_H_
#define ROSA_ATOMSEL_SCANNER_H_

#include "common.h"

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define	YY_DECL \
rosa::AtomSelectParser::token_type \
rosa::AtomSelectScanner::lex(	rosa::AtomSelectParser::semantic_type* yylval )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer AtomSelectFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#include <rosa/atomsel_parser.h>

namespace rosa {
  
  /** Scanner is a derived class to add some extra function to the scanner
   * class. Flex itself creates a class named yyFlexLexer, which is renamed using
   * macros to ExampleFlexLexer. However we change the context of the generated
   * yylex() function to be contained within the Scanner class. This is required
   * because the yylex() defined in ExampleFlexLexer has no parameters. */
  class AtomSelectScanner : public AtomSelectFlexLexer
    {
    public:
      /** Create a new scanner object. The streams arg_yyin and arg_yyout default
       * to cin and cout, but that assignment is only made when initializing in
       * yylex(). */
      AtomSelectScanner( std::istream* arg_yyin = 0,
                         std::ostream* arg_yyout = 0);
      
      /** Required for virtual functions */
      virtual ~AtomSelectScanner();
      
      /** This is the main lexing function. It is generated by flex according to
       * the macro declaration YY_DECL above. The generated bison parser then
       * calls this virtual function to fetch new tokens. */
      virtual AtomSelectParser::token_type lex( AtomSelectParser::semantic_type* yylval );
      
#ifdef ACTIVATE_DEBUG     
      /** Enable debug output (via arg_yyout) if compiled into the scanner. */
      void set_debug( bool b );
#endif
    };
  
} // namespace rosa

#endif