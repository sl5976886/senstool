/** 
 * @file xmlccErrException.h
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
#ifndef __xmlccErrException_h__
#define __xmlccErrException_h__

/******************************************************************************/

#include "./xmlccInclDefs.h" /// common include file for headers and typedefs

/******************************************************************************/

namespace XMLCC {

namespace ERR {

/******************************************************************************/

#define _XMLCC_VERSION_ERR_Exception_ 0.71 // 20100430
#define _XMLCC_DEBUG_ERR_Exception_

/******************************************************************************/

class /// base class for errors
Exception {
 public:

  Exception( void ); /// constructor
  Exception( String message ); /// constructor overloaded
  Exception( String message, int lineNo ); /// use __LINE__ @ lineNo
  Exception( String message, char* fileName ); /// use __FILE__ @ fileName
  Exception( String message, char* fileName, int lineNo ); /// use __FILE__ @ fileName and __LINE__ @ lineNo
  virtual ~Exception( void ); /// destructor

  String declare( void ) const; /// returns message as std::string
  void report( void ) const; /// message to console
  void stop( void ) const; /// message to console and wait for enter
  void nuke( void ) const; /// do a nuke and melt down afterwards

  friend std::ostream& operator << ( std::ostream& s, Exception& e ); /// cout
  friend std::ostream& operator << ( std::ostream& s, Exception* e ); /// cout

 protected:

  String _message; /// the generated exception message  

 private:

  virtual void mark( void ); /// mark exception

}; // class Exception

/******************************************************************************/

} // namespace ERR

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccErrException_h__
