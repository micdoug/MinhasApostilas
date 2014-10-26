#ifndef _QX_DLL1_EXPORT_H_
#define _QX_DLL1_EXPORT_H_

#ifdef _MSC_VER
#pragma once
#endif

#ifdef _QX_BUILDING_DLL1
#define QX_DLL1_EXPORT QX_DLL_EXPORT_HELPER
#else // _QX_BUILDING_DLL1
#define QX_DLL1_EXPORT QX_DLL_IMPORT_HELPER
#endif // _QX_BUILDING_DLL1

#ifdef _QX_BUILDING_DLL1
#define QX_REGISTER_HPP_QX_DLL1 QX_REGISTER_HPP_EXPORT_DLL
#define QX_REGISTER_CPP_QX_DLL1 QX_REGISTER_CPP_EXPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_HPP_QX_DLL1 QX_REGISTER_COMPLEX_CLASS_NAME_HPP_EXPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_CPP_QX_DLL1 QX_REGISTER_COMPLEX_CLASS_NAME_CPP_EXPORT_DLL
#else // _QX_BUILDING_DLL1
#define QX_REGISTER_HPP_QX_DLL1 QX_REGISTER_HPP_IMPORT_DLL
#define QX_REGISTER_CPP_QX_DLL1 QX_REGISTER_CPP_IMPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_HPP_QX_DLL1 QX_REGISTER_COMPLEX_CLASS_NAME_HPP_IMPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_CPP_QX_DLL1 QX_REGISTER_COMPLEX_CLASS_NAME_CPP_IMPORT_DLL
#endif // _QX_BUILDING_DLL1

#endif // _QX_DLL1_EXPORT_H_
