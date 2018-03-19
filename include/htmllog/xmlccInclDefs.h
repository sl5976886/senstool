/** 
 * @file xmlccInclDefs.h
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

#ifndef __xmlccInclDefs_h__
#define __xmlccInclDefs_h__

/******************************************************************************/

#include <exception> // std::exception
#include <iostream>  // std::cout
#include <typeinfo>  // dynmaic_cast<T>
#include <sstream>   // std::strstream
#include <fstream>   // std::fsteam
#include <string>    // std::string

/******************************************************************************/

namespace XMLCC {

#define _XMLCC_DEBUG_ /// enable this for debug code running

#define _XMLCC_INDENTION_SIZE_ 2; /// indention of the number of whitespaces

#define _XMLCC_USE_TEST_ /// enables test methods mostly for components

// #define _XMLCC_USE_DEV_PARSER_ /// use components under developement 

// #define _XMLCC_USE_DEV_CDATA_ /// use components of <![CDATA[ .. ]]>

typedef std::string     String; /// STL typedef for std:string
typedef std::fstream    FileStr; /// STL typedef for std::fstream
typedef std::ifstream   FileStrIn; /// STL typedef for std::ifstream
typedef std::ofstream   FileStrOut; /// STL typedef for std::ofstream

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccInclDefs_h__
