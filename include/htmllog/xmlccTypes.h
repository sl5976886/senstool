/** 
 * @file xmlccTypes.h
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

#ifndef __xmlccTypes_h__
#define __xmlccTypes_h__

/******************************************************************************/

#include "./xmlccInclDefs.h" /// common include file for headers and typedefs

/******************************************************************************/

namespace XMLCC {

/******************************************************************************/

#define _XMLCC_VERSION_Types_ 0.71 // 20100430
#define _XMLCC_DEBUG_Types_

/******************************************************************************/

namespace Types { /// namespace for types

enum /// types for building XML elements (XMLCC objects)
Type {
  Root,
  Header,
  Attribute,
  Element,
  Comment,
  CData, // TODO: working on it for version 0.70
  Doctype, // TODO: working on it for version 0.70
  Value
}; // enum Type

/******************************************************************************/

} // namespace Types

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccTypes_h__
