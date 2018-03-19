/** 
 * @file xmlccObjAttribute.cpp
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

#include "./xmlccObjAttribute.h" // header

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

/// constructor
Attribute::Attribute( String name ) : Object( name ) {
 _value = ""; /// attribute's value; attribute's name is stored in _tag
} // Attribute

/// constructor
Attribute::Attribute( String name, String value ) : Object( name ) {
 _value = value; /// attribute's value; attribute's name is stored in _tag
} // Attribute

/// destructor
Attribute::~Attribute( void ) {
} // ~Attribute

/******************************************************************************/

String /// returns the stored name of this attribute
Attribute::getName( void ) {
  return getString( );
} // Attribute::getName

void /// sets the name of this attribute
Attribute::setName( String name ) {
  setString( name );
} // Attribute::setName

/******************************************************************************/

String /// returns the stored value of this attribute
Attribute::getValue( void ) {
  return _value;
} // Attribute::getValue

void /// sets the value of this attribute
Attribute::setValue( String value ) {
  _value = value;
} // Attribute::setValue

/******************************************************************************/

std::ostream& // for std::cout
operator << ( std::ostream& s, Attribute* obj ) {

  s << obj->getName( ) 
    << "=\"" 
    << obj->getValue( ) 
    << "\"" 
    << std::flush;

  return s;

} // Object::operator <<

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/
