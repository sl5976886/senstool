/** 
 * @file xmlccObjDoctype.cpp
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

#include "./xmlccObjDoctype.h" // header

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/
  
/// <!DOCTYPE html>
Doctype::Doctype( void ) 
       : Object( "DOCTYPE" ) {
  _rootType = "html";
} // Doctype::Doctype

/// <!DOCTYPE rootType>
Doctype::Doctype( String rootType ) 
       : Object( "DOCTYPE" ) {
  _rootType = rootType;
} // Doctype::Doctype

/// sys -> SYSTEM "{file|url}.dtd"
Doctype::Doctype( String rootType, 
         String sys, String pathDtdFile ) 
       : Object( "DOCTYPE" ) {
  _rootType    = rootType;
  _sysORpub    = sys;
  _pathDtdFile = pathDtdFile;
} // Doctype::Doctype

/// pub -> PUBLIC "public identifier" "dtd"
Doctype::Doctype( String rootType, 
         String pub, 
         String pathPubIdent, 
         String pathDtdFile ) 
       : Object( "DOCTYPE" ) {
  _rootType     = rootType;
  _sysORpub     = pub;
  _pathPubIdent = pathPubIdent;
  _pathDtdFile  = pathDtdFile;
} // Doctype::Doctype

/// destructor
Doctype::~Doctype( void ) {
} // ~Doctype

/******************************************************************************/

String /// returns the stored DOCTYPE
Doctype::getDoctype( void ) {
  return getString( );
} // Doctype::getDoctype

void /// sets the DOCTYPE
Doctype::setDoctype( String doctype ) {
  setString( doctype );
} // Doctype::setDoctype 


String /// returns the stored root type for document
Doctype::getRootType( void ) {
  return _rootType;
} // Doctype::getRootType

void /// sets the root type for document
Doctype::setRootType( String rootType ) {
  _rootType = rootType;
} // Doctype::setRootType 


String /// returns the stored SYSTEM or PUBLIC
Doctype::getSysOrPub( void ) {
  return _sysORpub;
} // Doctype::getSysOrPub

void /// sets the SYSTEM or PUBLIC
Doctype::setSysOrPub( String sysORpub ) {
  _sysORpub = sysORpub;
} // Doctype::setSysOrPub 


String /// returns the stored public identifier
Doctype::getPathPublicIdentifier( void ) {
  return _pathPubIdent;
} // Doctype::getPathPublicIdentifier

void /// sets the public identifier
Doctype::setPathPublicIdentifier( String pubIdent ) {
  _pathPubIdent = pubIdent;
} // Doctype::setPathPublicIdentifier 


String /// returns the stored path to DTD file
Doctype::getPathDtdFile( void ) {
  return _pathDtdFile;
} // Doctype::getPathDtdFile

void /// sets the path to DTD file
Doctype::setPathDtdFile( String dtdFile ) {
  _pathDtdFile = dtdFile;
} // Doctype::setPathDtdFile 

/******************************************************************************/

std::ostream& /// std::ostream
operator << ( std::ostream& s, Doctype* obj ) {

  s << "<!" 
    << obj->getDoctype( )
    << " "
    << obj->getRootType( )
    << std::flush;

  String pathPubIdent = obj->getPathPublicIdentifier( );
  if( pathPubIdent.compare( "" ) != 0 ) {
    s << " "
      << "\""
      << obj->getPathPublicIdentifier( )
      << "\""
      << std::flush;
  } // if public identifier exists
  
  String pathDtdFile = obj->getPathDtdFile( );
  if( pathDtdFile.compare( "" ) != 0 ) {
    s << " "
      << "\""
      << obj->getPathDtdFile( )
      << "\""
      << std::flush;
  } // if dtd file exists

  s << ">" 
    << std::flush
    << std::endl;

  return s;

} // Object::operator <<

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/
