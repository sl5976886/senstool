/** 
 * @file xmlccObject.cpp
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

#include "./xmlccObject.h" // OBJ::Object
#include "./xmlccObjRoot.h" // OBJ::Root
#include "./xmlccObjHeader.h" // OBJ::Header
#include "./xmlccObjDoctype.h" // OBJ::Doctype
#include "./xmlccObjComment.h" // OBJ::Comment
#include "./xmlccObjCData.h" // OBJ::CData
#include "./xmlccObjElement.h" // OBJ::Element
#include "./xmlccObjAttribute.h" // OBJ::Attribute
#include "./xmlccObjValue.h" // OBJ::Value

/******************************************************************************/

namespace XMLCC {

/******************************************************************************/

// constructor
Object::Object( String string ) {
  
  _listOfObjects = new ListObjects( ); /// DOES NOT ALLOCATE MEMORY IN ADVANCE

  _string = string;
  
  _indent = 0;
  _indentSize = _XMLCC_INDENTION_SIZE_; /// set in xmlccInclDefs.h to 1,2,3,..

} // Object

// destructor
Object::~Object( void ) {

  int sizeOfList = _listOfObjects->size( );
  for( int o = 0; o < sizeOfList; o++ )
    delete _listOfObjects->get( o );
  delete _listOfObjects;

} // ~Object

/******************************************************************************/

void // set tag for an object
Object::setString( String string ) {
  _string = string;
} // Object::setTag

String // get string of an object
Object::getString( void ) {
  return _string;
} // Object::getTag

/******************************************************************************/

void /// push object back 2 list
Object::addObject( Object* object ) {
  _listOfObjects->add( object );
} // Object::pushObject

/******************************************************************************/

int /// get no of objects
Object::getNoOfObjects( void ) {
  return _listOfObjects->size( );
} // Object::getNoOfObjects

Object* /// get object of internal no
Object::getObject( int no ) {
  return _listOfObjects->get( no );
} // Object::getObject

Object**  /// get all objects as arrays
Object::getObjects( void ) {
  return _listOfObjects->arr( );
} // Object::getArrayOfObjects

/******************************************************************************/

void // /// set indention for std::ostream
Object::setIndent( Object* obj ) {
  _indent = obj->getIndent( );
} // Object::setIndent

int /// get indention for std::ostream
Object::getIndent( void ) {
  return _indent;
} // Object::getIndent

void /// increase indention
Object::incIndent( Object* obj ) {
  _indent = obj->getIndent( ) + _indentSize;
} // Object::incIndent

void /// decrease indention
Object::decIndent( Object* obj ) {
  _indent = obj->getIndent( ) - _indentSize;
} // Object::decIndent

/******************************************************************************/

std::ostream& // for std::cout
operator << ( std::ostream& s, Object* obj ) {

  if( dynamic_cast<OBJ::Root*>( obj ) != 0 ) {
    
    OBJ::Root* root = (OBJ::Root*)obj;

    s << root
      << std::flush;
    
  } else if( dynamic_cast<OBJ::Header*>( obj ) != 0 ) {

    OBJ::Header* header = (OBJ::Header*)obj;

    s << header
      << std::flush;

  } else if( dynamic_cast<OBJ::Doctype*>( obj ) != 0 ) {

    OBJ::Doctype* doctype = (OBJ::Doctype*)obj;

    s << doctype 
      << std::flush;

  } else if( dynamic_cast<OBJ::Comment*>( obj ) != 0 ) {

    OBJ::Comment* comment = (OBJ::Comment*)obj;

    s << comment
      << std::flush;

  } else if( dynamic_cast<OBJ::CData*>( obj ) != 0 ) {

    OBJ::CData* cdata = (OBJ::CData*)obj;

    s << cdata 
      << std::flush;

  } else if( dynamic_cast<OBJ::Element*>( obj ) != 0 ) {

    OBJ::Element* element = (OBJ::Element*)obj;

    s << element
      << std::flush;

  } else if( dynamic_cast<OBJ::Attribute*>( obj ) != 0 ) {

    OBJ::Attribute* attribute = (OBJ::Attribute*)obj;

    s << attribute
      << std::flush;

  } else if( dynamic_cast<OBJ::Value*>( obj ) != 0 ) {

    OBJ::Value* value = (OBJ::Value*)obj;

    s << value
      << std::flush;

  } // if

  return s;

} // Object::operator << 

std::ostream& // for std::cout
operator << ( std::ostream& s, int indention ) {

  for( int w = 0; w < indention; w++ )
    s << " " << std::flush;

  return s;

} // Object::operator << 

/******************************************************************************/

void /// add indention to ostream
Object::doIndent( std::ostream& s ) {
  
  for( int w = 0; w < _indent; w++ )
    s << " " << std::flush;

} // Object::addIndent

/******************************************************************************/

} // namespace XMLCC

/******************************************************************************/
