/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef _LINGUISTIC_LNGPROPHELP_HXX_
#define _LINGUISTIC_LNGPROPHELP_HXX_

#include <tools/solar.h>

#include <uno/lbnames.h>
#include <cppuhelper/implbase2.hxx>
#include <cppuhelper/interfacecontainer.h>
#include <com/sun/star/beans/XPropertyChangeListener.hpp>
#include <com/sun/star/beans/PropertyValues.hpp>

#include <com/sun/star/linguistic2/XLinguServiceEventBroadcaster.hpp>

namespace com { namespace sun { namespace star { namespace beans {
	class	XPropertySet;
}}}}

namespace com { namespace sun { namespace star { namespace linguistic2 {
	struct	LinguServiceEvent;
}}}}


namespace linguistic
{

///////////////////////////////////////////////////////////////////////////
// PropertyChgHelper
// Base class for all XPropertyChangeListener members of the
// various lingu services.


// Flags for type of events allowed to be launched
#define	AE_SPELLCHECKER	1
#define	AE_HYPHENATOR 	2
//#define	AE_THESAURUS	4

typedef cppu::WeakImplHelper2
<
    ::com::sun::star::beans::XPropertyChangeListener,
    ::com::sun::star::linguistic2::XLinguServiceEventBroadcaster
> PropertyChgHelperBase;

class PropertyChgHelper :
    public PropertyChgHelperBase
{
	::com::sun::star::uno::Sequence< ::rtl::OUString >  aPropNames;
	::com::sun::star::uno::Reference<
		::com::sun::star::uno::XInterface >				xMyEvtObj;
	::cppu::OInterfaceContainerHelper					aLngSvcEvtListeners;
	::com::sun::star::uno::Reference<
		::com::sun::star::beans::XPropertySet >			xPropSet;

	int		nEvtFlags;	// flags for event types allowed to be launched

	// default values
	sal_Bool	bIsIgnoreControlCharacters;
	sal_Bool	bIsUseDictionaryList;
	
	// return values, will be set to default value or current temporary value
	sal_Bool	bResIsIgnoreControlCharacters;
	sal_Bool	bResIsUseDictionaryList;
	
	
	// disallow use of copy-constructor and assignment-operator
	PropertyChgHelper( const PropertyChgHelper & );
	PropertyChgHelper & operator = ( const PropertyChgHelper & );

protected:
	virtual void	SetDefaultValues();
	virtual void	GetCurrentValues();
	
	::com::sun::star::uno::Sequence< ::rtl::OUString > &
			GetPropNames()	{ return aPropNames; }
	::com::sun::star::uno::Reference<
		::com::sun::star::beans::XPropertySet > &
			GetPropSet()	{ return xPropSet; }

	void	AddPropNames( const char *pNewNames[], sal_Int32 nCount );
	
	virtual sal_Bool	propertyChange_Impl( 
							const ::com::sun::star::beans::PropertyChangeEvent& rEvt );

public:
	PropertyChgHelper(
			const ::com::sun::star::uno::Reference<
				::com::sun::star::uno::XInterface > &rxSource,
			::com::sun::star::uno::Reference<
				::com::sun::star::beans::XPropertySet > &rxPropSet,
			int nAllowedEvents );
	virtual ~PropertyChgHelper();

	virtual void	SetTmpPropVals( const com::sun::star::beans::PropertyValues &rPropVals );
	
	// XEventListener
	virtual void SAL_CALL
		disposing( const ::com::sun::star::lang::EventObject& rSource )
			throw(::com::sun::star::uno::RuntimeException);

	// XPropertyChangeListener
	virtual void SAL_CALL
		propertyChange( const ::com::sun::star::beans::PropertyChangeEvent& rEvt )
			throw(::com::sun::star::uno::RuntimeException);

	// XLinguServiceEventBroadcaster
    virtual sal_Bool SAL_CALL
		addLinguServiceEventListener(
				const ::com::sun::star::uno::Reference<
					::com::sun::star::linguistic2::XLinguServiceEventListener >& rxListener )
			throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL
		removeLinguServiceEventListener(
				const ::com::sun::star::uno::Reference<
					::com::sun::star::linguistic2::XLinguServiceEventListener >& rxListener )
			throw(::com::sun::star::uno::RuntimeException);

	// non-UNO functions
	void 	AddAsPropListener();
	void	RemoveAsPropListener();
	void	LaunchEvent(
				const ::com::sun::star::linguistic2::LinguServiceEvent& rEvt );

	const ::com::sun::star::uno::Sequence< ::rtl::OUString > &
			GetPropNames() const	{ return aPropNames; }
	const ::com::sun::star::uno::Reference<
		::com::sun::star::beans::XPropertySet >	&
			GetPropSet() const		{ return xPropSet; }
	const ::com::sun::star::uno::Reference<
		::com::sun::star::uno::XInterface > &
			GetEvtObj() const		{ return xMyEvtObj; }

	sal_Bool	IsIgnoreControlCharacters() const	{ return bResIsIgnoreControlCharacters; }
	sal_Bool	IsUseDictionaryList() const			{ return bResIsUseDictionaryList; }
};


///////////////////////////////////////////////////////////////////////////

class PropertyHelper_Thes :
	public PropertyChgHelper
{
	// disallow use of copy-constructor and assignment-operator
	PropertyHelper_Thes( const PropertyHelper_Thes & );
	PropertyHelper_Thes & operator = ( const PropertyHelper_Thes & );

public:
	PropertyHelper_Thes(
			const ::com::sun::star::uno::Reference<
				::com::sun::star::uno::XInterface > &rxSource,
			::com::sun::star::uno::Reference<
				::com::sun::star::beans::XPropertySet > &rxPropSet );
	virtual ~PropertyHelper_Thes();
	
	// XPropertyChangeListener
	virtual void SAL_CALL
		propertyChange( const ::com::sun::star::beans::PropertyChangeEvent& rEvt )
			throw(::com::sun::star::uno::RuntimeException);
};

///////////////////////////////////////////////////////////////////////////

class PropertyHelper_Spell :
	public PropertyChgHelper
{
	// default values
	sal_Bool	bIsSpellUpperCase;
	sal_Bool	bIsSpellWithDigits;
	sal_Bool	bIsSpellCapitalization;

	// return values, will be set to default value or current temporary value
    sal_Int16   nResMaxNumberOfSuggestions; // special value that is not part of the property set and thus needs to be handled differently
	sal_Bool	bResIsSpellUpperCase;
	sal_Bool	bResIsSpellWithDigits;
	sal_Bool	bResIsSpellCapitalization;


	// disallow use of copy-constructor and assignment-operator
	PropertyHelper_Spell( const PropertyHelper_Spell & );
	PropertyHelper_Spell & operator = ( const PropertyHelper_Spell & );

protected:
	// PropertyChgHelper
	virtual void	SetDefaultValues();
	virtual void	GetCurrentValues();
	virtual sal_Bool	propertyChange_Impl( 
							const ::com::sun::star::beans::PropertyChangeEvent& rEvt );

public:
	PropertyHelper_Spell(
			const ::com::sun::star::uno::Reference<
				::com::sun::star::uno::XInterface > &rxSource,
			::com::sun::star::uno::Reference<
				::com::sun::star::beans::XPropertySet > &rxPropSet );
	virtual ~PropertyHelper_Spell();

	virtual void	SetTmpPropVals( const com::sun::star::beans::PropertyValues &rPropVals );

	// XPropertyChangeListener
	virtual void SAL_CALL
		propertyChange( const ::com::sun::star::beans::PropertyChangeEvent& rEvt )
			throw(::com::sun::star::uno::RuntimeException);

    virtual sal_Int16   GetDefaultNumberOfSuggestions() const;

    sal_Int16   GetMaxNumberOfSuggestions() const   { return nResMaxNumberOfSuggestions; }
	sal_Bool	IsSpellUpperCase() const			{ return bResIsSpellUpperCase; }
	sal_Bool	IsSpellWithDigits() const			{ return bResIsSpellWithDigits; }
	sal_Bool	IsSpellCapitalization() const		{ return bResIsSpellCapitalization; }
};

///////////////////////////////////////////////////////////////////////////

class PropertyHelper_Hyphen :
	public PropertyChgHelper
{
	// default values
	sal_Int16	nHyphMinLeading,
			nHyphMinTrailing,
			nHyphMinWordLength;

	// return values, will be set to default value or current temporary value
	sal_Int16	nResHyphMinLeading,
			nResHyphMinTrailing,
			nResHyphMinWordLength;

	// disallow use of copy-constructor and assignment-operator
    PropertyHelper_Hyphen( const PropertyHelper_Hyphen & );
    PropertyHelper_Hyphen & operator = ( const PropertyHelper_Hyphen & );

protected:
	// PropertyChgHelper
	virtual void	SetDefaultValues();
	virtual void	GetCurrentValues();
	virtual sal_Bool	propertyChange_Impl( 
							const ::com::sun::star::beans::PropertyChangeEvent& rEvt );

public:
    PropertyHelper_Hyphen(
			const ::com::sun::star::uno::Reference<
				::com::sun::star::uno::XInterface > &rxSource,
			::com::sun::star::uno::Reference<
				::com::sun::star::beans::XPropertySet > &rxPropSet);
    virtual ~PropertyHelper_Hyphen();

	virtual void	SetTmpPropVals( const com::sun::star::beans::PropertyValues &rPropVals );

	// XPropertyChangeListener
	virtual void SAL_CALL
		propertyChange( const ::com::sun::star::beans::PropertyChangeEvent& rEvt )
			throw(::com::sun::star::uno::RuntimeException);

	sal_Int16	GetMinLeading() const				{ return nResHyphMinLeading; }
	sal_Int16	GetMinTrailing() const				{ return nResHyphMinTrailing; }
	sal_Int16	GetMinWordLength() const			{ return nResHyphMinWordLength; }
};

///////////////////////////////////////////////////////////////////////////

}   // namespace linguistic

#endif

