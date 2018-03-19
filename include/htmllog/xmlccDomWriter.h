/** 
 * @file xmlccDomWriter.h
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

#ifndef __xmlccDomWriter_h__
#define __xmlccDomWriter_h__

/******************************************************************************/

#include "./xmlccBuilder.h" // XMLCC builder and objects

/******************************************************************************/

namespace XMLCC {

namespace DOM {

/******************************************************************************/

#define _XMLCC_VERSION_DOM_Writer_ 0.71 // 20100430
#define _XMLCC_DEBUG_DOM_Writer_

/******************************************************************************/

class /// class gets its information by overloading Dumper's functions
Writer {
 public:

  Writer( void ); /// constructor
  virtual ~Writer( void ); /// destructor

  void write( OBJ::Root* root ); /// writes to file
  void write( String fileName, Object* obj ); /// writes to file

}; // class Writer

/******************************************************************************/

} // namespace DOM

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccDomWriter_h__
