#ifndef PYKEP_UTILS_H
#define PYKEP_UTILS_H

#include <Python.h>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/python/class.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/docstring_options.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/tuple.hpp>
#include <sstream>
#include <string>


template <class T>
inline T Py_copy_from_ctor(const T &x)
{
	return T(x);
}

template <class T>
inline T Py_deepcopy_from_ctor(const T &x, boost::python::dict)
{
	return T(x);
}

// Generic pickle suite for C++ classes with default constructor.
template <class T>
struct generic_pickle_suite : boost::python::pickle_suite
{
	static boost::python::tuple getinitargs(const T &)
	{
		return boost::python::make_tuple();
	}
	static boost::python::tuple getstate(const T &x)
	{
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa << x;
		return boost::python::make_tuple(ss.str());
	}
	static void setstate(T &x, boost::python::tuple state)
	{
		using namespace boost::python;
		if (len(state) != 1)
		{
			PyErr_SetObject(PyExc_ValueError,("expected 1-item tuple in call to __setstate__; got %s" % state).ptr());
			throw_error_already_set();
		}
		const std::string str = extract<std::string>(state[0]);
		std::stringstream ss(str);
		boost::archive::text_iarchive ia(ss);
		ia >> x;
	}
};

template <class T>
inline void py_cpp_loads(T &x, const std::string &s)
{
	std::stringstream ss(s);
	boost::archive::text_iarchive ia(ss);
	ia >> x;
}

template <class T>
inline std::string py_cpp_dumps(const T &x)
{
	std::stringstream ss;
	boost::archive::text_oarchive oa(ss);
	oa << x;
	return ss.str();
}

#endif //PYKEP_UTILS_H
