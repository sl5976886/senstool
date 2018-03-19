/** 
 * @file xmlccDomViewer.cpp
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

#include "./xmlccDomViewer.h" // header

/******************************************************************************/

#ifdef _WIN32
 #pragma warning( disable:4100 ) // warning C4100: 'object' : unreferenced formal parameter
#endif // _WIN32

/******************************************************************************/

namespace XMLCC {

namespace DOM {

/******************************************************************************/

/// constructor
Viewer::Viewer( void ) {
} // Writer

/// destructor
Viewer::~Viewer( void ) {
} // ~Writer
  
/******************************************************************************/

void /// print object tree to std::cout
Viewer::view( Object* obj ) {

  std::cout << obj << std::flush;

} // Viewer::view

} // namespace DOM 

} // namespace XMLCC

/******************************************************************************/
