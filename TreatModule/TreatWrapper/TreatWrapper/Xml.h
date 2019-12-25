#ifndef	_XML_H_
#define	_XML_H_

#ifndef	__msxml2_h__
	#error	You must include msxml2.h before this file...
#endif	//	__msxml2_h__

#ifndef	__ATLMISC_H__
	#error You must include atlmisc.h before this file...
#endif	__ATLMISC_H__


using namespace ATL;

////////////////////
//	This class from Book "Modern C++ Design : Generic Programming and Design Pattern Applied"
//	Written by Andrei Alexandrescu.
template<int v>
struct Int2Type
{
	enum { value = v };
};
////////////////////////////////////////////////////////////////////////////////
//	Forward declarations
class CXMLNode;
template<bool TAuto> class CXMLDocumentT;


////////////////////////////////////////////////////////////////////////////////
//	CXMLIterator
class CXMLIterator
{
public:
	virtual ~CXMLIterator() {}
	virtual void Begin() = 0L;
	virtual void Next() = 0L;
	virtual bool IsDone() = 0L;
	virtual CXMLNode CurrentItem() = 0L;
};


////////////////////////////////////////////////////////////////////////////////
//	CXMLIteratorNodes
class CXMLIteratorNodes : public CXMLIterator
{
public:
	CXMLIteratorNodes();
	~CXMLIteratorNodes();

	void Init(IXMLDOMNodeList* n);
	virtual void Begin();
	virtual void Next();
	virtual bool IsDone();
	virtual CXMLNode CurrentItem();

private:
	CComPtr<IXMLDOMNodeList> nl_;
	CXMLNode* n_;
};



////////////////////////////////////////////////////////////////////////////////
//	CXMLNode
class CXMLNode
{
public:
	friend class CXMLNodeMap;
	friend class CXMLDocumentT<true>;
	friend class CXMLDocumentT<false>;

	CXMLNode() { n_.p = 0L; }
	CXMLNode(const CXMLNode& n) { n_ = n.n_; }
	CXMLNode(IXMLDOMNode* n) { n_ = n; }

	void operator=(const CXMLNode& n) { n_ = n.n_; }


	////////////////////
	//	Init/Term
	void Init(IXMLDOMNode* n) { n_ = n; }
	void Term() { n_.Release(); }
	bool IsNull() { return (n_.p == 0L); }


	////////////////////
	//	GetChildren
	CXMLIterator* GetChildren()
	{
		IXMLDOMNodeList* nl;

		switch (get_nodeType())
		{
		case NODE_TEXT:
			nl = 0;
			break;
		default:
		{
			HRESULT h = n_->get_childNodes(&nl);
			ATLASSERT(SUCCEEDED(h));
		}
			break;
		}

		it_.Init(nl);
		if (nl)
			nl->Release();

		return static_cast<CXMLIterator*>(&it_);
	}

	////////////////////
	//	GetChild
	CXMLNode GetChild(long index)
	{
		CXMLIterator* it = GetChildren();
		if (it == 0L) return 0L;
		for (it->Begin(); ((index > 0) && it->IsDone() == false); it->Next(), --index);
		if (it->IsDone())
			return CXMLNode();

		return it->CurrentItem();
	}


	////////////////////
	//	get_attributes
	CXMLNodeMap get_attributes();


	////////////////////
	//	get_dataType/put_dataType
	CString get_dataType();
	void put_dataType(LPCTSTR n);


	////////////////////
	//	get_nodeName
	CString get_nodeName();


	////////////////////
	//	get_nodeType
	DOMNodeType get_nodeType();


	////////////////////
	//	get_nodeTypedValue/put_nodeTypedValue
	CString get_nodeTypedValue(Int2Type<VT_BSTR>);
	long	get_nodeTypedValue(Int2Type<VT_I4>);
	bool	get_nodeTypedValue(Int2Type<VT_BOOL>);
	double	get_nodeTypedValue(Int2Type<VT_R8>);

	void put_nodeTypedValue(LPCTSTR v);
	void put_nodeTypedValue(long v);
	void put_nodeTypedValue(bool v);
	void put_nodeTypedValue(double v);


	////////////////////
	//	get_nodeValue/put_nodeValue
	CString get_nodeValue();
	void put_nodeValue(LPCTSTR v);


	////////////////////
	//	appendChild/
	//	hasChildNodes/
	//	removeChild/
	//	replaceChild/
	//	selectNodes
	bool appendChild(CXMLNode* n);
	bool hasChildNodes();
	void removeChild(CXMLNode* n);
	bool replaceChild(CXMLNode* newone, CXMLNode* oldone);
	CXMLIterator* selectNodes(LPCTSTR expression);
	CXMLNode selectSingleNode(LPCTSTR expression);

	void getXML(CString& xml);

private:
	CComPtr<IXMLDOMNode>	n_;
	CXMLIteratorNodes		it_;
};





////////////////////////////////////////////////////////////////////////////////
//	CXMLDocumentT
template<bool TAuto = true>
class CXMLDocumentT
{
	CXMLDocumentT(const CXMLDocumentT<TAuto>& t) {}
	void operator=(const CXMLDocumentT<TAuto>& t) {}

public:
	////////////////////
	//	CTOR/DTOR
	CXMLDocumentT(CComPtr<IXMLDOMDocument>& ptr)
	{
		doc_ = ptr;
		fn_[0] = _T('\0');
	}

	////////////////////
	//	CTOR/DTOR
	CXMLDocumentT() { if (TAuto) Init(); }
	~CXMLDocumentT() { if (TAuto) Term(); }


	////////////////////
	//	Init/Term
	void Init() { doc_.CoCreateInstance(CLSID_DOMDocument); }
	void Term() { doc_.Release(); }


	////////////////////
	//	Open/Close
	bool Open(LPCTSTR fn);
	bool Open(CComPtr<IStream> stm);
	bool Open(BSTR ixml);
	void Close();

	////////////////////
	//	Replace
	void Replace(CComPtr<IXMLDOMDocument>& doc) { doc_.Release(); doc_ = doc; fn_[0] = _T('\0'); }

	////////////////////
	//	Save
	bool Save(LPCTSTR fn);


	////////////////////
	//	GetChildrens
	CXMLIterator* GetChildren()
	{
		IXMLDOMNodeList*	nl;
		HRESULT h = doc_->get_childNodes(&nl);
		ATLASSERT(SUCCEEDED(h));

		it_.Init(nl);
		nl->Release();
		return &it_;
	}


	////////////////////
	//	setProperty/getProperty
	void setProperty(LPCTSTR key, LPCTSTR value);
	CString getProperty(LPCTSTR key);


	////////////////////
	//	Create XXXX
	CXMLNode createElement(LPCTSTR tagName);
	CXMLNode createTextNode(LPCTSTR textData);
	CXMLNode createAttribute(LPCTSTR name);
	CXMLNode createEntityReference(LPCTSTR name);
	CXMLNode createDocumentFragment();

	////////////////////
	//	getRootNode
	CXMLNode getRootNode();


	////////////////////
	//	putref/get_documentElement	
	void putref_documentElement(CXMLNode* n);
	CXMLNode get_documentElement();


	CComPtr<IXMLDOMDocument>	get_document() { return doc_; }

	////////////////////
	//	Internal data
private:
	enum { bufSizeFile = 1024 };
	TCHAR	fn_[bufSizeFile];				//	XML Filename.
	CComPtr<IXMLDOMDocument>	doc_;	//	XML Document.
	CXMLIteratorNodes	it_;
};

typedef CXMLDocumentT<true>	CXMLDocument;
typedef	CXMLDocumentT<false>	CXMLDocumentHandle;

////////////////////////////////////////////////////////////////////////////////
//	CXMLIteratorMaps
class CXMLIteratorMaps : public CXMLIterator
{
public:
	void Init(IXMLDOMNamedNodeMap* nm) { nm_ = nm; }
	virtual void Begin()
	{
		nm_->reset();
		HRESULT h = nm_->get_length(&length_);
		if (FAILED(h))
			length_ = 0;

		index_ = 0;
	}

	virtual void Next() { index_++; }
	virtual bool IsDone() { return (index_ >= length_); }
	virtual CXMLNode CurrentItem()
	{
		CXMLNode node;

		IXMLDOMNode* n;
		HRESULT h = nm_->get_item(index_, &n);
		ATLASSERT(SUCCEEDED(h));

		node.Init(n);
		n->Release();
		return node;
	}

private:
	CComPtr<IXMLDOMNamedNodeMap> nm_;
	long length_;
	long index_;
};


////////////////////////////////////////////////////////////////////////////////
//	CXMLNodeMap
class CXMLNodeMap
{
public:
	////////////////////
	//	Constructor
	CXMLNodeMap() {}
	CXMLNodeMap(const CXMLNodeMap& m) { (*this) = m; }
	CXMLNodeMap(IXMLDOMNamedNodeMap* m) { m_ = m; }
	void operator=(const CXMLNodeMap& m) { m_ = m.m_; }


	////////////////////
	//	Init/Term
	void Init(IXMLDOMNamedNodeMap* m) { m_ = m; }
	void Term() { m_.Release(); }


	////////////////////
	//	IsNull
	bool IsNull() { return (m_.p == 0L); }

	////////////////////
	//	length
	long length()
	{
		if (m_.p == 0L)
			return 0;

		long v;
		HRESULT h = m_->get_length(&v);
		ATLASSERT(SUCCEEDED(h));
		return v;
	}


	////////////////////
	//	Item
	CXMLNode Item(LPCTSTR name);
	CXMLNode Item(long index);


	////////////////////
	//	appendNode/removeNode
	bool appendNode(CXMLNode* newone);
	void removeNode(LPCTSTR name);


	////////////////////
	//	GetIterator
	CXMLIterator* GetIterator()
	{
		it_.Init(m_);
		return &it_;
	}

	////////////////////
	//	Internal Datas
private:
	CComPtr<IXMLDOMNamedNodeMap>	m_;
	CXMLIteratorMaps	it_;
};

#endif // _XML_H_