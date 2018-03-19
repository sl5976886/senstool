/** 
 * @file xmlccDomGrabber.h
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

#ifndef __xmlccDomGrabber_h__
#define __xmlccDomGrabber_h__

/******************************************************************************/

#include "./xmlccBuilder.h" // XMLCC::DOM::Builder

/******************************************************************************/

namespace XMLCC {

namespace DOM {

/******************************************************************************/

#define _XMLCC_VERSION_DOM_Grabber_ 0.71 // 20100430
#define _XMLCC_DEBUG_DOM_Grabber_

/******************************************************************************/

class /// class sorts Obejcts and Object trees and hands back requested stuff
Grabber {
 public:

  Grabber( void ); /// constructor
  virtual ~Grabber( void ); /// destructor
  
  String getValue4Object( Object* object ); /// returns a string keeping FIRST value 4 this object
  ListStrings* getValues4Object( Object* object ); /// returns a list keeping strings for all set values 4 this object

  String getAttributeName4Object( Object* object ); /// returns a string keeping label 4 FIRST attribute 4 this object
  ListStrings* getAttributeNames4Object( Object* object ); /// returns a list keeping values 4 for all set attributes 4 this object as strings
  
  String getAttributeValue4Object( Object* object ); /// returns a string keeping value 4 FIRST attribute 4 this object
  ListStrings* getAttributeValues4Object( Object* object ); /// returns a list keeping values 4 for all set attributes 4 this object as strings

  String getComment4Object( Object* object ); /// returns a string keeping FIRST comment 4 this object
  ListStrings* getComments4Object( Object* object ); /// returns a list keeping strings for all set comments 4 this object

  String tryAttributeName4Object( Object* object, String attributeName ); /// pass Element and attribute name, receive value or an exception

  bool check4Root( Object* obect ); /// return true if object is of type root
  bool check4Header( Object* obect ); /// return true if object is of type header
  bool check4Element( Object* obect ); /// return true if object is of type Element
  bool check4Attribute( Object* obect ); /// return true if object is of type Attribute
  bool check4Value( Object* obect ); /// return true if object is of type Value
  bool check4CData( Object* obect ); /// return true if object is of type CData
  bool check4Comment( Object* obect ); /// return true if object is of type Comment

  int getNoOfHeaders( Object* object ); /// get number of headers added at an object
  int getNoOfCData( Object* object ); /// get number of CDATA added at an object
  int getNoOfAttributes( Object* object ); /// get number of attributes added at an object
  int getNoOfValues( Object* object ); /// get number of values added at an object
  int getNoOfElements( Object* object ); /// get number of elements added at an object
  int getNoOfComments( Object* object ); /// get number of comments added at an object

  void sort2Headers( int& sizeOfList, Object**& list, Object* object ); /// get all headers of an object by a generated array
  void sort2CData( int& sizeOfList, Object**& list, Object* object ); /// get all meta data of an object by a generated array
  void sort2Attributes( int& sizeOfList, Object**& list, Object* object ); /// get all attributes of an object by a generated array
  void sort2Values( int& sizeOfList, Object**& list, Object* object ); /// get all values of an object by a generated array
  void sort2Elements( int& sizeOfList, Object**& list, Object* object ); /// get all elements of an object by a generated array
  void sort2Comments( int& sizeOfList, Object**& list, Object* object ); /// get all comments of an object by a generated array

  int findNoOfTags( Object* object, String tag ); /// find all tags in structure and hand back no of
  int findNoOfValues( Object* object, String value ); /// find all values in structure and hand back no of
  int findNoOfTagsWithValue( Object* object, String tag, String value ); /// find all tags with value in structure and hand back no of

  ListObjects* findObjectsByTag( Object* object, String tag ); /// find all tags in structure and hand back an object list
  void findObjectsByTag( int& sizeOfList, Object**& list, Object* object, String tag ); /// find all tags in structure and hand back an object list

  ListObjects* findObjectsByValue( Object* object, String value ); /// find all values in structure and hand back an object list
  void findObjectsByValue( int& sizeOfList, Object**& list, Object* object, String value ); /// find all values in structure and hand back an object list

  ListObjects* findObjectsByTagAndValue( Object* object, String tag, String value ); /// find all objects keeping this tag and value in structure and hand back an object list
  void findObjectsByTagAndValue( int& sizeOfList, Object**& list, Object* object, String tag, String value ); /// find all objects keeping this tag and value in structure and hand back an object list

}; // class Grabber

/******************************************************************************/

} // namespace DOM

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccDomGrabber_h__
