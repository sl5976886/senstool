/** 
 * @file xmlccErrException.cpp
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

#include "./xmlccErrException.h"

/******************************************************************************/

namespace XMLCC {

namespace ERR {

/******************************************************************************/

// constructor
Exception::Exception( void ) {
  mark( );
} // Exception::Exception

// constructor overloaded
Exception::Exception( String message ) : _message( message ) { 
  mark( );
} // Exception::Exception

// use __LINE__ @ lineNo
Exception::Exception( String message, int lineNo ) {
  std::ostringstream lineNoStream;
  lineNoStream << lineNo;
  _message = "line: ";
  _message.append( lineNoStream.str( ) );
  _message.append( " " );
  _message.append( message );
  mark( );
} // Exception::Exception

// use __FILE__ @ fileName
Exception::Exception( String message, char* fileName ) {
  _message = "file: ";
  _message.append( fileName );
  _message.append( " " );
  _message.append( message );
  mark( );
} // Exception::Exception

// use __FILE__ @ fileName and __LINE__ @ lineNo
Exception::Exception( String message, char* fileName, int lineNo ) {
  std::ostringstream lineNoStream;
  lineNoStream << lineNo;
  _message = "file: ";
  _message.append( fileName );
  _message.append( " in line: " );
  _message.append( lineNoStream.str( ) );
  _message.append( " - " );
  _message.append( message );
  mark( );
} // Exception::Exception

// destructor
Exception::~Exception( void ) {
} // Exception::~Exception

/******************************************************************************/

String // returns message
Exception::declare( void ) const {
  return _message;
} // Exception::declare

void // message to console
Exception::report( void ) const {
  std::cout << _message << std::endl << std::flush;
} // Exception::report

void // message to console and stop
Exception::stop( void ) const {
  report( );
  std::cin.get( );
} // Exception::stop

/******************************************************************************/

void // do a nuke
Exception::nuke( void ) const {
  std::cout << std::endl << std::flush;
  std::cout << "                  ____             " << std::endl << std::flush;
  std::cout << "          __,-~~/~    `---.        " << std::endl << std::flush;
  std::cout << "        _/_,---(      ,    )       " << std::endl << std::flush;
  std::cout << "    __ /        NUKED     ) \\ __  " << std::endl << std::flush;
  std::cout << "   ====------------------===;;;==  " << std::endl << std::flush;
  std::cout << "      /  ~\"~\"~\"~\"~\"~~\"~)     " << std::endl << std::flush;
  std::cout << "      (_ (      (     >    \\)     " << std::endl << std::flush;
  std::cout << "       \\_( _ <         >_>\'      " << std::endl << std::flush;
  std::cout << "           ~ `-i' ::>|--\"         " << std::endl << std::flush;
  std::cout << "               I;|.|.|             " << std::endl << std::flush;
  std::cout << "              <|i::|i|>            " << std::endl << std::flush;
  std::cout << "               |[::|.|             " << std::endl << std::flush;
  std::cout << "                ||: |              " << std::endl << std::flush;
  std::cout << std::endl << std::flush;
} // Exception::nuke

/******************************************************************************/

std::ostream& // for std::cout
operator << ( std::ostream& s, Exception& e ) {
  s << e._message << std::endl << std::flush;
  return s;
} // Exception::operator << 

std::ostream& // for std::cout
operator << ( std::ostream& s, Exception* e ) {
  s << e->_message << std::endl << std::flush;
  return s;
} // Exception::operator << 

/******************************************************************************/

void // mark exception
Exception::mark( void ) {
  String tmp = "XMLCC::Exception::";
  tmp.append( _message );
  _message = tmp;
} // Exception::mark

/******************************************************************************/

} // namespace ERR

} // namespace XMLCC

/******************************************************************************/
