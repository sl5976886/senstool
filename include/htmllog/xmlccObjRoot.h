/** 
 * @file xmlccObjRoot.h
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

#ifndef __xmlccObjRoot_h__
#define __xmlccObjRoot_h__

/******************************************************************************/

#include "./xmlccObject.h" // base class

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

#define _XMLCC_VERSION_OBJ_Root_ 0.71 // 20100430
#define _XMLCC_DEBUG_OBJ_Root_

/******************************************************************************/

class
Root : public Object {
 public:

  Root( void ); /// constructor
  Root( String fileName ); /// set a file name
  
  Root( String fileName, Object* header  ); /// add a header
  
  Root( String fileName, Object* header, 
        Element* rootElement ); /// add also the single XML root element
  
  Root( String fileName, Object* header, 
        Comment*,
        Element* rootElement  ); /// add one comment
  
  Root( String fileName, Object* header, 
        Comment*, Comment*,  
        Element* rootElement  ); /// add two comments
  
  Root( String fileName, Object* header, 
        Comment*, Comment*, Comment*,
        Element* rootElement  ); /// add three comments
  
  Root( String fileName, Object* header, 
        Comment*, Comment*, Comment*, 
        Comment*,
        Element* rootElement  ); /// add four comments
  
  Root( String fileName, Object* header, 
        Comment*, Comment*, Comment*, 
        Comment*, Comment*,  
        Element* rootElement  ); /// add five comments

  virtual ~Root( void ); /// destructor

  String getFileName( void ); /// returns the stored file name of this root
  void setFileName( String fileName ); /// sets the file name of this root

  friend std::ostream& operator << ( std::ostream& s, Root* obj );

}; // class Root

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccObjRoot_h__
