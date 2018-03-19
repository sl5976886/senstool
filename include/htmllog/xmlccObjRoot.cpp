/** 
 * @file xmlccObjRoot.cpp
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

#include "./xmlccObjRoot.h" // OBJ::Root
#include "./xmlccObjHeader.h" // OBJ::Header
#include "./xmlccObjComment.h" // OBJ::Comment
#include "./xmlccObjElement.h" // OBJ::Element

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

/// constructor
Root::Root( void )
    : Object( "XMLCC_ROOT" ) {
} // Root::Root

/// constructor
Root::Root( String fileName ) 
    : Object( fileName ) {
} // Root::Root

/// add a header
Root::Root( String fileName, 
            Object* header  ) 
    : Object( fileName ) {
  addObject( header );
} // Root::Root 

/// add also the single XML root element
Root::Root( String fileName, 
            Object* header, 
            Element* rootElement ) 
    : Object( fileName ) {
  addObject( header );
  addObject( rootElement );
} // Root::Root 

/// add one comment
Root::Root( String fileName, 
            Object* header, 
            Comment* c0,
            Element* rootElement  ) 
    : Object( fileName ) {
  addObject( header );
  addObject( c0 );
  addObject( rootElement );
} // Root::Root 

/// add two comments
Root::Root( String fileName, 
            Object* header, 
            Comment* c0, Comment* c1,  
            Element* rootElement  ) 
    : Object( fileName ) {
  addObject( header );
  addObject( c0 );
  addObject( c1 );
  addObject( rootElement );
} // Root::Root 

/// add three comments
Root::Root( String fileName, 
            Object* header, 
            Comment* c0, Comment* c1, Comment* c2,
            Element* rootElement  ) 
    : Object( fileName ) {
  addObject( header );
  addObject( c0 );
  addObject( c1 );
  addObject( c2 );
  addObject( rootElement );
} // Root::Root 

/// add four comments
Root::Root( String fileName, 
            Object* header, 
            Comment* c0, Comment* c1, Comment* c2, 
            Comment* c3,
            Element* rootElement  ) 
    : Object( fileName ) {
  addObject( header );
  addObject( c0 );
  addObject( c1 );
  addObject( c2 );
  addObject( c3 );
  addObject( rootElement );
} // Root::Root 

/// add five comments
Root::Root( String fileName, 
            Object* header, 
            Comment* c0, Comment* c1, Comment* c2, 
            Comment* c3, Comment* c4,  
            Element* rootElement  ) 
    : Object( fileName ) {
  addObject( header );
  addObject( c0 );
  addObject( c1 );
  addObject( c2 );
  addObject( c3 );
  addObject( c4 );
  addObject( rootElement );
} // Root::Root 

/// destructor
Root::~Root( void ) {
} // ~Root

/******************************************************************************/

String /// returns the stored file name of this root
Root::getFileName( void ) {
  return getString( );
} // Root::getFileName

void /// sets the file name of this root
Root::setFileName( String fileName ) {
  setString( fileName );
} // Root::setFileName

/******************************************************************************/

std::ostream& /// std::ostream
operator << ( std::ostream& s, Root* obj ) {

  //s << "file name: " 
  //  << obj->getString( ) 
  //  << std::flush 
  //  << std::endl;

  int noOfObjects = obj->getNoOfObjects( );

  for( int o = 0; o < noOfObjects; o++ ) {

    Object* sonObj = obj->getObject( o );

    sonObj->setIndent( obj );

    s << sonObj << std::flush;

  } // o

  return s;

} // Object::operator <<

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/
