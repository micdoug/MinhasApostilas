/****************************************************************************
**
** http://www.qxorm.com/
** Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software
**
** Commercial Usage
** Licensees holding valid commercial QxOrm licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Lionel Marty
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met : http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, or
** if you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_IS_QT_MULTI_MAP_H_
#define _QX_IS_QT_MULTI_MAP_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_qt_multi_map.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_qt_multi_map<T>::value : return true if T is a QMultiMap<> container of Qt library, otherwise return false
 */

#include <QtCore/QMultiMap>

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_qt_multi_map<T>::value : return true if T is a QMultiMap<> container of Qt library, otherwise return false
 */
template <typename T>
class is_qt_multi_map
{

private:

   template <typename V, typename W> static char isContainer(const QMultiMap<V, W> &);
   static int isContainer(...);
   static T t;

public:

   enum { value = (sizeof(qx::trait::is_qt_multi_map<T>::isContainer(t)) == sizeof(char)) };

   typedef typename boost::mpl::if_c<qx::trait::is_qt_multi_map<T>::value, 
                                     boost::mpl::true_, 
                                     boost::mpl::false_>::type type;

};

} // namespace trait
} // namespace qx

#endif // _QX_IS_QT_MULTI_MAP_H_
