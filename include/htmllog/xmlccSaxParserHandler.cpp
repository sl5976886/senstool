/** 
 * @file xmlccSaxParserHandler.cpp
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

#include "./xmlccSaxParserHandler.h" // header

/******************************************************************************/

#ifdef _WIN32
 #pragma warning( disable:4100 ) // for unused objects
#endif // _WIN32

/******************************************************************************/

namespace XMLCC {

namespace SAX {

/******************************************************************************/

/// constructor
ParserHandler::ParserHandler( void ) {
  _tokenizer = new DOM::Tokenizer( );
  _grabber = new DOM::Grabber( );
  _strTool = new SYS::StringTool( );
} // ParserHandler

/// destructor
ParserHandler::~ParserHandler( void ) {
  delete _strTool;
  delete _grabber;
  delete _tokenizer;
} // ~ParserHandler

/******************************************************************************/

void // called before reading document
ParserHandler::startDocument( void ) {
} // ParserHandler::startDocument

void // called for each object starting
ParserHandler::startObject( Object* object ) {
} // ParserHandler::startObject

/******************************************************************************/

void // called for each value in file
ParserHandler::characters( Object* object ) {
} // ParserHandler::characters

/******************************************************************************/

void // called for each object ending
ParserHandler::endObject( Object* object ) {
} // ParserHandler::endObject

void // called after reading document
ParserHandler::endDocument( void ) {
} // ParserHandler::endDocument

/******************************************************************************/

} // namespace SAX

} // namespace XMLCC

/******************************************************************************/
