/** 
 * @file xmlccSaxParserHandlerExample.h
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

#ifndef __xmlccSaxParserHandlerExample_h__
#define __xmlccSaxParserHandlerExample_h__

/******************************************************************************/

#include "./xmlccSaxParserHandler.h" // for converting strings 2 objects

namespace XMLCC {

namespace SAX {

/******************************************************************************/

#define _XMLCC_VERSION_SAX_ParserHandlerExample_ 0.71 // 20100430
#define _XMLCC_DEBUG_SAX_ParserHandlerExample_

/******************************************************************************/

class /// example for an handler pushing writing data 2 console
ParserHandlerExample : public ParserHandler {
 public:

  ParserHandlerExample( void ); /// constructor
  virtual ~ParserHandlerExample( void ); /// destructor

  void startDocument( void ); /// called before reading document

  void startObject( Object* object ); /// called for each object starting

  void characters( Object* object ); /// called for each value in file

  void endObject( Object* object ); /// called for each object ending

  void endDocument( void ); /// called after reading document

}; // class ParserHandlerExample

/******************************************************************************/

} // namespace SAX

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccSaxParserHandlerExample_h__
