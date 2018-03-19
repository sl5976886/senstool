/** 
 * @file xmlccSaxParserHandlerExample.cpp
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

#include "./xmlccSaxParserHandlerExample.h" // header

/******************************************************************************/

namespace XMLCC {

namespace SAX {

/******************************************************************************/

/// constructor
ParserHandlerExample::ParserHandlerExample( void ) {
} // ParserHandlerExample

/// destructor
ParserHandlerExample::~ParserHandlerExample( void ) {
} // ~ParserHandlerExample

/******************************************************************************/

void // called before reading document
ParserHandlerExample::startDocument( void ) {

  std::cout << "starting 2 parse document" << std::flush << std::endl;

} // ParserHandlerExample::startDocument

void // called for each object starting
ParserHandlerExample::startObject( Object* object ) {

  String tag = object->getString( );
  std::cout << "start object: " << "\t" << tag << std::flush << std::endl;

  int noOfAttributes = object->getNoOfObjects( );
  for( int a = 0; a < noOfAttributes; a++ ) {

    Object* oAtt = object->getObject( a );

    String att = oAtt->getString( );

    std::cout << "attribute: " << "\t" << att << std::flush << std::endl;

  } // a

} // ParserHandlerExample::startObject

/******************************************************************************/

void // called for each value in file
ParserHandlerExample::characters( Object* object ) {

  String value = object->getString( );
  std::cout << "object value: " << "\t" << value << std::flush << std::endl;

} // ParserHandlerExample::characters

/******************************************************************************/

void // called for each object ending
ParserHandlerExample::endObject( Object* object ) {

  String tag = object->getString( );
  std::cout << "end object: " << "\t" << tag << std::flush << std::endl;

} // ParserHandlerExample::endObject

void // called after reading document
ParserHandlerExample::endDocument( void ) {

  std::cout << "ending 2 parse document" << std::flush << std::endl;

} // ParserHandlerExample::endDocument

/******************************************************************************/

} // namespace SAX

} // namespace XMLCC

/******************************************************************************/
