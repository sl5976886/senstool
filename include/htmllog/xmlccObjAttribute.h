/** 
 * @file xmlccObjAttribute.h
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
 */

#ifndef __xmlccObjAttribute_h__
#define __xmlccObjAttribute_h__

/******************************************************************************/

#include "./xmlccObject.h" // base class

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

#define _XMLCC_VERSION_OBJ_Attribute_ 0.71 // 20100430
#define _XMLCC_DEBUG_OBJ_Attribute_

/******************************************************************************/

class 
Attribute : public Object {
 public:

  Attribute( String name ); /// constructor
  Attribute( String name, String value ); /// constructor
  virtual ~Attribute( void ); /// destructor

  String getName( void ); /// returns the stored name of this attribute
  void setName( String name ); /// sets the name of this attribute

  String getValue( void ); /// returns the stored value of this attribute
  void setValue( String value ); /// sets the value of this attribute

  friend std::ostream& operator << ( std::ostream& s, Attribute* obj );

protected:

  String _value; /// attrite's valie; attribute's name is stored in _tag

}; // class Attribute

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccObjAttribute_h__
