/** 
 * @file xmlccDomParser.h
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

#ifndef __xmlccDomParser_h__
#define __xmlccDomParser_h__

/******************************************************************************/

#include "./xmlccDomTokenizer.h" // for string manipulations
#include "./xmlccDomGrabber.h" // for sorting objects
#include "./xmlccBuilder.h" // for building objects

/******************************************************************************/

namespace XMLCC {

namespace DOM {

/******************************************************************************/

#define _XMLCC_VERSION_DOM_Parser_ 0.71 // 20100430
#define _XMLCC_DEBUG_DOM_Parser_

/******************************************************************************/

class /// class parses from file or buffer and hands back a DOM structure
Parser {
 public:

  Parser( void ); /// constructor
  virtual ~Parser( void ); /// destructor

  Object* parseBuffer( char* buffer ); /// reads buffer of type char*
  Object* parseBuffer( String buffer ); /// reads buffer of type std::string
  OBJ::Root* parseFile( String fileName ); /// reads XML file and returns root object

 protected:
  
  DOM::Grabber* _grabber; /// a grabber for objects
  DOM::Tokenizer* _tokenizer; /// a converter for strings of type String
  SYS::StringTool* _strTool; /// a filter to convert strings with tags 2 objects

}; // class Parser

/******************************************************************************/

} // namespace DOM

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccDomParser_h__
