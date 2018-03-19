/** 
 * @file xmlccBuilder.h
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

#ifndef __xmlccBuilder_h__
#define __xmlccBuilder_h__

/******************************************************************************/

#include "./xmlccTypes.h"        // an XMLCC TYPES
#include "./xmlccObjRoot.h"      // an XMLCC root object
#include "./xmlccObjHeader.h"    // an XMLCC header object
#include "./xmlccObjElement.h"   // an XMLCC element object
#include "./xmlccObjAttribute.h" // an XMLCC attribute object
#include "./xmlccObjValue.h"     // an XMLCC value object
#include "./xmlccObjComment.h"   // an XMLCC comment object
#include "./xmlccObjCData.h"     // an XMLCC CDATA object
#include "./xmlccObjDoctype.h"   // an XMLCC DOCTYPE object

/******************************************************************************/

namespace XMLCC {

/******************************************************************************/

#define _XMLCC_VERSION_Builder_ 0.71 // 20100430
#define _XMLCC_DEBUG_Builder_

/******************************************************************************/

class /// class for building objects
Builder {
 public:

  Builder( void ); /// constructor
  virtual ~Builder( void ); /// destructor

  OBJ::Root* createRoot( void ); /// XMLCC root, representing the file
  OBJ::Root* createRoot( String fileName ); /// XMLCC root, representing the file
  Object* createHeader( void ); /// an XML header with standard attributes
  Object* createDoctype( void ); /// a HTML DOCTYPE header with most common attributes

  Object* create( Types::Type type, String tag ); /// create a new object and return it
  Object* create( Types::Type type, String tag, String value ); /// create a new object with value and return it

  Object* create( Types::Type type, String tag, Object* object ); /// create a new object and add the passed
  Object* create( Types::Type type, String tag, String value, Object* object ); /// create a new object with value and add the passed

  void create( Object* object, Types::Type type, String tag ); /// create a new object and add it to object
  void create( Object* object, Types::Type type, String tag, String value ); /// create a new object with value and add it to object

}; // class Builder

/******************************************************************************/

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccDomBuilder_h__
