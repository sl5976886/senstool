/** 
 * @file xmlccObjDoctype.h
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

#ifndef __xmlccObjDoctype_h__
#define __xmlccObjDoctype_h__

/******************************************************************************/

#include "./xmlccObject.h" // base class

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

#define _XMLCC_VERSION_OBJ_Doctype_ 0.71 // 20100430
#define _XMLCC_DEBUG_OBJ_Doctype_

/******************************************************************************/

class
Doctype : public Object {
 public:

  Doctype( void ); /// <!DOCTYPE html>

  Doctype( String rootType ); /// <!DOCTYPE rootType>

  Doctype( String rootType, 
           String sys, String pathDtdFile ); /// sys -> SYSTEM "{file|url}.dtd"

  Doctype( String rootType, 
           String pub, String pathPubIdent, 
           String pathDtdFile ); /// pub -> PUBLIC "public identifier" "dtd"

  virtual ~Doctype( void ); /// destructor

  String getDoctype( void ); /// returns the stored DOCTYPE
  void setDoctype( String doctype ); /// sets the DOCTYPE

  String getRootType( void ); /// returns the stored root type for document
  void setRootType( String rootType ); /// sets the root type for document

  String getSysOrPub( void ); /// returns the stored SYSTEM or PUBLIC
  void setSysOrPub( String sysORpub ); /// sets the SYSTEM or PUBLIC

  String getPathPublicIdentifier( void ); /// returns the stored public identifier
  void setPathPublicIdentifier( String pubIdent ); /// sets the public identifier

  String getPathDtdFile( void ); /// returns the stored path to DTD file
  void setPathDtdFile( String dtdFile ); /// sets the path to DTD file

  friend std::ostream& operator << ( std::ostream& s, Doctype* obj );

protected:

  String _rootType; /// "html" for example
  String _sysORpub; /// "SYSTEM" or "PUBLIC" for example
  String _pathPubIdent; /// "-//W3C//DTD XHTML 1.0 Strict//EN" for example
  String _pathDtdFile; /// "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"

}; // class Doctype

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccObjDoctype_h__
