#include "stdafx.h"
#include "Xml.h"

////////////////////////////////////////////////////////////////////////////////
//	CXMLDocument
////////////////////////////////////////////////////////////////////////////////


////////////////////
//	Open
//	REMARK:	XML 파일을 불러온다
//	RETURN VALUES:	
//		-	true	:	성공
//		-	false	:	실패
bool
	CXMLDocumentT<>::Open
	(LPCTSTR fn)
{
		if (doc_.p == 0L) {
			Init();
		}

		ATLASSERT(doc_.p != 0L);
		ATLASSERT(fn != 0L);

		VARIANT	v;
		VARIANT_BOOL b;

		USES_CONVERSION;

		v.vt = VT_BSTR;
		v.bstrVal = T2BSTR(fn);

		HRESULT h = doc_->load(v, &b);
		if (FAILED(h) ||
			(h == S_FALSE))
		{
			//		ShowLastError();
			ATLTRACE(_T("CXMLDocument::Open: Failed\n"));
			::SysFreeString(v.bstrVal);
			return false;
		}


		//	Copy file name
		_tcscpy(fn_, fn);
		::SysFreeString(v.bstrVal);

		return true;
}



////////////////////
//	Open
//	REMARK:	XML 파일을 불러온다. IStream interface를 통해서 데이터를 가져온다
//	RETURN VALUES:	
//		-	true	:	성공
//		-	false	:	실패
bool
	CXMLDocumentT<>::Open
	(CComPtr<IStream> stm)
{
		if (doc_.p == 0L) {
			Init();
		}

		ATLASSERT(doc_.p != 0L);

		VARIANT	v;
		VARIANT_BOOL b;

		USES_CONVERSION;

		v.vt = VT_UNKNOWN;
		HRESULT h = stm.QueryInterface(&v.punkVal);
		ATLASSERT(SUCCEEDED(h));

		h = doc_->load(v, &b);
		if (FAILED(h) ||
			(h == S_FALSE))
		{
			ATLTRACE(_T("CXMLDocument::Open: Failed\n"));
			return false;
		}


		//	Clear file name
		fn_[0] = _T('\0');

		return true;
}



////////////////////
//	Open
//	REMARK:	XML 파일을 불러온다. IStream interface를 통해서 데이터를 가져온다
//	RETURN VALUES:	
//		-	true	:	성공
//		-	false	:	실패
bool
	CXMLDocumentT<>::Open
	(BSTR ixml)
{
		if (doc_.p == 0L) {
			Init();
		}

		ATLASSERT(doc_.p != 0L);


		VARIANT_BOOL b;

		HRESULT h = doc_->loadXML(ixml, &b);
		if (FAILED(h) ||
			(h == S_FALSE))
		{
			ATLTRACE(_T("CXMLDocument::Open: Failed\n"));
			return false;
		}


		//	Clear file name
		fn_[0] = _T('\0');

		return true;
}

bool
	CXMLDocumentT<false>::Open
	(BSTR ixml)
{
		if (doc_.p == 0L) {
			Init();
		}

		ATLASSERT(doc_.p != 0L);


		VARIANT_BOOL b;

		HRESULT h = doc_->loadXML(ixml, &b);
		if (FAILED(h) ||
			(h == S_FALSE))
		{
			ATLTRACE(_T("CXMLDocument::Open: Failed\n"));
			return false;
		}


		//	Clear file name
		fn_[0] = _T('\0');

		return true;
}



////////////////////
//	Close
//	REMARK:	XML 문서를 닫는다
void
	CXMLDocumentT<>::Close()
{
		ATLASSERT(doc_.p != 0L);

		doc_.Release();

		fn_[0] = _T('\0');	//	Clear file name.
}


////////////////////
//	Save
bool
	CXMLDocumentT<>::Save
	(LPCTSTR fn)
{
		ATLASSERT(fn != 0L);

		USES_CONVERSION;
		VARIANT v;

		v.vt = VT_BSTR;
		v.bstrVal = T2BSTR(fn);

		HRESULT h = doc_->save(v);

		::SysFreeString(v.bstrVal);

		return (SUCCEEDED(h) == TRUE);
}


////////////////////
//	setProperty
void
	CXMLDocumentT<>::setProperty
	(LPCTSTR key,
	LPCTSTR value)
{
		USES_CONVERSION;
		BSTR bstr_key = T2BSTR(key);

		VARIANT v;
		v.vt = VT_BSTR;
		v.bstrVal = T2BSTR(value);

		CComPtr<IXMLDOMDocument2>	doc2;
		doc_.QueryInterface(&doc2);
		HRESULT h = doc2->setProperty(bstr_key, v);
		ATLASSERT(SUCCEEDED(h));

		::SysFreeString(bstr_key);
		::SysFreeString(v.bstrVal);
}

////////////////////
//	getProperty
CString
	CXMLDocumentT<>::getProperty
	(LPCTSTR key)
{
		USES_CONVERSION;

		BSTR bstr_key = T2BSTR(key);

		VARIANT v;

		CComPtr<IXMLDOMDocument2>	doc2;
		doc_.QueryInterface(&doc2);

		CString s;
		HRESULT h = doc2->getProperty(bstr_key, &v);
		switch (v.vt)
		{
		case VT_EMPTY:
		case VT_NULL:
			s.Empty();
			break;
		case VT_BSTR:
			s = OLE2CA(v.bstrVal);
			::SysFreeString(v.bstrVal);
			break;
		default:
			ATLASSERT(FALSE);
			break;
		}

		::SysFreeString(bstr_key);
		return s;
}



////////////////////
//	createElement
CXMLNode
	CXMLDocumentT<>::createElement
	(LPCTSTR tagName)
{
		USES_CONVERSION;
		BSTR bstr_tagName = T2BSTR(tagName);

		IXMLDOMElement* e;
		HRESULT h = doc_->createElement(bstr_tagName, &e);
		ATLASSERT(SUCCEEDED(h));

		IXMLDOMNode* n;
		h = e->QueryInterface(__uuidof(IXMLDOMNode), reinterpret_cast<void**>(&n));
		ATLASSERT(SUCCEEDED(h));

		CXMLNode nn(n);
		n->Release();
		e->Release();

		::SysFreeString(bstr_tagName);

		return nn;
}


CXMLNode
	CXMLDocumentT<false>::createElement
	(LPCTSTR tagName)
{
		USES_CONVERSION;
		BSTR bstr_tagName = T2BSTR(tagName);

		IXMLDOMElement* e;
		HRESULT h = doc_->createElement(bstr_tagName, &e);
		ATLASSERT(SUCCEEDED(h));

		IXMLDOMNode* n;
		h = e->QueryInterface(__uuidof(IXMLDOMNode), reinterpret_cast<void**>(&n));
		ATLASSERT(SUCCEEDED(h));

		CXMLNode nn(n);
		n->Release();
		e->Release();

		::SysFreeString(bstr_tagName);

		return nn;
}


////////////////////
//	createTextNode
CXMLNode
	CXMLDocumentT<>::createTextNode
	(LPCTSTR textData)
{
		USES_CONVERSION;
		BSTR bstr_textData = T2BSTR(textData);

		IXMLDOMText* text;
		HRESULT h = doc_->createTextNode(bstr_textData, &text);
		ATLASSERT(SUCCEEDED(h));

		IXMLDOMNode* n;
		h = text->QueryInterface(__uuidof(IXMLDOMNode), reinterpret_cast<void**>(&n));
		ATLASSERT(SUCCEEDED(h));

		CXMLNode nn(n);
		n->Release();
		text->Release();

		::SysFreeString(bstr_textData);
		return nn;
}



////////////////////
//	createEntityReference
CXMLNode
	CXMLDocumentT<>::createEntityReference
	(LPCTSTR tagName)
{
		USES_CONVERSION;
		BSTR bstr_tagName = T2BSTR(tagName);

		IXMLDOMEntityReference* e;
		HRESULT h = doc_->createEntityReference(bstr_tagName, &e);
		ATLASSERT(SUCCEEDED(h));

		IXMLDOMNode* n;
		h = e->QueryInterface(__uuidof(IXMLDOMNode), reinterpret_cast<void**>(&n));
		ATLASSERT(SUCCEEDED(h));

		CXMLNode nn(n);
		n->Release();
		e->Release();

		::SysFreeString(bstr_tagName);

		return nn;
}



////////////////////
//	createDocumentFragment
CXMLNode
	CXMLDocumentT<>::createDocumentFragment()
{
		IXMLDOMDocumentFragment* f;
		HRESULT h = doc_->createDocumentFragment(&f);
		ATLASSERT(SUCCEEDED(h));

		IXMLDOMNode* n;
		h = f->QueryInterface(__uuidof(IXMLDOMNode), reinterpret_cast<void**>(&n));
		ATLASSERT(SUCCEEDED(h));

		CXMLNode nn(n);
		n->Release();
		f->Release();

		return nn;
}



////////////////////
//	createAttribute
CXMLNode
	CXMLDocumentT<>::createAttribute
	(LPCTSTR attr)
{
		USES_CONVERSION;

		BSTR bstr_attr = T2BSTR(attr);

		IXMLDOMAttribute* a;
		HRESULT h = doc_->createAttribute(bstr_attr, &a);
		ATLASSERT(SUCCEEDED(h));

		IXMLDOMNode* n;
		h = a->QueryInterface(__uuidof(IXMLDOMNode), reinterpret_cast<void**>(&n));
		ATLASSERT(SUCCEEDED(h));

		CXMLNode nn(n);
		n->Release();
		a->Release();

		::SysFreeString(bstr_attr);
		return nn;
}


////////////////////
//	getRootNode
CXMLNode
	CXMLDocumentT<>::getRootNode()
{
		IXMLDOMNode* n = 0L;
		HRESULT h = doc_.QueryInterface(&n);
		ATLASSERT(SUCCEEDED(h));

		CXMLNode nn(n);
		n->Release();
		return nn;
}


////////////////////
//	getRootNode
CXMLNode
	CXMLDocumentT<false>::getRootNode()
{
		IXMLDOMNode* n = 0L;
		HRESULT h = doc_.QueryInterface(&n);
		ATLASSERT(SUCCEEDED(h));

		CXMLNode nn(n);
		n->Release();
		return nn;
}






////////////////////
//	putref_documentElement
void
	CXMLDocumentT<>::putref_documentElement
	(CXMLNode* n)
{
		IXMLDOMElement* e = 0L;
		HRESULT h = n->n_.QueryInterface(&e);
		ATLASSERT(SUCCEEDED(h));

		h = doc_->putref_documentElement(e);
		ATLASSERT(SUCCEEDED(h));

		e->Release();
}


////////////////////
//	get_documentElement
CXMLNode
	CXMLDocumentT<>::get_documentElement()
{
		IXMLDOMElement* e;
		HRESULT h = doc_->get_documentElement(&e);
		ATLASSERT(SUCCEEDED(h));

		IXMLDOMNode* n;
		h = e->QueryInterface(__uuidof(IXMLDOMNode), reinterpret_cast<void**>(&n));
		ATLASSERT(SUCCEEDED(h));

		CXMLNode nn(n);
		n->Release();
		e->Release();
		return nn;
}


////////////////////////////////////////////////////////////////////////////////
//	CXMLIteratorNode
////////////////////////////////////////////////////////////////////////////////


////////////////////
//	CXMLIteratorNodes
CXMLIteratorNodes::CXMLIteratorNodes()
{
	n_ = NULL;
}


////////////////////
//	~CXMLIteratorNodes
CXMLIteratorNodes::~CXMLIteratorNodes()
{
	if (n_)
	{
		if (n_->IsNull() == false)
			n_->Term();

		delete n_;
	}
	if (nl_)
		nl_.Release();
}


////////////////////
//	Init
void
	CXMLIteratorNodes::Init
	(IXMLDOMNodeList* n)
{
		nl_ = n;
}


////////////////////
//	Begin
void
	CXMLIteratorNodes::Begin()
{
		if (nl_.p == 0L) return;

		if (!n_)
			n_ = new CXMLNode;

		nl_->reset();
		Next();
}


////////////////////
//	Next
void
	CXMLIteratorNodes::Next()
{
		ATLASSERT(n_);

		if (n_->IsNull() == false)
			n_->Term();

		CComPtr<IXMLDOMNode> n;
		nl_->nextNode(&n);
		n_->Init(n);
}


////////////////////
//	IsDone
bool
	CXMLIteratorNodes::IsDone()
{
		ATLASSERT(n_);

		if (nl_.p == 0L) return true;
		return n_->IsNull();
}


////////////////////
//	CurrentItem
CXMLNode
	CXMLIteratorNodes::CurrentItem()
{
		ATLASSERT(n_);

		return *n_;
}


////////////////////////////////////////////////////////////////////////////////
//	CXMLNode
////////////////////////////////////////////////////////////////////////////////

////////////////////
//	get_dataType
CString
	CXMLNode::get_dataType()
{
		VARIANT v;

		v.vt = VT_EMPTY;
		n_->get_dataType(&v);

		CString s;
		if ((v.vt == VT_EMPTY) ||
			(v.vt == VT_NULL))
		{
			s.Empty();
		}
		else
		{
			USES_CONVERSION;
			s = OLE2CT(v.bstrVal);
		}

		::SysFreeString(v.bstrVal);

		return s;
}


////////////////////
//	put_dataType
void
	CXMLNode::put_dataType
	(LPCTSTR n)
{
		ATLASSERT(n != 0L);

		USES_CONVERSION;
		BSTR v;

		v = T2BSTR(n);

		n_->put_dataType(v);

		::SysFreeString(v);		//	????????????????????????????????????????????????
		//	Mysterious..........................
}



////////////////////
//	get_nodeName
CString
	CXMLNode::get_nodeName()
{
		BSTR n;

		HRESULT h = n_->get_nodeName(&n);
		ATLASSERT(SUCCEEDED(h));

		USES_CONVERSION;
		CString s;
		s = OLE2CT(n);

		::SysFreeString(n);
		return s;
}



////////////////////
//	get_nodeType
DOMNodeType
	CXMLNode::get_nodeType()
{
		DOMNodeType t;

		HRESULT h = n_->get_nodeType(&t);
		ATLASSERT(SUCCEEDED(h));

		return t;
}



////////////////////
//	get_nodeTypedValue
CString
	CXMLNode::get_nodeTypedValue
	(Int2Type<VT_BSTR>)
{
		VARIANT v;
		HRESULT h = n_->get_nodeTypedValue(&v);
		ATLASSERT(SUCCEEDED(h));

		USES_CONVERSION;
		CString s;
		switch (v.vt)
		{
		case VT_BSTR:
			s = OLE2CT(v.bstrVal);
			::SysFreeString(v.bstrVal);
			break;
		case VT_EMPTY:
		case VT_NULL:
			s.Empty();
			break;
		default:
			ATLTRACE(_T("get_nodeTypedValue:Invalid Data Type\n"));
			ATLASSERT(FALSE);
			break;
		}

		return s;
}


////////////////////
//	get_nodeTypedValue
long
	CXMLNode::get_nodeTypedValue
	(Int2Type<VT_I4>)
{
		VARIANT v;
		HRESULT h = n_->get_nodeTypedValue(&v);
		ATLASSERT(SUCCEEDED(h));

		switch (v.vt)
		{
		case VT_I1:
		case VT_I2:
		case VT_I4:
		case VT_UI1:
		case VT_UI2:
		case VT_UI4:
			return v.lVal;
		default:
			ATLTRACE(_T("get_nodeTypedValue:Invalid Data Type\n"));
			ATLASSERT(FALSE);
			break;
		}

		ATLASSERT(FALSE);
		return -1;
}


////////////////////
//	get_nodeTypedValue
bool
	CXMLNode::get_nodeTypedValue
	(Int2Type<VT_BOOL>)
{
		VARIANT v;
		HRESULT h = n_->get_nodeTypedValue(&v);
		ATLASSERT(SUCCEEDED(h));

		switch (v.vt)
		{
		case VT_BOOL:
			return (v.boolVal == VARIANT_TRUE);

		case VT_EMPTY:
		case VT_NULL:
			return false;

		default:
			ATLTRACE(_T("get_nodeTypedValue:Invalid Data Type\n"));
			ATLASSERT(FALSE);
			break;
		}

		ATLASSERT(FALSE);
		return false;
}


////////////////////
//	get_nodeTypedValue
double
	CXMLNode::get_nodeTypedValue
	(Int2Type<VT_R8>)
{
		VARIANT v;
		HRESULT h = n_->get_nodeTypedValue(&v);
		ATLASSERT(SUCCEEDED(h));

		switch (v.vt)
		{
		case VT_R4:
		case VT_R8:
			return v.dblVal;

		case VT_EMPTY:
		case VT_NULL:
			return 0.0f;

		default:
			ATLTRACE(_T("get_nodeTypedValue:Invalid Data Type\n"));
			ATLASSERT(FALSE);
			break;
		}

		ATLASSERT(FALSE);
		return 0.0f;
}


////////////////////
//	put_nodeTypedValue	
void
	CXMLNode::put_nodeTypedValue
	(LPCTSTR value)
{
		USES_CONVERSION;
		VARIANT v;
		v.vt = VT_BSTR;
		v.bstrVal = T2BSTR(value);

		HRESULT h = n_->put_nodeTypedValue(v);
		ATLASSERT(SUCCEEDED(h));

		::SysFreeString(v.bstrVal);
}


////////////////////
//	put_nodeTypedValue	
void
	CXMLNode::put_nodeTypedValue
	(long value)
{
		USES_CONVERSION;
		VARIANT v;
		v.vt = VT_I4;
		v.lVal = value;

		HRESULT h = n_->put_nodeTypedValue(v);
		ATLASSERT(SUCCEEDED(h));
}


////////////////////
//	put_nodeTypedValue	
void
	CXMLNode::put_nodeTypedValue
	(bool value)
{
		USES_CONVERSION;
		VARIANT v;
		v.vt = VT_BOOL;
		v.boolVal = (value) ? VARIANT_TRUE : VARIANT_FALSE;

		HRESULT h = n_->put_nodeTypedValue(v);
		ATLASSERT(SUCCEEDED(h));
}


////////////////////
//	put_nodeTypedValue	
void
	CXMLNode::put_nodeTypedValue
	(double value)
{
		USES_CONVERSION;
		VARIANT v;
		v.vt = VT_R8;
		v.dblVal = value;

		HRESULT h = n_->put_nodeTypedValue(v);
		ATLASSERT(SUCCEEDED(h));
}


////////////////////
//	get_nodeTypedValue
CString
	CXMLNode::get_nodeValue()
{
		VARIANT v;
		HRESULT h = n_->get_nodeTypedValue(&v);
		ATLASSERT(SUCCEEDED(h));

		USES_CONVERSION;
		CString s;
		switch (v.vt)
		{
		case VT_BSTR:
			s = OLE2CT(v.bstrVal);
			::SysFreeString(v.bstrVal);
			break;
		case VT_EMPTY:
		case VT_NULL:
			s.Empty();
			break;
		default:
			ATLTRACE(_T("get_nodeTypedValue:Invalid Data Type\n"));
			ATLASSERT(FALSE);
			break;
		}

		return s;
}


////////////////////
//	put_nodeValue
void
	CXMLNode::put_nodeValue
	(LPCTSTR value)
{
		USES_CONVERSION;
		VARIANT v;
		v.vt = VT_BSTR;
		v.bstrVal = T2BSTR(value);

		HRESULT h = n_->put_nodeTypedValue(v);
		ATLASSERT(SUCCEEDED(h));

		::SysFreeString(v.bstrVal);
}


////////////////////
//	appendChild
bool
	CXMLNode::appendChild
	(CXMLNode* n)
{
		IXMLDOMNode* newnode = 0L;

		HRESULT h = n_->appendChild(n->n_, &newnode);
		if (FAILED(h))
		{
			IXMLError* err = 0L;
			h = n_->QueryInterface(IID_IXMLError, reinterpret_cast<void**>(&err));
			ATLASSERT(SUCCEEDED(h));

			XML_ERROR xmlerr;
			err->GetErrorInfo(&xmlerr);

			_ASSERTE(FALSE);
		}

		if (newnode)
			newnode->Release();

		return true;
}


////////////////////
//	hasChildNodes
bool
	CXMLNode::hasChildNodes()
{
		VARIANT_BOOL v;

		HRESULT h = n_->hasChildNodes(&v);
		ATLASSERT(SUCCEEDED(h));

		return (v == VARIANT_TRUE);
}


////////////////////
//	removeChild
void
	CXMLNode::removeChild
	(CXMLNode* n)
{
		IXMLDOMNode* oldnode = 0L;
		HRESULT h = n_->removeChild(n->n_, 0L);
		ATLASSERT(SUCCEEDED(h));

		if (oldnode)
			oldnode->Release();
}


////////////////////
//	replaceChild
bool
	CXMLNode::replaceChild
	(CXMLNode* newone,
	CXMLNode* oldone)
{
		IXMLDOMNode* oldnode = 0L;
		HRESULT h = n_->replaceChild(newone->n_, oldone->n_, &oldnode);
		ATLASSERT(SUCCEEDED(h));

		if (oldnode)
			oldnode->Release();

		return true;
}


////////////////////
//	selectNodes
CXMLIterator*
	CXMLNode::selectNodes
	(LPCTSTR expression)
{
		IXMLDOMNodeList* nl = 0L;
		BSTR bstr_expr;

		USES_CONVERSION;
		bstr_expr = T2BSTR(expression);

		HRESULT h = n_->selectNodes(bstr_expr, &nl);
		ATLASSERT(SUCCEEDED(h));

		it_.Init(nl);

		nl->Release();
		::SysFreeString(bstr_expr);
		return &it_;
}


////////////////////
//	selectSingleNode
CXMLNode
	CXMLNode::selectSingleNode
	(LPCTSTR expression)
{
		BSTR bstr_expr;
		USES_CONVERSION;

		bstr_expr = T2BSTR(expression);

		IXMLDOMNode* n;
		HRESULT h = n_->selectSingleNode(bstr_expr, &n);

		ATLASSERT(SUCCEEDED(h));
		::SysFreeString(bstr_expr);

		CXMLNode node(n);
		if (n)
			n->Release();

		return node;
}


////////////////////
//	getXML
void
	CXMLNode::getXML
	(CString& xml)
{
		BSTR bstrxml;
		USES_CONVERSION;

		HRESULT h = n_->get_xml(&bstrxml);
		ATLASSERT(SUCCEEDED(h));

		xml = OLE2CT(bstrxml);
		::SysFreeString(bstrxml);
}



////////////////////
//	get_attributes
CXMLNodeMap
	CXMLNode::get_attributes()
{
		IXMLDOMNamedNodeMap* m = 0L;
		HRESULT h = n_->get_attributes(&m);
		ATLASSERT(SUCCEEDED(h));

		CXMLNodeMap map;
		map.Init(m);
		if (m)
			m->Release();

		return map;
}



////////////////////////////////////////////////////////////////////////////////
//	CXMLNodeMap
////////////////////////////////////////////////////////////////////////////////


////////////////////
//	Item
CXMLNode
	CXMLNodeMap::Item
	(LPCTSTR name)
{
		ATLASSERT(m_.p != 0L);

		USES_CONVERSION;
		BSTR bstr_name = T2BSTR(name);

		IXMLDOMNode* n;
		HRESULT h = m_->getNamedItem(bstr_name, &n);
		ATLASSERT(SUCCEEDED(h));

		::SysFreeString(bstr_name);

		CXMLNode node;
		node.Init(n);
		n->Release();
		return node;
}


////////////////////
//	Item
CXMLNode
	CXMLNodeMap::Item
	(long index)
{
		ATLASSERT(m_.p != 0L);

		IXMLDOMNode* n;
		HRESULT h = m_->get_item(index, &n);
		ATLASSERT(SUCCEEDED(h));

		CXMLNode node;
		node.Init(n);

		n->Release();
		return node;
}


////////////////////
//	appendNode
bool
	CXMLNodeMap::appendNode
	(CXMLNode* newone)
{
		ATLASSERT(m_.p != 0L);

		IXMLDOMNode* appendedone = 0L;
		HRESULT h = m_->setNamedItem(newone->n_, &appendedone);
		ATLASSERT(SUCCEEDED(h));

		if (appendedone)
			appendedone->Release();

		return true;
}


////////////////////
//	removeNode
void
	CXMLNodeMap::removeNode
	(LPCTSTR name)
{
		ATLASSERT(m_.p != 0L);

		USES_CONVERSION;
		BSTR bstr_name = T2BSTR(name);

		IXMLDOMNode* oldone = 0L;
		HRESULT h = m_->removeNamedItem(bstr_name, &oldone);
		ATLASSERT(SUCCEEDED(h));

		if (oldone)
			oldone->Release();

		::SysFreeString(bstr_name);
}















