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
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include "function.h"

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CFunction, CBaseNode, curVersion);

//---------------------------------------------------------------------------
void CFunction::Format(CExportContext& ctx, const SFString& fmtIn, void *data) const
{
	if (!isShowing())
		return;

	if (fmtIn.IsEmpty())
	{
		ctx << toJson();
		return;
	}

	SFString fmt = fmtIn;
	if (handleCustomFormat(ctx, fmt, data))
		return;

	CFunctionNotify dn(this);
	while (!fmt.IsEmpty())
		ctx << getNextChunk(fmt, nextFunctionChunk, &dn);
}

//---------------------------------------------------------------------------
SFString nextFunctionChunk(const SFString& fieldIn, SFBool& force, const void *data)
{
	CFunctionNotify *fu = (CFunctionNotify*)data;
	const CFunction *fun = fu->getDataPtr();

	// Now give customized code a chance to override
	SFString ret = nextFunctionChunk_custom(fieldIn, force, data);
	if (!ret.IsEmpty())
		return ret;

	switch (tolower(fieldIn[0]))
	{
		case 'a':
			if ( fieldIn % "anonymous" ) return asString(fun->anonymous);
			break;
		case 'c':
			if ( fieldIn % "constant" ) return asString(fun->constant);
			break;
		case 'e':
			if ( fieldIn % "encoding" ) return fun->encoding;
			break;
		case 'i':
			if ( fieldIn % "indexed" ) return asString(fun->indexed);
			if ( fieldIn % "inputs" )
			{
				SFInt32 cnt = fun->inputs.getCount();
				SFString ret = "[\n";
				for (int i=0;i<cnt;i++)
				{
					ret += fun->inputs[i].Format();
					ret += ((i<cnt-1) ? ",\n" : "\n");
				}
				return ret+"    ]";
			}
			break;
		case 'n':
			if ( fieldIn % "name" ) return fun->name;
			break;
		case 'o':
			if ( fieldIn % "outputs" )
			{
				SFInt32 cnt = fun->outputs.getCount();
				SFString ret = "[\n";
				for (int i=0;i<cnt;i++)
				{
					ret += fun->outputs[i].Format();
					ret += ((i<cnt-1) ? ",\n" : "\n");
				}
				return ret+"    ]";
			}
			break;
		case 't':
			if ( fieldIn % "type" ) return fun->type;
			break;
	}

	// Finally, give the parent class a chance
	ret = nextBasenodeChunk(fieldIn, force, fun);
	if (!ret.IsEmpty())
		return ret;

	return "<span class=warning>Field not found: [{" + fieldIn + "}]</span>\n";
}

//---------------------------------------------------------------------------------------------------
SFBool CFunction::setValueByName(const SFString& fieldName, const SFString& fieldValue)
{
	// EXISTING_CODE
	if ( fieldName % "inputs" )
	{
		parseParams(TRUE, fieldValue);
		return TRUE;
	}
	if ( fieldName % "outputs" )
	{
		parseParams(FALSE, fieldValue);
		return TRUE;
	}
	// EXISTING_CODE

	switch (tolower(fieldName[0]))
	{
		case 'a':
			if ( fieldName % "anonymous" ) { anonymous = toBool(fieldValue); return TRUE; }
			break;
		case 'c':
			if ( fieldName % "constant" ) { constant = toBool(fieldValue); return TRUE; }
			break;
		case 'e':
			if ( fieldName % "encoding" ) { encoding = fieldValue; return TRUE; }
			break;
		case 'i':
			if ( fieldName % "indexed" ) { indexed = toBool(fieldValue); return TRUE; }
			if ( fieldName % "inputs" ) return TRUE;
			break;
		case 'n':
			if ( fieldName % "name" ) { name = fieldValue; return TRUE; }
			break;
		case 'o':
			if ( fieldName % "outputs" ) return TRUE;
			break;
		case 't':
			if ( fieldName % "type" ) { type = fieldValue; return TRUE; }
			break;
		default:
			break;
	}
	return FALSE;
}

//---------------------------------------------------------------------------------------------------
void CFunction::finishParse()
{
	// EXISTING_CODE
	for (int i=0;i<inputs.getCount();i++)
		hasAddrs |= (inputs[i].type == "address");
	// EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
void CFunction::Serialize(SFArchive& archive)
{
	if (!SerializeHeader(archive))
		return;

	if (archive.isReading())
	{
		archive >> name;
		archive >> type;
		archive >> indexed;
		archive >> anonymous;
		archive >> constant;
		archive >> encoding;
		archive >> inputs;
		archive >> outputs;
		finishParse();
	} else
	{
		archive << name;
		archive << type;
		archive << indexed;
		archive << anonymous;
		archive << constant;
		archive << encoding;
		archive << inputs;
		archive << outputs;

	}
}

//---------------------------------------------------------------------------
void CFunction::registerClass(void)
{
	static bool been_here=false;
	if (been_here) return;
	been_here=true;

	SFInt32 fieldNum=1000;
	ADD_FIELD(CFunction, "schema",  T_NUMBER|TS_LABEL, ++fieldNum);
	ADD_FIELD(CFunction, "deleted", T_RADIO|TS_LABEL,  ++fieldNum);
	ADD_FIELD(CFunction, "name", T_TEXT, ++fieldNum);
	ADD_FIELD(CFunction, "type", T_TEXT, ++fieldNum);
	ADD_FIELD(CFunction, "indexed", T_RADIO, ++fieldNum);
	ADD_FIELD(CFunction, "anonymous", T_RADIO, ++fieldNum);
	ADD_FIELD(CFunction, "constant", T_RADIO, ++fieldNum);
	ADD_FIELD(CFunction, "encoding", T_TEXT, ++fieldNum);
	ADD_FIELD(CFunction, "inputs", T_TEXT|TS_ARRAY, ++fieldNum);
	ADD_FIELD(CFunction, "outputs", T_TEXT|TS_ARRAY, ++fieldNum);

	// Hide our internal fields, user can turn them on if they like
	HIDE_FIELD(CFunction, "schema");
	HIDE_FIELD(CFunction, "deleted");

	// EXISTING_CODE
	HIDE_FIELD(CFunction, "indexed");
	HIDE_FIELD(CFunction, "anonymous");
	// EXISTING_CODE
}

//---------------------------------------------------------------------------
int sortFunction(const SFString& f1, const SFString& f2, const void *rr1, const void *rr2)
{
	CFunction *g1 = (CFunction*)rr1;
	CFunction *g2 = (CFunction*)rr2;

	SFString v1 = g1->getValueByName(f1);
	SFString v2 = g2->getValueByName(f1);
	SFInt32 s = v1.Compare(v2);
	if (s || f2.IsEmpty())
		return (int)s;

	v1 = g1->getValueByName(f2);
	v2 = g2->getValueByName(f2);
	return (int)v1.Compare(v2);
}
int sortFunctionByName(const void *rr1, const void *rr2) { return sortFunction("fu_Name", "", rr1, rr2); }
int sortFunctionByID  (const void *rr1, const void *rr2) { return sortFunction("functionID", "", rr1, rr2); }

//---------------------------------------------------------------------------
SFString nextFunctionChunk_custom(const SFString& fieldIn, SFBool& force, const void *data)
{
	return EMPTY;
}

//---------------------------------------------------------------------------
SFBool CFunction::handleCustomFormat(CExportContext& ctx, const SFString& fmtIn, void *data) const
{
	// EXISTING_CODE
	// EXISTING_CODE
	return FALSE;
}

//---------------------------------------------------------------------------
SFBool CFunction::readBackLevel(SFArchive& archive)
{
	SFBool done=FALSE;
	// EXISTING_CODE
	// EXISTING_CODE
	return done;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
void CFunction::parseParams(SFBool input, const SFString& contents)
{
	char *p = (char *)(const char*)contents;
	while (p && *p)
	{
		CParameter param;SFInt32 nFields=0;
		p = param.parseJson(p,nFields);
		if (nFields)
		{
			if (input)
				inputs[inputs.getCount()] = param;
			else
				outputs[outputs.getCount()] = param;
		}
	}
}
// EXISTING_CODE
