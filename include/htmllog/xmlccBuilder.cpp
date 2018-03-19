/** 
 * @file xmlccBuilder.cpp
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

#include "./xmlccBuilder.h" // header

/******************************************************************************/

namespace XMLCC {

/******************************************************************************/

/// constructor
Builder::Builder( void ) {
} // Builder

/// destructor
Builder::~Builder( void ) {
} // ~Builder

/******************************************************************************/

OBJ::Root* /// create a XMLCC root
Builder::createRoot( void ) {
  return new OBJ::Root( "xmlcc.xml" );
} // Builder::createRoot

/******************************************************************************/

OBJ::Root* /// create XMLCC root, representing the file
Builder::createRoot( String fileName ) {
  return new OBJ::Root( fileName );
} // Builder::createRoot

/******************************************************************************/

Object* /// an XML header with standard attributes
Builder::createHeader( void ) {
  // <? xml version="1.0" encoding="UTF-8" standalone="no" ?>
  Object* header = create( Types::Header, "xml" );
  create( header, Types::Attribute, "version", "1.0" );
  //create( header, Types::Attribute, "encoding", "UTF-8" ); // seems to be ~8>
  //create( header, Types::Attribute, "standalone", "no" );
  return header;
} // Builder::createHeader

/******************************************************************************/

Object* /// a HTML DOCTYPE header with most common attributes
Builder::createDoctype( void ) {
  // <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" 
  //      "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
  Object* doctype = create( Types::Doctype, "HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\"" );
//  create( doctype, Types::Element, "HTML" ); // Element for single value
//  create( doctype, Types::Element, "PUBLIC" ); // Element for single value
//  create( doctype, Types::Attribute, "type", "-//W3C//DTD HTML 4.01 Transitional//EN" );
//  create( doctype, Types::Attribute, "dtd", "http://www.w3.org/TR/html4/loose.dtd" );
  return doctype;
} // Builder::createDoctype

/******************************************************************************/

Object* // create a new object and return it
Builder::create( Types::Type type, String tag ) {
 
  Object* object = 0;

  switch( type ) {

    case Types::Root :
     object = new OBJ::Root( tag );
     break;  

    case Types::Header :
     object = new OBJ::Header( tag );
     break;

    case Types::Doctype :
     object = new OBJ::Doctype( tag );
     break;

    case Types::Element :
     object = new OBJ::Element( tag );
     break;

    case Types::Attribute :
     object = new OBJ::Attribute( tag );
     break;

    case Types::Value :
     object = new OBJ::Value( tag );
     break;

    case Types::CData :
     object = new OBJ::CData( tag );
     break;

    case Types::Comment :
     object = new OBJ::Comment( tag );
     break;

    default :
      throw ERR::Failure( "Builder - unknown type of object" );

  } // switch

  return object;

} // Builder::create

Object* // create a new object with value and return it
Builder::create( Types::Type type, String tag, String value ) {
  
  Object* object = 0;
  
  switch( type ) {

    case Types::Element :
     object = new OBJ::Element( tag, value );
     break;

    case Types::Attribute :
     object = new OBJ::Attribute( tag, value );
     break;

    default :
      throw ERR::Failure( "Builder::create( Type, tag, val ) - must be Element or Attribute" );
  } // switch

  return object;

} // Builder::create

Object* // create a new object and add the passed
Builder::create( Types::Type type, String tag, Object* list ) {

  Object* object = 0;

  switch( type ) {

    case Types::Element :
     object = new OBJ::Element( tag );
     break;

    default :
      throw ERR::Failure( "Builder::create(type, tag, obj) - must be Element" );

  } // switch

  object->addObject( list );

  return object;

} // Builder::create

Object* // create a new object with value and add the passed
Builder::create( Types::Type type, String tag, String value, Object* list ) {

  Object* object = 0;

  switch( type ) {

    case Types::Element :
     object = new OBJ::Element( tag, value );
     break;

    default :
      throw ERR::Failure( "Builder::create(type, tag, value, obj ) - must be Element" );

  } // switch

  object->addObject( list );

  return object;

} // Builder::create

void // create a new object and add it to object
Builder::create( Object* root, Types::Type type, String tag ) {

  Object* object = 0;

  switch( type ) {

    case Types::Header :
     object = new OBJ::Header( tag );
     break;

    case Types::Doctype :
     object = new OBJ::Doctype( tag );
     break;

    case Types::Element :
     object = new OBJ::Element( tag );
     break;

    case Types::Attribute :
     object = new OBJ::Attribute( tag );
     break;

    case Types::Value :
     object = new OBJ::Value( tag );
     break;

    case Types::CData :
     object = new OBJ::CData( tag );
     break;

    case Types::Comment :
     object = new OBJ::Comment( tag );
     break;

    default :
      throw ERR::Failure( "Builder::create( obj, type, tag ) - wrong type of object" );

  } // switch

  root->addObject( object );

} // Builder::create

void // create a new object with value and add it to object
Builder::create( Object* root, Types::Type type, String tag, String value ) {

  Object* object = 0;

  switch( type ) {

    case Types::Element :
     object = new OBJ::Element( tag, value );
     break;

    case Types::Attribute :
     object = new OBJ::Attribute( tag, value );
     break;

    default :
      throw ERR::Failure( "Builder::create( obj, type, tag, val ) - must be Element or Attribute" );

  } // switch

  root->addObject( object );

} // Builder::create

/******************************************************************************/

} // namespace XMLCC

/******************************************************************************/
