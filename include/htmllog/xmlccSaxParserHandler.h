/** 
 * @file xmlccSaxParserHandler.h
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

#ifndef __xmlccSaxParserHandler_h__
#define __xmlccSaxParserHandler_h__

/******************************************************************************/

#include "./xmlccDomTokenizer.h" // for converting strings 2 objects
#include "./xmlccDomGrabber.h" // for sorting objects
#include "./xmlccBuilder.h" // for building objects

/******************************************************************************/

namespace XMLCC {

namespace SAX {

/******************************************************************************/

#define _XMLCC_VERSION_SAX_ParserHandler_ 0.71 // 20100430
#define _XMLCC_DEBUG_SAX_ParserHandler_

/******************************************************************************/

class /// base class for all handlers 2 be implemented
ParserHandler {
 public:

  ParserHandler( void ); /// constructor
  virtual ~ParserHandler( void ); /// destructor

  virtual void startDocument( void ); /// called before reading document

  virtual void startObject( Object* object ); /// called for each object starting

  virtual void characters( Object* object ); /// called for each value in file

  virtual void endObject( Object* object ); /// called for each object ending

  virtual void endDocument( void ); /// called after reading document

 protected:
  
  DOM::Tokenizer*  _tokenizer; /// converts strings with tags 2 objects
  DOM::Grabber*    _grabber; /// grabs objects
  SYS::StringTool* _strTool; /// filtering content of Strings

}; // class ParserHandler

/******************************************************************************/

} // namespace SAX

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccSaxParserHandler_h__
