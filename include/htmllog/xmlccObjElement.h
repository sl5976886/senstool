/** 
 * @file xmlccObjElement.h
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

#ifndef __xmlccObjElement_h__
#define __xmlccObjElement_h__

/******************************************************************************/

#include "./xmlccObject.h" // base class

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

#define _XMLCC_VERSION_OBJ_Element_ 0.71 // 20100430
#define _XMLCC_DEBUG_OBJ_Element_

/******************************************************************************/

class
Element : public Object {
 public:

  Element( String tag ); /// constructor
  Element( String tag, String value ); /// constructor

  Element( String tag, Object* ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*  ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object* 
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*
                       ); /// COMPOSITE PATTERN


  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*,
                       Object*
                       ); /// COMPOSITE PATTERN


  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*
                       ); /// COMPOSITE PATTERN


  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object* 
                       ); /// COMPOSITE PATTERN


  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object* 
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*, 
                       Object* ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*, 
                       Object*, Object* ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*, 
                       Object*, Object*, Object*
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*, 
                       Object*, Object*, Object*, Object*
                       ); /// COMPOSITE PATTERN

  Element( String tag, Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*,
                       Object*, Object*, Object*, Object*, Object*, 
                       Object*, Object*, Object*, Object*, Object*
                       ); /// COMPOSITE PATTERN


  Element( String tag, 
           int noOfObjects, Object*, ... 
           ); /// COMPOSITE PATTERN for more than 20
  Element( String tag, String value, 
           int noOfObjects, Object*, ... 
           ); /// COMPOSITE PATTERN for more than 20;

  //Element( String tag, Object*, ... ); /// COMPOSITE PATTERN
  //Element( String tag, String value, Object*, ... ); /// COMPOSITE PATTERN

  virtual ~Element( void ); /// destructor

  String getTag( void ); /// returns the stored tag of this element
  void setTag( String tag ); /// sets the tag of this element

  String getValue( void ); /// returns the FIRST stored value of this element
  String getValue( int indx ); /// returns the stored value at indx 

  void addValue( String value ); /// sets the FIRST value of this element

  int getNoOfValues( void ); /// returns the number of stored values

  friend std::ostream& operator << ( std::ostream& s, Element* obj );

}; // class Element

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccObjElement_h__
