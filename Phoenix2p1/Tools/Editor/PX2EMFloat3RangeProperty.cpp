/*
*
* �ļ�����	��	PX2EMFloat3RangeProperty.cpp
*
*/

#include "PX2EMFloat3RangeProperty.hpp"
#include "PX2PropertyPage.hpp"
#include "wxPropertyExtend.hpp"
using namespace PX2Editor;
using namespace PX2;

EMFloat3RangeProperty::EMFloat3RangeProperty (PropertyPage *parent,
	std::string name, InterpCurvePointFloat3 *pointMin,
	InterpCurvePointFloat3 *pointMax, bool isForInit)
	:
Property(parent, name, Property::PT_EMFLOAT3RANGE, 0),
	mPropertyInValMax(0),
	mPropertyOutValMax(0),
	mPropertyArriveTangentMax(0),
	mPropertyLeaveTangentMax(0),
	mInterpModeMax(0),
	mPropertyInValMin(0),
	mPropertyOutValMin(0),
	mPropertyArriveTangentMin(0),
	mPropertyLeaveTangentMin(0),
	mInterpModeMin(0),
	mPointMin(pointMin),
	mPointMax(pointMax),
	mIsForInit(isForInit)
{
	mProperty = parent->mPage->Append(new wxStringProperty(
		name, name, wxT("<composed>")) );

	// max
	wxPGProperty *propMax = parent->mPage->AppendIn(mProperty,
		new wxStringProperty(wxT("Max"), wxT("Max"), wxT("<composed>")) );

	if (!mIsForInit)
	{
		mPropertyInValMax = parent->mPage->AppendIn(propMax,
			new wxFloatProperty(wxT("InVal"), wxT("InVal"),
			double(mPointMax->InVal)) );

		mPropertyOutValMax = parent->mPage->AppendIn(propMax,
			new wxFloat3Property(wxT("OutVal"), wxT("OutVal"), 
			mPointMax->OutVal) );

		mPropertyArriveTangentMax = parent->mPage->AppendIn(propMax,
			new wxFloat3Property(wxT("ArriveTangent"), wxT("ArriveTangent"),
			mPointMax->ArriveTangent) );

		mPropertyLeaveTangentMax = parent->mPage->AppendIn(propMax,
			new wxFloat3Property(wxT("OutTangent"), wxT("OutTangent"), 
			mPointMax->LeaveTangent) );

		wxArrayString labels;
		labels.push_back(ICMToString(ICM_LINEAR));
		labels.push_back(ICMToString(ICM_CONSTANT));
		labels.push_back(ICMToString(ICM_CURVE_AUTO));
		labels.push_back(ICMToString(ICM_CURVE_AUTOCLAMPED));
		labels.push_back(ICMToString(ICM_CURVE_USER));
		labels.push_back(ICMToString(ICM_CURVE_BREAK));
		wxArrayInt arrayInt;
		arrayInt.push_back(ICM_LINEAR);
		arrayInt.push_back(ICM_CONSTANT);
		arrayInt.push_back(ICM_CURVE_AUTO);
		arrayInt.push_back(ICM_CURVE_AUTOCLAMPED);
		arrayInt.push_back(ICM_CURVE_USER);
		arrayInt.push_back(ICM_CURVE_BREAK);
		mInterpModeMax = parent->mPage->AppendIn(propMax, 
			new wxEnumProperty(wxT("InterpMode"), wxT("InterpMode"), labels, 
			arrayInt, (int)(mPointMax->InterpMode)));
	}
	else
	{
		mPropertyOutValMax = parent->mPage->AppendIn(propMax,
			new wxFloat3Property(wxT("OutVal"), wxT("OutVal"), 
			mPointMax->OutVal) );
	}

	// min
	wxPGProperty *propMin = parent->mPage->AppendIn(mProperty,
		new wxStringProperty(wxT("Min"), wxT("Min"), wxT("<composed>")) );

	if (!mIsForInit)
	{
		mPropertyInValMin = parent->mPage->AppendIn(propMin,
			new wxFloatProperty(wxT("InVal"), wxT("InVal"),
			double(mPointMin->InVal)) );

		mPropertyOutValMin = parent->mPage->AppendIn(propMin,
			new wxFloat3Property(wxT("OutVal"), wxT("OutVal"), 
			mPointMin->OutVal) );

		mPropertyArriveTangentMin = parent->mPage->AppendIn(propMin,
			new wxFloat3Property(wxT("ArriveTangent"), wxT("ArriveTangent"),
			mPointMin->ArriveTangent) );

		mPropertyLeaveTangentMin = parent->mPage->AppendIn(propMin,
			new wxFloat3Property(wxT("OutTangent"), wxT("OutTangent"), 
			mPointMin->LeaveTangent) );

		wxArrayString labels;
		labels.push_back(ICMToString(ICM_LINEAR));
		labels.push_back(ICMToString(ICM_CONSTANT));
		labels.push_back(ICMToString(ICM_CURVE_AUTO));
		labels.push_back(ICMToString(ICM_CURVE_AUTOCLAMPED));
		labels.push_back(ICMToString(ICM_CURVE_USER));
		labels.push_back(ICMToString(ICM_CURVE_BREAK));
		wxArrayInt arrayInt;
		arrayInt.push_back(ICM_LINEAR);
		arrayInt.push_back(ICM_CONSTANT);
		arrayInt.push_back(ICM_CURVE_AUTO);
		arrayInt.push_back(ICM_CURVE_AUTOCLAMPED);
		arrayInt.push_back(ICM_CURVE_USER);
		arrayInt.push_back(ICM_CURVE_BREAK);
		mInterpModeMin = parent->mPage->AppendIn(propMin, 
			new wxEnumProperty(wxT("InterpMode"), wxT("InterpMode"), labels, 
			arrayInt, (int)(mPointMin->InterpMode)));
	}
	else
	{
		mPropertyOutValMin = parent->mPage->AppendIn(propMin,
			new wxFloat3Property(wxT("OutVal"), wxT("OutVal"), 
			mPointMin->OutVal) );
	}
}
//-----------------------------------------------------------------------------
EMFloat3RangeProperty::~EMFloat3RangeProperty ()
{
}
//-----------------------------------------------------------------------------
void EMFloat3RangeProperty::OnChange (wxPropertyGridEvent &event)
{
	wxPGProperty *prop = event.GetProperty();
	const wxString &wxName = event.GetPropertyName();
	wxVariant var = prop->GetValue();

	if (var.IsNull())
		return;

	if (mPropertyInValMax == prop || mPropertyInValMin == prop)
	{
		float fValue = (float)(var.GetDouble());

		mPointMax->InVal = fValue;
		mPointMin->InVal = fValue;

		if (mPropertyInValMax)
			mPropertyInValMax->SetValue(fValue);

		if (mPropertyInValMin)
			mPropertyInValMin->SetValue(fValue);
	}
	else if (mPropertyOutValMax == prop)
	{
		mPointMax->OutVal = Float3RefFromVariant(var);
	}
	else if (mPropertyArriveTangentMax == prop)
	{
		mPointMax->ArriveTangent = Float3RefFromVariant(var);
	}
	else if (mPropertyLeaveTangentMax == prop)
	{
		mPointMax->LeaveTangent = Float3RefFromVariant(var);
	}
	else if (mInterpModeMax == prop)
	{
		int val = var.GetInteger();
		mPointMax->InterpMode = (InterpCurveMode)val;
	}

	else if (mPropertyOutValMin == prop)
	{
		mPointMin->OutVal = Float3RefFromVariant(var);
	}
	else if (mPropertyArriveTangentMin == prop)
	{
		mPointMin->ArriveTangent = Float3RefFromVariant(var);
	}
	else if (mPropertyLeaveTangentMin == prop)
	{
		mPointMin->LeaveTangent = Float3RefFromVariant(var);
	}
	else if (mInterpModeMin == prop)
	{
		int val = var.GetInteger();
		mPointMin->InterpMode = (InterpCurveMode)val;
	}
}
//-----------------------------------------------------------------------------
void EMFloat3RangeProperty::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void EMFloat3RangeProperty::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void EMFloat3RangeProperty::DoLeave ()
{
}
//-----------------------------------------------------------------------------