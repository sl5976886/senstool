/** 
 * @file xmlccSaxParser.h
 * @author Christian Scheiblich
 *
 * DESCRIPTION
 *
 * XMLCC is an XML library written in C++ based on design patterns
 * for generating, searching, and parsing even malformed XML files.
 * Two Parsers are available: C++ SAX API for event based parsing and
 * a C++ DOM like Parser based on a document object model.
 * splendid time indeed ~8>
 * 
 * This file is part of XMLCC.
 * 
 * XMLCC Copyright (C) 2008-2012 Christian Scheiblich
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License. 
 * You may obtain a copy of the License at 
 *  
 *     http://www.apache.org/licenses/LICENSE-2.0 
 *      
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. 
 * 
 */

#ifndef __xmlccSaxParser_h__
#define __xmlccSaxParser_h__

/******************************************************************************/

#include "./xmlccSaxParserHandler.h" // for handling data
#include "./xmlccSaxParserHandlerExample.h" // for handling data
#include "./xmlccDomTokenizer.h" // for string manipulations
#include "./xmlccDomGrabber.h" // for sorting objects
#include "./xmlccBuilder.h" // for building objects

/******************************************************************************/

namespace XMLCC {

namespace SAX {

/******************************************************************************/

#define _XMLCC_VERSION_SAX_Parser_ 0.71 // 20100430
#define _XMLCC_DEBUG_SAX_Parser_

/******************************************************************************/

class  /// SAX parser calling handler function with read data
Parser {
 public:

  Parser( ParserHandler* handler ); /// constructor
  virtual ~Parser( void ); /// destructor

  void parseBuffer( char* buffer ); /// parses XML from buffer and calls handler's virtual functions
  void parseBuffer( String buffer ); /// parses XML from buffer and calls handler's virtual functions
  void parseFile( String fileName ); /// parses XML from file and calls handler's virtual functions

 protected:
  
  ParserHandler* _handler; /// a handler for parsed data

  DOM::Grabber* _grabber; /// a grabber for objects
  DOM::Tokenizer* _tokenizer; /// a converter for strings of type String
  SYS::StringTool* _strTool; /// a filter to convert strings with tags 2 objects

}; // class Parser

/******************************************************************************/

} // namespace SAX

} // namespace XMLCC

#endif // __xmlccSaxParser_h__

/******************************************************************************/
