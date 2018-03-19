/** 
 * @file xmlccObjCData.h
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

#ifndef __xmlccObjCData_h__
#define __xmlccObjCData_h__

/******************************************************************************/

#include "./xmlccObject.h" // base class

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

#define _XMLCC_VERSION_OBJ_CData_ 0.71 // 20100430
#define _XMLCC_DEBUG_OBJ_CData_

/******************************************************************************/

class
CData : public Object {
 public:

  CData( String content ); /// constructor
  virtual ~CData( void ); /// destructor

  String getContent( void ); /// returns the stored content of this CData
  void setContent( String content ); /// sets the content of this CData

  friend std::ostream& operator << ( std::ostream& s, CData* obj );

}; // class CData

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccObjCData_h__
