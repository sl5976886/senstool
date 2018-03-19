/** 
 * @file xmlccErrFailure.h
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

#ifndef __xmlccErrFailure_h__
#define __xmlccErrFailure_h__

/******************************************************************************/

#include "./xmlccErrException.h"

/******************************************************************************/

namespace XMLCC {

namespace ERR {

/******************************************************************************/

#define _XMLCC_VERSION_ERR_Failure_ 0.71 // 20100430
#define _XMLCC_DEBUG_ERR_Failure_

/******************************************************************************/

class /// class for marking a recoverable error
Failure : public Exception { // for failure 2 be handled
 public:

  Failure( void ); /// constructor
  Failure( String message ); /// constructor overloaded
  Failure( String message, int lineNo ); /// use __LINE__ @ lineNo
  Failure( String message, char* fileName ); /// use __FILE__ @ fileName
  Failure( String message, char* fileName, int lineNo ); /// use __FILE__ @ fileName and __LINE__ @ lineNo
  virtual ~Failure( void ); /// destructor
  
 private:

  virtual void mark( void ); /// mark an exception

}; // class Failure

/******************************************************************************/

} // namespace ERR

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccErrFailure_h__
