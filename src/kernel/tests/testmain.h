/*                                                                              
 * PDFedit - free program for PDF document manipulation.                        
 * Copyright (C) 2006, 2007  PDFedit team:      Michal Hocko, 
 *                                              Miroslav Jahoda,       
 *                                              Jozef Misutka, 
 *                                              Martin Petricek                                             
 *
 * Project is hosted on http://sourceforge.net/projects/pdfedit                                                                      
 */ 
// vim:tabstop=4:shiftwidth=4:noexpandtab:textwidth=80

/*
 * $RCSfile$
 *
 * $Log$
 * Revision 1.29  2007/11/11 13:43:22  mstsxfx
 * * Typo fixes
 * * getIndirectProperty has reference property now
 * 	- non compatible usage corrected
 *
 * Revision 1.28  2007/11/11 12:41:47  mstsxfx
 * * XPdf 3.02 ported to the tree
 * 	- compilable but not tested at the moment
 * 	- previous state marked by XPDF_3_01-PDFedit_patches
 * 	- mark whole tree with XPDF_3_02-PDFedit_patches after testing
 * * kernel, kpdf-kde-3.3.2 code synced with changes
 * 	- mainly Parser constructor signature change
 *
 * Revision 1.27  2007/02/04 20:17:03  mstsxfx
 * Common Licence comment for all cc and h files available in doc/licence_header
 * file and its content to all cc and h files in src/{gui,kernel,utils}
 * directories.
 * Xpdf code, QSA and QOutputDevice code are not touched
 *
 * Revision 1.26  2006/09/04 01:22:58  misuj1am
 *
 * -- code cleanup
 * 	-- removed not used testing output
 * 	-- tests do not create temporary files if not specified
 *
 * Revision 1.25  2006/06/17 15:11:50  misuj1am
 *
 * -- observers updated
 * -- changes due to cobjectcomplex division
 *
 * Revision 1.24  2006/06/14 23:04:22  misuj1am
 *
 * -- minor fixes
 *
 * Revision 1.23  2006/06/14 22:48:13  misuj1am
 *
 * -- minor updates
 *
 * Revision 1.22  2006/06/09 15:48:24  misuj1am
 *
 *
 * -- structure updates
 *
 * Revision 1.21  2006/06/02 11:31:46  misuj1am
 *
 * -- ADD: outline get text function
 * -- CHANGE: getOutlines returns just iproperites
 * --tests changed
 *
 * Revision 1.20  2006/06/02 01:34:56  misuj1am
 *
 * -- ADD: outline test
 *
 * Revision 1.19  2006/05/29 00:11:53  misuj1am
 *
 * -- tests fixed / improved
 *
 * Revision 1.18  2006/05/27 21:08:10  misuj1am
 *
 * -- tests improved
 * 	-- tests are testing every page instead of only on the first page
 *
 * Revision 1.17  2006/05/10 21:36:59  misuj1am
 *
 * -- adapted to ~CPdf beeing made private
 *
 * Revision 1.16  2006/05/03 01:06:18  misuj1am
 *
 * -- tests improvments
 *
 * Revision 1.15  2006/05/01 12:29:34  misuj1am
 *
 * -- CStream update, CContentStream update, CInlineImage added - test version
 *
 * Revision 1.14  2006/04/23 23:01:28  misuj1am
 *
 * -- tests improved
 *
 * Revision 1.13  2006/04/22 14:57:52  misuj1am
 *
 * --Observers improved
 *
 * Revision 1.12  2006/04/22 02:36:50  misuj1am
 *
 * -- observer correction
 *
 * Revision 1.11  2006/04/21 20:39:50  misuj1am
 *
 * -- test output improved
 *
 * Revision 1.10  2006/04/21 19:06:21  misuj1am
 *
 * -- tests improved
 *
 * Revision 1.9  2006/04/20 21:53:20  misuj1am
 *
 * --minor improvments
 *
 * Revision 1.8  2006/04/20 19:06:28  misuj1am
 *
 * -- tests improved
 *
 * Revision 1.7  2006/04/20 18:27:57  misuj1am
 *
 * -- cppunit tests
 *
 * Revision 1.6  2006/04/20 13:22:23  misuj1am
 *
 * --ADD: cppunittests, improved other tests
 *
 * Revision 1.5  2006/04/20 12:17:51  misuj1am
 *
 * -- IMPORTANT: when kernel output in tests needed, write ./kernel [file] all
 *
 * Revision 1.4  2006/04/10 23:07:22  misuj1am
 *
 *
 * -- ADD support for getObjectsAddPosition
 * 	-- almost done
 *
 * Revision 1.3  2006/04/02 17:15:17  misuj1am
 *
 *
 * -- testing
 *
 * Revision 1.2  2006/04/01 17:55:44  misuj1am
 *
 *
 * --ADD: MEM_CHECK at the end of testing
 *
 * Revision 1.1  2006/04/01 00:39:51  misuj1am
 *
 *
 * -- tests
 *
 */
#ifndef _TESTMAIN_H_
#define _TESTMAIN_H_

#include "../static.h"
#include "../cobject.h"
#include "../cpdf.h"
#include "../cpage.h"
#include "../pdfoperators.h"
#include "../coutline.h"
#include "../exceptions.h"

//CPPUNITTEST
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/CompilerOutputter.h>


// TFUJJ
using namespace std;
using namespace pdfobjects;

//
// Extern variable that will hold files that we should test
//
typedef std::vector<std::string> FileList;
extern FileList fileList;


//========= NASTY =============
#define OUTPUT		cout
#define KOUTPUT		cerr

#define	INIT_BUFS			ofstream redirect_file("/dev/null"); streambuf * strm_buffer = NULL;bool swap = false;
#define	SWAP_BUFS			{swap=true;strm_buffer = KOUTPUT.rdbuf(); KOUTPUT.rdbuf(redirect_file.rdbuf());}
#define SWAP_BUFS_BACK		{KOUTPUT.rdbuf(strm_buffer);}
#define OUTPUT_MAGIC_WORD 	"all"
#define CHECK_OUTPUT(a,b)	INIT_BUFS;\
							if (NULL != argv[1] && 0 == strcmp(argv[1],OUTPUT_MAGIC_WORD))\
							{--(a);++(b);}\
							else\
							{SWAP_BUFS;}
#define KERNEL_OUTPUT_BACK	if (swap) {SWAP_BUFS_BACK;}
#define TEST(a)		OUTPUT << "\t//== " << (a) << "  " << flush;
#define START_TEST	OUTPUT << endl << "Started testing..." << endl;
#define END_TEST	OUTPUT << "Ended testing..." << endl; KERNEL_OUTPUT_BACK;
#define OK_TEST		OUTPUT << "\t...TEST PASSED...\n" << flush;
//==========================

// if set validation functions will output
#define REALLY_ALL_OUTPUT	0

// If set, some tests can create files with some special information
#define TEMP_FILES_CREATE	0

// MAX. of tested pages on 1 pdf.. if many, could take hours to complete
static const size_t TEST_MAX_PAGE_COUNT = 10000;

//
// PrintDbg from tests
//
#define testPrintDbg(level, msg) _printDbg("TEST", level,  OUTPUT, msg);

//
//
//
template<PropertyType T>
IProperty*
createSimpleObjFromXpdf (CPdf& pdf, Object& obj, IndiRef ref)
{
		return new CObjectSimple<T> (pdf, obj, ref);
}

inline ostream& 
operator << (ostream& os, IProperty& ip)
{
	string str;
	ip.getStringRepresentation (str);

	#if REALLY_ALL_OUTPUT
	os << "[CObject Type " << ip.getType () << "] " << str << endl;
	#endif
	
	return os;
}

//
//
//
inline ostream& 
operator << (ostream& os, Object* o)
{
	string str;
	assert (NULL != o);
	
	if (o->isCmd() || o->isEOF())
	{
		os << o->getCmd() << endl;

	}else
	{
		utils::xpdfObjToString (*o,str);
		#if REALLY_ALL_OUTPUT
		os << "[Xpdf Type " << o->getTypeName () << "] " << str << endl;
		os << str;
		#endif
	}

	return os;
}

//
//
//
inline void
print (__attribute__((unused)) ostream& os, Object* o, XRef* xref)
{
	if (!o->isStream())
		throw;
	
	Object obj;
	assert (NULL != xref);
	boost::scoped_ptr<Parser> parser (new Parser(xref, new Lexer(xref, o),
				gTrue  // TODO is gtrue ok here?
				)
			);
	parser->getObj(&obj);
	while (!obj.isEOF()) 
	{
		//os << &obj;
		obj.free ();
		// grab the next object
		parser->getObj(&obj);
	}
}


//
//
//
inline ostream& 
operator << (ostream& os, Dict* d)
{
	string str;
	Object obj;
	assert (NULL != d);

	for (int i = 0; i < d->getLength(); ++i)
	{
		#if REALLY_ALL_OUTPUT
		os << d->getKey(i) << "\t" << d->getValNF (i, &obj) << endl;
		#endif
	}

	return os;
}

//
//
//
//
inline std::ostream& 
operator << (ostream& os, const IndiRef& rf)
{
	os  << " Num: " << rf.num << "Gen: " << rf.gen;
	return os;
}


//
//
//
inline ostream& 
operator << (ostream& os, Stream* s)
{
	string str;
	assert (NULL != s);

	#if REALLY_ALL_OUTPUT
	os << "Stream:";
	#endif
	int c;
	while (EOF != (c=s->getRawChar()))
	{
		#if REALLY_ALL_OUTPUT
		os << (char)c << " ";
		#endif
	}

	#if REALLY_ALL_OUTPUT
	os << endl;
	#endif
	return os;
}

//
//
//
template<typename T>
bool
ip_validate (const T& val, const T& expected)
{
	
	if (val == expected)
	{
		#if REALLY_ALL_OUTPUT
		OUTPUT << "*** Validation OK! <comparison of values>" << endl;
		#endif
		return true;
	}
	else
	{
		OUTPUT << "DOES NOT MATCH: " << endl;
		throw;
		return false;
	}
}

inline bool
ip_validate (const IndiRef& val, const IndiRef& expected)
{
	
	if ((val.gen == expected.gen) && (val.num == expected.num))
	{
		#if REALLY_ALL_OUTPUT
		OUTPUT << "*** Validation OK! <comparison of Indiref>" << endl;
		#endif
		return true;
	}
	else
	{
		OUTPUT << "DOES NOT MATCH: " << endl;
		throw;
		return false;
	}
}

inline bool
ip_validate (Object* o, const string& expected,__attribute__((unused)) bool out = true)
{
	string str;
	assert (NULL != o);
	utils::xpdfObjToString (*o,str);

	if (str == expected)
	{
		#if REALLY_ALL_OUTPUT
		if (out)
			OUTPUT << "*** Validation OK! " << expected << endl;
		else
			OUTPUT << "*** Validation OK! " << "<not shown, output probably too long>"<< endl;
		#endif
		return true;
	}
	else
	{
		OUTPUT << "DOES NOT MATCH: " << str << " with " << expected << endl;
		throw;
		return false;
	}
}

inline bool
ip_validate (Object& o, IProperty& ip,__attribute__((unused)) bool out = true)
{
	string str;
	utils::xpdfObjToString (o,str);

	string str1;
	ip.getStringRepresentation (str1);

	if (str == str1)
	{
		#if REALLY_ALL_OUTPUT
		if (out)
			OUTPUT << "*** Validation OK! " << str << endl;
		else
			OUTPUT << "*** Validation OK! " << "<not shown, output probably too long>"<< endl;
		#endif
		return true;
	}
	else
	{
		OUTPUT << "DOES NOT MATCH: " << str << " with " << str1 << endl;
		throw;
		return false;
	}
}

inline bool
ip_validate (const IProperty& ip, const string& expected,__attribute__((unused)) bool out = true)
{
	string str;
	ip.getStringRepresentation (str);
	
	if (str == expected)
	{
		#if REALLY_ALL_OUTPUT
		if (out)
			OUTPUT << "*** Validation OK! " << expected << endl;
		else
			OUTPUT << "*** Validation OK! " << "<not shown, output probably too long>"<< endl;
		#endif		
		return true;
	}
	else
	{
		OUTPUT << "DOES NOT MATCH: " << str << " with " << expected << endl;
		throw;
		return false;
	}
}

inline bool
ip_validate (const IProperty& ip1, const IProperty& ip2)
{
	string str1, str2;
	ip1.getStringRepresentation (str1);
	ip2.getStringRepresentation (str2);
	
	if (str1 == str2)
	{
		#if REALLY_ALL_OUTPUT
		OUTPUT << "*** Validation OK! " << str1 << endl;
		#endif
		return true;
	}
	else
	{
		OUTPUT << "DOES NOT MATCH: " << str1 << " with " << str2 << endl;
		throw;
		return false;
	}
}

inline bool
ip_validate (PropertyType tp1, PropertyType tp2)
{
	if (tp1 == tp2)
	{
		#if REALLY_ALL_OUTPUT
		OUTPUT << "*** validation ok! " << tp1 << endl;
		#endif
		return true;
	}
	else
	{
		OUTPUT << "does not match: " << tp1 << " with " << tp2 << endl;
		throw;
		return false;
	}
}

inline bool
ip_validate (size_t n, size_t m)
{
	if (n == m)
	{
		#if REALLY_ALL_OUTPUT
		OUTPUT << "*** validation ok! size:" << n << endl;
		#endif
		return true;
	}
	else
	{
		OUTPUT << "does not match: " << n << " with " << m << endl;
		throw;
		return false;
	}
}

inline bool
ip_validate (vector<string>& n, vector<string>& m)
{
	if (equal (n.begin(), n.end(), m.begin()))
	{
		#if REALLY_ALL_OUTPUT
		OUTPUT << "*** validation ok!" <<  endl;
		#endif
		return true;
	}
	else
	{
		OUTPUT << "does not match: ";
		for (vector<string>::iterator it = n.begin (); it != n.end(); ++it)
				OUTPUT << *it << "|";
		OUTPUT << "... with ...";
		for (vector<string>::iterator it = m.begin (); it != m.end(); ++it)
				OUTPUT << *it << "|";
		OUTPUT << endl;
		throw;
		return false;
	}
}

//
// Get test objects
//
inline boost::shared_ptr<CStream>
getTestStreamContent (boost::shared_ptr<CPage> page)
{
	boost::shared_ptr<CDict> dict = page->getDictionary();
	assert (dict);
	boost::shared_ptr<IProperty> ccs = utils::getReferencedObject (dict->getProperty("Contents"));
	if (isStream(ccs))
		return IProperty::getSmartCObjectPtr<CStream> (ccs);
	else if (isArray(ccs))
		return utils::getCStreamFromArray (ccs, 0);
	else
	{
		//assert (!"Bad content stream type.");
		throw CObjInvalidObject ();
	}
}


//
// Indicate we are working
//
template<typename T>
void _working (T& oss)
{
	static int i = 0;
	static char chars[4] = { 'o', '/', '-', '\\' };
	
	if (0 == (i % 4))
		i = 0;
	
	oss << "\b" << flush;
	assert (4 > i);
	oss << chars[i] << flush;
	i++;
}


//=====================================================================================

struct pdf_deleter
{
	void operator() (CPdf* p)
	{assert (p); p->close();}
};


#endif // _TESTMAIN_H_
