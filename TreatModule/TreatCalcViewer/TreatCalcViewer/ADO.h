// ADO.h: interface for the CADO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADO_H__6E5F784C_B3FB_42B5_9D3C_03B4E433F551__INCLUDED_)
#define AFX_ADO_H__6E5F784C_B3FB_42B5_9D3C_03B4E433F551__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <map>
#include <atlcom.h>
#include <atlapp.h>
#include <atlmisc.h>

#pragma warning (disable:4146)

// import ADO library
#import	"C:\Program Files (x86)\Common Files\System\ado\msado60.tlb"		raw_interfaces_only, rename_namespace("ADO")


// ADO 컴포넌트가 시스템에 설치되지 않았을 경우 발생하는 메시지 박스
#define		SHOW_ADO_INSTALLATION_ERROR_MESSAGE					::MessageBox(NULL,																					\
																 _T("시스템에 ADO 컴포넌트가 설치되어있지 않습니다.\n데이터베이스 작업을 진행할 수 없습니다."),		\
																 _T("ADO 설치 오류"),																				\
																 MB_ICONSTOP)


using namespace ADO;

//////////////////////////////////////////////////////////////////////
// Class forwarding
class CADOConnection;
class CADOConnectionEventsHandler;
class CADOParameter;
class CADORecordset;


//////////////////////////////////////////////////////////////////////
// CADOUtil class
class CADOUtill
{
public:
	static BOOL GetVariantValue(VARIANT varValue, BSTR* pbstrValue);
	static BOOL GetVariantValue(VARIANT varValue, long* plValue);
	static BOOL GetVariantValue(VARIANT varValue, short* pnValue);
	static BOOL GetVariantValue(VARIANT varValue, float* pfValue);
	static BOOL GetVariantValue(VARIANT varValue, double* pdblValue);
	static BOOL GetVariantValue(VARIANT varValue, CString* pstrValue);
	static BOOL GetVariantValue(VARIANT varValue, BOOL* pbValue);
	static BOOL GetVariantValue(VARIANT varValue, SYSTEMTIME* pstValue);
	static BOOL GetVariantValue(VARIANT varValue, CHAR* pcValue);
	static BOOL GetVariantValue(VARIANT varValue, CY* pcyValue);
	static BOOL GetVariantValue(VARIANT varValue, DECIMAL* pdecValue);
};



//////////////////////////////////////////////////////////////////////
// CADOError class
class CADOError
{
// Constructor
public:
	CADOError();
	CADOError(Error* pError);
	virtual ~CADOError();


// Attributes
public:
	CComPtr<Error>		m_pobError;


// Operations
public:
	BOOL GetDescription(CString* pstrDescription);
	BOOL GetHelpContext(long* plHelpContextID);
	BOOL GetHelpFile(CString* pstrHelpFile);
	BOOL GetNativeError(long* plNativeError);
	BOOL GetNumber(ErrorValueEnum *penErrorValue);
	BOOL GetSource(CString* pstrSource);
	BOOL GetSQLState(CString* pstrSQLState);
};



//////////////////////////////////////////////////////////////////////
// CADOProperty class
class CADOProperty
{
// Constructor
public:
	CADOProperty();
	virtual ~CADOProperty();


// Attributes
public:
	CComPtr<Property>	m_pobProperty;


// Operations
public:
	BOOL GetAttributes(PropertyAttributesEnum* penPropertyAttributes);
	BOOL SetAttributes(long lAttributes);
	BOOL GetName(CString* pstrName);
	BOOL GetType(DataTypeEnum* penType);
	BOOL GetValue(VARIANT* pvarValue);
	BOOL GetValue(long* plValue);
	BOOL GetValue(short* pnValue);
	BOOL GetValue(float* pfValue);
	BOOL GetValue(double* pdblValue);
	BOOL GetValue(CString* pstrValue);
	BOOL GetValue(BOOL* pbValue);
	BOOL GetValue(SYSTEMTIME* pstValue);
	BOOL GetValue(CHAR* pcValue);
	BOOL GetValue(CY* pcyValue);
	BOOL GetValue(DECIMAL* pdecValue);
	BOOL SetValue(VARIANT varValue);
	BOOL SetValue(long lValue);
	BOOL SetValue(short nValue);
	BOOL SetValue(float fValue);
	BOOL SetValue(double dblValue);
	BOOL SetValue(LPCTSTR lpszValue);
	BOOL SetValue(BOOL bValue);
	BOOL SetValue(SYSTEMTIME stValue);
	BOOL SetValue(CHAR cValue);
	BOOL SetValue(CY cyValue);
	BOOL SetValue(DECIMAL decValue);
};



//////////////////////////////////////////////////////////////////////
// CADOField class
class CADOField
{
// Constructor
public:
	CADOField();
	virtual ~CADOField();


// Attributes
public:
	CComPtr<Field>	m_pobField;


// Operations
public:
	BOOL GetActualSize(long* plSize);
	BOOL GetAttributes(FieldAttributeEnum* penFieldAttribute);
	BOOL GetDefinedSize(long* plSize);
	BOOL GetName(CString* pstrName);
	BOOL GetNumericScale(BYTE* pbtNumericScale);
	BOOL SetNumericScale(BYTE btNumericScale);
	BOOL GetOriginalValue(VARIANT* pvtOriginalValue);
	BOOL GetPrecision(BYTE* pbtPrecision);
	BOOL SetPrecision(BYTE btPrecision);
	BOOL GetPropertyCount(long* plPropertyCount);
	BOOL GetProperty(long lIndex, CADOProperty* pobProperty);
	BOOL GetStatus(FieldStatusEnum* penFieldStatus);
	BOOL GetType(DataTypeEnum* penDataType);
	BOOL SetType(DataTypeEnum enDataType);
	BOOL GetUnderlyingValue(VARIANT* pvtUnderlyingValue);
	BOOL IsNull();
	BOOL GetValue(VARIANT* pvarValue);
	BOOL GetValue(long* plValue);
	BOOL GetValue(short* pnValue);
	BOOL GetValue(float* pfValue);
	BOOL GetValue(double* pdblValue);
	BOOL GetValue(CString* pstrValue);
	BOOL GetValue(BOOL* pbValue);
	BOOL GetValue(SYSTEMTIME* pstValue);
	BOOL GetValue(CHAR* pcValue);
	BOOL GetValue(CY* pcyValue);
	BOOL GetValue(DECIMAL* pdecValue);
	BOOL GetValue(BSTR* pbstrValue);
	BOOL SetValue(VARIANT varValue);
	BOOL SetValue(long lValue);
	BOOL SetValue(short nValue);
	BOOL SetValue(float fValue);
	BOOL SetValue(double dblValue);
	BOOL SetValue(LPCTSTR lpszValue);
	BOOL SetValue(BOOL bValue);
	BOOL SetValue(SYSTEMTIME stValue);
	BOOL SetValue(CHAR cValue);
	BOOL SetValue(CY cyValue);
	BOOL SetValue(DECIMAL decValue);
	BOOL AppendChunk(VARIANT varData);
	BOOL GetChunk(long lLength, VARIANT* pvarData);
};



//////////////////////////////////////////////////////////////////////
// CADOCommand class
class CADOCommand
{
// Constructor
public:
	CADOCommand();
	CADOCommand(_Command* pCommand);
	virtual ~CADOCommand();


// Attributes
public:
	CComPtr<_Command>				m_pobCommand;


// Operations
public:
	BOOL GetActiveConnection(CADOConnection *pobConnection);
	BOOL SetActiveConnection(LPCTSTR lpszConnStr);
	BOOL SetActiveConnection(CADOConnection *pobConnection);
	BOOL GetCommandStream(IStream* pStream);
	BOOL GetCommandText(CString* pstrCommand);
	BOOL SetCommandText(LPCTSTR lpszCommand);
	BOOL GetCommandTimeout(long* plSeconds);
	BOOL SetCommandTimeout(long lSeconds);
	BOOL GetCommandTypeEnum(CommandTypeEnum* penType);
	BOOL SetCommandTypeEnum(CommandTypeEnum enType);
	BOOL GetDialect(CString* pstrDialect);
	BOOL SetDialect(LPCTSTR lpszDialect);
	BOOL GetName(CString* pstrName);
	BOOL SetName(LPCTSTR lpszName);
	BOOL GetNamedParameters(BOOL* pbNamed);
	BOOL SetNamedParameters(BOOL bNamed);
	BOOL GetParameterCount(long *plCount);
	BOOL GetParameter(long lIndex, CADOParameter* pobParameter);
	BOOL GetPrepared(BOOL* pbPrepared);
	BOOL SetPrepared(BOOL bPrepared);
	BOOL GetPropertiesCount(long *plCount);
	BOOL GetProperty(long lIndex, CADOProperty* pobProperty);
	BOOL GetState(ObjectStateEnum* penState);
	BOOL Cancel();
	BOOL CreateParameter(LPCTSTR lpszName, DataTypeEnum enType, ParameterDirectionEnum enDirection, long lSize, VARIANT varValue, CADOParameter* pParameter);
	BOOL Execute(long* plRecordsAffected, VARIANT* pvarParameters, long lOptions, CADORecordset* pRecordset);
};



//////////////////////////////////////////////////////////////////////
// CADORecord class
class CADORecord
{
// Constructor
public:
	CADORecord();
	CADORecord(_Record* pRecord);
	virtual ~CADORecord();


// Attributes
public:
	CComPtr<_Record>	m_pobRecord;


// Operations
public:
	BOOL GetActiveConnection(CADOConnection* pobDbConn);
	BOOL SetActiveConnection(LPCTSTR lpszConnectionStr);
	BOOL GetFieldCount(long *plCount);
	BOOL GetField(long lIndex, CADOField* pobField);
	BOOL GetMode(ConnectModeEnum* penMode);
	BOOL SetMode(ConnectModeEnum enMode);
	BOOL GetParentURL(CString* pstrParentURL);
	BOOL GetPropertyCount(long *plCount);
	BOOL GetProperty(long lIndex, CADOProperty* pobProperty);
	BOOL GetRecordType(RecordTypeEnum* penRecordType);
	BOOL GetSource(VARIANT* pvarSource);
	BOOL SetSource(LPCTSTR lpszSource);
	BOOL GetState(ObjectStateEnum* penState);
	BOOL Cancel();
	BOOL Close();
	BOOL CopyRecord(CString strSource, CString strDestination, CString strUserName, CString strPassword, CopyRecordOptionsEnum enOptions, BOOL bAsync, CString* pstrNewURL);
	BOOL DeleteRecord(CString strSource, BOOL bAsync);
	BOOL GetChildren(CADORecordset* pobRecordset);
	BOOL MoveRecord(CString strSource, CString strDestination, CString strUserName, CString strPassword, MoveRecordOptionsEnum enRecordOptions, BOOL bAsync, CString* pstrNewURL);
	BOOL Open(VARIANT varSource, VARIANT varActiveConnection, ConnectModeEnum enMode, RecordCreateOptionsEnum enCreateOptions, RecordOpenOptionsEnum enOpenOptions, CString strUserName, CString strPassword);
	BOOL Open(CString strSource, CString strConnectionStr, ConnectModeEnum enMode, RecordCreateOptionsEnum enCreateOptions, RecordOpenOptionsEnum enOpenOptions, CString strUserName, CString strPassword);
	BOOL Open(CString strSource, CADOConnection* pobDbConn, ConnectModeEnum enMode, RecordCreateOptionsEnum enCreateOptions, RecordOpenOptionsEnum enOpenOptions, CString strUserName, CString strPassword);
	BOOL Open(CADOCommand* pobCommand, CString strConnectionStr, ConnectModeEnum enMode, RecordCreateOptionsEnum enCreateOptions, RecordOpenOptionsEnum enOpenOptions, CString strUserName, CString strPassword);
	BOOL Open(CADOCommand* pobCommand, CADOConnection* pobDbConn, ConnectModeEnum enMode, RecordCreateOptionsEnum enCreateOptions, RecordOpenOptionsEnum enOpenOptions, CString strUserName, CString strPassword);
};


//////////////////////////////////////////////////////////////////////
// CADORecordset class
class CADORecordset
{
// Constructor
public:
	CADORecordset();
	CADORecordset(_Recordset *pRecordset);
	virtual ~CADORecordset();


// Attributes
public:
	CComPtr<_Recordset>	m_pobRecordset;


// Operations
public:
	BOOL Reconnect();
	void operator=(CADORecordset& obRecordset);
	BOOL GetAbsolutePage(PositionEnum* penPos);
	BOOL SetAbsolutePage(PositionEnum enPos);
	BOOL GetAbsolutePosition(PositionEnum* penPos);
	BOOL SetAbsolutePosition(PositionEnum enPos);
	BOOL GetActiveCommand(CADOCommand *pobCommand);
	BOOL GetActiveConnection(VARIANT* pvarConnection);
	BOOL GetActiveConnection(CString* pstrConnection);
	BOOL GetActiveConnection(CADOConnection* pDbConn);
	BOOL SetActiveConnection(VARIANT varConnection);
	BOOL SetActiveConnection(CString strConnection);
	BOOL SetActiveConnection(CADOConnection *pDbConn);
	BOOL IsEOF();
	BOOL IsBOF();
	BOOL GetBookmark(VARIANT* pvarBookmark);
	BOOL SetBookmark(VARIANT varBookmark);
	BOOL GetCacheSize(long* plSize);
	BOOL SetCacheSize(long lSize);
	BOOL GetCursorLocation(CursorLocationEnum* penLoc);
	BOOL SetCursorLocation(CursorLocationEnum enLoc);
	BOOL GetCursorType(CursorTypeEnum* penType);
	BOOL SetCursorType(CursorTypeEnum enType);
	BOOL GetDataMember(CString* pstrDataMember);
	BOOL SetDataMember(CString strDataMember);
	BOOL GetDataSource(IUnknown **ppUnkn);
	BOOL GetEditMode(EditModeEnum* penMode);
	BOOL IsEditInProgress(BOOL* pbResult);
	BOOL IsEditAdd(BOOL* pbResult);
	BOOL IsEditDelete(BOOL* pbResult);
	BOOL IsEditNone(BOOL* pbResult);
	BOOL IsFieldExist(long lIndex);
	BOOL IsFieldNULL(long lIndex);
	BOOL IsFieldExist(LPCTSTR lpszFieldName);
	BOOL IsFieldNULL(LPCTSTR lpszFieldName);
	BOOL GetFieldCount(long *plCount);
	BOOL GetField(long lIndex, CADOField* pobField);
	BOOL GetField(LPCTSTR lpszFieldName, CADOField* pobField);
	BOOL GetFieldValue(long lIndex, VARIANT* pvarValue);
	BOOL GetFieldValue(long lIndex, long* plValue);
	BOOL GetFieldValue(long lIndex, short* pnValue);
	BOOL GetFieldValue(long lIndex, float* pfValue);
	BOOL GetFieldValue(long lIndex, double* pdblValue);
	BOOL GetFieldValue(long lIndex, CString* pstrValue);
	BOOL GetFieldValue(long lIndex, BOOL* pbValue);
	BOOL GetFieldValue(long lIndex, SYSTEMTIME* pstValue);
	BOOL GetFieldValue(long lIndex, CHAR* pcValue);
	BOOL GetFieldValue(long lIndex, CY* pcyValue);
	BOOL GetFieldValue(long lIndex, DECIMAL* pdecValue);
	BOOL GetFieldValue(long lIndex, __int64* pwnValue);
	BOOL GetFieldValue(long lIndex, BSTR* pbstrValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, VARIANT* pvarValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, long* plValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, short* pnValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, float* pfValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, double* pdblValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, CString* pstrValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, BOOL* pbValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, SYSTEMTIME* pstValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, CHAR* pcValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, CY* pcyValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, DECIMAL* pdecValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, __int64* pwnValue);
	BOOL GetFieldValue(LPCTSTR lpszFieldName, BSTR* pbstrValue);
	BOOL SetFieldValue(long lIndex, VARIANT varValue);
	BOOL SetFieldValue(long lIndex, long lValue);
	BOOL SetFieldValue(long lIndex, short nValue);
	BOOL SetFieldValue(long lIndex, float fValue);
	BOOL SetFieldValue(long lIndex, double dblValue);
	BOOL SetFieldValue(long lIndex, CString strValue);
	BOOL SetFieldValue(long lIndex, BOOL bValue);
	BOOL SetFieldValue(long lIndex, SYSTEMTIME stValue);
	BOOL SetFieldValue(long lIndex, CHAR cValue);
	BOOL SetFieldValue(long lIndex, CY cyValue);
	BOOL SetFieldValue(long lIndex, DECIMAL decValue);
	BOOL SetFieldValue(long lIndex, __int64 wnValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, VARIANT varValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, long lValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, short nValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, float fValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, double dblValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, CString strValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, BOOL bValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, SYSTEMTIME stValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, CHAR cValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, CY cyValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, DECIMAL decValue);
	BOOL SetFieldValue(LPCTSTR lpszFieldName, __int64 wnValue);
	BOOL SetFieldValueNull(long lIndex);
	BOOL SetFieldValueNull(LPCTSTR lpszFieldName);
	CString GetFieldValueStr(LPCTSTR lpszFieldName);
	CString GetFieldValueStr(long lIndex);
	BOOL GetBinaryFieldSize(long lIndex, long* plSize);
	BOOL GetBinaryFieldSize(LPCTSTR lpszFieldName, long* plSize);
	BOOL GetBinaryFieldValue(long lIndex, BYTE* pbtValue, long lDataSize);
	BOOL SetBinaryFieldValue(long lIndex, BYTE* pbtValue, long lSize);
	BOOL GetBinaryFieldValue(LPCTSTR lpszFieldName, BYTE* pbtValue, long lDataSize);
	BOOL SetBinaryFieldValue(LPCTSTR lpszFieldName, BYTE* pbtValue, long lSize);
	BOOL GetBinaryFieldToFile(long lIndex, LPCTSTR lpszFileName);
	BOOL SetBinaryFieldFromFile(long lIndex, LPCTSTR lpszFileName);
	BOOL GetBinaryFieldToFile(LPCTSTR lpszFieldName, LPCTSTR lpszFileName);
	BOOL SetBinaryFieldFromFile(LPCTSTR lpszFieldName, LPCTSTR lpszFileName);
	BOOL GetFilter(VARIANT* pvarFilter);
	BOOL SetFilter(VARIANT varFilter);
	BOOL GetIndex(CString* pstrIndex);
	BOOL SetIndex(CString strIndex);
	BOOL GetLockType(LockTypeEnum *penLockType);
	BOOL SetLockType(LockTypeEnum enLockType);
	BOOL GetMarshalOptions(MarshalOptionsEnum* penMarshalOptions);
	BOOL SetMarshalOptions(MarshalOptionsEnum enMarshalOptions);
	BOOL GetMaxRecords(long *plCount);
	BOOL SetMaxRecords(long lCount);
	BOOL GetPageCount(long *plCount);
	BOOL GetPageSize(long *plSize);
	BOOL SetPageSize(long lSize);
	BOOL GetPropertyCount(long* plCount);
	BOOL GetProperty(long lIndex, CADOProperty* pobProperty);
	BOOL GetRecordCount(long *plCount);
	BOOL GetSort(CString* pstrCriteria);
	BOOL SetSort(CString strCriteria);
	BOOL GetSource(CString *pstrSource);
	BOOL SetSource(CString strSource);
	BOOL GetState(ObjectStateEnum *penState);
	BOOL IsOpen(BOOL* pbOpen);
	BOOL IsOpen();
	BOOL GetStatus(long *plStatus);
	BOOL GetStayInSync(BOOL *pbStay);
	BOOL SetStayInSync(BOOL bStay);
	BOOL AddNew(VARIANT FieldList = vtMissing, VARIANT Values = vtMissing);
	BOOL Cancel();
	BOOL CancelBatch(AffectEnum enAffectRecords);
	BOOL CancelUpdate();
	BOOL Clone(LockTypeEnum enLockType, CADORecordset *pobRecordset);
	BOOL Close();
	BOOL CompareBookmarks(VARIANT varBookmark1, VARIANT varBookmark2, CompareEnum* penCompare);
	BOOL Delete(AffectEnum enAffectRecords);
	BOOL Find(CString strCriteria, long lSkipRecords=0, SearchDirectionEnum enSearchDirection=adSearchForward, VARIANT varStart = vtMissing);
	BOOL GetRows(long lRows, VARIANT varStart, VARIANT varFields, VARIANT *pvarArray);
	BOOL GetString(StringFormatEnum enStringFormat, long lNumRows, CString strColumnDelimeter, CString strRowDelimeter, CString strNullExpr, CString* pstrRetString);
	BOOL Move(long lNumRecords, VARIANT varStart = vtMissing);
	BOOL MoveFirst();
	BOOL MoveLast();
	BOOL MoveNext();
	BOOL MovePrevious();
	BOOL NextRecordset(long *plRecordsAffected, CADORecordset* pobRecordset);
	BOOL Open(VARIANT varSource, VARIANT varActiveConnection, CursorTypeEnum enCursorType=adOpenKeyset, LockTypeEnum enLockType=adLockOptimistic, long lOptions=adCmdUnspecified|adOptionUnspecified);
	BOOL Open(CString strSource, CADOConnection* pobConnection, CursorTypeEnum enCursorType=adOpenKeyset, LockTypeEnum enLockType=adLockOptimistic, long lOptions=adCmdUnspecified|adOptionUnspecified);
	BOOL Open(CString strSource, CString strConnectionStr, CursorTypeEnum enCursorType=adOpenKeyset, LockTypeEnum enLockType=adLockOptimistic, long lOptions=adCmdUnspecified|adOptionUnspecified);
	BOOL Open(CADOCommand *pobCommand, CADOConnection *pobConnection, CursorTypeEnum enCursorType=adOpenKeyset, LockTypeEnum enLockType=adLockOptimistic, long lOptions=adCmdUnspecified|adOptionUnspecified);
	BOOL Open(CADOCommand *pobCommand, CString strConnectionStr, CursorTypeEnum enCursorType=adOpenKeyset, LockTypeEnum enLockType=adLockOptimistic, long lOptions=adCmdUnspecified|adOptionUnspecified);
	BOOL Requery(long lOptions);
	BOOL Resync(AffectEnum enAffectRecords, ResyncEnum enResyncValues);	
	BOOL Save(VARIANT varDestination, PersistFormatEnum enPersistFormat);
	BOOL Save(CString strDestination, PersistFormatEnum enPersistFormat);
	BOOL Save(IUnknown* pUnkn, PersistFormatEnum enPersistFormat);
	BOOL Seek(VARIANT varKeyValues, SeekEnum enSeekOption);
	BOOL Supports(CursorOptionEnum enCursorOptions, BOOL* pbSupport);
	BOOL Update(VARIANT varFields = vtMissing, VARIANT varValues = vtMissing);
	BOOL UpdateBatch(AffectEnum enAffectRecords);
};


//////////////////////////////////////////////////////////////////////
// CADOParameter class
class CADOParameter
{
// Constructor
public:
	CADOParameter();
	CADOParameter(_Parameter* pParam);
	virtual ~CADOParameter();


// Attributes
public:
	CComPtr<_Parameter>			m_pobParameter;


// Operations
public:
	BOOL GetAttributes(ParameterAttributesEnum* penAttributes);
	BOOL SetAttributes(ParameterAttributesEnum enAttributes);
	BOOL GetDirection(ParameterDirectionEnum* penDirection);
	BOOL SetDirection(ParameterDirectionEnum enDirection);
	BOOL GetName(CString* pstrName);
	BOOL SetName(CString strName);
	BOOL GetNumericScale(BYTE* pbtNumericScale);
	BOOL SetNumericScale(BYTE btNumericScale);
};


//////////////////////////////////////////////////////////////////////
// CADOConnection class
class CADOConnection
{
// Constructor
public:
	CADOConnection();
	CADOConnection(IUnknown* pUnkn);
	CADOConnection(_Connection* pConn);
	virtual ~CADOConnection();


// Attributes
public:
	CComPtr<_Connection>				m_pobConnection;


protected:
	std::map<ConnectionEventsVt*, DWORD>		m_obConnectionPointMap;


// Operations
public:
	IUnknown*	GetUnknown();
	BOOL Attach(_Connection* pConn);
	BOOL Attach(IUnknown* pUnkn);
	BOOL Detach();
	void operator=(CADOConnection& obDbConn);
	void ShowErrorMessage(HWND hWndParent=::GetActiveWindow());
	CString GetErrorMessage();
	BOOL Open(LPCTSTR lpszConnectionStr, LPCTSTR lpszUserID=NULL, LPCTSTR lpszPassword=NULL, ConnectOptionEnum enOption=adConnectUnspecified);
	BOOL Close();
	BOOL GetAttributes(long* plAttributes);
	BOOL SetAttributes(long lAttributes);
	BOOL GetCommandTimeout(long* plSeconds);
	BOOL SetCommandTimeout(long lSeconds);
	BOOL GetConnectionString(CString* pstrConnectionStr);
	BOOL SetConnectionString(CString strConnectionStr);
	BOOL GetConnectionTimeout(long* plSeconds);
	BOOL SetConnectionTimeout(long lSeconds);
	BOOL GetCursorLocation(CursorLocationEnum* penCurLoc);
	BOOL SetCursorLocation(CursorLocationEnum enCurLoc);
	BOOL GetDefaultDatabase(CString* pstrDatabase);
	BOOL SetDefaultDatabase(CString strDatabase);
	BOOL GetIsolationLevel(IsolationLevelEnum* penLevel);
	BOOL SetIsolationLevel(IsolationLevelEnum enLevel);
	BOOL GetMode(ConnectModeEnum* penConnectMode);
	BOOL SetMode(ConnectModeEnum enConnectMode);
	BOOL GetProvider(CString* pstrProvider);
	BOOL SetProvider(CString strProvider);
	BOOL GetState(ObjectStateEnum *penState);
	BOOL GetErrorCount(long *plCount);
	BOOL GetError(long lIndex, CADOError *pobError);
	BOOL GetPropertyCount(long* plCount);
	BOOL GetProperty(long lIndex, CADOProperty *pobProperty);
	BOOL BeginTrans(long* plTransactionLevel);
	BOOL RollbackTrans();
	BOOL CommitTrans();
	BOOL Cancel();
	BOOL Execute(CString strCommandText, CADORecordset *pRs=NULL, long* plRecordsAffected=NULL, long lOptions=adOptionUnspecified|adCmdUnspecified);
	BOOL OpenSchema(SchemaEnum enSchema, VARIANT varRestrictions, VARIANT varSchemaID, CADORecordset *pRs);
	BOOL Advise(ConnectionEventsVt *pobConnectionEventsVt);
	BOOL Unadvise(ConnectionEventsVt *pobConnectionEventsVt);
	BOOL IsOpen(BOOL* pbOpen);
	BOOL IsOpen();
	BOOL IsClosed();
	BOOL IsConnecting();
	BOOL IsExecuting();
	BOOL IsFetching();
	BOOL ExecuteFile(LPCTSTR lpszFileName, BOOL bShowError=FALSE);
	BOOL Reconnect();
};



//////////////////////////////////////////////////////////////////////
// CADORecordsetEventsVt class
class CADORecordsetEventsHandler : public RecordsetEventsVt
{
// Constructor
public:
	CADORecordsetEventsHandler();
	virtual ~CADORecordsetEventsHandler();

protected:
	ULONG	m_cRef;

// Overridable handler
protected:
	virtual STDMETHODIMP WillChangeField(LONG cFields, VARIANT Fields, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual STDMETHODIMP FieldChangeComplete(LONG cFields, VARIANT Fields, Error *pError, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual STDMETHODIMP WillChangeRecord(EventReasonEnum adReason, LONG cRecords, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual STDMETHODIMP RecordChangeComplete(EventReasonEnum adReason, LONG cRecords, Error *pError, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual STDMETHODIMP WillChangeRecordset(EventReasonEnum adReason, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual STDMETHODIMP RecordsetChangeComplete(EventReasonEnum adReason, Error *pError, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual STDMETHODIMP WillMove(EventReasonEnum adReason, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual STDMETHODIMP MoveComplete(EventReasonEnum adReason, Error *pError, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual STDMETHODIMP EndOfRecordset(VARIANT_BOOL *fMoreData, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual STDMETHODIMP FetchProgress(long Progress, long MaxProgress, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual STDMETHODIMP FetchComplete(Error *pError, EventStatusEnum *padStatus, _Recordset *pRecordset);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	virtual STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);
};



//////////////////////////////////////////////////////////////////////
// CADOConnectionEventsVt class
class CADOConnectionEventsHandler : public ConnectionEventsVt
{
// Constructor
public:
	CADOConnectionEventsHandler();
	virtual ~CADOConnectionEventsHandler();

protected:
	ULONG	m_cRef;

// ADOConnection event handler
private:
    virtual STDMETHODIMP BeginTransComplete(LONG lTransactionLevel, Error *pError, EventStatusEnum *padStatus, _Connection *pConnection);
    virtual STDMETHODIMP CommitTransComplete(Error *pError, EventStatusEnum *padStatus, _Connection *pConnection);
	virtual STDMETHODIMP RollbackTransComplete(Error *pError, EventStatusEnum *padStatus, _Connection *pConnection);
    virtual STDMETHODIMP ConnectComplete(Error *pError, EventStatusEnum *padStatus, _Connection *pConnection);
    virtual STDMETHODIMP Disconnect(EventStatusEnum *padStatus, _Connection *pConnection);
	virtual STDMETHODIMP ExecuteComplete(LONG lRecordsAffected, Error *pError, EventStatusEnum *padStatus, _Command *pCommand, _Recordset *pRecordset, _Connection *pConnection);
	virtual STDMETHODIMP InfoMessage(Error *pError, EventStatusEnum *padStatus, _Connection *pConnection);
	virtual STDMETHODIMP WillConnect(BSTR *ConnectionString, BSTR *UserID, BSTR *Password, LONG *plOptions, EventStatusEnum *padStatus, _Connection *pConnection);
	virtual STDMETHODIMP WillExecute(BSTR *Source, CursorTypeEnum *CursorType, LockTypeEnum *LockType, LONG *plOptions, EventStatusEnum *padStatus, _Command *pCommand, _Recordset *pRecordset, _Connection *pConnection);

protected:
    virtual STDMETHODIMP OnBeginTransComplete(LONG lTransactionLevel, CADOError *pError, EventStatusEnum *padStatus, CADOConnection *pConnection);
    virtual STDMETHODIMP OnCommitTransComplete(CADOError *pError, EventStatusEnum *padStatus, CADOConnection *pConnection);
	virtual STDMETHODIMP OnRollbackTransComplete(CADOError *pError, EventStatusEnum *padStatus, CADOConnection *pConnection);
    virtual STDMETHODIMP OnConnectComplete(CADOError *pError, EventStatusEnum *padStatus, CADOConnection *pConnection);
    virtual STDMETHODIMP OnDisconnect(EventStatusEnum *padStatus, CADOConnection *pConnection);
	virtual STDMETHODIMP OnExecuteComplete(LONG lRecordsAffected, CADOError *pError, EventStatusEnum *padStatus, CADOCommand *pCommand, CADORecordset *pRecordset, CADOConnection *pConnection);
	virtual STDMETHODIMP OnInfoMessage(CADOError *pError, EventStatusEnum *padStatus, CADOConnection *pConnection);
	virtual STDMETHODIMP OnWillConnect(CString* pstrConnectionString, CString* pstrUserID, CString* pstrPassword, LONG *plOptions, EventStatusEnum *padStatus, CADOConnection *pConnection);
	virtual STDMETHODIMP OnWillExecute(CString* pstrSource, CursorTypeEnum *CursorType, LockTypeEnum *LockType, LONG *plOptions, EventStatusEnum *padStatus, CADOCommand *pCommand, CADORecordset *pRecordset, CADOConnection *pConnection);

	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	virtual STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);
};


#endif // !defined(AFX_ADO_H__6E5F784C_B3FB_42B5_9D3C_03B4E433F551__INCLUDED_)
