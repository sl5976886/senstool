/** 
 * @file xmlccObjHeader.cpp
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

#include "./xmlccObjHeader.h" // OBJ::Header
#include "./xmlccObjAttribute.h" // OBJ::Attribute

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

/// set tag to "xml"
Header::Header( void ) : Object( "xml" ) {
  // addObject( new Attribute( "version", "1.0" ) );
  // addObject( new Attribute( "encoding", "UTF-8" ) );
  // addObject( new Attribute( "standalone", "yes" ) );
} // Header::Header


/// set e.g. version="1.0"
Header::Header( Attribute* egVersion )
      : Object( "xml" ) {
  addObject( egVersion );
} // Header::Header

/// set e.g. version and encoding="UTF-8"
Header::Header( Attribute* egVersion, 
                Attribute* egEncoding )
      : Object( "xml" ) {
  addObject( egVersion );
  addObject( egEncoding );
} // Header::Header


///  set v., enc., and standalone="yes"
Header::Header( Attribute* egVersion, 
                Attribute* egEncoding, 
                Attribute* egStandalone )
      : Object( "xml" ) {
  addObject( egVersion );
  addObject( egEncoding );
  addObject( egStandalone );
} // Header::Header


/// set data type of object, should be always "xml"
Header::Header( String tag ) : Object( tag ) {
  // addObject( new Attribute( "version", "1.0" ) );
  // addObject( new Attribute( "encoding", "UTF-8" ) );
  // addObject( new Attribute( "standalone", "yes" ) );
} // Header


/// set e.g. version="1.0"
Header::Header( String tag, 
                Attribute* a0 )
      : Object( "xml" ) {
  addObject( a0 );
} // Header::Header

/// set e.g. version and encoding="UTF-8"
Header::Header( String tag, 
                Attribute* a0, 
                Attribute* a1 )
      : Object( "xml" ) {
  addObject( a0 );
  addObject( a1 );
} // Header::Header

 /// set v., enc., and standalone="yes"
Header::Header( String tag, 
                Attribute* a0, 
                Attribute* a1, 
                Attribute* a2 )
      : Object( "xml" ) {
  addObject( a0 );
  addObject( a1 );
  addObject( a2 );
} // Header::Header


/// destructor
Header::~Header( void ) {
} // ~Header

/******************************************************************************/
  
String /// returns the stored tag of this header 
Header::getTag( void ) {
  return getString( );
} // Header::getTag

void /// sets the tag of this header
Header::setTag( String tag ) {
  setString( tag );
} // Header::setTag

/******************************************************************************/

std::ostream& /// std::ostream
operator << ( std::ostream& s, Header* obj ) {

  int noOfAttributes = obj->getNoOfObjects( );

  s << "<?" 
    << obj->getTag( )
    << std::flush;

  for( int o = 0; o < noOfAttributes; o++ ) {

    Object* attribute = obj->getObject( o );

    s << " " 
      << attribute 
      << std::flush;

  } // o

  s << "?>" 
    << std::flush
    << std::endl;

  return s;

} // Object::operator <<

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/
