/** 
 * @file xmlccDomTokenizer.h
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

#ifndef __xmlccDomTokenizer_h__
#define __xmlccDomTokenizer_h__

/******************************************************************************/

#include "./xmlccBuilder.h" // building objects

/******************************************************************************/

namespace XMLCC {

namespace DOM {

/******************************************************************************/

#define _XMLCC_VERSION_DOM_Tokenizer_ 0.71 // 20100430
#define _XMLCC_DEBUG_DOM_Tokenizer_

/******************************************************************************/

class /// class converts strings keeping tags into objects of the DOM structure
Tokenizer {
 public:

  Tokenizer( void ); /// constructor
  virtual ~Tokenizer( void ); /// destructor

  Object* convertTag( String tag ); /// convert a tag 2 object
  Object* convertTagComplete( String tag ); /// convert a tag 2 object
  Object* convertValue( String value ); /// convert a value 2 object
  
  bool check4Ending( String tag ); /// check if tag is ending
  bool check4StandAlone( String tag ); /// check if tag is standalone

 protected:

  Object* convert2Object( String line ); /// filter string and hand back objects
  Object* convert2ObjectComplete( String tag ); /// convert a tag 2 object

  Object* conv2Header( String line ); /// convert header string to an object
  Object* conv2Comment( String line ); /// convert comment string to an object
  Object* conv2Tag( String line ); /// convert tag string to an object
  Object* conv2CData( String line ); /// convert CDATA to an object
  Object* conv2Doctype( String line );  /// convert DOCTYPE to an object

  ListObjects* convAttAndValList( String line ); /// get Strings: att="val"
  Object* conv2AttAndVal( String line ); /// convert to attrib and value object
  Object* conv2Val( String line ); /// convert a value string to an object

  String getTag( String line ); /// hand the tag back as string

  SYS::StringTool* _strTool; /// string manipulation

}; // class Tokenizer

/******************************************************************************/

} // namespace DOM

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccDomTokenizer_h__
