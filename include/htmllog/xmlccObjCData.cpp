/** 
 * @file xmlccObjCData.cpp
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

#include "./xmlccObjCData.h" // header

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

/// constructor
CData::CData( String content ) : Object( content ) {
} // CData

/// destructor
CData::~CData( void ) {
} // ~CData

/******************************************************************************/

String /// returns the stored content of this CData
CData::getContent( void ) {
  return getString( );
} // CData::getContent

void /// sets the content of this CData
CData::setContent( String content ) {
  setString( content );
} // CData::setContent

/******************************************************************************/

std::ostream& /// std::ostream
operator << ( std::ostream& s, CData* obj ) {

  obj->doIndent( s );

  s << "<![CDATA[" 
    << obj->getContent( )
    << "]]>"
    << std::endl
    << std::flush;

  return s;

} // Object::operator <<

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/
