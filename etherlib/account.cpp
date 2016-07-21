/*--------------------------------------------------------------------------------
 The MIT License (MIT)

 Copyright (c) 2016 Great Hill Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 --------------------------------------------------------------------------------*/
/*
 * This file was generated with makeClass. Edit only those parts inside 
 * of 'EXISTING_CODE' tags.
 */
#include "account.h"

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CAccount, CBaseNode, NO_SCHEMA);

//---------------------------------------------------------------------------
void CAccount::Format(CExportContext& ctx, const SFString& fmtIn, void *data) const
{
	if (!isShowing())
		return;

	SFString fmt = (fmtIn.IsEmpty() ? defaultFormat() : fmtIn);
	if (handleCustomFormat(ctx, fmt, data))
		return;

	CAccountNotify dn(this);
	while (!fmt.IsEmpty())
		ctx << getNextChunk(fmt, nextAccountChunk, &dn);
}

//---------------------------------------------------------------------------
SFString nextAccountChunk(const SFString& fieldIn, SFBool& force, const void *data)
{
	CAccountNotify *ac = (CAccountNotify*)data;
	const CAccount *acc = ac->getDataPtr();

	// Now give customized code a chance to override
	SFString ret = nextAccountChunk_custom(fieldIn, force, data);
	if (!ret.IsEmpty())
		return ret;
	
	switch (tolower(fieldIn[0]))
	{
		case 'a':
			if ( fieldIn % "addr" ) return acc->addr;
			break;
		case 'h':
			if ( fieldIn % "handle" ) return asString(acc->handle);
			break;
		case 'n':
			if ( fieldIn % "name" ) return acc->name;
			if ( fieldIn % "nTransactions" ) return asString(acc->nTransactions);
			break;
		case 's':
			if ( fieldIn % "source" ) return acc->source;
			break;
		case 't':
			return EMPTY;
//			if ( fieldIn % "transactions" ) return acc->transactions;
			break;
	}
	
	// Finally, give the parent class a chance
	ret = nextBasenodeChunk(fieldIn, force, acc);
	if (!ret.IsEmpty())
		return ret;
	
	return "<span class=warning>Field not found: [{" + fieldIn + "}]</span>\n";
}

//---------------------------------------------------------------------------------------------------
SFBool CAccount::setValueByName(const SFString& fieldName, const SFString& fieldValue)
{
	// EXISTING_CODE
	// EXISTING_CODE

	switch (tolower(fieldName[0]))
	{
		case 'a':
			if ( fieldName % "addr" ) { addr = fieldValue; return TRUE; }
			break;
		case 'h':
			if ( fieldName % "handle" ) { handle = toLong(fieldValue); return TRUE; }
			break;
		case 'n':
			if ( fieldName % "name" ) { name = fieldValue; return TRUE; }
			if ( fieldName % "nTransactions" ) { nTransactions = toLong(fieldValue); return TRUE; }
			break;
		case 's':
			if ( fieldName % "source" ) { source = fieldValue; return TRUE; }
			break;
		case 't':
			return TRUE;
//			if ( fieldName % "transactions" ) { transactions = fieldValue; return TRUE; }
			break;
		default:
			break;
	}
	return FALSE;
}

//---------------------------------------------------------------------------------------------------
void CAccount::finishParse()
{
	// EXISTING_CODE
	// EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
void CAccount::Serialize(SFArchive& archive)
{
	if (!SerializeHeader(archive))
		return;

	if (archive.isReading())
	{
		archive >> handle;
		archive >> addr;
		archive >> name;
		archive >> source;
		archive >> nTransactions;
//		archive >> transactions;
		finishParse();
	} else
	{
		archive << handle;
		archive << addr;
		archive << name;
		archive << source;
		archive << nTransactions;
//		archive << transactions;

	}
}

//---------------------------------------------------------------------------
void CAccount::registerClass(void)
{
	static bool been_here=false;
	if (been_here) return;
	been_here=true;

	SFInt32 fieldNum=1000;
	ADD_FIELD(CAccount, "schema",  T_NUMBER|TS_LABEL, ++fieldNum);
	ADD_FIELD(CAccount, "deleted", T_RADIO|TS_LABEL,  ++fieldNum);
	ADD_FIELD(CAccount, "handle", T_NUMBER|TS_LABEL,  ++fieldNum);
	ADD_FIELD(CAccount, "addr", T_TEXT, ++fieldNum);
	ADD_FIELD(CAccount, "name", T_TEXT, ++fieldNum);
	ADD_FIELD(CAccount, "source", T_TEXT, ++fieldNum);
	ADD_FIELD(CAccount, "nTransactions", T_NUMBER, ++fieldNum);
	ADD_FIELD(CAccount, "transactions", T_NONE, ++fieldNum);

	// Hide our internal fields, user can turn them on if they like
	HIDE_FIELD(CAccount, "schema");
	HIDE_FIELD(CAccount, "deleted");
	HIDE_FIELD(CAccount, "handle");

	// EXISTING_CODE
	// EXISTING_CODE
}

//---------------------------------------------------------------------------
int sortAccount(const SFString& f1, const SFString& f2, const void *rr1, const void *rr2)
{
	CAccount *g1 = (CAccount*)rr1;
	CAccount *g2 = (CAccount*)rr2;

	SFString v1 = g1->getValueByName(f1);
	SFString v2 = g2->getValueByName(f1);
	SFInt32 s = v1.Compare(v2);
	if (s || f2.IsEmpty())
		return (int)s;

	v1 = g1->getValueByName(f2);
	v2 = g2->getValueByName(f2);
	return (int)v1.Compare(v2);
}
int sortAccountByName(const void *rr1, const void *rr2) { return sortAccount("ac_Name", "", rr1, rr2); }
int sortAccountByID  (const void *rr1, const void *rr2) { return sortAccount("accountID", "", rr1, rr2); }

//---------------------------------------------------------------------------
SFString nextAccountChunk_custom(const SFString& fieldIn, SFBool& force, const void *data)
{
	CAccountNotify *ac = (CAccountNotify*)data;
	const CAccount *acc = ac->getDataPtr();
	switch (tolower(fieldIn[0]))
	{
		// EXISTING_CODE
		// EXISTING_CODE
		default:
			break;
	}
	
#pragma unused(ac)
#pragma unused(acc)

	return EMPTY;
}

//---------------------------------------------------------------------------
SFBool CAccount::handleCustomFormat(CExportContext& ctx, const SFString& fmtIn, void *data) const
{
	// EXISTING_CODE
	// EXISTING_CODE
	return FALSE;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
//---------------------------------------------------------------------------
SFBool CAccount::Match(const SFString& s1, const SFString& s2, const SFString& s3, SFBool matchCase, SFBool all)
{
	SFBool m11 = ( matchCase ?   addr.Contains(s1) :   addr.ContainsI(s1) );
	SFBool m12 = ( matchCase ?   name.Contains(s1) :   name.ContainsI(s1) );
	SFBool m13 = ( matchCase ? source.Contains(s1) : source.ContainsI(s1) );
	SFBool m2  = ( matchCase ?   name.Contains(s2) :   name.ContainsI(s2) );
	SFBool m3  = ( matchCase ? source.Contains(s3) : source.ContainsI(s3) );

	if (!s1.IsEmpty() && !s2.IsEmpty() && !s3.IsEmpty())
		return m11 && m2 && m3; // all three must match
	
	if (!s1.IsEmpty() && !s2.IsEmpty())
		return m11 && m2; // addr and name must both match

	if (s1.IsEmpty())
		return FALSE; // nothing matches

	// We have only s1
	return (all ? m11 || m12 || m13 : m11 || m12);
}
// EXISTING_CODE