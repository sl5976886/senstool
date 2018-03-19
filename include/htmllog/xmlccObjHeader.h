/** 
 * @file xmlccObjHeader.h
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

#ifndef __xmlccObjHeader_h__
#define __xmlccObjHeader_h__

/******************************************************************************/

#include "./xmlccObject.h" // base class

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

#define _XMLCC_VERSION_OBJ_Header_ 0.71 // 20100430
#define _XMLCC_DEBUG_OBJ_Header_

/******************************************************************************/

class
Header : public Object {
 public:

  Header( void ); /// set tag to "xml"
  Header( Attribute* egVersion ); /// set e.g. version="1.0"
  Header( Attribute* egVersion, 
          Attribute* egEncoding ); /// set e.g. version and encoding="UTF-8"
  Header( Attribute* egVersion, 
          Attribute* egEncoding, 
          Attribute* egStandalone ); ///  set v., enc., and standalone="yes"

  Header( String tag ); /// set tag, should be always "xml"
  Header( String tag, 
          Attribute* a0 ); /// set e.g. version="1.0"
  Header( String tag, 
          Attribute* a0, 
          Attribute* a1 ); /// set e.g. version and encoding="UTF-8"
  Header( String tag, 
          Attribute* a0, 
          Attribute* a1, 
          Attribute* a2 ); /// set v., enc., and standalone="yes"

  virtual ~Header( void ); /// destructor

  String getTag( void ); /// returns the stored tag of this header
  void setTag( String tag ); /// sets the tag of this header

  friend std::ostream& operator << ( std::ostream& s, Header* obj );

}; // class Header

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccObjHeader_h__
