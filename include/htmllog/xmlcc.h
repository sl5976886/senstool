/** 
 * @file xmlcc.h
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

#ifndef __xmlcc_h__
#define __xmlcc_h__

/******************************************************************************/

#include "./xmlccInclDefs.h"   // XMLCC:: STL includes and typedefs
#include "./xmlccBuilder.h"    // XMLCC::Builder
#include "./xmlccDomGrabber.h" // XMLCC::DOM::Grabber
#include "./xmlccDomViewer.h"  // XMLCC::DOM::Viewer
#include "./xmlccDomWriter.h"  // XMLCC::DOM::Writer
#include "./xmlccDomParser.h"  // XMLCC::DOM::Parser
#include "./xmlccSaxParser.h"  // XMLCC::SAX::Parser

/******************************************************************************/

#ifdef _XMLCC_USE_DEV_PARSER_

 #include "./xmlccDevParser.h" // XMLCC::DOM::Parser

#endif

/******************************************************************************/

namespace XMLCC {

#define _XMLCC_LICENSE_ Apache_2.0 /// use and share by the Apache License, version 2.0
#define _XMLCC_PACKAGE_ "Vivian Creighton" /// from http://www.kleimo.com/random/name.cfm female, 1, 99
#define _XMLCC_VERSION_ 0.71 /// version number of the current implementation
#define _XMLCC_DATE_ 20100430 /// date of the current implementation
#define _XMLCC_BUILD_DATE_ __DATE__ /// for compiling the actual date
#define _XMLCC_BUILD_TIME_ __TIME__ /// for compiling the actual time
#define _XMLCC_DEBUG_ /// enable this for debug code running

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlcc_h__
